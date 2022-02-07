// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "Kismet/GameplayStatics.h"

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}
	GEngine->GameViewport->Viewport->LockMouseToViewport(true);
	if (RestartGameButton)
	{
		RestartGameButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnRestartGameClick);
	}
	if (BackToMenuButton)
	{
		BackToMenuButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnBackToMenuClick);
	}
}

void UPauseMenuWidget::OnRestartGameClick()
{
	if (PC)
	{
		PC->bShowMouseCursor = false;
		PC->bEnableClickEvents = false;
		PC->bEnableMouseOverEvents = false;
	}
}

void UPauseMenuWidget::OnBackToMenuClick()
{
}