// Fill out your copyright notice in the Description page of Project Settings.

#include "StealthGameMode.h"


AStealthGameMode::AStealthGameMode()
{
	GameStateClass = AStealthGameModeInGameState::StaticClass();
	InGameGameState = GetGameState<AStealthGameModeInGameState>();
}

int32 AStealthGameMode::GetFoodInChest() const
{
	if (InGameGameState != nullptr)
	{
		return InGameGameState->FoodCountInChest;
	}
	else
	{
		return -1;
	}
}

int32 AStealthGameMode::GetFoodOnFoodSpot() const
{
	if (InGameGameState != nullptr)
	{
		return InGameGameState->FoodCountOnFoodSpot;
	}
	else
	{
		return -1;
	}
}

void AStealthGameMode::IncreaseFoodInChest(int32 FoodValue)
{
	if (InGameGameState != nullptr)
	{
		InGameGameState->FoodCountInChest += FoodValue;
		DecrementFoodOnFoodSpot();
	}
}

void AStealthGameMode::IncrementFoodOnFoodSpot()
{
	if (InGameGameState != nullptr)
	{
		InGameGameState->FoodCountOnFoodSpot++;
	}
}

void AStealthGameMode::DecrementFoodOnFoodSpot()
{
	if (InGameGameState != nullptr)
	{
		InGameGameState->FoodCountOnFoodSpot--;
	}
}

