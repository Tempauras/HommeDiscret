// Fill out your copyright notice in the Description page of Project Settings.


#include "HDAnimInstance.h"

UHDAnimInstance::UHDAnimInstance()
{
	Speed = 0;
	IsMoving = false;
}

void UHDAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	AActor* OwningActor = GetOwningActor();

	if (OwningActor != nullptr) {
		Speed = OwningActor->GetVelocity().Size();
	}

	if (Speed > 0) {
		IsMoving = true;
	}
	else
		IsMoving = false;
}
