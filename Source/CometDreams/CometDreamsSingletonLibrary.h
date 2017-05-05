// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CometDreamsSingleton.h"
#include "CometDreamsSingletonLibrary.generated.h"

/**
 * 
 */
UCLASS()
class COMETDREAMS_API UCometDreamsSingletonLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    UCometDreamsSingletonLibrary();


    UFUNCTION(BlueprintPure, Category = "Comet Dreams Singleton")
        static UCometDreamsSingleton* GetCometDreamsData(bool& IsValid);
	
	
	
	
};
