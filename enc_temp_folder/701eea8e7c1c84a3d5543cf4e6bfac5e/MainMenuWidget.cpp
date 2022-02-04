// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "HommeDiscret/Tools/GameMode/StealthGameMode.h"


void UMainMenuWidget::NativeConstruct()
{
	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartClick);
	}
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly::FInputModeUIOnly());
}

void UMainMenuWidget::OnStartClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("InGameLevel"));
}
