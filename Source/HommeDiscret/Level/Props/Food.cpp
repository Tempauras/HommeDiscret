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
	
	SphereCollider = CreateDefaultSubobject<USphereComponent>(FName("SphereCollider"));
	SphereCollider->SetupAttachment(RootComponent);
	SphereCollider->InitSphereRadius(60.0f);
	StaticMesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	/*SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AFood::CallbackComponentBeginOverlap);
	SphereCollider->OnComponentEndOverlap.AddDynamic(this, &AFood::CallbackComponentEndOverlap);*/
}

void AFood::Hide()
{
	this->StaticMesh->SetSimulatePhysics(false);
	this->SetActorLocation(FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z - UnderFloorPosition));
}

void AFood::Show(FVector DropActorPos, FVector DropActorForward)
{
	FVector newPos = FVector(DropActorPos + DropActorForward * InFrontPosition);
	newPos.Z = UnderFloorPosition;
	this->SetActorLocation(newPos);
	this->SetActorRotation(FQuat(0.0f, 0.0f, 0.0f, 0.0f));
}

/*
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
}*/

/*
void AFood::CallbackComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
	AHero* Hero = Cast<AHero>(OtherActor);
	if (Hero != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Overlap"));
		if (Hero->IsHoldingFood == false)
		{
			Hero->FoodRef = nullptr;
		}
	}
}*/
