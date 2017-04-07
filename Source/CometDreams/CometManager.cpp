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
	SpawnComet();

	
}

void ACometManager::SpawnComet()
{
	if (CometBP)
	{
		FActorSpawnParameters SpawnParams;

		AComet* CometRef = GetWorld()->SpawnActor<AComet>(CometBP, GetTransform(), SpawnParams);

		// Get a random color from the color list
		UStaticMeshComponent* CometMesh = Cast<UStaticMeshComponent>(CometRef->GetRootComponent());
		UMaterialInstanceDynamic* CometMaterial = UMaterialInstanceDynamic::Create(CometMesh->GetMaterial(0), this);
		CometMaterial->SetVectorParameterValue(CometColorParameterName, CometColors[0]);
		CometMesh->SetMaterial(0, CometMaterial);
	}
}

// Called every frame
void ACometManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACometManager::ShowSequence()
{

}

