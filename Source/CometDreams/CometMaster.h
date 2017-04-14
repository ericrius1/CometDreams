// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "CometMaster.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMETDREAMS_API UCometMaster : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCometMaster();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    void ChangeColorUIComet(FColor NewColor);

    void CreateSequence();

private:
    TArray<FColor> CometSequence;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


    UPROPERTY(EditDefaultsOnly, Category = "Comet")
        UStaticMeshComponent* UIComet;

    UPROPERTY(EditAnywhere, Category = "Comet")
        TArray<FColor> CometColors;

    UPROPERTY(EditDefaultsOnly, Category = "Comet")
        FName CometColorParameterName;

 
		
	
};
