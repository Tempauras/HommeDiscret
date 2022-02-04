// Fill out your copyright notice in the Description page of Project Settings.


#include "FoeSpawner.h"
#include "Foe.h"

// Sets default values
AFoeSpawner::AFoeSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFoeSpawner::BeginPlay()
{
	Super::BeginPlay();
	Loc = this->GetActorLocation();
	Rot = this->GetActorRotation();
	SpawnFoe(true);
	//SpawnFoe(false);

}

void AFoeSpawner::SpawnFoe(bool HaveFood)
{
	if (ActorToSpawn != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		AActor* SpawnedActorRef = GetWorld()->SpawnActor<AFoe>(ActorToSpawn, Loc, Rot, SpawnParams);
		AFoe* NewFoe = Cast<AFoe>(SpawnedActorRef);
		if (HaveFood)
		{
			NewFoe->InstantiateFood();
		}
	}
}

// Called every frame
void AFoeSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

