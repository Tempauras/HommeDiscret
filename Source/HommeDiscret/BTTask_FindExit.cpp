// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindExit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AIC_Foe.h"
//#include "BehaviorTree/Blackboard/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BB_keys.h"


UBTTask_FindExit::UBTTask_FindExit(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Exit");
}


EBTNodeResult::Type UBTTask_FindExit::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	auto const cont = Cast<AAIC_Foe>(owner_comp.GetAIOwner());
	//GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, cont->ExitLocation.ToString());

	if (cont != nullptr)
	{
		cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, cont->ExitLocation);
	}

	//finish with success
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

