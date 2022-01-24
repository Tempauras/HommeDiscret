#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"

	UENUM(BlueprintType, Category="")
	enum class EFoeStatus : uint8
	{
		Entering UMETA(DisplayName = "Entering"),
		Exiting UMETA(DisplayName = "Exiting"),
		Patrolling UMETA(DisplayName = "Patrolling"),
		Chasing UMETA(DisplayName = "Chasing"),
		DroppingFood UMETA(DisplayName = "DroppingFood"),
		RecoveringFood UMETA(DisplayName = "RecoveringFood"),
	};