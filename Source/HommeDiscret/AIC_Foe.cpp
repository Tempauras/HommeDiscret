// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_Foe.h"
#include "Hero.h"
#include "NavigationPoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "BB_keys.h"
#include "GameFramework/Character.h"



AAIC_Foe::AAIC_Foe(FObjectInitializer const& object_initializer)
{
   //Find the behavior tree with its relative path
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj((TEXT("BehaviorTree'/Game/Blueprints/Characters/IA/BT_Foe.BT_Foe'")));
    //If the searching is succeessed then btree take its object value
    if (obj.Succeeded())
    {
        btree = obj.Object;
    }
    //Adding behavior tree component and blackboard component to our object 
    behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTree"));
    blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
    setup_perception_system();
}


void AAIC_Foe::BeginPlay()
{       
    Super::BeginPlay();
    TSubclassOf<AActor> ClassToFind = ANavigationPoint::StaticClass();
    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundEnemies);
    EntranceLocation = FoundEnemies[1]->GetActorLocation();
    ExitLocation = FoundEnemies[2]->GetActorLocation();
    OriginLocation = FoundEnemies[0]->GetActorLocation();
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

void AAIC_Foe::on_target_detected(AActor* actor, FAIStimulus const stimulus)
{
    if (auto const ch = Cast<AHero>(actor))
    {
        get_blackboard()->SetValueAsBool(bb_keys::player_onSight, stimulus.WasSuccessfullySensed());
    }
}


void AAIC_Foe::setup_perception_system()
{
    sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
    sight_config->SightRadius = 500.0f;
    sight_config->LoseSightRadius = sight_config->SightRadius + 25.0f;
    sight_config->PeripheralVisionAngleDegrees = 90.0f;
    sight_config->SetMaxAge(5.0f);
    sight_config->AutoSuccessRangeFromLastSeenLocation = 520.0f;
    sight_config->DetectionByAffiliation.bDetectEnemies =
    sight_config->DetectionByAffiliation.bDetectFriendlies =
    sight_config->DetectionByAffiliation.bDetectNeutrals = true;
     // add sight configuration component to perception component
     GetPerceptionComponent()->SetDominantSense(*sight_config->GetSenseImplementation());
     GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC_Foe::on_target_detected);
     GetPerceptionComponent()->ConfigureSense(*sight_config);

}

