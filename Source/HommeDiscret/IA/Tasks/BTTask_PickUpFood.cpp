// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PickUpFood.h"
#include "HommeDiscret/IA/AIC_Foe.h"
#include "HommeDiscret/IA/Tasks/BB_keys.h"
#include "HommeDiscret/IA/Foe.h"

UBTTask_PickUpFood::UBTTask_PickUpFood(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("PickUpFood");
}


EBTNodeResult::Type UBTTask_PickUpFood::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAIC_Foe* FoeController = Cast<AAIC_Foe>(owner_comp.GetAIOwner());

	AFoe* Foe = Cast<AFoe>(FoeController->GetCharacter());

	Foe->PickUpFood();

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
