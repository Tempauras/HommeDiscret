// Fill out your copyright notice in the Description page of Project Settings.


#include "Hero.h"
#include "Food.h"
#include "Components/WidgetComponent.h"
#include "HommeDiscret/HungerBar.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"

// Sets default values
AHero::AHero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	FoodMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("FoodMesh"));
	FoodMesh->SetSimulatePhysics(false);
	FoodMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	FoodRef = nullptr;
	HoldingFood = false;
	bDead = false;

	//setup_stimulus();
}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();
	if (GetMesh()->DoesSocketExist("FoodSocket"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Exist!"));
		FoodMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("FoodSocket"));
		FoodMesh->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));
	}
}

// Called every frame
void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AHero::Interact);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHero::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHero::MoveRight);

	PlayerInputComponent->BindAxis("Zoom", this, &AHero::Zoom);
}


void AHero::setup_stimulus()
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("stimulus"));
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	stimulus->RegisterWithPerceptionSystem();

}

void AHero::MoveForward(float Axis)
{
	if (!bDead)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void AHero::MoveRight(float Axis)
{
	if (!bDead)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

void AHero::Zoom(float value)
{
	if (value)
	{
		float temp = CameraBoom->TargetArmLength + (value * -10);
		if (temp < 810 && temp > 100)
		{
			CameraBoom->TargetArmLength = temp;
		}
	}
}

void AHero::DropObject()
{
	FoodMesh->SetStaticMesh(nullptr);
	FVector newPos =  FVector(this->GetActorLocation() + this->GetActorForwardVector()*100.0f);
	newPos.Z = 170.0f;
	FoodRef->SetActorLocation(newPos);
	FoodRef->SetActorRotation(FQuat(0.0f, 0.0f, 0.0f,0.0f));
	//FoodRef->StaticMesh->SetSimulatePhysics(true);
	FoodRef = nullptr;
	HoldingFood = false;

}

void AHero::PickUpObject(AFood* newFood)
{
	HoldingFood = true;
	newFood->StaticMesh->SetSimulatePhysics(false);
	FoodMesh->SetStaticMesh(newFood->StaticMesh->GetStaticMesh());
	newFood->SetActorLocation(FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z-150.0f));
}

void AHero::Interact()
{
	if (FoodRef != nullptr)
	{
		if (!HoldingFood)
		{
			PickUpObject(FoodRef);
		}
		else
		{
			DropObject();
		}
	}


	/*if (FoodRef == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("WantsToInteract"));
		AreInteracting = true;
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AHero::DontInteract, 1.0f, false,0.5f);
	}
	else {
		DropObject();
	}*/
	/*
	TArray<AActor*> OverlappedActors;
	this->GetOverlappingActors(OverlappedActors);
	for(AActor* OverlappedActor : OverlappedActors)
	{
		AFood* Food = Cast<AFood>(OverlappedActor);
		if (Food != nullptr)
		{
			if (Food->bIsAblePickup)
			{
				UE_LOG(LogTemp, Warning, TEXT("Interacting with food!"));
				FoodMesh->SetStaticMesh(Food->StaticMesh->GetStaticMesh());
				Food->Destroy();
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Interacting!"));
		}
	}
	OverlappedActors.Empty();*/
}
