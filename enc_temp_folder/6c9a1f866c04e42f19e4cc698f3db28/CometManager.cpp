// Fill out your copyright notice in the Description page of Project Settings.

#include "CometDreams.h"
#include "CometManager.h"


// Sets default values
ACometManager::ACometManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACometManager::BeginPlay()
{
	Super::BeginPlay();

	
}

void ACometManager::SpawnComet()
{
	if (CometBP)
	{
		FActorSpawnParameters SpawnParams;

		AComet* CometRef = GetWorld()->SpawnActor<AComet>(CometBP, GetTransform(), SpawnParams);
	}
}

// Called every frame
void ACometManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

