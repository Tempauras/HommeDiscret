// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIFoe.generated.h"

/**
 * 
 */
UCLASS()
class HOMMEDISCRET_API AAIFoe : public AAIController
{
	GENERATED_BODY()

private:
	UStaticMeshComponent* staticMesh;
};
