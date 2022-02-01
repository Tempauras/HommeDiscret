// Fill out your copyright notice in the Description page of Project Settings.


#include "Foe.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "HommeDiscret/Level/Props/Food.h"
#include "HommeDiscret/Level/Props/FoodSpot.h"
#include "AIC_Foe.h"

// Sets default values
AFoe::AFoe()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//HaveToDroppedFood = false;
	IsHoldingFood = false;
	AIControllerClass = AAIC_Foe::StaticClass();
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(CollisionSphereRadius);
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionCylinder = Cast<UCapsuleComponent>(GetComponentByClass(UCapsuleComponent::StaticClass()));

	FoodMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("FoodMesh"));
	FoodMesh->SetSimulatePhysics(false);
	FoodMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
}
// Called when the game starts or when spawned
void AFoe::BeginPlay()
{
	Super::BeginPlay();
	if (GetMesh()->DoesSocketExist("FoodSocket"))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Exist!"));
		FoodMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("FoodSocket"));
		FoodMesh->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));
		//SetupSphereTrace();
	}
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AFoe::CallbackComponentBeginOverlap);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AFoe::CallbackComponentEndOverlap);
}

void AFoe::CallbackComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AFood::StaticClass()))
	{
		if (!IsHoldingFood)
		{
			AFood* NewFood = Cast<AFood>(OtherActor);
			if (NewFood != nullptr)
			{
				FoodRef = NewFood;
			}
		}
	}
	else if (OtherActor->IsA(AFoodSpot::StaticClass()))
	{

	}
}

void AFoe::CallbackComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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

	}
}

void AFoe::SetAreInteracting(bool NewInteract)
{
	AreInteracing = NewInteract;
}

void AFoe::PickUpFood()
{
	if (FoodRef != nullptr)
	{
		FoodRef->Hide();
		IsHoldingFood = true;
		FoodMesh->SetStaticMesh(FoodRef->StaticMesh->GetStaticMesh());
	}
}

void AFoe::DropFood()
{
	FoodRef->Show(this->GetActorLocation(),this->GetActorForwardVector());
	FoodRef=nullptr;
	IsHoldingFood = false;
	FoodMesh->SetStaticMesh(nullptr);
}

bool AFoe::GetHaveToDroppedFood()
{
	return HaveToDroppedFood;
}

bool AFoe::GetHoldingFood()
{
	return IsHoldingFood;
}

// Called every frame
void AFoe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFoe::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

