// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayerDirection.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AIC_Foe.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BB_keys.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"


UBTTask_FindPlayerDirection::UBTTask_FindPlayerDirection(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("FindPlayerDirection");
}

EBTNodeResult::Type UBTTask_FindPlayerDirection::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	auto const cont = Cast<AAIC_Foe>(owner_comp.GetAIOwner());
	APawn* PawnFoe = cont->GetPawn();
	UBlackboardComponent* Blackboard = cont->GetBlackboardComponent();
	FVector FoeLocation = PawnFoe->GetActorLocation();
	FVector newLocation  = PawnFoe->GetActorForwardVector() + ((Blackboard->GetValueAsVector(bb_keys::LastPlayerLocation) -FoeLocation)*DirectionLength).GetSafeNormal();
	Blackboard->SetValueAsVector(bb_keys::target_location, newLocation);
	DrawDebugLine(GetWorld(), FoeLocation, newLocation, FColor::Purple, true, -1.0f);
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
