// Fill out your copyright notice in the Description page of Project Settings.


#include "HungerBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <string>


void UHungerBar::NativeConstruct()
{
	Super::NativeConstruct();

	Chest = Cast<AChest>(UGameplayStatics::GetActorOfClass(GetWorld(), AChest::StaticClass()));
	Chest->HungerBar_OnFoodStocked.AddUObject(this, &UHungerBar::OnFoodStocked); //see above in wiki

	GameMode = Cast<AStealthGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameState = Cast<ASurvivalGameState>(UGameplayStatics::GetGameState(GetWorld()));

	setMaxFood();
	setCurrentFood();
}

void UHungerBar::setMaxFood()
{
	int32 YourInt = GameMode->getMaxFoodsInRoom();
	FText intAsText = FText::AsNumber(YourInt);
	MaxHungerLabel->SetText(intAsText);
}

void UHungerBar::setCurrentFood()
{
	int YourInt = GameState->getCurrentFoodsInChest();
	FText intAsText = FText::AsNumber(YourInt);
	CurrentHungerLabel->SetText(intAsText);
}

void UHungerBar::OnFoodStocked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Called"));
	//CurrentHungerLabel = SurvivalGameState. FoodCountInChest
}

void UHungerBar ::NativeOnInitiliazed()
{
	Super::OnInitialized();

	Chest = Cast<AChest>(UGameplayStatics::GetActorOfClass(GetWorld(), AChest::StaticClass()));
	Chest->HungerBar_OnFoodStocked.AddUObject(this, &UHungerBar::OnFoodStocked); //see above in wiki
}

