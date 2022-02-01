// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Foe.generated.h"

class AFood;
class UCapsuleComponent;
class USphereComponent;
UCLASS()
class HOMMEDISCRET_API AFoe : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFoe();

protected:


	UPROPERTY(VisibleAnywhere)
		USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* CollisionCylinder;

	UPROPERTY(VisibleAnywhere)
		float CollisionSphereRadius = 200.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Food")
		UStaticMeshComponent* FoodMesh;

	UPROPERTY(VisibleAnywhere)
		UWorld* CurrentWorld;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> FoodClass;

	FActorSpawnParameters SpawnInfo;
	FVector SpawnLocation;
	FRotator SpawnRotation;

	UPROPERTY(VisibleAnywhere)
		bool HaveToDroppedFood;

	UPROPERTY(VisibleAnywhere)
		bool AreInteracing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool IsHoldingFood;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AFood* FoodRef;


	UFUNCTION()
		void CallbackComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void CallbackComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetAreInteracting(bool NewInteract);
	void PickUpFood();
	FVector DropFood();
	AFood* GetFoodRef();
	void SetFoodRef(AFood* NewFood);

	void InstantiateFood();

	// Called every frame
	bool GetHaveToDroppedFood();
	bool GetHoldingFood();
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
