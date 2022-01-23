// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeTile.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AMazeTile::AMazeTile()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootScene;

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	Floor->SetupAttachment(RootComponent);

	Wall_0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_0"));
	Wall_0->SetupAttachment(RootComponent);

	Wall_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_1"));
	Wall_1->SetupAttachment(RootComponent);

	Wall_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_2"));
	Wall_2->SetupAttachment(RootComponent);

	Wall_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_3"));
	Wall_3->SetupAttachment(RootComponent);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMazeTile::BeginPlay()
{
	Super::BeginPlay();
	
	NumberWallsUp = 4;
	bCreated = false;

	Floor->SetVisibility(false, true);
	Wall_0->SetVisibility(false, true);
	Wall_1->SetVisibility(false, true);
	Wall_2->SetVisibility(false, true);
	Wall_3->SetVisibility(false, true);
}


void AMazeTile::Initialize(int32 Row, int32 Column, int32 Index)
{
	bCreated = false;

	RowIndex = Row;
	ColumnIndex = Column;

	NumberWallsUp = 4;
}

void AMazeTile::HideFloor()
{
	Floor->SetVisibility(false, true);
}

void AMazeTile::ShowFloor()
{
	Floor->SetVisibility(true, true);
}

void AMazeTile::ShowWall(int32 WallIndex)
{
	switch (WallIndex)
	{
	case 0:
		Wall_0->SetVisibility(true, true); // Front Wall (ToTop) 
		Wall_0->SetCollisionProfileName(TEXT("BlockAll"));
		break;
	case 1:
		Wall_1->SetVisibility(true, true); // Back wall (ToDown)
		Wall_1->SetCollisionProfileName(TEXT("BlockAll"));
		break;
	case 2:
		Wall_2->SetVisibility(true, true); // Left wall (ToLeft)
		Wall_2->SetCollisionProfileName(TEXT("BlockAll"));
		break;
	case 3:
		Wall_3->SetVisibility(true, true); // Right wall (ToRight)
		Wall_3->SetCollisionProfileName(TEXT("BlockAll"));
		break;
	}
}

void AMazeTile::HideWall(int32 WallIndex)
{
	switch (WallIndex)
	{
	case 0:
		Wall_0->SetVisibility(false, true); // Front Wall (ToTop)
		Wall_0->SetCollisionProfileName(TEXT("OverlapAll"));
		break;
	case 1:
		Wall_1->SetVisibility(false, true); // Back wall (ToDown)
		Wall_1->SetCollisionProfileName(TEXT("OverlapAll"));
		break;
	case 2:
		Wall_2->SetVisibility(false, true); // Left wall (ToLeft)
		Wall_2->SetCollisionProfileName(TEXT("OverlapAll"));
		break;
	case 3:
		Wall_3->SetVisibility(false, true); // Right wall (ToRight)
		Wall_3->SetCollisionProfileName(TEXT("OverlapAll"));
		break;
	}
}

void AMazeTile::CreatePassage(int32 WallIndex)
{
	switch (WallIndex)
	{
	case 0:
		Wall_0->SetVisibility(false, true); // Front Wall (ToTop) 
		Wall_0->SetCollisionProfileName(TEXT("OverlapAll"));
		NumberWallsUp -= 1;
		break;
	case 1:
		Wall_1->SetVisibility(false, true); // Back wall (ToDown)
		Wall_1->SetCollisionProfileName(TEXT("OverlapAll"));
		NumberWallsUp -= 1;
		break;
	case 2:
		Wall_2->SetVisibility(false, true); // Left wall (ToLeft)
		Wall_2->SetCollisionProfileName(TEXT("OverlapAll"));
		NumberWallsUp -= 1;
		break;
	case 3:
		Wall_3->SetVisibility(false, true); // Right wall (ToRight)
		Wall_3->SetCollisionProfileName(TEXT("OverlapAll"));
		NumberWallsUp -= 1;
		break;
	}
}

