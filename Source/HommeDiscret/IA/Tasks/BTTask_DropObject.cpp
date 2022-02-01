// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DropObject.h"
#include "HommeDiscret/IA/AIC_Foe.h"
#include "HommeDiscret/IA/Foe.h"
#include "HommeDiscret/Level/Props/Food.h"
#include "HommeDiscret/Level/Props/FoodSpot.h"
#include "HommeDiscret/IA/Tasks/BB_keys.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_DropObject::UBTTask_DropObject(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("DropFood");
}


EBTNodeResult::Type UBTTask_DropObject::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{

	AAIC_Foe* FoeController = Cast<AAIC_Foe>(owner_comp.GetAIOwner());

	AFoe* Foe = Cast<AFoe>(FoeController->GetCharacter());
	UBlackboardComponent* Blackboard = FoeController->GetBlackboardComponent();
	FVector LastFoodLocation = Foe->DropFood();
	Blackboard->SetValueAsVector(bb_keys::LastFoodLocation, LastFoodLocation);

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Foe Drops %s"),*Foe->GetFoodRef()->GetName()));
	
	/*AFood* Food = Cast<AFood>(Foe->FoodRef);
	if (Food != nullptr)
	{
		USphereComponent* CollisionSphere = Cast<USphereComponent>(Food->GetComponentByClass(USphereComponent::StaticClass()));
		FVector LastFoodLocation = Food->GetActorLocation() + CollisionSphere->GetScaledSphereRadius() - 5.0f;
		Blackboard->SetValueAsVector(bb_keys::LastFoodLocation, LastFoodLocation);
		Foe->SetFoodRef(nullptr);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Food is NULL"));

	}*/
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
