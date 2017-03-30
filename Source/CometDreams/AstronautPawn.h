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

	UPROPERTY()
		USceneComponent* RootSceneComponent;


	UPROPERTY(EditAnywhere)
		UCameraComponent* MyCamera;

	/** How far can the player target comets? */
	UPROPERTY(EditAnywhere, Category = "Firing")
		float TraceRangeForGaze;

	/** How long does the player need to gaze at a comet to charge and fire their laser in seconds? */
	UPROPERTY(EditAnywhere, Category = "Firing")
		float ChargeTime;

	/*Curve float reference*/
	UPROPERTY(EditAnywhere, Category = "Firing")
		UCurveFloat* ChargeCurve;

	UPROPERTY(EditAnywhere, Category = "Firing")
		UAudioComponent*  LaserChargeSound;

	UPROPERTY(EditAnywhere, Category = "Firing")
		UParticleSystemComponent* Laser;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void GazeCheck();

	void Fire();

	bool bFiring;



private:
	bool bLockedOntoComet;

	FTimeline ChargingTimeline;

	UFUNCTION()
		void HandleChargingProgress(float value);

	UFUNCTION()
		void HandleChargingFinish();



};
