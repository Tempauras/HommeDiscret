// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaygroundGenerator.h"
#include "DrawDebugHelpers.h"

// Sets default values
APlaygroundGenerator::APlaygroundGenerator()
{
	Params.Owner = this;
	Offset = 100.f;
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
	//CreateGrid();
	//PlacePointOnGrid();
}

void APlaygroundGenerator::SpawnPlayground()
{
	RandomTileHideout = FMath::RandRange(0, HorizontalTileNumber - 1);
	CrateNumber = (VerticalTileNumber * HorizontalTileNumber) % 2 == 0 ? (VerticalTileNumber * HorizontalTileNumber) / 2.5 : (VerticalTileNumber * HorizontalTileNumber) / 2.5 + 1;
	if (!FloorIsSet)
	{
		BaseLocation.X = Offset;
		BaseLocation.Y = Offset;
		FloorIsSet = true;

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

				if ((i == 0) && j == RandomTileHideout)
				{
					HideoutReferences = GetWorld()->SpawnActor<AHideout>(Hideout, FVector(BaseLocation.X - SizeOfTile, BaseLocation.Y - SizeOfTile, BaseLocation.Z), FRotator(0.f, 90.f, 0.f), Params);

					if (HideoutReferences != nullptr)
					{
						HideoutReferences->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
						TileList.Last()->bIsHoldingCrate = true;
					}
					
				}
			}
			BaseLocation.Y -= SizeOfTile * HorizontalTileNumber;
			BaseLocation.X += SizeOfTile;
		}
		GenerateTopWall();
		GenerateBottomWall();
		GenerateRightWall();
		GenerateLefttWall();

		while (ActualCrateNumber < CrateNumber)
		{
			SpawnCrates();
			ActualCrateNumber++;
		}
		FixHoles();
	}
}

void APlaygroundGenerator::GenerateTopWall()
{
	FVector WallStartLocation;
	WallStartLocation.Set(VerticalTileNumber * SizeOfTile, Offset, Offset);
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
}

void APlaygroundGenerator::GenerateBottomWall()
{
	FVector WallStartLocation;
	WallStartLocation.Set(0.f, Offset, Offset);
	FRotator WallRotation;
	WallRotation.Yaw = 90.f;
	WallRotation.Pitch = 0.f;
	WallRotation.Roll = 0.f;

	for (size_t i = 0; i < HeightTileNumber; i++)
	{
		for (size_t j = 0; j < HorizontalTileNumber; j++)
		{
			if (((i == 0) && (j != RandomTileHideout)) || i != 0)
			{
				AWall* SpawnedWall = GetWorld()->SpawnActor<AWall>(Wall, WallStartLocation, WallRotation, Params);
				WallStartLocation.Y += SizeOfTile;

				if (SpawnedWall != nullptr)
				{
					SpawnedWall->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
					WallList.Add(SpawnedWall);
				}
			}
			else
			{
				WallStartLocation.Y += SizeOfTile;
			}
		}
		WallStartLocation.Y -= SizeOfTile * HorizontalTileNumber;
		WallStartLocation.Z += SizeOfTile;
	}
}

void APlaygroundGenerator::GenerateRightWall()
{
	FVector WallStartLocation;
	WallStartLocation.Set(Offset, HorizontalTileNumber * SizeOfTile, Offset);

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
}

void APlaygroundGenerator::GenerateLefttWall()
{
	FVector WallStartLocation;
	WallStartLocation.Set(Offset, 0.f, Offset);

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
}

void APlaygroundGenerator::DespawnPlayground()
{
	if (TileList.Num() > 0)
	{
		for (AFloorTile* CurrentFloorTile : TileList)
		{
			CurrentFloorTile->Destroy();
		}
		TileList.Empty();
	}
	if (WallList.Num() > 0)
	{
		for (AWall* CurrentWallTile : WallList)
		{
			CurrentWallTile->Destroy();
		}
		WallList.Empty();
	}
	if (HideoutReferences != nullptr)
	{
		HideoutReferences->Destroy();
	}

	if (CrateList.Num() > 0)
	{
		for (ACrate* CurrentCrateTile : CrateList)
		{
			CurrentCrateTile->Destroy();
		}
		CrateList.Empty();
	}
	BaseLocation.X = 0.0f;
	BaseLocation.Y = 0.0f;
	FloorIsSet = false;
}

