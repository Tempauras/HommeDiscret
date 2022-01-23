// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"
#include "MazeTile.h"

// Sets default values
AMazeGenerator::AMazeGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMazeGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	FVector SpawnPosition = GetActorLocation();

	for (int iRow = 0; iRow < RowNumber; iRow++)
	{
		SpawnPosition.X = GetActorLocation().X;
			for (int iCol = 0; iCol < ColumnNumber; iCol++)
			{
				//Spawn each tile
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.Owner = this;

				AMazeTile* SpawnedTile = GetWorld()->SpawnActor<AMazeTile>(TileToSwapClass, SpawnPosition, FRotator::ZeroRotator, SpawnParameters);

				if (SpawnedTile != nullptr)
				{
					SpawnedTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

					int32 TileIndex = iRow * ColumnNumber + iCol;

					SpawnedTile->Initialize(iRow, iCol, TileIndex);

					TileList.Add(SpawnedTile);
				}
				SpawnPosition.X += SizeOfTile;
			}
			SpawnPosition.Y += SizeOfTile;
	}

	//Generate Random tile to start with
	int32 RandomRow = FMath::RandRange(0, RowNumber - 1);
	int32 RandomCol = FMath::RandRange(0, ColumnNumber - 1);

	CurrentIndexTile = RandomRow * ColumnNumber + RandomCol;

	//Create first tile
	TileList[CurrentIndexTile]->SetIsCreated(true);
	TileList[CurrentIndexTile]->ShowFloor();
	TileList[CurrentIndexTile]->ShowWall(0);
	TileList[CurrentIndexTile]->ShowWall(1);
	TileList[CurrentIndexTile]->ShowWall(2);
	TileList[CurrentIndexTile]->ShowWall(3);

	//Add tile to the tileStack
	TileStack.Push(CurrentIndexTile);
	VisitedTiles = 1;
	//Start randomizing the maze
	bRandomizeMaze = true;
}

// Called every frame
void AMazeGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRandomizeMaze)
	{
		CurrentDeltaTime += DeltaTime;

		if (CurrentDeltaTime > WaitTimeBetweenCreateTiles)
		{
			CurrentDeltaTime = 0.0f;

			if (VisitedTiles < TileList.Num())
			{
				UE_LOG(LogTemp, Warning, TEXT("Adding Tile: %d / %d "), TileStack.Num(), TileList.Num());

				//Find neighbour and create passage for that tile
				int32 NextIndexTile = GetAdjacentTileWithWalls(CurrentIndexTile);

				if (NextIndexTile > -1)
				{
					TileStack.Push(CurrentIndexTile);
					CurrentIndexTile = NextIndexTile;
					VisitedTiles++;
				}
				else
				{
					if (TileStack.Num() > 0)
					{
						CurrentIndexTile = TileStack.Pop();
					}
					else
					{
						VisitedTiles = TileList.Num();
						UE_LOG(LogTemp, Warning, TEXT("Random Maze generation finished"));
						
						bRandomizeMaze = false;
					}
				}
				CurrentDeltaTime = 0.0f;
			}
			else
			{
				VisitedTiles = TileList.Num();
				bRandomizeMaze = false;
				UE_LOG(LogTemp, Warning, TEXT("Random Maze generation finished"), TileStack.Num());
			}
		}
	}
	//Create an entry and an exit
	TileList[0]->HideWall(2);
	TileList[RowNumber * ColumnNumber - 1]->HideWall(3);
}

int32 AMazeGenerator::GetAdjacentTileWithWalls(const int32& IndexTile)
{
	TArray<int32> NeighbourTiles;
	TArray<int32> Directions;

	//Coordinates of the given tile
	int32 Col = TileList[IndexTile]->GetCoords().X;
	int32 Row = TileList[IndexTile]->GetCoords().Y;

	//Add Available directions
	//To top
	if ((Row - 1) >= 0)
	{
		int32 Next = (Row - 1) * ColumnNumber + Col;
		if (TileList[Next]->AllWallsIntact()) //All walls up for this tile
		{
			Directions.Add(0);
			NeighbourTiles.Add(Next);
		}
	}

	//To Bottom
	if ((Row + 1) < RowNumber)
	{
		int32 Next = (Row + 1) * ColumnNumber + Col;

		if (TileList[Next]->AllWallsIntact()) //All walls up for this tile
		{
			Directions.Add(1);
			NeighbourTiles.Add(Next);
		}
	}

	//To Left
	if ((Col - 1) >= 0)
	{
		int32 Next = Row * ColumnNumber + (Col - 1);
		if (TileList[Next]->AllWallsIntact()) //All walls up for this tile
		{
			Directions.Add(2);
			NeighbourTiles.Add(Next);
		}
	}

	//To Right
	if ((Col + 1) < ColumnNumber)
	{
		int32 Next = Row * ColumnNumber + (Col + 1);

		if (TileList[Next]->AllWallsIntact()) //All walls up for tile
		{
			Directions.Add(3);
			NeighbourTiles.Add(Next);
		}
	}

	int32 NextTileIndex = -1;

	//Chose a randm direction among all the available.
	if (NeighbourTiles.Num() > 0)
	{
		int32 RandomDirection = FMath::RandRange(0, Directions.Num() - 1);

		NextTileIndex = NeighbourTiles[RandomDirection];

		if (!TileList[NextTileIndex]->GetIsCreated())
		{
			TileList[NextTileIndex]->SetIsCreated(true);
			//Show floor and walls
			TileList[NextTileIndex]->ShowFloor();
			TileList[NextTileIndex]->ShowWall(0);
			TileList[NextTileIndex]->ShowWall(1);
			TileList[NextTileIndex]->ShowWall(2);
			TileList[NextTileIndex]->ShowWall(3);
		}
		switch (Directions[RandomDirection])
		{
		case 0:
			TileList[NextTileIndex]->CreatePassage(1);
			TileList[IndexTile]->CreatePassage(0);
			break;
		case 1:
			TileList[NextTileIndex]->CreatePassage(0);
			TileList[IndexTile]->CreatePassage(1);
			break;
		case 2:
			TileList[NextTileIndex]->CreatePassage(3);
			TileList[IndexTile]->CreatePassage(2);
			break;
		case 3:
			TileList[NextTileIndex]->CreatePassage(2);
			TileList[IndexTile]->CreatePassage(3);
			break;
		}
	}
	return NextTileIndex;
}

bool AMazeGenerator::IsTileSurrounded(const int32& IndexTile)
{
	bool bIsSurrounded = false;

	bool bSurroundedTop = false;
	bool bSurroundedBottom = false;
	bool bSurroundedRight = false;
	bool bSurroundedLeft = false;

	//Coordinates of the given tile
	int32 Col = TileList[IndexTile]->GetCoords().X;
	int32 Row = TileList[IndexTile]->GetCoords().Y;

	//To top
	if ((Row - 1) >= 0)
	{
		bSurroundedTop = true;
	}
	//To Bottom
	if ((Row + 1) < RowNumber)
	{
		bSurroundedBottom = true;
	}
	//To Left
	if ((Col - 1) >= 0)
	{
		bSurroundedLeft = true;
	}
	//To Right
	if ((Col + 1) < ColumnNumber)
	{
		bSurroundedRight = true;
	}

	if (bSurroundedTop && bSurroundedBottom)
	{

	}

	return bIsSurrounded;
}

