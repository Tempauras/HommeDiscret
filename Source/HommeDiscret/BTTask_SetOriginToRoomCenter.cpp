// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetOriginToRoomCenter.h"
#include "AIC_Foe.h"
#include "BB_keys.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetOriginToRoomCenter::UBTTask_SetOriginToRoomCenter(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Set Origin To Room Center");
}


EBTNodeResult::Type UBTTask_SetOriginToRoomCenter::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAIC_Foe* FoeController = Cast<AAIC_Foe>(owner_comp.GetAIOwner());
	FoeController->GetBlackboardComponent()->SetValueAsVector(bb_keys::target_location, FoeController->OriginLocation);
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
