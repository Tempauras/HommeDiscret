#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"

	UENUM(BlueprintType, Category="")
	enum class EFoeStatus : uint8
	{
		Entering UMETA(DisplayName = "Entering"),
		Exiting UMETA(DisplayName = "Exiting"),
		Chasing UMETA(DisplayName = "Chasing"),
		NormalBehavior UMETA(DisplayName = "NormalBehavior"),
		Patrolling UMETA(DisplayName = "Patrolling"),
		DroppingFood UMETA(DisplayName = "DroppingFood"),
		RecoveringFood UMETA(DisplayName = "RecoveringFood"),
	};