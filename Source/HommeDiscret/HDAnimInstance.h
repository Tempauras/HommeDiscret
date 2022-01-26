// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool IsMoving;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
