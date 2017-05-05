// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "GlobalEventHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLevelEventDelegate_OnLevelComplete, uint8, LevelIndex);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStateEventDelegate_OnTransitionToCometSpecificMode);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Category = "Global Events" )
class COMETDREAMS_API UGlobalEventHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGlobalEventHandler();



    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
        FLevelEventDelegate_OnLevelComplete OnLevelComplete;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
        FGameStateEventDelegate_OnTransitionToCometSpecificMode OnTransitionToCometSpecificMode;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
