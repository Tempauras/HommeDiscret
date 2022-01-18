// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_Foe.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "AIFoe.h"


AAIC_Foe::AAIC_Foe(FObjectInitializer const& object_initializer)
{
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj((TEXT("BehaviorTree'/Game/Blueprints/Characters/IA/BT_Foe.BT_Foe'")));
    if (obj.Succeeded())
    {
        btree = obj.Object;
    }
    behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTree"));
    blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}


void AAIC_Foe::BeginPlay()
{
    Super::BeginPlay();
    RunBehaviorTree(btree);
    behavior_tree_component->StartTree(*btree);
}

void AAIC_Foe::OnPossess(APawn* const pawn)
{
    Super::OnPossess(pawn);
    if (blackboard)
    {
        blackboard->InitializeBlackboard(*btree->BlackboardAsset);

    }
}

UBlackboardComponent* AAIC_Foe::get_blackboard() const 
{
    return blackboard;
}

