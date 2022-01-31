// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Chest.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Food.h"
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

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AChest* ChestRef;*/
	/*
	int CMaxFoodsToWin;
	int CNumberFoodsContained;*/

	void NativeOnInitiliazed();
	void RefreshChest(AFood &FoodToAdd);
};
