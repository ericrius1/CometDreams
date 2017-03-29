// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "AstronautPawn.generated.h"

UCLASS()
class COMETDREAMS_API AAstronautPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAstronautPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UCameraComponent* MyCamera;

	/** How far can the player target comets? */
	UPROPERTY(EditAnywhere, Category = "Shooting")
	float TraceRangeForGaze;

	/** How long does the player need to gaze at a comet to charge and fire their laser in seconds? */
	UPROPERTY(EditAnywhere, Category = "Shooting")
	float ChargeTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	void GazeCheck();

	void Fire();

	bool bFiring;


	FTimerHandle ChargeLaserTimerHandler;

private:
	bool bLockedOntoComet;

	AActor* CurrentTarget = nullptr;



};
