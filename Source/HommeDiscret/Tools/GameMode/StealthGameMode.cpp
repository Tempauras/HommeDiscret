// Fill out your copyright notice in the Description page of Project Settings.

#include "StealthGameMode.h"
#include "HommeDiscret/IA/FoeSpawner.h"

AStealthGameMode::AStealthGameMode()
{
}


void AStealthGameMode::BeginPlay()
{
	Super::BeginPlay();
	SurvivalGameState =GetGameState<ASurvivalGameState>();
	ShowNormalHUD(); 
	LaunchIA();
}

void AStealthGameMode::PlayerWon()
{
	if (SurvivalGameState->FoodCountInChest == FoodInChestToWin)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Won!"));
	}
}


void AStealthGameMode::LostGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Loose!"));
}

void AStealthGameMode::AddFoodInChest(int FoodValue)
{
	SurvivalGameState->FoodCountInChest += FoodValue;
	RemoveFoodInRoom();
	PlayerWon();
}

void AStealthGameMode::AddFoodInRoom()
{
	SurvivalGameState->FoodCountInRoom++;

	if (SurvivalGameState->FoodCountInRoom >=MaxFoodsInRoom)
	{
		SetFoeCarryFood(false);
	}
}

void AStealthGameMode::RemoveFoodInRoom()
{
	SurvivalGameState->FoodCountInRoom--;
	if (SurvivalGameState->FoodCountInRoom < MaxFoodsInRoom)
	{
		SetFoeCarryFood(true);
		if (SurvivalGameState->FoodCountInRoom <= 0)
		{
			SurvivalGameState->FoodCountInRoom = 0;
		}
	}
}

void AStealthGameMode::AddFoeInRoom()
{
	SurvivalGameState->FoeCountInRoom++;
}

void AStealthGameMode::RemoveFoeInRoom()
{
	SurvivalGameState->FoeCountInRoom--;
	//If there's no foe in room : SpawnFoelos
	//else : LaunchTimer between 0 et 5
	if (SurvivalGameState->FoeCountInRoom <= 0)
	{
		CreateFoe();
	}
	else
	{
		int RandomTimer = rand() % 6;
		LaunchTimer((float)RandomTimer, false, 0.0f);
	}
}

void AStealthGameMode::SetFoeCarryFood(bool NewNextFood)
{
	SurvivalGameState->FoeCarryFood = NewNextFood;
}

void AStealthGameMode::CreateFoe()
{
	FoeSpawner->SpawnFoe(SurvivalGameState->FoeCarryFood);
	AddFoeInRoom();
	if (SurvivalGameState->FoeCarryFood)
	{
		AddFoodInRoom();
	}
}

void AStealthGameMode::LaunchIA()
{
	CreateFoe();
	CreateFoe();
	LaunchTimer(60.0f, false, 0.0f);
}

void AStealthGameMode::LaunchTimer(float InRate, bool IsLooping, float Delay)
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AStealthGameMode::CreateFoe, InRate, IsLooping, Delay);
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
