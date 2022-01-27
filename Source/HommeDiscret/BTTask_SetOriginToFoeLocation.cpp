// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetOriginToFoeLocation.h"
#include "AIC_Foe.h"
#include "BB_keys.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetOriginToFoeLocation::UBTTask_SetOriginToFoeLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Set Origin To Foe Location");
}

EBTNodeResult::Type UBTTask_SetOriginToFoeLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAIC_Foe* FoeController = Cast<AAIC_Foe>(owner_comp.GetAIOwner());
	auto const* CurrentFoe = FoeController->GetPawn();
	FoeController->GetBlackboardComponent()->SetValueAsVector(bb_keys::target_location,CurrentFoe->GetActorLocation());
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
