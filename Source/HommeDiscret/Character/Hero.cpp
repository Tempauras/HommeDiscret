// Fill out your copyright notice in the Description page of Project Settings.


#include "Hero.h"
#include "HommeDiscret/Level/Props/Food.h"
#include "HommeDiscret/Level/Props/FoodSpot.h"
#include "HommeDiscret/IA/Foe.h"
#include "HommeDiscret/Level/Props/Chest.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

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

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(CollisionSphereRadius);
	CollisionSphere->SetupAttachment(RootComponent);
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

	FoodSpotNearby = nullptr;
	FoodRef = nullptr;
	IsHoldingFood = false;
	ChestNearby = nullptr;
	bDead = false;
	HeroSpeed = 200;

	SetupStimulus();
}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();
	if (GetMesh()->DoesSocketExist("FoodSocket"))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Exist!"));
		FoodMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("FoodSocket"));
		FoodMesh->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));
		//SetupSphereTrace();
	}
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHero::CallbackComponentBeginOverlap);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AHero::CallbackComponentEndOverlap);
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
	/*
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);*/

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AHero::Interact);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHero::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHero::MoveRight);

	PlayerInputComponent->BindAxis("Zoom", this, &AHero::Zoom);
}

void AHero::CallbackComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Overlap %s"),*OtherActor->GetName()));
	if (OtherActor->IsA(AFood::StaticClass()))
	{
		if (!IsHoldingFood)
		{
			FoodRef = Cast<AFood>(OtherActor);
		}
	}
	else if (OtherActor->IsA(AFoodSpot::StaticClass()))
	{
		AFoodSpot* FoodSpot = Cast<AFoodSpot>(OtherActor);
		if (!IsHoldingFood)
		{
			if (FoodSpot->FoodRef != nullptr)
			{
				FoodSpotNearby = FoodSpot;
				AFood* FoodSpotFood = Cast<AFood>(FoodSpot->FoodRef);
				if(FoodSpotFood!=nullptr)
				{
					FoodRef = FoodSpotFood;
				}
			}
		}
		else
		{
			if (FoodSpot->FoodRef == nullptr)
			{
				FoodSpotNearby = FoodSpot;
			}
		}

	}
	else if (OtherActor->IsA(AChest::StaticClass()))
	{
		if (IsHoldingFood)
		{
			AChest* Chest = Cast<AChest>(OtherActor);
			ChestNearby = Chest;
		}
	}
}

void AHero::CallbackComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AFood::StaticClass()))
	{
		if (!IsHoldingFood)
		{
			FoodRef = nullptr;
		}

	}
	else if (OtherActor->IsA(AFoodSpot::StaticClass()))
	{
		//AFoodSpot* FoodSpot = Cast<AFoodSpot>(OtherActor);
		FoodSpotNearby = nullptr;
		if (!IsHoldingFood)
		{
			FoodRef = nullptr;
		}
	}
	else if (OtherActor->IsA(AChest::StaticClass()))
	{
		ChestNearby = nullptr;
		/*
		if (IsHoldingFood)
		{
			ChestNearby = nullptr;
		}*/
	}
}

void AHero::SetupStimulus()
{
	Stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("stimulus"));
	Stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	Stimulus->RegisterWithPerceptionSystem();
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
	
	if (ChestNearby==nullptr && FoodSpotNearby==nullptr)
	{
		/*
		FVector newPos = FVector(this->GetActorLocation() + this->GetActorForwardVector() * 100.0f);
		newPos.Z = 170.0f;
		FoodRef->SetActorLocation(newPos);
		FoodRef->SetActorRotation(FQuat(0.0f, 0.0f, 0.0f, 0.0f));*/
		FoodRef->Show(this->GetActorLocation(), this->GetActorForwardVector());
	}
	else if (FoodSpotNearby != nullptr && ChestNearby == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Player Wants to drop in fs this : %s"), *FoodRef->GetName()));
		FoodSpotNearby->FillFoodSpot(FoodRef);
	}
	else if(FoodSpotNearby == nullptr && ChestNearby != nullptr)
	{
		ChestNearby->AddingFood();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Player Wants to drop in chest this : %s"), *FoodRef->GetName()));
		FoodRef->Destroy();
	}
	FoodRef = nullptr;
	IsHoldingFood = false;
	FoodMesh->SetStaticMesh(nullptr);
}


void AHero::PickUpObject(AFood* NewFood)
{
	if (FoodSpotNearby == nullptr)
	{
		NewFood->Hide();
		//IsHoldingFood = true;
		/*NewFood->StaticMesh->SetSimulatePhysics(false);
		NewFood->SetActorLocation(FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z - 150.0f));*/
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Player Wants to take in fs this : %s"), *FoodRef->GetName()));
		FoodSpotNearby->EmptyFoodSpot();
	}
	FoodRef = NewFood;
	IsHoldingFood = true;
	FoodMesh->SetStaticMesh(NewFood->StaticMesh->GetStaticMesh());
}


void AHero::Interact()
{
	
	if (FoodRef != nullptr)
	{
		if (!IsHoldingFood)
		{
			PickUpObject(FoodRef);
		}
		else
		{
			DropObject();
		}
	}
}