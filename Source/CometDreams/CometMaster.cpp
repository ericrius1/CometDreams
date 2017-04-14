// Fill out your copyright notice in the Description page of Project Settings.

#include "CometDreams.h"
#include "CometMaster.h"


// Sets default values for this component's properties
UCometMaster::UCometMaster()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


    UIComet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UI Comet"));
    UIComet->AttachTo(this);


	// ...
}


// Called when the game starts
void UCometMaster::BeginPlay()
{
	Super::BeginPlay();
    ChangeColorUIComet();


	// ...
	
}

void UCometMaster::ChangeColorUIComet()
{
    //UStaticMeshComponent* CometMesh = Cast<UStaticMeshComponent>(CometRef->GetRootComponent());
    //UMaterialInstanceDynamic* CometMaterial = UMaterialInstanceDynamic::Create(CometMesh->GetMaterial(0), this);
    //CometMaterial->SetVectorParameterValue(CometColorParameterName, CometColors[0]);
    //CometMesh->SetMaterial(0, CometMaterial);

    UMaterialInstanceDynamic* CometMaterial = UMaterialInstanceDynamic::Create(UIComet->GetMaterial(0), this);
    CometMaterial->SetVectorParameterValue(CometColorParameterName, CometColors[0]);
    UIComet->SetMaterial(0, CometMaterial);
}


// Called every frame
void UCometMaster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

