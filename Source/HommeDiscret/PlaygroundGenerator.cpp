// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaygroundGenerator.h"
#include "DrawDebugHelpers.h"

// Sets default values
APlaygroundGenerator::APlaygroundGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Params.Owner = this;
	Offset = 100.f;
	Radius = 35.0f;
	GridHeight = 50.0f;
	TopLeft = FVector(0.0f);
}

// Called when the game starts or when spawned
void APlaygroundGenerator::BeginPlay()
{
	Super::BeginPlay();
	if (!FloorIsSet)
	{
		SpawnPlayground();
	}
	//SpawnItem(Object);
	CreateGrid();
	PlacePointOnGrid();
}

void APlaygroundGenerator::SpawnPlayground()
{
	if (!FloorIsSet)
	{
		BaseLocation.X = Offset;
		BaseLocation.Y = Offset;
		FloorIsSet = true;
		RoomLength = HorizontalTileNumber * SizeOfTile;
		RoomWidth = VerticalTileNumber * SizeOfTile;
		BottomRight = FVector(RoomWidth, RoomLength, 0.0f);

		for (size_t i = 0; i < VerticalTileNumber; i++)
		{
			for (size_t j = 0; j < HorizontalTileNumber; j++)
			{

				AFloorTile* SpawnedTile = GetWorld()->SpawnActor<AFloorTile>(FloorTile, BaseLocation, BaseRotation, Params);
				BaseLocation.Y += SizeOfTile;

				if (SpawnedTile != nullptr)
				{
					SpawnedTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
					TileList.Add(SpawnedTile);
				}
			}
			BaseLocation.Y -= SizeOfTile * HorizontalTileNumber;
			BaseLocation.X += SizeOfTile;
		}

		GenerateTopWall();
		GenerateBottomWall();
		GenerateRightWall();
		GenerateLefttWall();
	}
}

void APlaygroundGenerator::GenerateTopWall()
{
	FVector WallStartLocation;
	WallStartLocation.Set(VerticalTileNumber * SizeOfTile, Offset, 0.f);
	FRotator WallRotation;
	WallRotation.Yaw = 90.f;
	WallRotation.Pitch = 0.f;
	WallRotation.Roll = 0.f;

	for (size_t i = 0; i < HeightTileNumber; i++)
	{
		for (size_t j = 0; j < HorizontalTileNumber; j++)
		{
			AWall* SpawnedWall = GetWorld()->SpawnActor<AWall>(Wall, WallStartLocation, WallRotation, Params);
			WallStartLocation.Y += SizeOfTile;

			if (SpawnedWall != nullptr)
			{
				SpawnedWall->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				WallList.Add(SpawnedWall);
			}
		}
		WallStartLocation.Y -= SizeOfTile * HorizontalTileNumber;
		WallStartLocation.Z += SizeOfTile;
	}
	WallStartLocation.Set(0.f, 0.f, 0.f);
}

void APlaygroundGenerator::GenerateBottomWall()
{
	FVector WallStartLocation;
	WallStartLocation.Set(0.f, Offset, 0.f);
	FRotator WallRotation;
	WallRotation.Yaw = 90.f;
	WallRotation.Pitch = 0.f;
	WallRotation.Roll = 0.f;

	for (size_t i = 0; i < HeightTileNumber; i++)
	{
		for (size_t j = 0; j < HorizontalTileNumber; j++)
		{
			AWall* SpawnedWall = GetWorld()->SpawnActor<AWall>(Wall, WallStartLocation, WallRotation, Params);
			WallStartLocation.Y += SizeOfTile;

			if (SpawnedWall != nullptr)
			{
				SpawnedWall->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				WallList.Add(SpawnedWall);
			}
		}
		WallStartLocation.Y -= SizeOfTile * HorizontalTileNumber;
		WallStartLocation.Z += SizeOfTile;
	}
	WallStartLocation.Set(0.f, 0.f, 0.f);
}

void APlaygroundGenerator::GenerateRightWall()
{
	FVector WallStartLocation;
	WallStartLocation.Set(Offset, HorizontalTileNumber * SizeOfTile, 0.f);

	for (size_t i = 0; i < HeightTileNumber; i++)
	{
		for (size_t j = 0; j < VerticalTileNumber; j++)
		{
			AWall* SpawnedWall = GetWorld()->SpawnActor<AWall>(Wall, WallStartLocation, FRotator::ZeroRotator, Params);
			WallStartLocation.X += SizeOfTile;

			if (SpawnedWall != nullptr)
			{
				SpawnedWall->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				WallList.Add(SpawnedWall);
			}
		}
		WallStartLocation.X -= SizeOfTile * VerticalTileNumber;
		WallStartLocation.Z += SizeOfTile;
	}
	WallStartLocation.Set(0.f, 0.f, 0.f);
}

