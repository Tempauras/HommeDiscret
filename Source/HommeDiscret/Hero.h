// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

//#include "Blueprint/UserWidget.h"

#include "GameFramework/Character.h"

#include "Hero.generated.h"

UCLASS()
class HOMMEDISCRET_API AHero : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHero();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = "Food")
		UStaticMeshComponent* FoodMesh;

	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void Zoom(float value);

	void Interact();

	// Can't move if he's dead CQFD MON GARS
	bool bDead;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	class UAIPerceptionStimuliSourceComponent* stimulus;

	void setup_stimulus();
};
