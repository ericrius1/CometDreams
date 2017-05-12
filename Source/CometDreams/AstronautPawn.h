// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CometMaster.h"
#include "AstronautPawn.generated.h"

UCLASS(Blueprintable)
class COMETDREAMS_API AAstronautPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAstronautPawn(const FObjectInitializer& OI);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
		USceneComponent* RootSceneComponent;

    UPROPERTY(EditAnywhere , BlueprintReadWrite)
        UCometMasterComponent* CometMaster;



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

    /* Cursor Size Change curve reference*/
    UPROPERTY(EditAnywhere, Category = "Firing")
        UCurveFloat* CursorSizeCurve;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		UAudioComponent*  LaserChargeSound;

    UPROPERTY(VisibleAnywhere, Category = "Firing")
        UStaticMeshComponent*  UIComet;


	UPROPERTY(EditAnywhere, Category = "Firing")
		UAudioComponent* LaserShootSound;

	UPROPERTY(EditAnywhere, Category = "Firing")
		UParticleSystemComponent* Laser;

	UPROPERTY(EditAnywhere, Category = "Firing")
		UParticleSystemComponent* Cursor;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MovementSpeed;


  
    /* Time laser takes to charge and fire. Make sure this value is equal to the time of the Charge Curve. This won't 
    actually change charge time- it's just used to coordinate with other curves like cursor color and size change as laser charges*/
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
        float LaserChargeTime = 2.0f;


    UPROPERTY(EditAnywhere, Category = "Firing")
        float LaserChargeTimeDecreaseOnCometSpeedIncrease;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



    UPROPERTY(EditAnywhere)
        UCameraComponent* MyCamera;

	void GazeCheck();

	void Fire();

    void IncreaseDifficulty();

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

    FTimerHandle NewRoundWaitTimeHandler;

	FLinearColor StartingCursorColor;

    float StartingCursorSize;

    FDateTime MyDateTime;

    float CurrentTime;

    float PreviousTime;

    int PauseTimeNeededToTriggerHMDReset = 2.0f;

};
