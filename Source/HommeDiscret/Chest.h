// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Food.h"
#include "Chest.generated.h"

UCLASS()
class HOMMEDISCRET_API AChest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChest();

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		UStaticMeshComponent* BaseStaticMesh;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		UStaticMeshComponent* TopStaticMesh;

	UPROPERTY(VisibleAnywhere)
		USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere)
		int NumberFoodsContained;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AddingFood(AFood* FoodToAdd);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void CallbackComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
