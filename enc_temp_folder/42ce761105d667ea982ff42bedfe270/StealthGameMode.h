// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Hero.h"
#include "StealthGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HOMMEDISCRET_API AStealthGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "PlayerPawn")
		TSubclassOf<AHero> PlayerPawn;
public:
	AStealthGameMode();

	virtual ~AStealthGameMode() = default;
	
	/*Return the number of food the player has placed in the chest*/
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
};
