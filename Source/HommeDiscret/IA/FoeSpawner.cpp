// Fill out your copyright notice in the Description page of Project Settings.


#include "FoeSpawner.h"
#include "Foe.h"
#include "Components/SphereComponent.h"

// Sets default values
AFoeSpawner::AFoeSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(CollisionSphereRadius);
	//CollisionSphere->SetupAttachment(RootComponent);
	RootComponent = CollisionSphere;
}

// Called when the game starts or when spawned
void AFoeSpawner::BeginPlay()
{
	Super::BeginPlay();
	Loc = FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z);
	//Loc.X = Loc.X + 200.0f;
	Rot = this->GetActorRotation();
	//SpawnFoe(true);
	//SpawnFoe(false);
}

bool AFoeSpawner::SpawnFoe(bool HaveFood)
{
	bool Result = false;
	if (ActorToSpawn != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		AActor* SpawnedActorRef = GetWorld()->SpawnActor<AFoe>(ActorToSpawn, Loc, Rot, SpawnParams);
		if (SpawnedActorRef != nullptr)
		{
			AFoe* NewFoe = Cast<AFoe>(SpawnedActorRef);
			if (NewFoe != nullptr)
			{
				if (HaveFood)
				{
					GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, TEXT("Foe with food spawned"));
					NewFoe->InstantiateFood();
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, TEXT("Foe spawned"));
				}
				Result = true;
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, TEXT("No Foe spawned : Cast doesn't work"));
			}
		}
		else 
		{
			GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, TEXT("No Foe spawned : SpawnActor doesn't work"));
		}
	}
	return Result;
}

// Called every frame
void AFoeSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

