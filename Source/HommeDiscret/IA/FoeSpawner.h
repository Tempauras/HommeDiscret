// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FoeSpawner.generated.h"

class USphereComponent;
UCLASS()
class HOMMEDISCRET_API AFoeSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoeSpawner();

	UPROPERTY(VisibleAnywhere)
		USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere)
		float CollisionSphereRadius=10.0f;

private:

	UPROPERTY(VisibleAnywhere)
		FVector Loc;
	UPROPERTY(VisibleAnywhere)
		FRotator Rot;

protected:
	UPROPERTY(EditAnywhere)
		UClass* ActorToSpawn;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool SpawnFoe(bool HaveFood);
};
