// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorTile.h"
#include "Wall.h"
#include "PlaygroundGenerator.generated.h"


UCLASS()
class HOMMEDISCRET_API APlaygroundGenerator : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APlaygroundGenerator();
	/*Reference the blueprint to generate the playground floor*/
	UPROPERTY(EditAnywhere)
		TSubclassOf<AFloorTile> FloorTile;
	/*Reference the blueprint to generate the playground wall*/
	UPROPERTY(EditAnywhere)
		TSubclassOf<AWall> Wall;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Object;
	/*Size of the tile to align the creation correctly*/
	UPROPERTY(VisibleAnywhere)
		float SizeOfTile = 200;
	/*Set the number of vertical tile to create to fill the playground. MinValue = 10; MaxValue = 15*/
	UPROPERTY(EditAnywhere, Category = "PlaygroundGeneration", meta = (UIMin = "10", UIMax = "15"))
		int VerticalTileNumber = 10;
	/*Set the number of horizontal tile to create to fill the playground. MinValue = 10; MaxValue = 15*/
	UPROPERTY(EditAnywhere, Category = "PlaygroundGeneration", meta = (UIMin = "10", UIMax = "15"))
		int HorizontalTileNumber = 10;
	/*Set the number of tile to create the wall. MinValue = 5; MaxValue = 10*/
	UPROPERTY(EditAnywhere, Category = "PlaygroundGeneration", meta = (UIMin = "5", UIMax = "10"))
		int HeightTileNumber = 5;
	TArray<AFloorTile*> TileList;
	TArray<AWall*> WallList;
	FActorSpawnParameters Params;
	bool FloorIsSet = false;
	FVector BaseLocation;
	FRotator BaseRotation;
	size_t CounterVertical = 0;
	size_t CounterHorizontal = 0;
	float Offset;
	float XCoordinateMax = VerticalTileNumber * SizeOfTile;
	float YCoordinateMax = HorizontalTileNumber * SizeOfTile;
	float XCoordinateMin = 0.0f;
	float YCoordinateMin = 0.0f;
	float GridHeight;
	float RoomLength;
	float RoomWidth;
	float Radius;
	FVector TopLeft;
	FVector BottomRight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Generate the maze with the size specified in the VerticalTileNumber and HorizontalTileNumber. Doesn't do anything if the floor is already spawned.
	UFUNCTION(CallInEditor, Category = "PlaygroundGeneration")
		void SpawnPlayground();
	
	void GenerateTopWall();
	void GenerateBottomWall();
	void GenerateRightWall();
	void GenerateLefttWall();

	//Despawn the maze. Doesn't do anything if the floor isn't spawned.
	UFUNCTION(CallInEditor, Category = "PlaygroundGeneration")
		void DespawnPlayground();

	void SpawnItem(UClass* ItemToSpawn);

	void CreateGrid();

	FVector GetRandomPointInSquare(const FVector& UpperLeft, const FVector& LowerRight);

	void PlacePointOnGrid();
};