void APlaygroundGenerator::SpawnCrates()
{
	int RandomTile = FMath::RandRange(0, (VerticalTileNumber * HorizontalTileNumber) - 1);
	switch (IsTileAtWall(RandomTile))
	{
	case NearWhichWall::LEFT:
		if ((!TileList[RandomTile]->bIsHoldingCrate) && 
			(!TileList[RandomTile + 1]->bIsHoldingCrate) && 
			(!TileList[RandomTile + VerticalTileNumber]->bIsHoldingCrate) &&
			(!TileList[RandomTile - VerticalTileNumber]->bIsHoldingCrate))
		{
			UE_LOG(LogTemp, Warning, TEXT("LEFT | SPAWNCRATE"));
			ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[RandomTile]->GetCoordinate(), FRotator::ZeroRotator, Params);
			TileList[RandomTile]->bIsHoldingCrate = true;

			if (SpawnedCrate != nullptr)
			{
				SpawnedCrate->AttachToActor(TileList[RandomTile], FAttachmentTransformRules::KeepWorldTransform);
				CrateList.Add(SpawnedCrate);
			}
		}
		break;
	case NearWhichWall::RIGHT:
		if ((!TileList[RandomTile]->bIsHoldingCrate) &&
			(!TileList[RandomTile - 1]->bIsHoldingCrate) &&
			(!TileList[RandomTile + VerticalTileNumber]->bIsHoldingCrate) &&
			(!TileList[RandomTile - VerticalTileNumber]->bIsHoldingCrate))
		{
			UE_LOG(LogTemp, Warning, TEXT("RIGHT | SPAWNCRATE"));
			ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[RandomTile]->GetCoordinate(), FRotator::ZeroRotator, Params);
			TileList[RandomTile]->bIsHoldingCrate = true;

			if (SpawnedCrate != nullptr)
			{
				SpawnedCrate->AttachToActor(TileList[RandomTile], FAttachmentTransformRules::KeepWorldTransform);
				CrateList.Add(SpawnedCrate);
			}
		}
		break;
	case NearWhichWall::BOTTOM:
		if ((!TileList[RandomTile]->bIsHoldingCrate) &&
			(!TileList[RandomTile + 1]->bIsHoldingCrate) &&
			(!TileList[RandomTile - 1]->bIsHoldingCrate) &&
			(!TileList[RandomTile + VerticalTileNumber]->bIsHoldingCrate))
		{
			UE_LOG(LogTemp, Warning, TEXT("BOTTOM | SPAWNCRATE"));
			ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[RandomTile]->GetCoordinate(), FRotator::ZeroRotator, Params);
			TileList[RandomTile]->bIsHoldingCrate = true;

			if (SpawnedCrate != nullptr)
			{
				SpawnedCrate->AttachToActor(TileList[RandomTile], FAttachmentTransformRules::KeepWorldTransform);
				CrateList.Add(SpawnedCrate);
			}
		}
		break;
	case NearWhichWall::TOP:
		if ((!TileList[RandomTile]->bIsHoldingCrate) &&
			(!TileList[RandomTile + 1]->bIsHoldingCrate) &&
			(!TileList[RandomTile - 1]->bIsHoldingCrate) &&
			(!TileList[RandomTile - VerticalTileNumber]->bIsHoldingCrate))
		{
			UE_LOG(LogTemp, Warning, TEXT("TOP | SPAWNCRATE"));
			ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[RandomTile]->GetCoordinate(), FRotator::ZeroRotator, Params);
			TileList[RandomTile]->bIsHoldingCrate = true;

			if (SpawnedCrate != nullptr)
			{
				SpawnedCrate->AttachToActor(TileList[RandomTile], FAttachmentTransformRules::KeepWorldTransform);
				CrateList.Add(SpawnedCrate);
			}
		}
		break;
	case NearWhichWall::TOP_LEFT_CORNER:
		if ((!TileList[RandomTile]->bIsHoldingCrate) &&
			(!TileList[RandomTile + 1]->bIsHoldingCrate) &&
			(!TileList[RandomTile - VerticalTileNumber]->bIsHoldingCrate) &&
			(!TileList[RandomTile - VerticalTileNumber + 1]->bIsHoldingCrate))
		{
			UE_LOG(LogTemp, Warning, TEXT("TOP LEFT CORNER | SPAWNCRATE"));
			ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[RandomTile]->GetCoordinate(), FRotator::ZeroRotator, Params);
			TileList[RandomTile]->bIsHoldingCrate = true;

			if (SpawnedCrate != nullptr)
			{
				SpawnedCrate->AttachToActor(TileList[RandomTile], FAttachmentTransformRules::KeepWorldTransform);
				CrateList.Add(SpawnedCrate);
			}
		}
		break;
	case NearWhichWall::TOP_RIGHT_CORNER:
		if ((!TileList[RandomTile]->bIsHoldingCrate) &&
			(!TileList[RandomTile - 1]->bIsHoldingCrate) &&
			(!TileList[RandomTile - VerticalTileNumber]->bIsHoldingCrate) &&
			(!TileList[RandomTile - VerticalTileNumber - 1]->bIsHoldingCrate))
		{
			UE_LOG(LogTemp, Warning, TEXT("TOP RIGHT CORNER | SPAWNCRATE"));
			ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[RandomTile]->GetCoordinate(), FRotator::ZeroRotator, Params);
			TileList[RandomTile]->bIsHoldingCrate = true;

			if (SpawnedCrate != nullptr)
			{
				SpawnedCrate->AttachToActor(TileList[RandomTile], FAttachmentTransformRules::KeepWorldTransform);
				CrateList.Add(SpawnedCrate);
			}
		}
		break;
	case NearWhichWall::BOTTOM_LEFT_CORNER:
		if ((!TileList[RandomTile]->bIsHoldingCrate) &&
			(!TileList[RandomTile + 1]->bIsHoldingCrate) &&
			(!TileList[RandomTile + VerticalTileNumber]->bIsHoldingCrate) &&
			(!TileList[RandomTile + VerticalTileNumber + 1]->bIsHoldingCrate))
		{
			UE_LOG(LogTemp, Warning, TEXT("BOTTOM LEFT CORNER | SPAWNCRATE"));
			ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[RandomTile]->GetCoordinate(), FRotator::ZeroRotator, Params);
			TileList[RandomTile]->bIsHoldingCrate = true;

			if (SpawnedCrate != nullptr)
			{
				SpawnedCrate->AttachToActor(TileList[RandomTile], FAttachmentTransformRules::KeepWorldTransform);
				CrateList.Add(SpawnedCrate);
			}
		}
		break;
	case NearWhichWall::BOTTOM_RIGHT_CORNER:
		if ((!TileList[RandomTile]->bIsHoldingCrate) &&
			(!TileList[RandomTile - 1]->bIsHoldingCrate) &&
			(!TileList[RandomTile + VerticalTileNumber]->bIsHoldingCrate) &&
			(!TileList[RandomTile + VerticalTileNumber - 1]->bIsHoldingCrate))
		{
			UE_LOG(LogTemp, Warning, TEXT("BOTTOM RIGHT CORNER | SPAWNCRATE"));
			ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[RandomTile]->GetCoordinate(), FRotator::ZeroRotator, Params);
			TileList[RandomTile]->bIsHoldingCrate = true;

			if (SpawnedCrate != nullptr)
			{
				SpawnedCrate->AttachToActor(TileList[RandomTile], FAttachmentTransformRules::KeepWorldTransform);
				CrateList.Add(SpawnedCrate);
			}
		}
		break;
	case NearWhichWall::NONE:
		if ((!TileList[RandomTile]->bIsHoldingCrate) &&
			//(!TileList[RandomTile + 1]->bIsHoldingCrate) &&
			//(!TileList[RandomTile - 1]->bIsHoldingCrate) &&
			(!TileList[RandomTile + VerticalTileNumber]->bIsHoldingCrate) &&
			(!TileList[RandomTile - VerticalTileNumber]->bIsHoldingCrate) &&
			(!TileList[RandomTile + VerticalTileNumber + 1]->bIsHoldingCrate) &&
			(!TileList[RandomTile + VerticalTileNumber - 1]->bIsHoldingCrate) &&
			(!TileList[RandomTile - VerticalTileNumber + 1]->bIsHoldingCrate) &&
			(!TileList[RandomTile - VerticalTileNumber - 1]->bIsHoldingCrate))
		{
			UE_LOG(LogTemp, Warning, TEXT("NONE | SPAWNCRATE"));
			ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[RandomTile]->GetCoordinate(), FRotator::ZeroRotator, Params);
			TileList[RandomTile]->bIsHoldingCrate = true;

			if (SpawnedCrate != nullptr)
			{
				SpawnedCrate->AttachToActor(TileList[RandomTile], FAttachmentTransformRules::KeepWorldTransform);
				CrateList.Add(SpawnedCrate);
			}
		}
		break;
	}
}

