// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerateFloor.h"

// Sets default values
AGenerateFloor::AGenerateFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GridSizeX = 5;
	GridSizeY = 5;
	GridHeight = 1.0f;
	SquareWidth = 100;
	TopLeft = FVector(0.0f);
	BottomRight = FVector(VerticalTileNumber * SizeOfTile, HorizontalTileNumber * SizeOfTile, 0.0f);
}

// Called when the game starts or when spawned
void AGenerateFloor::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, BaseRotation.ToString());
	for (size_t i = 0; i < VerticalTileNumber; i++)
	{
		for (size_t o = 0; o < HorizontalTileNumber; o++)
		{
			GetWorld()->SpawnActor<AActor>(FloorTile, BaseLocation, BaseRotation);
			BaseLocation.Y += SizeOfTile;
		}
		BaseLocation.Y -= SizeOfTile * HorizontalTileNumber;
		BaseLocation.X += SizeOfTile;
	}
	
	SpawnItem(Object);

}

void AGenerateFloor::SpawnItem(UClass* ItemToSpawn)
{
	float XCoordinate = FMath::FRandRange(XCoordinateMin, XCoordinateMax);
	float YCoordinate = FMath::FRandRange(YCoordinateMin, YCoordinateMax);

	float Yaw = FMath::FRandRange(0.0f, 360.0f);

	FVector SpawnLocation(XCoordinate, YCoordinate, 0.0f);
	FRotator SpawnRotation(0.0f, Yaw, 0.0f);

	GetWorld()->SpawnActor<AActor>(ItemToSpawn, SpawnLocation, SpawnRotation);
}

void AGenerateFloor::CreateGrid()
{
	for (int32 i = 0; i < GridSizeX; i++)
	{
		FVector Start = TopLeft + FVector(i * SquareWidth, 0.0f, GridHeight);
	}
}

