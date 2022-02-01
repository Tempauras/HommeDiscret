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
	MovementPtr = Cast<UCharacterMovementComponent>(Hero->GetCharacterMovement());
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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("end"));
	MovementPtr->MaxWalkSpeed = Hero->HeroSpeed;
}

void UHDAnimInstance::AnimNotify_Begin(UAnimNotify* Notify)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("begin"));
	IsInHand = true;
	MovementPtr->MaxWalkSpeed = 0;
}
