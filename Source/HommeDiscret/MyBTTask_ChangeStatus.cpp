// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_ChangeStatus.h"
#include "Foe.h"
#include "AIC_Foe.h"

UMyBTTask_ChangeStatus::UMyBTTask_ChangeStatus(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Change Status");

}

EBTNodeResult::Type UMyBTTask_ChangeStatus::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	auto const cont = Cast<AAIC_Foe>(owner_comp.GetAIOwner());

	if (status.GetValue() == EFoeStatus::NormalBehavior)
	{
		auto const foe = Cast<AFoe>(cont->GetCharacter());
		if (foe->GetHaveToDroppedFood() == true)
		{
			if (foe->GetHoldingFood() == true)
			{
				status = EFoeStatus::RecoveringFood;
			}
			else 
			{
				status = EFoeStatus::DroppingFood;
			}
		}
		else {
			status = EFoeStatus::Patrolling;
		}
	}

	newStatus = (uint8)status.GetValue();
	cont->GetBlackboard()->SetValueAsEnum(bb_keys::foe_status, newStatus);
	
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
