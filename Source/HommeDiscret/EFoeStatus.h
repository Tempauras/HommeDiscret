#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"

/*
UCLASS(Blueprintable)
class */
UENUM(BlueprintType, Category = "",Blueprintable)
enum class EFoeStatus : uint8
{
		Waiting UMETA(DisplayName = "Waiting"),
		Entering UMETA(DisplayName = "Entering"),
		Exiting UMETA(DisplayName = "Exiting"),
		NormalBehavior UMETA(DisplayName = "NormalBehavior"),
		Patrolling UMETA(DisplayName = "Patrolling"),
		Chasing UMETA(DisplayName = "Chasing"),
		DroppingFood UMETA(DisplayName = "DroppingFood"),
		RecoveringFood UMETA(DisplayName = "RecoveringFood"),
	};