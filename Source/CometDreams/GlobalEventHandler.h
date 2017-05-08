// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "GlobalEventHandler.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStateEventDelegate_OnTransitionToCometSpecificMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStateEventDelegate_OnTransitionToSequenceMode);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStateEventDelegate_OnScoreIncrease);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Category = "Global Events" )
class COMETDREAMS_API UGlobalEventHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGlobalEventHandler();


    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events", meta = (DisplayName = "On Transition To Specific Comet Mode"))
        FGameStateEventDelegate_OnTransitionToCometSpecificMode OnTransitionToCometSpecificMode;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events", meta = (DisplayName = "On Transition To Sequence Mode"))
        FGameStateEventDelegate_OnTransitionToCometSpecificMode OnTransitionToSequenceMode;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events", meta = (DisplayName = "On Score Increase"))
        FGameStateEventDelegate_OnScoreIncrease OnScoreIncrease;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
