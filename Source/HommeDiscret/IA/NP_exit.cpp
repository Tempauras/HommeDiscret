// Fill out your copyright notice in the Description page of Project Settings.


#include "NP_exit.h"
#include "Foe.h"

ANP_exit::ANP_exit()
{
	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(FName("SphereComponent"));
	RootComponent = CollisionSphere;

}

void ANP_exit::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->SetCollisionProfileName(FName("OverlapAll"));
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ANP_exit::CallbackComponentBeginOverlap);
}

void ANP_exit::CallbackComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AFoe::StaticClass()))
	{
		//Substract one to number of foes in the game (Game Mode)
		//Destroy Foe
		//DestroyActor(OtherActor);
	}
}
