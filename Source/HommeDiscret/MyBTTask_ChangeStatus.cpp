// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_ChangeStatus.h"
#include "AIC_Foe.h"

UMyBTTask_ChangeStatus::UMyBTTask_ChangeStatus(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Change Status");

}

EBTNodeResult::Type UMyBTTask_ChangeStatus::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	auto const cont = Cast<AAIC_Foe>(owner_comp.GetAIOwner());

	newStatus = (uint8)status.GetValue();
	cont->get_blackboard()->SetValueAsEnum(bb_keys::foe_status, newStatus);
	
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