void APlaygroundGenerator::FixHoles()
{
	for (AFloorTile* CurrentFloorTile : TileList)
	{
		if (!CurrentFloorTile->bIsHoldingCrate)
		{
			int CurrentTileNumber = TileList.Find(CurrentFloorTile);
			switch (IsTileAtWall(CurrentTileNumber))
			{
			case NearWhichWall::LEFT:
				if ((TileList[CurrentTileNumber + 1]->bIsHoldingCrate) &&
					(TileList[CurrentTileNumber + VerticalTileNumber]->bIsHoldingCrate) &&
					(TileList[CurrentTileNumber - VerticalTileNumber]->bIsHoldingCrate))
				{
					UE_LOG(LogTemp, Warning, TEXT("LEFT | FIX HOLE"));
					ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[CurrentTileNumber]->GetCoordinate(), FRotator::ZeroRotator, Params);
					TileList[CurrentTileNumber]->bIsHoldingCrate = true;

					if (SpawnedCrate != nullptr)
					{
						SpawnedCrate->AttachToActor(TileList[CurrentTileNumber], FAttachmentTransformRules::KeepWorldTransform);
						CrateList.Add(SpawnedCrate);
					}
				}
				break;
			case NearWhichWall::RIGHT:
				if ((TileList[CurrentTileNumber - 1]->bIsHoldingCrate) &&
					(TileList[CurrentTileNumber + VerticalTileNumber]->bIsHoldingCrate) &&
					(TileList[CurrentTileNumber - VerticalTileNumber]->bIsHoldingCrate))
				{
					UE_LOG(LogTemp, Warning, TEXT("RIGHT | FIX HOLE"));
					ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[CurrentTileNumber]->GetCoordinate(), FRotator::ZeroRotator, Params);
					TileList[CurrentTileNumber]->bIsHoldingCrate = true;

					if (SpawnedCrate != nullptr)
					{
						SpawnedCrate->AttachToActor(TileList[CurrentTileNumber], FAttachmentTransformRules::KeepWorldTransform);
						CrateList.Add(SpawnedCrate);
					}
				}
				break;
			case NearWhichWall::BOTTOM:
				if ((TileList[CurrentTileNumber + 1]->bIsHoldingCrate) &&
					(TileList[CurrentTileNumber - 1]->bIsHoldingCrate) &&
					(TileList[CurrentTileNumber + VerticalTileNumber]->bIsHoldingCrate))
				{
					UE_LOG(LogTemp, Warning, TEXT("BOTTOM | FIX HOLE"));
					ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[CurrentTileNumber]->GetCoordinate(), FRotator::ZeroRotator, Params);
					TileList[CurrentTileNumber]->bIsHoldingCrate = true;

					if (SpawnedCrate != nullptr)
					{
						SpawnedCrate->AttachToActor(TileList[CurrentTileNumber], FAttachmentTransformRules::KeepWorldTransform);
						CrateList.Add(SpawnedCrate);
					}
				}
				break;
			case NearWhichWall::TOP:
				if ((TileList[CurrentTileNumber + 1]->bIsHoldingCrate) &&
					(TileList[CurrentTileNumber - 1]->bIsHoldingCrate) &&
					(TileList[CurrentTileNumber - VerticalTileNumber]->bIsHoldingCrate))
				{
					UE_LOG(LogTemp, Warning, TEXT("TOP| FIX HOLE"));
					ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[CurrentTileNumber]->GetCoordinate(), FRotator::ZeroRotator, Params);
					TileList[CurrentTileNumber]->bIsHoldingCrate = true;

					if (SpawnedCrate != nullptr)
					{
						SpawnedCrate->AttachToActor(TileList[CurrentTileNumber], FAttachmentTransformRules::KeepWorldTransform);
						CrateList.Add(SpawnedCrate);
					}
				}
				break;
			case NearWhichWall::TOP_LEFT_CORNER:
				if ((TileList[CurrentTileNumber + 1]->bIsHoldingCrate) &&
					(TileList[CurrentTileNumber - VerticalTileNumber]->bIsHoldingCrate))
				{
					UE_LOG(LogTemp, Warning, TEXT("TOP LEFT CORNER | FIX HOLE"));
					ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[CurrentTileNumber]->GetCoordinate(), FRotator::ZeroRotator, Params);
					TileList[CurrentTileNumber]->bIsHoldingCrate = true;

					if (SpawnedCrate != nullptr)
					{
						SpawnedCrate->AttachToActor(TileList[CurrentTileNumber], FAttachmentTransformRules::KeepWorldTransform);
						CrateList.Add(SpawnedCrate);
					}
				}
				break;
			case NearWhichWall::TOP_RIGHT_CORNER:
				if ((TileList[CurrentTileNumber - 1]->bIsHoldingCrate) &&
					(TileList[CurrentTileNumber - VerticalTileNumber]->bIsHoldingCrate))
				{
					UE_LOG(LogTemp, Warning, TEXT("TOP RIGHT CORNER | FIX HOLE"));
					ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[CurrentTileNumber]->GetCoordinate(), FRotator::ZeroRotator, Params);
					TileList[CurrentTileNumber]->bIsHoldingCrate = true;

					if (SpawnedCrate != nullptr)
					{
						SpawnedCrate->AttachToActor(TileList[CurrentTileNumber], FAttachmentTransformRules::KeepWorldTransform);
						CrateList.Add(SpawnedCrate);
					}
				}
				break;
			case NearWhichWall::BOTTOM_LEFT_CORNER:
				if ((TileList[CurrentTileNumber + 1]->bIsHoldingCrate) &&
					(TileList[CurrentTileNumber + VerticalTileNumber]->bIsHoldingCrate))
				{
					UE_LOG(LogTemp, Warning, TEXT("BOTTOM LEFT CORNER | FIX HOLE"));
					ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[CurrentTileNumber]->GetCoordinate(), FRotator::ZeroRotator, Params);
					TileList[CurrentTileNumber]->bIsHoldingCrate = true;

					if (SpawnedCrate != nullptr)
					{
						SpawnedCrate->AttachToActor(TileList[CurrentTileNumber], FAttachmentTransformRules::KeepWorldTransform);
						CrateList.Add(SpawnedCrate);
					}
				}
				break;
			case NearWhichWall::BOTTOM_RIGHT_CORNER:
				if ((TileList[CurrentTileNumber - 1]->bIsHoldingCrate) &&
					(TileList[CurrentTileNumber + VerticalTileNumber]->bIsHoldingCrate))
				{
					UE_LOG(LogTemp, Warning, TEXT("BOTTOM RIGHT CORNER | FIX HOLE"));
					ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[CurrentTileNumber]->GetCoordinate(), FRotator::ZeroRotator, Params);
					TileList[CurrentTileNumber]->bIsHoldingCrate = true;

					if (SpawnedCrate != nullptr)
					{
						SpawnedCrate->AttachToActor(TileList[CurrentTileNumber], FAttachmentTransformRules::KeepWorldTransform);
						CrateList.Add(SpawnedCrate);
					}
				}
				break;
			case NearWhichWall::NONE:
				if ((TileList[CurrentTileNumber + 1]->bIsHoldingCrate) &&
					(TileList[CurrentTileNumber - 1]->bIsHoldingCrate) &&
					(TileList[CurrentTileNumber + VerticalTileNumber]->bIsHoldingCrate) &&
					(TileList[CurrentTileNumber - VerticalTileNumber]->bIsHoldingCrate))
				{
					UE_LOG(LogTemp, Warning, TEXT("NONE | FIX HOLE"));
					ACrate* SpawnedCrate = GetWorld()->SpawnActor<ACrate>(Crate, TileList[CurrentTileNumber]->GetCoordinate(), FRotator::ZeroRotator, Params);
					TileList[CurrentTileNumber]->bIsHoldingCrate = true;

					if (SpawnedCrate != nullptr)
					{
						SpawnedCrate->AttachToActor(TileList[CurrentTileNumber], FAttachmentTransformRules::KeepWorldTransform);
						CrateList.Add(SpawnedCrate);
					}
				}
				break;
			}
		}
	}
}

