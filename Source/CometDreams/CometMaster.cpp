// Fill out your copyright notice in the Description page of Project Settings.

#include "CometDreams.h"
#include "CometMaster.h"
#include "CometDreamsSingleton.h"


// Sets default values for this component's properties
UCometMasterComponent::UCometMasterComponent(const FObjectInitializer& OI) :
    Super(OI),
    StartingCometSpeed(10.0f),
    DifficultyIncrementCometSpeed(5.0f),
    Score(0)
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

    CurrentCometSpeed = StartingCometSpeed;
    CorrectCometAudioComponent->SetSound(CorrectCometSound);

}

void UCometMasterComponent::SetupUIComet(UStaticMeshComponent* InUIComet)
{
    UIComet = InUIComet;
    UICometMaterial = UMaterialInstanceDynamic::Create(UIComet->GetMaterial(0), this);
    UIComet->SetMaterial(0, UICometMaterial);


    //UI Comet should be invisible until the player destroys a comet
    UIComet->SetVisibility(false);
}

void UCometMasterComponent::IncreaseDifficulty()
{
    CurrentCometSpeed += DifficultyIncrementCometSpeed;
}

int UCometMasterComponent::GetScore() const
{
    return Score;
}

void UCometMasterComponent::DestroyComet(AActor* Comet)
{
    AComet* CometToCheck = Cast<AComet>(Comet);
    CometToCheck->TakeHit();
    Score++;

    if (GameState == EGameState::AnyComet)
    {
        GameState = EGameState::SpecificComet;
     
        UCometDreamsSingleton* DataInstance = Cast<UCometDreamsSingleton>(GEngine->GameSingleton);
        DataInstance->GlobalEventHandler->OnTransitionToCometSpecificMode.Broadcast();
        int ColorIndex = FMath::Rand() % CometColors.Num();
        CurrentTargetColor = CometColors[ColorIndex];
        UIComet->SetVisibility(true);
        ChangeColorUIComet(CurrentTargetColor);
    }

}


void UCometMasterComponent::SpawnComet()
{
    if (CometBP)
    {
        FActorSpawnParameters SpawnParams;
        FTransform CometSpawnPoint = GetOwner()->GetTransform();
        CometSpawnPoint.AddToTranslation(FVector(ForwardSpawnDistanceFromPlayer, FMath::RandRange(-25, 25), FMath::RandRange(-25, 25)));
        AComet* NewComet = GetWorld()->SpawnActor<AComet>(CometBP, CometSpawnPoint, SpawnParams);
        NewComet->SetSpeed(CurrentCometSpeed);

        int ColorIndex = FMath::Rand() % CometColors.Num();
        NewComet->ChangeMaterial(CometColors[ColorIndex]);
        GetWorld()->GetTimerManager().SetTimer(CometSpawnerHandle, this, &UCometMasterComponent::SpawnComet, SpawnIntervalTime, true);

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
}

