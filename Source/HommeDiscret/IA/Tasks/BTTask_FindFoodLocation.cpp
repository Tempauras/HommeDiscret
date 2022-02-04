// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindFoodLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HommeDiscret/IA/AIC_Foe.h"
#include "HommeDiscret/Level/Props/Food.h"
#include "Kismet/GameplayStatics.h"
#include "HommeDiscret/IA/Tasks/BB_keys.h"

UBTTask_FindFoodLocation::UBTTask_FindFoodLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Food Location");
}


EBTNodeResult::Type UBTTask_FindFoodLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	/*TSubclassOf<AActor> ClassToFind = AFood::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, Foods);*/

	AAIC_Foe* FoeController = Cast<AAIC_Foe>(owner_comp.GetAIOwner());
	UBlackboardComponent* Blackboard = FoeController->GetBlackboardComponent();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Overlap %s"),*Foods[0]->GetName()));
	//FVector NewTargetLocation = Foods[0]->GetActorLocation();

	Blackboard->SetValueAsVector(bb_keys::target_location, Blackboard->GetValueAsVector(bb_keys::LastFoodLocation));

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
