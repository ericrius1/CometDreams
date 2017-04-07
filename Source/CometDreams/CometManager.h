// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Comet.h"
#include "CometManager.generated.h"

UCLASS()
class COMETDREAMS_API ACometManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACometManager();

	UPROPERTY(EditAnywhere, Category = "Comet")
		TArray<FLinearColor> CometColors;

	/* Blueprint Reference of Comet Class*/
	UPROPERTY(EditDefaultsOnly, Category = "Comet")
		TSubclassOf<AComet> CometBP;

	UFUNCTION()
		void SpawnComet();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ShowSequence();



};
