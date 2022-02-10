// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckFoeHaveFood.h"
#include "HommeDiscret/IA/AIC_Foe.h"
#include "HommeDiscret/IA/Foe.h"
#include "HommeDiscret/IA/Tasks/BB_keys.h"
#include "BehaviorTree/BlackboardComponent.h"



UBTTask_CheckFoeHaveFood::UBTTask_CheckFoeHaveFood(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("CheckFoeHaveFood");
}


EBTNodeResult::Type UBTTask_CheckFoeHaveFood::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAIC_Foe* FoeController = Cast<AAIC_Foe>(owner_comp.GetAIOwner());
	AFoe* Foe = Cast<AFoe>(FoeController->GetPawn());
	UBlackboardComponent* Blackboard = FoeController->GetBlackboardComponent();
	Blackboard->SetValueAsBool(bb_keys::HaveToDroppedFood,Foe->GetHaveToDroppedFood());

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
