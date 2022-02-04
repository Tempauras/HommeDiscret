// Fill out your copyright notice in the Description page of Project Settings.

#include "StealthGameMode.h"

AStealthGameMode::AStealthGameMode()
{
	GameStateClass = AStealthGameModeInGameState::StaticClass();
	SurvivalGameState = GetGameState<AStealthGameModeInGameState>();
}


void AStealthGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeUI(GameStates::SURVIVAL);
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

void AStealthGameMode::ChangeUI(GameStates GameStateEnum)
{
	switch (GameStateEnum)
	{
	case MAINMENU:
		if (PlayerHUDClassMainMenu != nullptr)
		{
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClassMainMenu);
			if (CurrentWidget != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("CurrentWidget is set to main menu"));
				CurrentWidget->AddToViewport();
			}
		}
		break;
	case SURVIVAL:
		if (PlayerHUDClassSurvival != nullptr)
		{
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClassSurvival);
			if (CurrentWidget != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("CurrentWidget is set to survival"));
				CurrentWidget->AddToViewport();
			}
		}
		break;
	case SCORING:
		if (PlayerHUDClassScoring != nullptr)
		{
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClassScoring);
			if (CurrentWidget != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("CurrentWidget is set to survival to scoring"));
				CurrentWidget->AddToViewport();
			}
		}
		break;
	}
}

