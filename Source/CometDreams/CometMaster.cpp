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
    CometSequence.Empty();
    int NumCometsInSequence = FMath::RandRange(2, 4);
    if (CometColors.Num() > 0)
    {
        for (int i = 0; i < NumCometsInSequence; i++)
        {
            int ColorIndex = FMath::Rand() % CometColors.Num();
           // GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Color Index Number %i"), ColorsIndex));
            CometSequence.Add(CometColors[ColorIndex]);

        }
  

        ChangeColorUIComet(CometSequence[0]);
    }

}

void UCometMaster::ChangeColorUIComet(FColor NewColor)
{

    UMaterialInstanceDynamic* CometMaterial = UMaterialInstanceDynamic::Create(UIComet->GetMaterial(0), this);
    CometMaterial->SetVectorParameterValue(CometColorParameterName, NewColor);
    UIComet->SetMaterial(0, CometMaterial);
}


// Called every frame
void UCometMaster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

