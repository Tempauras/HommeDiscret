// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "Kismet/GameplayStatics.h"

AMainMenuGameMode::AMainMenuGameMode()
{

}

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Load UI
	if (PlayerHUDClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
	FInputModeUIOnly InputType;
	InputType.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(InputType);
}