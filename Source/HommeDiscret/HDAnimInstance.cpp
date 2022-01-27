// Fill out your copyright notice in the Description page of Project Settings.


#include "HDAnimInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UHDAnimInstance::UHDAnimInstance()
{
	Speed = 0;
	IsMoving = false;
	IsHolding = false;
	IsInHand = false;
}

void UHDAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Hero = Cast<AHero>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UHDAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	AActor* OwningActor = GetOwningActor();

	if (OwningActor != nullptr)
		Speed = OwningActor->GetVelocity().Size();

	if (Speed > 0)
		IsMoving = true;
	else
		IsMoving = false;

	if (Hero != nullptr)
		IsHolding = Hero->IsHoldingFood;

	if (!IsHolding)
		IsInHand = false;
}

void UHDAnimInstance::AnimNotify_End(UAnimNotify* Notify)
{
	IsInHand = true;
}
