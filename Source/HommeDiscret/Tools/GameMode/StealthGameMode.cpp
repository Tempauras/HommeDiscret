// Fill out your copyright notice in the Description page of Project Settings.

#include "StealthGameMode.h"

AStealthGameMode::AStealthGameMode()
{
}


void AStealthGameMode::BeginPlay()
{
	Super::BeginPlay();
	SurvivalGameState = GetGameState<ASurvivalGameState>();
	ShowNormalHUD();
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
		PlayerWon();
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

bool AStealthGameMode::PlayerWon()
{
	if (SurvivalGameState->FoodCountInChest == NumberOfFoodInChestForVictory)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Won!"));
		return true;
	}
	else
	{
		return false;
	}
}

void AStealthGameMode::ShowPauseMenu()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	FInputModeUIOnly InputType;
	InputType.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(InputType);
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}
	//Load UI
	if (PauseHUDClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PauseHUDClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void AStealthGameMode::ShowNormalHUD()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	FInputModeGameOnly InputType;
	InputType.SetConsumeCaptureMouseDown(true);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(InputType);
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = false;
		PC->bEnableClickEvents = false;
		PC->bEnableMouseOverEvents = false;
	}
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

