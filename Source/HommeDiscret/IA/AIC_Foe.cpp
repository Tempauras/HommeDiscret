// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_Foe.h"
#include "HommeDiscret/Character/Hero.h"
#include "NavigationPoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "HommeDiscret/IA/Tasks/BB_keys.h"
#include "HommeDiscret/Level/Props/FoodSpot.h"
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
    //Adding behavior tree component and blackboard component to our object 
    BehaviorTreeComponent = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTree"));
    Blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
    SetupPerceptionSystem();
}


void AAIC_Foe::BeginPlay()
{       
    Super::BeginPlay();
    TSubclassOf<AActor> ClassToFind = ANavigationPoint::StaticClass();
    TArray<AActor*> FoundNavigationP;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundNavigationP);
    EntranceLocation = FoundNavigationP[0]->GetActorLocation();
    ExitLocation = FoundNavigationP[2]->GetActorLocation();
    OriginLocation = FoundNavigationP[1]->GetActorLocation();
    FindFoodSpots();
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

UBlackboardComponent* AAIC_Foe::get_blackboard() const 
{
    return Blackboard;
}



void AAIC_Foe::OnTargetDetected(AActor* actor, FAIStimulus const stimulus)
{
    if (auto const ch = Cast<AHero>(actor))
    {
        get_blackboard()->SetValueAsBool(bb_keys::player_onSight, stimulus.WasSuccessfullySensed());
    }
}


void AAIC_Foe::SetupPerceptionSystem()
{
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
    SightConfig->SightRadius = 500.0f;
    SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.0f;
    SightConfig->PeripheralVisionAngleDegrees = 90.0f;
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

void AAIC_Foe::FindFoodSpots()
{
    TSubclassOf<AActor> ClassToFind = AFoodSpot::StaticClass();
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoodSpots);
}

AFoodSpot* AAIC_Foe::GetOneRandomFoodSpot()
{
    int RandomIndex = rand() % FoodSpots.Max();
    AFoodSpot* NewFoodSpot = Cast<AFoodSpot>(FoodSpots[RandomIndex]);
    return NewFoodSpot;
}