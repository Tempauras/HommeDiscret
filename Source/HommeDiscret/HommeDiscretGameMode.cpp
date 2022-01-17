// Copyright Epic Games, Inc. All Rights Reserved.

#include "HommeDiscretGameMode.h"
#include "HommeDiscretCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHommeDiscretGameMode::AHommeDiscretGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