NearWhichWall APlaygroundGenerator::IsTileAtWall(int TileNumber)
{
	bool bIsLeftWall = false;
	bool bIsRightWall = false;
	bool bIsTopWall = false;
	bool bIsBottomWall = false;

	NearWhichWall NearWall = NearWhichWall::NONE;

	switch (TileNumber % VerticalTileNumber)
	{
	case 0:
		NearWall = NearWhichWall::LEFT;
		bIsLeftWall = true;
		break;
	case 14:
		NearWall = NearWhichWall::RIGHT;
		bIsRightWall = true;
		break;
	}

	if ((TileNumber >= 0) && (TileNumber < VerticalTileNumber))
	{
		NearWall = NearWhichWall::BOTTOM;
		bIsBottomWall = true;
	}

	if ((TileNumber >= (VerticalTileNumber * HorizontalTileNumber) - VerticalTileNumber) && (TileNumber < (VerticalTileNumber* HorizontalTileNumber)))
	{
		NearWall = NearWhichWall::TOP;
		bIsTopWall = true;
	}

	if (bIsTopWall && bIsLeftWall)
	{
		NearWall = NearWhichWall::TOP_LEFT_CORNER;
	}
	else if (bIsTopWall && bIsRightWall)
	{
		NearWall = NearWhichWall::TOP_RIGHT_CORNER;
	}
	else if (bIsBottomWall && bIsLeftWall)
	{
		NearWall = NearWhichWall::BOTTOM_LEFT_CORNER;
	}
	else if (bIsBottomWall && bIsRightWall)
	{
		NearWall = NearWhichWall::BOTTOM_RIGHT_CORNER;
	}

	return NearWall;
}

/*void APlaygroundGenerator::SpawnItem(UClass* ItemToSpawn)
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

				//DrawDebugPoint(GetWorld(), RandomPointInSquare, 5.0f, FColor::Red, true);
				//DrawDebugCircle(GetWorld(), RandomPointInSquare, Radius, 48, FColor::Red, true, -1.f, 0, 2.5f, FVector(0.0f, 1.0f, 0.0f), FVector(1.0f, 0.0f, 0.0f), true);
				float RandomYaw = FMath::FRandRange(0.f, 360.f);
				GetWorld()->SpawnActor<AActor>(Object, RandomPointInSquare, FRotator(0.0f, RandomYaw, 0.0f));
			}
			else
			{
				FirstBlockPassed = true;
			}
		}
	}
}*/

