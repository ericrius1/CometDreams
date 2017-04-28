// Fill out your copyright notice in the Description page of Project Settings.

#include "CometDreams.h"
#include "CometMaster.h"


// Sets default values for this component's properties
UCometMasterComponent::UCometMasterComponent(const FObjectInitializer& OI) :
    Super(OI),
    CurrentIndexInDisplaySequence(0),
    CurrentIndexInActualSequence(0),
    TimeBetweenSequenceItems(2.0f)
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    CorrectCometAudioComponent = OI.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Correct Comet Audio Component"));
    CorrectCometAudioComponent->SetupAttachment(this);
}


// Called when the game starts
void UCometMasterComponent::BeginPlay()
{
    Super::BeginPlay();
    CorrectCometAudioComponent->SetSound(CorrectCometSound);
    CurrentNumCometsInSequence = StartingNumCometsInSequence;


}

void UCometMasterComponent::Reset()
{
    CurrentNumCometsInSequence = StartingNumCometsInSequence;
    NewRound();
}

void UCometMasterComponent::SetupUIComet(UStaticMeshComponent* InUIComet)
{
    UIComet = InUIComet;
    UICometMaterial = UMaterialInstanceDynamic::Create(UIComet->GetMaterial(0), this);
    UIComet->SetMaterial(0, UICometMaterial);
}

void UCometMasterComponent::IncreaseDifficulty()
{
    CurrentNumCometsInSequence++;
}

void UCometMasterComponent::DestroyComet(AActor* Comet)
{
    AComet* CometToCheck = Cast<AComet>(Comet);
    FLinearColor Color;
    CometToCheck->CometMesh->GetMaterial(0)->GetVectorParameterValue(CometColorParameterName, Color);

    GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, FString::Printf(TEXT("Targeted Comet %f"), Color.R));
    GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, FString::Printf(TEXT("Sequence Comet %f"), CometSequence[CurrentIndexInDisplaySequence].R));


    if (Color.Equals(CometSequence[CurrentIndexInActualSequence]))
    {
        // We destroyed the correct comet!

        CorrectCometAudioComponent->Play();
        CurrentPitch += PitchIncrement;
        CorrectCometAudioComponent->SetFloatParameter(FName("pitch"), CurrentPitch);
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Destroyed Right Comet!!"));
        CurrentIndexInActualSequence++;
        if (CurrentIndexInActualSequence == CometSequence.Num())
        {
            GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, TEXT("Congrats you destroyed all the comets in this sequence!"));
            CurrentIndexInActualSequence = 0;
            UGameplayStatics::PlaySound2D(this, RoundCompleteSound);
            NewRound();
        }
    }
    Comet->Destroy();
}

void UCometMasterComponent::NewRound()
{
    DestroyAllComets();

    CurrentPitch = StartingPitch;


    UIComet->SetVisibility(false);
    FTimerDelegate NewRoundTimerCallback;
    NewRoundTimerCallback.BindLambda([this]
    {
        CreateSequence();
        PlaySequence();
    });

    GetWorld()->GetTimerManager().SetTimer(RoundWaitTimeHandle, NewRoundTimerCallback, TimeBetweenRounds, false);


}

void UCometMasterComponent::DestroyAllComets()
{
    GetWorld()->GetTimerManager().ClearTimer(CometSpawnerHandle);

    for (AComet* Comet : SpawnedComets)
    {
        Comet->Destroy();
    }

    SpawnedComets.Empty();

}


void UCometMasterComponent::SpawnComet()
{
    if (CometBP)
    {
        FActorSpawnParameters SpawnParams;
        FTransform CometSpawnPoint = GetOwner()->GetTransform();
        CometSpawnPoint.AddToTranslation(FVector(100, FMath::RandRange(-25, 25), FMath::RandRange(-25, 25)));
        AComet* NewComet = GetWorld()->SpawnActor<AComet>(CometBP, CometSpawnPoint, SpawnParams);

        int ColorIndex = FMath::Rand() % CometColors.Num();
        NewComet->ChangeMaterial(CometColors[ColorIndex]);
        SpawnedComets.Add(NewComet);
        GetWorld()->GetTimerManager().SetTimer(CometSpawnerHandle, this, &UCometMasterComponent::SpawnComet, SpawnIntervalTime, true);

    }
}

// Create a sequence of comets to be destroyed out of available colors that the player needs to remember
void UCometMasterComponent::CreateSequence()
{
    CurrentIndexInDisplaySequence = 0;
    CometSequence.Empty();
    if (CometColors.Num() > 0)
    {
        int PreviousColorIndex = -1;
        int ColorIndex = -1;
        for (int i = 0; i < CurrentNumCometsInSequence; i++)
        {

            while (ColorIndex == PreviousColorIndex)
            {
                // Ensures the next comet in the sequence has a different color than the last.
                ColorIndex = FMath::Rand() % CometColors.Num();
            }

            CometSequence.Add(CometColors[ColorIndex]);

            PreviousColorIndex = ColorIndex;

        }
    }

    UIComet->SetVisibility(true);


}

void UCometMasterComponent::PlaySequence()
{
    GetWorld()->GetTimerManager().ClearTimer(SequenceTimerHandle);
    if (CurrentIndexInDisplaySequence == CometSequence.Num())
    {
        CurrentIndexInDisplaySequence = 0;

        //Once sequence is finished playing we start spawning comets and make ui comet invisible
        UIComet->SetVisibility(false);
        SpawnComet();
    }

    else
    {
        ChangeColorUIComet(CometSequence[CurrentIndexInDisplaySequence]);
        CurrentIndexInDisplaySequence++;

        GetWorld()->GetTimerManager().SetTimer(SequenceTimerHandle, this, &UCometMasterComponent::PlaySequence, TimeBetweenSequenceItems, false);

    }

}

void UCometMasterComponent::ChangeColorUIComet(FLinearColor NewColor)
{

    UICometMaterial->SetVectorParameterValue(CometColorParameterName, NewColor);
}


// Called every frame
void UCometMasterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

