// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"
#include "BTTask_FindEntrance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class HOMMEDISCRET_API UBTTask_FindEntrance : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_FindEntrance(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory);
	
};
