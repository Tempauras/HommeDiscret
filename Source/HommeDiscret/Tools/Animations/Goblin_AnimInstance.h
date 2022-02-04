// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "Goblin_AnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class HOMMEDISCRET_API UGoblin_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UGoblin_AnimInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool IsMovingG;



	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
