// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "HDGameInstance.h"
#include "Chest.h"

// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//HDGameInstance* GameInstanceRef = Cast<HDGameInstance>(GEngine->GetWorld()->GetGameInstance());
	//Hungerbar = GameInstanceRef->Hungerbar;

	SphereRadius = 80.0f;
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT(" Sphere collision"));
	SphereCollision->InitSphereRadius(SphereRadius);
	SphereCollision->SetupAttachment(RootComponent);

	BaseStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base StaticMesh"));
	TopStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top StaticMesh"));
	BaseStaticMesh->SetupAttachment(RootComponent);
	TopStaticMesh->SetupAttachment(BaseStaticMesh);

	NumberFoodsContained = 0;
}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AChest::CallbackComponentBeginOverlap);
	MaxFoodsToWin = 5;
}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//DrawDebugSphere(GetWorld(),GetActorLocation(), SphereRadius,20,FColor::Purple,false,-1,0,1);
}

void AChest::AddingFood(AFood* FoodToAdd)
{
	NumberFoodsContained++;
	FoodToAdd->Destroy();
	if (NumberFoodsContained >= MaxFoodsToWin)
	{
		//Win Call GameMode
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("You won !"));
	}
}


void AChest::CallbackComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Overlap"));
	AFood* Food = Cast<AFood>(OtherActor);
	if (Food != nullptr)
	{
		AddingFood(Food);
	}
}

int AChest::GetNumberFoodsContained()
{
	return NumberFoodsContained;
}

int AChest::GetMaxFoodsToWin()
{
	return MaxFoodsToWin;
}

