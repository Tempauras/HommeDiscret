// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeTile.generated.h"

UCLASS()
class HOMMEDISCRET_API AMazeTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class UStaticMeshComponent* Floor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class UStaticMeshComponent* Wall_0; // Front Wall

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class UStaticMeshComponent* Wall_1; // Right Wall

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class UStaticMeshComponent* Wall_2; // Left Wall

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MazeCell")
		class UStaticMeshComponent* Wall_3; // Back Wall

public:	
	void Initialize(int32 Row, int32 Column, int32 Index);

	FORCEINLINE bool GetIsCreated() { return bCreated; };
	FORCEINLINE void SetIsCreated(bool Value) { bCreated = Value; };

	FORCEINLINE bool AllWallsIntact() { return (NumberWallsUp >= 4); };

	void HideFloor();

	void ShowFloor();

	void ShowWall(int32 WallIndex);

	void HideWall(int32 WallIndex);

	void CreatePassage(int32 WallIndex);


	FORCEINLINE FVector2D GetCoords()
	{
		return FVector2D(ColumnIndex, RowIndex); // X, Y
	}
private:
	bool bCreated;

	int32 ColumnIndex;
	int32 RowIndex;
	int32 NumberWallsUp = 0;
};
