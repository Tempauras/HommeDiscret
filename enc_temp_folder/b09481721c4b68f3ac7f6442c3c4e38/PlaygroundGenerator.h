// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorTile.h"
#include "Wall.h"
#include "Hideout.h"
#include "Crate.h"
#include "PlaygroundGenerator.generated.h"


UCLASS()
class HOMMEDISCRET_API APlaygroundGenerator : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APlaygroundGenerator();
	/*Reference the blueprint to generate the playground floor*/
	UPROPERTY(EditAnywhere, Category = "PlaygroundGeneration")
		TSubclassOf<AFloorTile> FloorTile;
	/*Reference the blueprint to generate the playground wall*/
	UPROPERTY(EditAnywhere, Category = "PlaygroundGeneration")
		TSubclassOf<AWall> Wall;
	UPROPERTY(EditAnywhere, Category = "PlaygroundGeneration")
		TSubclassOf<AHideout> Hideout;
	/*Size of the tile to align the creation correctly*/
	UPROPERTY(VisibleAnywhere)
		float SizeOfTile = 200;
	/*Set the number of vertical tile to create to fill the playground. MinValue = 10; MaxValue = 15*/
	UPROPERTY(EditAnywhere, Category = "PlaygroundGeneration", meta = (UIMin = "10", UIMax = "15"))
		int VerticalTileNumber = 10;
	/*Set the number of horizontal tile to create to fill the playground. MinValue = 10; MaxValue = 15*/
	UPROPERTY(EditAnywhere, Category = "PlaygroundGeneration", meta = (UIMin = "10", UIMax = "15"))
		int HorizontalTileNumber = 10;
	/*Height of the wall*/
	UPROPERTY(EditAnywhere, Category = "PlaygroundGeneration")
		int HeightTileNumber = 1;

	UPROPERTY(EditAnywhere, Category = "PlaygroundGeneration/Crates")
		TSubclassOf<ACrate> Crate;
		int CrateNumber;
	TArray<AFloorTile*> TileList;
	TArray<AWall*> WallList;
	TArray<ACrate*> CrateList;
	AHideout* HideoutReferences;

	AFloorTile* HideoutEntranceFloorTile;
	AFloorTile* EnemySpawnEntranceFloorTile;

	int RandomTileHideout;

	FActorSpawnParameters Params;
	bool FloorIsSet = false;
	FVector BaseLocation;
	FRotator BaseRotation;
	float Offset;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Object;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Generate the playground with the size specified in the VerticalTileNumber and HorizontalTileNumber. Doesn't do anything if the floor is already spawned.
	UFUNCTION(CallInEditor, Category = "PlaygroundGeneration")
		void SpawnPlayground();
	
	void GenerateTopWall();
	void GenerateBottomWall();
	void GenerateRightWall();
	void GenerateLefttWall();

	//Despawn the playground. Doesn't do anything if the floor isn't spawned.
	UFUNCTION(CallInEditor, Category = "PlaygroundGeneration")
		void DespawnPlayground();

	void SpawnCrates(UClass* CrateToSpawn);

	/*void SpawnItem(UClass* ItemToSpawn);

	void CreateGrid();

	FVector GetRandomPointInSquare(const FVector& UpperLeft, const FVector& LowerRight);

	void PlacePointOnGrid();*/
};
