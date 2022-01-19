// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenerateFloor.generated.h"

UCLASS()
class HOMMEDISCRET_API AGenerateFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerateFloor();
	/*Reference the blueprint to copy to generate the playground*/
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> FloorTile;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Object;
	/*Size of the tile to align the creation correctly*/
	UPROPERTY(VisibleAnywhere)
		float SizeOfTile = 200;
	/*Set the number of vertical tile to create to fill the playground. MinValue = 10; MaxValue=15*/
	UPROPERTY(EditAnywhere, Category = "PlaygroundSize", meta=(UIMin = "10", UIMax = "15"))
		int VerticalTileNumber = 10;
	/*Set the number of horizontal tile to create to fill the playground. MinValue = 10; MaxValue=15*/
	UPROPERTY(EditAnywhere, Category = "PlaygroundSize", meta = (UIMin = "10", UIMax = "15"))
		int HorizontalTileNumber = 10;
	FVector BaseLocation;
	FRotator BaseRotation;
	size_t CounterVertical = 0;
	size_t CounterHorizontal = 0;
	float XCoordinateMax = VerticalTileNumber * SizeOfTile;
	float YCoordinateMax = HorizontalTileNumber * SizeOfTile;
	float XCoordinateMin = 0.0f;
	float YCoordinateMin = 0.0f;
	float SquareWidth;
	float GridHeight;
	int32 GridSizeX;
	int32 GridSizeY;
	FVector TopLeft;
	FVector BottomRight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void SpawnItem(UClass* ItemToSpawn);

	void CreateGrid();
};
