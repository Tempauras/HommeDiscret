// Fill out your copyright notice in the Description page of Project Settings.


#include "Foe.h"
#include "AIC_Foe.h"

// Sets default values
AFoe::AFoe()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HaveFood = false;
	LostFood = false;
	AIControllerClass = AAIC_Foe::StaticClass();
	GetCharacterMovement()->bOrientRotationToMovement = true;

}
// Called when the game starts or when spawned
void AFoe::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFoe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFoe::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

