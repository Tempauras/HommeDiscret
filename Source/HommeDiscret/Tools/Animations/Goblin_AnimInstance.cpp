// Fill out your copyright notice in the Description page of Project Settings.


#include "Goblin_AnimInstance.h"

UGoblin_AnimInstance::UGoblin_AnimInstance()
{
	Speed = 0;
	IsMovingG = false;
}

void UGoblin_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	AActor* OwningActor = GetOwningActor();

	if (OwningActor != nullptr)
		Speed = OwningActor->GetVelocity().Size();

	if (Speed > 0)
		IsMovingG = true;
	else
		IsMovingG = false;
}