// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BB_keys.h"
#include "EFoeStatus.h"
#include "Containers/EnumAsByte.h"
#include "MyBTTask_ChangeStatus.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class HOMMEDISCRET_API UMyBTTask_ChangeStatus : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		TEnumAsByte<EFoeStatus> status;

	UMyBTTask_ChangeStatus(FObjectInitializer const& object_initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory);

private:
	UPROPERTY()
		uint8 newStatus;

};
