// Fill out your copyright notice in the Description page of Project Settings.


#include "Foe.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "HommeDiscret/Level/Props/Food.h"
#include "HommeDiscret/Level/Props/FoodSpot.h"
#include "HommeDiscret/Tools/GameMode/StealthGameMode.h"
#include "AIC_Foe.h"
#include "FoeSpawner.h"

// Sets default values
AFoe::AFoe()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//HaveToDroppedFood = false;
	AIControllerClass = AAIC_Foe::StaticClass();
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	CharacMov = GetCharacterMovement();

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(CollisionSphereRadius);
	CollisionSphere->SetupAttachment(RootComponent);

	FoodMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("FoodMesh"));
	FoodMesh->SetSimulatePhysics(false);
	FoodMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	FoeSpeed = CharacMov->MaxWalkSpeed;
	FoodRef = nullptr;
	FoodSpotNearby = nullptr;
	HaveToDroppedFood = false;
	IsHoldingFood = false;
	GameMode = Cast<AStealthGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
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
	CurrentWorld=GetWorld();
	SpawnLocation = FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z - 300.0f);
	SpawnRotation = this->GetActorRotation();
	//InstantiateFood();
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
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Food is near %s"), *NewFood->GetName()));
				FoodRef = NewFood;
			}
		}
	}
	else if (OtherActor->IsA(AFoodSpot::StaticClass()))
	{
		if (IsHoldingFood)
		{
			AFoodSpot* NewFoodSpot = Cast<AFoodSpot>(OtherActor);
			if (NewFoodSpot->FoodRef == nullptr)
			{
				FoodSpotNearby = NewFoodSpot;
			}
		}
	}
	else if (OtherActor->IsA(AFoeSpawner::StaticClass()))
	{
		Destroy();
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Collides with %s"), OtherActor->GetName()));
		//GameMode->RemoveFoeInRoom();
	}
}

void AFoe::CallbackComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AFood::StaticClass()))
	{
		if (!IsHoldingFood)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Food is not here"));
			FoodRef = nullptr;
		}
	}
	else if (OtherActor->IsA(AFoodSpot::StaticClass()))
	{
		FoodSpotNearby = nullptr;
		/*if (IsHoldingFood)
		{
			FoodSpotNearby = nullptr;
		}*/
	}
}

bool AFoe::PickUpFood()
{
	bool Return = false;
	if (FoodRef != nullptr)
	{
		IsHoldingFood = true;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Foe PickUp %s"),*FoodRef->GetName()));
		FoodMesh->SetStaticMesh(FoodRef->StaticMesh->GetStaticMesh());
		FoodRef->Hide();
		Return = true;
		CharacMov->MaxWalkSpeed = FoeSpeed / 2;
	}
	return Return;
}

FVector AFoe::DropFoodOnTheFloor()
{
	FVector NewVector = FVector(0, 0, 0);
	if (FoodRef != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Foe Drops %s"), *FoodRef->GetName()));
		FoodRef->Show(this->GetActorLocation(), this->GetActorForwardVector());
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Test foodRef %s"), *FoodRef->GetName()));
		NewVector = FoodRef->GetRealLocation();
		FoodRef = nullptr;
		IsHoldingFood = false;
		FoodMesh->SetStaticMesh(nullptr);
		CharacMov->MaxWalkSpeed = FoeSpeed;
	}
	return NewVector;
}

bool AFoe::DropFoodInFoodSpot()
{
	bool Return = false;
	if (FoodSpotNearby != nullptr)
	{
		if (FoodRef != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("FoodRef %s"), *FoodRef->GetName()));
			bool Success = FoodSpotNearby->FillFoodSpot(FoodRef);
			if (Success == true)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Foe have filled the spot with  %s"), *FoodRef->GetName()));
				IsHoldingFood = false;
				FoodMesh->SetStaticMesh(nullptr);
				FoodRef = nullptr;
				Return = true;
				CharacMov->MaxWalkSpeed = FoeSpeed;

			}
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Foe have filled the spot with  %d"), Return));
	return Return;
}

void AFoe::InstantiateFood()
{
	if (FoodClass != nullptr)
	{
		if (!IsHoldingFood)
		{
			AActor* Actor = CurrentWorld->SpawnActor(FoodClass, &SpawnLocation, &SpawnRotation, SpawnInfo);
			if (Actor != nullptr)
			{
				AFood* NewFood = Cast<AFood>(Actor);
				if (NewFood != nullptr)
				{
					FoodRef = NewFood;
					//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Foe Wants to Pick Up  %s"), *FoodRef->GetName()));
					PickUpFood();
					HaveToDroppedFood = true;

				}
			}
		}
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("FoodClass is not defined"));
	}
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

