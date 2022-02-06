// Fill out your copyright notice in the Description page of Project Settings.

#include "StealthGameMode.h"
#include "HommeDiscret/IA/FoeSpawner.h"

AStealthGameMode::AStealthGameMode()
{
}


void AStealthGameMode::BeginPlay()
{
	Super::BeginPlay();
	SurvivalGameState = GetGameState<ASurvivalGameState>();
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

void AStealthGameMode::AddFoodInRoom()
{
	SurvivalGameState->FoodsInRoom++;

	if (SurvivalGameState->FoodsInRoom >= SurvivalGameState->MaxFoodsInRoom)
	{
		SetFoeCarryFood(false);
	}
}

void AStealthGameMode::RemoveFoodInRoom()
{
	SurvivalGameState->FoodsInRoom--;
	if (SurvivalGameState->FoodsInRoom < SurvivalGameState->MaxFoodsInRoom)
	{
		SetFoeCarryFood(true);
	}
}

void AStealthGameMode::AddFoeInRoom()
{
	SurvivalGameState->FoesInRoom++;
}

void AStealthGameMode::RemoveFoeInRoom()
{
	SurvivalGameState->FoesInRoom--;
	//If there's no foe in room : SpawnFoe
	//else : LaunchTimer between 0 et 5
	if (SurvivalGameState->FoesInRoom <= 0)
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
	GetWorldTimerManager().SetTimer(TimerHandle, this, AStealthGameMode::CreateFoe, InRate, IsLooping, Delay);
}
