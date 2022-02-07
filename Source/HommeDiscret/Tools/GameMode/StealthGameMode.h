// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "SurvivalGameState.h"
#include "MainMenuGameState.h"
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
class AFoeSpawner;
UCLASS()
class HOMMEDISCRET_API AStealthGameMode : public AGameModeBase
{
	GENERATED_BODY()

	//Call when the game start
	virtual void BeginPlay() override;

public:
	UPROPERTY()
		ASurvivalGameState* SurvivalGameState;
	UPROPERTY(EditAnywhere)
		AFoeSpawner* FoeSpawner;

	FTimerHandle TimerHandle;
protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UUserWidget> PlayerHUDClass;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UUserWidget> PauseHUDClass;
	UPROPERTY()
		UUserWidget* PlayerWidget;
	UPROPERTY()
		UUserWidget* PauseWidget;
	//The number of food that are needed for the player to be declared the winner. Defaults = 5
	UPROPERTY(EditAnywhere, Category = "Victory Condition")
		int32 NumberOfFoodInChestForVictory = 5;
	UPROPERTY(EditAnywhere)
		int FoodInChestToWin = 5;

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

	UFUNCTION(Category = "Victory Condition")
		virtual bool PlayerWon();

	UFUNCTION(Category = "Victory Condition")
		void VictoryTest();

	UFUNCTION(Category = "Defeat Condition")
		void LostGame();

	UFUNCTION(Category = "Food")
		void AddFoodInChest(int FoodValue);

	UFUNCTION(Category = "Food")
		void AddFoodInRoom();

	UFUNCTION(Category = "Food")
		void RemoveFoodInRoom();

	UFUNCTION(Category = "Foe")
		void AddFoeInRoom();

	UFUNCTION(Category = "Foe")
		void RemoveFoeInRoom();

	UFUNCTION(Category = "Foe")
		void SetFoeCarryFood(bool NewNextFood);

	UFUNCTION(Category = "Foe")
		void CreateFoe();

	UFUNCTION(Category = "Foe")
		void LaunchIA();

	UFUNCTION(Category = "Foe")
		void LaunchTimer(float InRate, bool IsLooping, float Delay);

	UFUNCTION(Category = "UI")
		virtual void ShowPauseMenu();
	UFUNCTION(Category = "UI")
		virtual void ShowNormalHUD();

};
