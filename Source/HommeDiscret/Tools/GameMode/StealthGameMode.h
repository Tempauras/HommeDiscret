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
	UPROPERTY(EditAnywhere)
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

		UUserWidget* CurrentWidget;


	//The number of food that are needed for the player to be declared the winner. Defaults = 5
	UPROPERTY(EditAnywhere, Category = "Victory Condition")
		int32 NumberOfFoodInChestForVictory = 5;

	UPROPERTY(EditAnywhere)
		int FoodInChestToWin = 5;

	UPROPERTY(EditAnywhere)
		int MaxFoodsInRoom = 5;

	class UHDGameInstance* GameInstance = Cast<UHDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

public:
	AStealthGameMode();

	virtual ~AStealthGameMode() = default;

	UFUNCTION(Category = "Victory Condition")
		virtual void PlayerWon();

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

	UFUNCTION(Category = "UI")
		int getMaxFoodsInRoom();

};
