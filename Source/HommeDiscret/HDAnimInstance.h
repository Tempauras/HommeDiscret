// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Hero.h"

#include "HDAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class HOMMEDISCRET_API UHDAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UHDAnimInstance();
	AHero* Hero;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool IsMoving;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool IsHolding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool IsInHand;

	UFUNCTION(BlueprintCallable, Category = "MyAnim")
		void AnimNotify_End(UAnimNotify* Notify);

	UFUNCTION(BlueprintCallable, Category = "MyAnim")
		void AnimNotify_Begin(UAnimNotify* Notify);

	UCharacterMovementComponent* MovementPtr;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	virtual void NativeBeginPlay() override;
};
