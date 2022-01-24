// Fill out your copyright notice in the Description page of Project Settings.


#include "HungerBar.h"
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>

void UHungerBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!Hero.IsValid())
		return;

	HungerBar->SetPercent(Hero->GetHunger() / Hero->GetMaxHunger());

	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	CurrentHungerLabel->SetText(FText::AsNumber(Hero->GetHunger(), &Opts));
	MaxHungerLabel->SetText(FText::AsNumber(Hero->GetMaxHunger(), &Opts));
}