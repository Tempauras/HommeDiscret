// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodSpot.h"
#include "Food.h"
// Sets default values
AFoodSpot::AFoodSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	RootComponent = StaticMesh;

	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Plate Mesh"));
	PlateMesh->SetupAttachment(RootComponent);

	FoodMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Food Mesh"));
	FoodMesh->SetupAttachment(PlateMesh);
	FoodMesh->SetRelativeLocation(PlateMesh->GetRelativeLocation());

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(FName("Collision Sphere"));
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->SetSphereRadius(CollisionSphereRadius);
}

// Called when the game starts or when spawned
void AFoodSpot::BeginPlay()
{
	Super::BeginPlay();
	CurrentWorld = GetWorld();
	SpawnLocation = FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z - 150.0f);
    SpawnRotation = this->GetActorRotation();
	if (FoodClass != nullptr)
	{
		InstantiateFoodSpot();
	}

}

void AFoodSpot::FillFoodSpot(AFood* NewFood)
{
	NewFood->StaticMesh->SetSimulatePhysics(false);
	FoodMesh->SetStaticMesh(NewFood->StaticMesh->GetStaticMesh());
	FoodRef = NewFood;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Fill %s"),*FoodRef->GetName()));
}

void AFoodSpot::EmptyFoodSpot()
{
	FoodMesh->SetStaticMesh(nullptr);
	FoodRef = nullptr;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,TEXT("Empty"));

}

void AFoodSpot::InstantiateFoodSpot()
{
	AActor* Actor = CurrentWorld->SpawnActor(FoodClass, &SpawnLocation, &SpawnRotation, SpawnInfo);
	AFood* FoodActor = Cast<AFood>(Actor);
	FillFoodSpot(FoodActor);
	/*FoodActor->StaticMesh->SetSimulatePhysics(false);
	FoodMesh->SetStaticMesh(FoodActor->StaticMesh->GetStaticMesh());
	FoodRef = FoodActor;*/
}

// Called every frame
void AFoodSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

