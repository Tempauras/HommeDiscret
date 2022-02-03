// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HommeDiscret/Level/Props/Chest.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HommeDiscret/Level/Props/Food.h"
#include "HungerBar.generated.h"

/**
 *
 */
UCLASS()
class HOMMEDISCRET_API UHungerBar : public UUserWidget
{
	GENERATED_BODY()

public:
	//UHungerBar();
protected:

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HungerBar;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CurrentHungerLabel;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MaxHungerLabel;

	UFUNCTION()
		void OnFoodStocked();

	DECLARE_DELEGATE(FHungerBar);
	FHungerBar HungerBar_OnFoodStocked;
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AChest* ChestRef;*/
	/*
	int CMaxFoodsToWin;
	int CNumberFoodsContained;*/

	void NativeOnInitiliazed();
	void RefreshChest(AFood &FoodToAdd);
};
