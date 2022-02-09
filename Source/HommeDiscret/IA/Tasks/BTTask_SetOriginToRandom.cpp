// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetOriginToRandom.h"
#include "HommeDiscret/IA/Tasks/BB_keys.h"
#include "HommeDiscret/IA/AIC_Foe.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetOriginToRandom::UBTTask_SetOriginToRandom(FObjectInitializer const& object_initializer)
{
    NodeName = TEXT("Set Origin To Random Location");
}

EBTNodeResult::Type UBTTask_SetOriginToRandom::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
  
    auto const cont = Cast<AAIC_Foe>(owner_comp.GetAIOwner());

    if (FoeLocation)
    {
        auto const npc = cont->GetPawn();
        cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, npc->GetActorLocation());
    }
    else 
    {
        cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, cont->GetOriginLocation());
    }

    FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}


