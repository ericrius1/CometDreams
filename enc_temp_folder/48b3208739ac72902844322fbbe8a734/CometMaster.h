// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "Comet.h"
#include "CometMaster.generated.h"


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

    void CreateSequence();

    UFUNCTION()
        void PlaySequence();

    UFUNCTION()
        void SpawnComet();


        UStaticMeshComponent* UIComet;

    //TODO : Write spawn comet method and keep track of when player has successfully destroyed comets in right order

private:
    TArray<FLinearColor> CometSequence;

    FTimerHandle SequenceTimerHandle;

    FTimerHandle CometSpawnerHandle;

    UMaterialInstanceDynamic* UICometMaterial;


    int CurrentIndexInDisplaySequence;

    //Where are we in terms of which comets have actually been destroyed?
    int CurrentIndexInActualSequence;


public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION()
        void SetupUIComet(UStaticMeshComponent* InUIComet);
    
    UFUNCTION()
        void DestroyComet(AActor* Comet);

    UPROPERTY(EditAnywhere, Category = "Comet")
        TArray<FLinearColor> CometColors;

    UPROPERTY(EditDefaultsOnly, Category = "Comet")
        FName CometColorParameterName;

    UPROPERTY(EditDefaultsOnly, Category = "Comet")
        float TimeBetweenSequenceItems;

    /* Blueprint Reference of Comet Class*/
    UPROPERTY(EditAnywhere, Category = "Comet")
        TSubclassOf<AComet> CometBP;

    /* How many comets the player needs to memorize and destroy in correct order */
    UPROPERTY(EditAnywhere, Category = "Comet")
        int NumCometsInSequence = 2;

    UPROPERTY(EditAnywhere, Category = "Comet")
        float SpawnIntervalTime = 2.0f;




};