// Fill out your copyright notice in the Description page of Project Settings.


#include "HDGameInstance.h"
#include "HommeDiscret/Tools/HungerBar.h"
#include "Components/WidgetComponent.h"

UHDGameInstance::UHDGameInstance()
{
	// Find the Widget and assigned to InGameUIClass
	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_HungerBarClass(TEXT("/Game/Blueprints/UI/WBP_HungerBar"));

	if (WBP_HungerBarClass.Class != nullptr)
	{
		WBP_HungerBar = WBP_HungerBarClass.Class;
	}
}

// Interface IInGameMenuInterface implementation

// Blueprint Callable Methods to create the the Menu
void UHDGameInstance::LoadHungerBar()
{
	if (WBP_HungerBar == nullptr) return;

	HungerBar = Cast<UHungerBar>(CreateWidget<UHungerBar>(this, WBP_HungerBar));
	if (HungerBar == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Overlap"));
		return;
	}
	HungerBar->AddToViewport();

	// Set the reference to the interface object
	//HungerBar->SetMenuInterface(this);
}

// Handles Start GamePathbutton
void UHDGameInstance::OnStartGamePath()
{
}

// Handles Start StartGame logic from the inGameMenu
void UHDGameInstance::OnStartGame()
{
	//StartGame();
}

void UHDGameInstance::Init()
{
	//UE_LOG(LogTemp, Warning, TEXT("We founded class %s"), *HungerBar->GetName());
}