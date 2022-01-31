// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthGameMode.h"
#include "StealthGameModeInGameState.h"

AStealthGameMode::AStealthGameMode()
{
}

int32 AStealthGameMode::GetFoodInChest() const
{
	return GetGameState<AStealthGameModeInGameState>()->FoodCountInChest;
}

int32 AStealthGameMode::GetFoodOnFoodSpot() const
{
	return GetGameState<AStealthGameModeInGameState>()->FoodCountOnFoodSpot;
}

void AStealthGameMode::IncreaseFoodInChest(int32 FoodValue)
{
	GetGameState<AStealthGameModeInGameState>()->FoodCountInChest += FoodValue;
}

void AStealthGameMode::IncrementFoodOnFoodSpot()
{
	GetGameState<AStealthGameModeInGameState>()->FoodCountOnFoodSpot++;
}

