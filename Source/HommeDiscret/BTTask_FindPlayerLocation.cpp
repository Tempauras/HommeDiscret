// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AIC_Foe.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BB_keys.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"


UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	//get player character and the npc's controller
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const cont = Cast<AAIC_Foe>(owner_comp.GetAIOwner());

	//get player location to use as an origin
	FVector const playerLocation = player->GetActorLocation();

	if (search_random)
	{
		FNavLocation loc;

		//get the navigation system and generate a random location on the NavMesh
		UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());

		if (nav_sys->GetRandomPointInNavigableRadius(playerLocation, search_radius, loc, nullptr))
		{
			cont->GetBlackboard()->SetValueAsVector(bb_keys::target_location, loc.Location);

		}
	}
	else {
		cont->GetBlackboard()->SetValueAsVector(bb_keys::target_location, playerLocation);
	}
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
