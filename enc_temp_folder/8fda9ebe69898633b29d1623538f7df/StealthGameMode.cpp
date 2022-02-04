// Fill out your copyright notice in the Description page of Project Settings.

#include "StealthGameMode.h"
#include "Blueprint/WidgetLayoutLibrary.h"

AStealthGameMode::AStealthGameMode()
{
}


void AStealthGameMode::BeginPlay()
{
	Super::BeginPlay();
	//Load UI
	if (PlayerHUDClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

int32 AStealthGameMode::GetFoodInChest() const
{
	if (SurvivalGameState != nullptr)
	{
		return SurvivalGameState->FoodCountInChest;
	}
	else
	{
		return -1;
	}
}

int32 AStealthGameMode::GetFoodOnFoodSpot() const
{
	if (SurvivalGameState != nullptr)
	{
		return SurvivalGameState->FoodCountOnFoodSpot;
	}
	else
	{
		return -1;
	}
}

void AStealthGameMode::IncreaseFoodInChest(int32 FoodValue)
{
	if (SurvivalGameState != nullptr)
	{
		SurvivalGameState->FoodCountInChest += FoodValue;
		DecrementFoodOnFoodSpot();
	}
}

void AStealthGameMode::IncrementFoodOnFoodSpot()
{
	if (SurvivalGameState != nullptr)
	{
		SurvivalGameState->FoodCountOnFoodSpot++;
	}
}

void AStealthGameMode::DecrementFoodOnFoodSpot()
{
	if (SurvivalGameState != nullptr)
	{
		SurvivalGameState->FoodCountOnFoodSpot--;
	}
}

