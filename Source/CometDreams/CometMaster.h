// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "Comet.h"
#include "CometDreamsSingleton.h"

#include "CometMaster.generated.h"


UENUM(BlueprintType)
enum class EGameState : uint8
{
    AnyComet      UMETA(DisplayName = "Any Comet"),
    SpecificComet UMETA(DisplayName = "Specific Comet"),
    CometSequence UMETA(DisplayName = "Comet Sequence")
};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class COMETDREAMS_API UCometMasterComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UCometMasterComponent(const FObjectInitializer& OI);

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    void ChangeColorUIComet(FLinearColor NewColor);


    UStaticMeshComponent* UIComet;

    //TODO : Write spawn comet method and keep track of when player has successfully destroyed comets in right order

private:


    FTimerHandle CometSpawnerHandle;

    FTimerHandle RoundWaitTimeHandle;

    UMaterialInstanceDynamic* UICometMaterial;


    FLinearColor CurrentTargetColor;

    UCometDreamsSingleton* CometDreamsSingletonInstance;


    float CurrentCometSpeed;

    int Score;

    int CurrentCometsZappedInSpecificMode;

    int CurrentColorIndex;

    int PreviousColorIndex;




public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
        EGameState GameState = EGameState::AnyComet;

    UFUNCTION()
        void SetupUIComet(UStaticMeshComponent* InUIComet);

    UFUNCTION(BlueprintCallable, Category = "Score")
        int GetScore() const;


    UFUNCTION()
        void SpawnComet();

    UFUNCTION()
        void DestroyComet(AActor* Comet);

    UFUNCTION()
        void IncreaseDifficulty();


    /* Make sure first element in this array is Red so UI instructions for destroying red comets works correctly */
    UPROPERTY(EditAnywhere, Category = "Comet")
        TArray<FLinearColor> CometColors;

    UPROPERTY(EditDefaultsOnly, Category = "Comet")
        FName CometColorParameterName;


    /* Blueprint Reference of Comet Class*/
    UPROPERTY(EditAnywhere, Category = "Comet")
        TSubclassOf<AComet> CometBP;



    UPROPERTY(EditAnywhere, Category = "Comet")
        float SpawnIntervalTime = 2.0f;

    UPROPERTY(EditAnywhere, Category = "Comet")
        float ForwardSpawnDistanceFromPlayer = 100.0f;


    UPROPERTY(EditAnywhere, Category = "Timing")
        float TimeBetweenRounds = 3.0f;

    UPROPERTY(EditAnywhere, Category = "Comet")
        USoundCue* CorrectCometSound;

    UPROPERTY(EditAnywhere, Category = "Comet")
        USoundCue* RoundCompleteSound;

    UPROPERTY(EditAnywhere, Category = "Comet")
        UAudioComponent* CorrectCometAudioComponent;


    UPROPERTY(EditAnywhere, Category = "Difficulty")
        float StartingCometSpeed;

    UPROPERTY(EditAnywhere, Category = "Difficulty")
        float DifficultyIncrementCometSpeed;




};
