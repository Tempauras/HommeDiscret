// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIC_Foe.generated.h"

/**
 * 
 */
class AFoodSpot;
UCLASS()
class HOMMEDISCRET_API AAIC_Foe : public AAIController
{
	GENERATED_BODY()
	
public:
	AAIC_Foe(FObjectInitializer const& object_initializer = FObjectInitializer::Get());
	void BeginPlay() override;
	void OnPossess(APawn* const pawn) override;
	class UBlackboardComponent* get_blackboard() const;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector EntranceLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector  ExitLocation;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
		FVector OriginLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<AFoodSpot*> FoodSpots;

	AFoodSpot* GetOneRandomFoodSpot();

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* Btree;

	class UBlackboardComponent* Blackboard;

	class UAISenseConfig_Sight* SightConfig;

	UFUNCTION()
		void OnTargetDetected(AActor* actor, FAIStimulus const stimulus);
		void SetupPerceptionSystem();
		void FindFoodSpots();
};
