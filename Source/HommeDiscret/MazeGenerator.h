// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.generated.h"

UCLASS()
class HOMMEDISCRET_API AMazeGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Maze Settings")
		TSubclassOf<class AMazeTile> TileToSwapClass = nullptr;

	/*Set the number of vertical tile to create to fill the playground. MinValue = 10; MaxValue=15*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Settings", meta = (UIMin = "10", UIMax = "15"))
		int32 ColumnNumber = 10;

	/*Set the number of horizontal tile to create to fill the playground. MinValue = 10; MaxValue=15*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Settings", meta = (UIMin = "10", UIMax = "15"))
		int32 RowNumber = 10;

	/*Size of the tile to align the creation correctly*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Maze Settings")
		float SizeOfTile = 200;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Settings")
		float WaitTimeBetweenCreateTiles = 0.05f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TArray<AMazeTile*> TileList;

	bool bRandomizeMaze = false;
	float CurrentDeltaTime = 0.0f;

	int32 VisitedTiles;
	TArray<int32>TileStack;
	int32 CurrentIndexTile;

	int32 GetAdjacentTileWithWalls(const int32& IndexTile);
	void GetNumberOfAdjacentTile(const int32& IndexTile, TArray<int32> Directions, TArray<int32> NeighbourTiles);
	bool IsTileSurrounded(const int32& IndexTile);
};
