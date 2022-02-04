// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "HommeDiscret/Tools/GameMode/StealthGameMode.h"


void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}
	GEngine->GameViewport->Viewport->LockMouseToViewport(true);
	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartClick);
	}
	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnCloseClick);
	}
}

void UMainMenuWidget::OnStartClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("InGameLevel"));
}

void UMainMenuWidget::OnCloseClick()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
