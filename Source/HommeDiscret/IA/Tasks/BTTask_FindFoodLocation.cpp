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
	TSubclassOf<AActor> ClassToFind = AFood::StaticClass();
	TArray<AActor*> Foods;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, Foods);

	AAIC_Foe* FoeController = Cast<AAIC_Foe>(owner_comp.GetAIOwner());
	UBlackboardComponent* Blackboard = FoeController->GetBlackboardComponent();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Overlap %s"),*Foods[0]->GetName()));
	FVector NewTargetLocation = Cast<AFood>(Foods[0])->GetRealLocation();

	Blackboard->SetValueAsVector(bb_keys::LastFoodLocation, NewTargetLocation);

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
