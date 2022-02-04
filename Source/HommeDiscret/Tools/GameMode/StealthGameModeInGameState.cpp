// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthGameModeInGameState.h"

AStealthGameModeInGameState::AStealthGameModeInGameState() :
	FoodCountInChest(0),
	FoodCountOnFoodSpot(0)
{

}

bool AStealthGameModeInGameState::IsGameWon()
{
	if (FoodCountInChest == NumberOfFoodInChestForVictory)
	{
		return true;
	}
	return false;
}
