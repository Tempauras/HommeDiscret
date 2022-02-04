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

	//Check the number of food that are present in the chest
	UPROPERTY(VisibleAnywhere)
		int32 FoodCountInChest;
	//Check the number of food that are present on a food spot
	UPROPERTY(VisibleAnywhere, Category = "Food Spot Spec")
		int32 FoodCountOnFoodSpot;
	//The number of food that are needed for the player to be declared the winner. Defaults = 5
	UPROPERTY(EditAnywhere, Category = "Victory Condition")
		int32 NumberOfFoodInChestForVictory = 5;
	//The number of food spot that can be occupied at any time. Defaults = 5;
	UPROPERTY(EditAnywhere, Category = "Food Spot Spec")
		int32 MaxNumberOfFoodSpotOccupied = 5;

	UFUNCTION()
		bool IsGameWon();
};
