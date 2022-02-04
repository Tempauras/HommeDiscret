// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "StealthGameModeInGameState.h"
#include "StealthGameMode.generated.h"

UENUM(BlueprintType)
enum GameStates
{
	MAINMENU UMETA(DisplayName = "Main Menu"),
	SURVIVAL UMETA(DisplayName = "Survival"),
	SCORING UMETA(DisplayName = "Score")
};

/**
 * 
 */
UCLASS()
class HOMMEDISCRET_API AStealthGameMode : public AGameModeBase
{
	GENERATED_BODY()

	//Call when the game start
	virtual void BeginPlay() override;

public:
	UPROPERTY()
		AStealthGameModeInGameState* SurvivalGameState;
	/*UPROPERTY(EditAnywhere, Category = "Game State")
		TSubclassOf<AGameStateBase> SurvivalGameStateClass;
	UPROPERTY()
		AStealthGameModeInGameState* SurvivalGameState;
	UPROPERTY(EditAnywhere, Category = "Game State")
		TSubclassOf<AGameStateBase> SurvivalGameStateClass;
	UPROPERTY()
		AStealthGameModeInGameState* SurvivalGameState;*/


protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UUserWidget> PlayerHUDClassSurvival;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UUserWidget> PlayerHUDClassMainMenu;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UUserWidget> PlayerHUDClassScoring;
	UPROPERTY()
		UUserWidget* CurrentWidget;
public:
	AStealthGameMode();

	virtual ~AStealthGameMode() = default;
	
	/*Return the number of food the player has placed in the chest. Return -1 if nullptr*/
	UFUNCTION(Category = "Food")
		virtual int32 GetFoodInChest() const;
	/*Return the number of food that is currently placed on a Food Spot*/
	UFUNCTION(Category = "Food")
		virtual int32 GetFoodOnFoodSpot() const;
	/*Increase the value of food in the chest by the FoodValue*/
	UFUNCTION(Category = "Food")
		virtual void IncreaseFoodInChest(int32 FoodValue);
	/*Increment the value of food on food spot*/
	UFUNCTION(Category = "Food")
		virtual void IncrementFoodOnFoodSpot();
	//Decrement the value of food on food spot
	UFUNCTION(Category = "Food")
		virtual void DecrementFoodOnFoodSpot();
	//Change the UI to fit the current game state
	UFUNCTION(Category = "UI")
		virtual void ChangeUI(GameStates GameStateEnum);
};
