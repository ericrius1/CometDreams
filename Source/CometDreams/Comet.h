// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Comet.generated.h"

UCLASS()
class COMETDREAMS_API AComet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AComet();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

    UPROPERTY()
        USceneComponent* RootSceneComponent;


    UPROPERTY(VisibleAnywhere, Category = "Comet")
        UDestructibleComponent* CometMesh;

    UFUNCTION()
        void TakeHit();


    UFUNCTION()
        void ChangeMaterial(FLinearColor NewColor);

  

private:

    UMaterialInstanceDynamic* CometMaterial;  



	
};
