// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "StealthGameModeInGameState.generated.h"

/**
 * 
 */
UCLASS()
class HOMMEDISCRET_API AStealthGameModeInGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AStealthGameModeInGameState();
	virtual ~AStealthGameModeInGameState() = default;

	UPROPERTY(EditAnywhere)
		int32 FoodCountInChest;
	UPROPERTY(EditAnywhere)
		int32 FoodCountOnFoodSpot;
};
