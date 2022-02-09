// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindEntrance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HommeDiscret/IA/AIC_Foe.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "HommeDiscret/IA/Tasks/BB_keys.h"


UBTTask_FindEntrance::UBTTask_FindEntrance(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Entrance");
}


EBTNodeResult::Type UBTTask_FindEntrance::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	/*auto const cont = Cast<AAIC_Foe>(owner_comp.GetAIOwner());
	
	if (cont!= nullptr)
	{
		cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, cont->GetEnterLocation());
	}*/

	//finish with success
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
