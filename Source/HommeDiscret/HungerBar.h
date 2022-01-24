// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <HommeDiscret/Hero.h>

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HungerBar.generated.h"

/**
 *
 */
UCLASS(Abstract)
class HOMMEDISCRET_API UHungerBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHero(AHero* InHero) { Hero = InHero; }

protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	TWeakObjectPtr<AHero> Hero;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HungerBar;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CurrentHungerLabel;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MaxHungerLabel;

};
