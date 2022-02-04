// Fill out your copyright notice in the Description page of Project Settings.


#include "HungerBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>


void UHungerBar::NativeConstruct()
{
	Super::NativeConstruct();

	Chest = Cast<AChest>(UGameplayStatics::GetActorOfClass(GetWorld(), AChest::StaticClass()));
	Chest->HungerBar_OnFoodStocked.AddUObject(this, &UHungerBar::OnFoodStocked); //see above in wiki
}

void UHungerBar::OnFoodStocked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Called"));
}

void UHungerBar ::NativeOnInitiliazed()
{
	Super::OnInitialized();

	Chest = Cast<AChest>(UGameplayStatics::GetActorOfClass(GetWorld(), AChest::StaticClass()));
	Chest->HungerBar_OnFoodStocked.AddUObject(this, &UHungerBar::OnFoodStocked); //see above in wiki
}

