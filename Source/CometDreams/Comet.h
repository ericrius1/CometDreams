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

	bool GetIsUIComet();

	void SetIsUIComet(bool NewIsUIComet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



private:

	// A UI comet is for showing player the sequence of comets to destroy
	bool IsUIComet;

	
};
