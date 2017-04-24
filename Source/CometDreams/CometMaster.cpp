// Fill out your copyright notice in the Description page of Project Settings.

#include "CometDreams.h"
#include "CometMaster.h"


// Sets default values for this component's properties
UCometMaster::UCometMaster() :
    CurrentIndexInSequence(0),
    TimeBetweenSequenceItems(2.0f)
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    UIComet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UI Comet"));
 
    UIComet->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
}


// Called when the game starts
void UCometMaster::BeginPlay()
{
    Super::BeginPlay();
    UICometMaterial = UMaterialInstanceDynamic::Create(UIComet->GetMaterial(0), this);
    UIComet->SetMaterial(0, UICometMaterial);

    CreateSequence();
    PlaySequence();
    SpawnComet();

}

void UCometMaster::SpawnComet()
{
    if (CometBP)
    {
        FActorSpawnParameters SpawnParams;
        FTransform CometSpawnPoint = GetOwner()->GetTransform();
        CometSpawnPoint.AddToTranslation(FVector(100, 0, 0));
        AComet* NewComet = GetWorld()->SpawnActor<AComet>(CometBP, CometSpawnPoint, SpawnParams);


    }
}

// Create a sequence of comets to be destroyed out of available colors that the player needs to remember
void UCometMaster::CreateSequence()
{
    CometSequence.Empty();
    int NumCometsInSequence = 4;
    if (CometColors.Num() > 0)
    {
        int PreviousColorIndex = -1;
        int ColorIndex = -1;
        for (int i = 0; i < NumCometsInSequence; i++)
        {

            while (ColorIndex == PreviousColorIndex)
            {
                // Ensures the next comet in the sequence has a different color than the last.
                ColorIndex = FMath::Rand() % CometColors.Num();
            }

            // GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Color Index Number %i"), ColorsIndex));
            CometSequence.Add(CometColors[ColorIndex]);

            PreviousColorIndex = ColorIndex;

        }
    }

}

void UCometMaster::PlaySequence()
{
    GetWorld()->GetTimerManager().ClearTimer(SequenceTimerHandle);
    if (CurrentIndexInSequence == CometSequence.Num())
    {
        CurrentIndexInSequence = 0;
    }

    else
    {
        GetWorld()->GetTimerManager().SetTimer(SequenceTimerHandle, this, &UCometMaster::PlaySequence, TimeBetweenSequenceItems, false);
        ChangeColorUIComet(CometSequence[CurrentIndexInSequence]);
        CurrentIndexInSequence++;
    }


}

void UCometMaster::ChangeColorUIComet(FColor NewColor)
{

    UICometMaterial->SetVectorParameterValue(CometColorParameterName, NewColor);
}


// Called every frame
void UCometMaster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

