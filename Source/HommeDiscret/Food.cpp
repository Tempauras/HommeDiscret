// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "GameFramework/Character.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	RootComponent = StaticMesh;
	
	ColliderBox = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collider Box"));
	ColliderBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	ColliderBox->OnComponentBeginOverlap.AddDynamic(this, &AFood::CallbackComponentBeginOverlap);
	ColliderBox->OnComponentEndOverlap.AddDynamic(this, &AFood::CallbackComponentEndOverlap);
}

void AFood::CallbackComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Overlap"));
	ACharacter* Player = Cast<ACharacter>(OtherActor);
	if (Player != nullptr)
	{
		bIsAblePickup = true;
	}
}

void AFood::CallbackComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsAblePickup = false;
}

