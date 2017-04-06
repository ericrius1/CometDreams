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



	/* How long does the laser display for before deactivating?*/
	UPROPERTY(EditAnywhere, Category = "Firing")
		float DisplayLaserTime;

	/* Charge Curve Time float reference*/
	UPROPERTY(EditAnywhere, Category = "Firing")
		UCurveFloat* ChargeCurve;

	/* Cursor Color Change curve reference*/
	UPROPERTY(EditAnywhere, Category = "Firing")
		UCurveLinearColor* CursorColorCurve;

	UPROPERTY(EditAnywhere, Category = "Firing")
		UAudioComponent*  LaserChargeSound;

	UPROPERTY(EditAnywhere, Category = "Firing")
		UAudioComponent* LaserShootSound;

	UPROPERTY(EditAnywhere, Category = "Firing")
		UParticleSystemComponent* Laser;

	UPROPERTY(EditAnywhere, Category = "Firing")
		UParticleSystemComponent* Cursor;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MovementSpeed;


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

	UFUNCTION()
		void DeactivateLaser();

	AActor* TargetedComet = nullptr;

	FTimerHandle ShowLaserTimerHandler;

	FLinearColor StartingCursorColor;





};
