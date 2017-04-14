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
    CreateSequence();



}

// Create a sequence of comets to be destroyed out of available colors that the player needs to remember
void UCometMaster::CreateSequence()
{
    if (CometColors.Num() > 0)
    {
        int ColorsIndex = FMath::Rand() % CometColors.Num();
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Color Index Number %i"), ColorsIndex));
        ChangeColorUIComet(ColorsIndex);
    }

}

void UCometMaster::ChangeColorUIComet(int ColorsIndex)
{

    UMaterialInstanceDynamic* CometMaterial = UMaterialInstanceDynamic::Create(UIComet->GetMaterial(0), this);
    CometMaterial->SetVectorParameterValue(CometColorParameterName, CometColors[ColorsIndex]);
    UIComet->SetMaterial(0, CometMaterial);
}


// Called every frame
void UCometMaster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

