// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "GameFramework/Character.h"
#include "Hero.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	RootComponent = StaticMesh;
	
	SphereCollider = CreateDefaultSubobject<USphereComponent>(FName("SphereCollider"));
	SphereCollider->SetupAttachment(RootComponent);
	SphereCollider->InitSphereRadius(60.0f);
	StaticMesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AFood::CallbackComponentBeginOverlap);
	SphereCollider->OnComponentEndOverlap.AddDynamic(this, &AFood::CallbackComponentEndOverlap);
}

void AFood::CallbackComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHero* Hero = Cast<AHero>(OtherActor);
	if (Hero != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Overlap"));
		if (Hero->FoodRef == nullptr)
		{
			Hero->FoodRef = this;
		}
	}
}

void AFood::CallbackComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHero* Hero = Cast<AHero>(OtherActor);
	if (Hero != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Overlap"));
		if (Hero->HoldingFood==false)
		{
			Hero->FoodRef = nullptr;
		}
	}
}