void APlaygroundGenerator::GenerateLefttWall()
{
	FVector WallStartLocation;
	WallStartLocation.Set(Offset, 0.f, 0.f);

	for (size_t i = 0; i < HeightTileNumber; i++)
	{
		for (size_t j = 0; j < VerticalTileNumber; j++)
		{
			AWall* SpawnedWall = GetWorld()->SpawnActor<AWall>(Wall, WallStartLocation, FRotator::ZeroRotator, Params);
			WallStartLocation.X += SizeOfTile;

			if (SpawnedWall != nullptr)
			{
				SpawnedWall->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				WallList.Add(SpawnedWall);
			}
		}
		WallStartLocation.X -= SizeOfTile * VerticalTileNumber;
		WallStartLocation.Z += SizeOfTile;
	}
	WallStartLocation.Set(0.f, 0.f, 0.f);
}

void APlaygroundGenerator::DespawnPlayground()
{
	if (TileList.Num() > 0)
	{
		for (AFloorTile* CurrentFloorTile : TileList)
		{
			CurrentFloorTile->Destroy();
		}
		BaseLocation.X = 0.0f;
		BaseLocation.Y = 0.0f;
		TileList.Empty();
		FloorIsSet = false;
	}
	if (WallList.Num() > 0)
	{
		for (AWall* CurrentWallTile : WallList)
		{
			CurrentWallTile->Destroy();
		}
		WallList.Empty();
	}
}

void APlaygroundGenerator::SpawnItem(UClass* ItemToSpawn)
{
	float XCoordinate = FMath::FRandRange(XCoordinateMin, XCoordinateMax);
	float YCoordinate = FMath::FRandRange(YCoordinateMin, YCoordinateMax);

	float Yaw = FMath::FRandRange(0.0f, 360.0f);

	FVector SpawnLocation(XCoordinate, YCoordinate, 0.0f);
	FRotator SpawnRotation(0.0f, Yaw, 0.0f);

	GetWorld()->SpawnActor<AActor>(ItemToSpawn, SpawnLocation, SpawnRotation);
}

void APlaygroundGenerator::CreateGrid()
{
	for (int32 i = 0; i < VerticalTileNumber + 1; i++)
	{
		FVector Start = TopLeft + FVector(i * SizeOfTile, 0.0f, GridHeight);
		FVector End = Start + FVector(0.0f, RoomLength, GridHeight);
		DrawDebugLine(GetWorld(), Start, End, FColor::Blue, true, -1.0f, 0, 5.0f);
	}
	for (int32 i = 0; i < HorizontalTileNumber + 1; i++)
	{
		FVector Start = TopLeft + FVector(0.0f, i * SizeOfTile, GridHeight);
		FVector End = Start + FVector(RoomWidth, 0.0f, GridHeight);
		DrawDebugLine(GetWorld(), Start, End, FColor::Blue, true, -1.0f, 0, 5.0f);
	}
}

FVector APlaygroundGenerator::GetRandomPointInSquare(const FVector& UpperLeft, const FVector& LowerRight)
{
	float RandomX = FMath::FRandRange(UpperLeft.X, LowerRight.X);
	float RandomY = FMath::FRandRange(UpperLeft.Y, LowerRight.Y);

	return FVector(RandomX, RandomY, 0.0f);
}

void APlaygroundGenerator::PlacePointOnGrid()
{
	bool FirstBlockPassed = false;
	for (int32 i = 0; i < VerticalTileNumber; i++)
	{
		for (int32 j = 0; j < HorizontalTileNumber; j++)
		{
			if (FirstBlockPassed)
			{
				FVector UpperLeft(i * SizeOfTile + Radius, j * SizeOfTile + Radius, 0.0f);
				FVector LowerRight(i * SizeOfTile + SizeOfTile - Radius, j * SizeOfTile + SizeOfTile - Radius, 0.0f);
				FVector RandomPointInSquare = GetRandomPointInSquare(UpperLeft, LowerRight);

				DrawDebugPoint(GetWorld(), RandomPointInSquare, 5.0f, FColor::Red, true);
				DrawDebugCircle(GetWorld(), RandomPointInSquare, Radius, 48, FColor::Red, true, -1.f, 0, 2.5f, FVector(0.0f, 1.0f, 0.0f), FVector(1.0f, 0.0f, 0.0f), true);
				float RandomYaw = FMath::FRandRange(0.f, 360.f);
				//GetWorld()->SpawnActor<AActor>(Object, RandomPointInSquare, FRotator(0.0f, RandomYaw, 0.0f));
			}
			else
			{
				FirstBlockPassed = true;
			}
		}
	}
}

