// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindFSLocation.h"
#include "HommeDiscret/AIC_Foe.h"
#include "HommeDiscret/FoodSpot.h"
#include "HommeDiscret/BB_keys.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_FindFSLocation::UBTTask_FindFSLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Food Spot Location");
}

EBTNodeResult::Type UBTTask_FindFSLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	auto const FoeController = Cast<AAIC_Foe>(owner_comp.GetAIOwner());
	
	AFoodSpot* NewFoodSpot = FoeController->GetFoodSpot();
	FoeController->get_blackboard()->SetValueAsVector(bb_keys::target_location,NewFoodSpot->GetActorLocation());
	
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
