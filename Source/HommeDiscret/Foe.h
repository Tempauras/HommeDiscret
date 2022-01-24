// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Foe.generated.h"

UCLASS()
class HOMMEDISCRET_API AFoe : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFoe();

protected:
	UPROPERTY(EditAnywhere)
		bool HaveToDroppedFood;
	
	UPROPERTY(EditAnywhere)
		bool HoldingFood;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	bool GetHaveToDroppedFood();
	bool GetHoldingFood();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
