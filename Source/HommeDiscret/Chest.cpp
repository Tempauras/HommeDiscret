// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"

// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//GlobalStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Global Static Mesh"));
	BaseStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base StaticMesh"));
	TopStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top StaticMesh"));
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT(" Sphere collision"));

	//GlobalStaticMesh->SetupAttachment(RootComponent);
	BaseStaticMesh->SetupAttachment(RootComponent);
	TopStaticMesh->SetupAttachment(BaseStaticMesh);
	CapsuleCollision->SetupAttachment(RootComponent);
	CapsuleCollision->InitCapsuleSize(80.0f,80.0f);
	NumberFoodsContained = 0;
}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();
	CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &AChest::CallbackComponentBeginOverlap);
}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChest::AddingFood(AFood* FoodToAdd)
{
	NumberFoodsContained++;
	FoodToAdd->Destroy();
	if (NumberFoodsContained >= 5)
	{
		//Win Call GameMode
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("You won !"));
	}
}

void AChest::CallbackComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Overlap"));
	AFood* Food = Cast<AFood>(OtherActor);
	if (Food != nullptr)
	{
		AddingFood(Food);
	}
}

