// Fill out your copyright notice in the Description page of Project Settings.


#include "HungerBar.h"
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>
#include "Delegates/DelegateSignatureImpl.inl"
#include <Runtime/ApplicationCore/Private/IOS/IOSAppDelegate.cpp>

void UHungerBar::OnFoodStocked()
{
}

void UHungerBar::NativeOnInitiliazed()
{
	Super::OnInitialized();
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
	HungerBar_OnFoodStocked.Broadcast();
	//CNumberFoodsContained = ChestRef->GetNumberFoodsContained();
	/*CurrentHungerLabel->SetText(FText::AsCultureInvariant(FString::FromInt(CurrentH)));
	MaxHungerLabel->SetText(FText::AsCultureInvariant(FString::FromInt(MaxH)));

	HungerBar->SetPercent((float)CurrentH / CMaxFoodsToWin);*/
}
