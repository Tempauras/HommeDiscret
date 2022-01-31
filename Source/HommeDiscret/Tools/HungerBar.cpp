// Fill out your copyright notice in the Description page of Project Settings.


#include "HungerBar.h"
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>
#include "Delegates/DelegateSignatureImpl.inl"

void UHungerBar::NativeOnInitiliazed()
{
	/*
	if (ChestRef != nullptr)
	{
		//ChestRef->AddingFood.AddUFunction(this, UHungerBar::RefreshChest);
		//CMaxFoodsToWin = ChestRef->GetMaxFoodsToWin();

		//MaxHungerLabel->SetText(FText::AsCultureInvariant(FString::FromInt(CMaxFoodsToWin)));
	}*/
}

void UHungerBar::RefreshChest(AFood &FoodToAdd)
{ 
	//CNumberFoodsContained = ChestRef->GetNumberFoodsContained();
	/*CurrentHungerLabel->SetText(FText::AsCultureInvariant(FString::FromInt(CurrentH)));
	MaxHungerLabel->SetText(FText::AsCultureInvariant(FString::FromInt(MaxH)));

	HungerBar->SetPercent((float)CurrentH / CMaxFoodsToWin);*/
}
