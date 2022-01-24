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
        Btree = obj.Object;
    }
    SetUpPerceptionSystem();
    //Adding behavior tree component and blackboard component to our object 
    BehaviorTreeComponent = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTree"));
    Blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
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
    RunBehaviorTree(Btree);
    BehaviorTreeComponent->StartTree(*Btree);
}

void AAIC_Foe::OnPossess(APawn* const pawn)
{
    Super::OnPossess(pawn);
    if (Blackboard)
    {
        Blackboard->InitializeBlackboard(*Btree->BlackboardAsset);
    }
}

UBlackboardComponent* AAIC_Foe::GetBlackboard() const
{
    return Blackboard;
}

void AAIC_Foe::OnTargetDetected(AActor* actor, FAIStimulus const stimulus)
{
    if (auto const ch = Cast<AHero>(actor))
    {
        GetBlackboard()->SetValueAsBool(bb_keys::player_onSight, stimulus.WasSuccessfullySensed());
    }
}


void AAIC_Foe::SetUpPerceptionSystem()
{
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
    SightConfig->SightRadius = 925.0f;
    SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.0f;
    SightConfig->PeripheralVisionAngleDegrees = 45.0f;
    SightConfig->SetMaxAge(5.0f);
    SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.0f;
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
     // add sight configuration component to perception component
     GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
     GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC_Foe::OnTargetDetected);
     GetPerceptionComponent()->ConfigureSense(*SightConfig);

}

