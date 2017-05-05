// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "GlobalEventHandler.h"
#include "CometDreamsSingleton.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class COMETDREAMS_API UCometDreamsSingleton : public UObject
{
    GENERATED_BODY()

public:
    UCometDreamsSingleton();

    UPROPERTY(BlueprintReadOnly, Category = "Global Events")
    UGlobalEventHandler* GlobalEventHandler;
};
