// Fill out your copyright notice in the Description page of Project Settings.

#include "CometDreams.h"
#include "CometDreamsSingletonLibrary.h"


UCometDreamsSingletonLibrary::UCometDreamsSingletonLibrary()
{

}

UCometDreamsSingleton* UCometDreamsSingletonLibrary::GetCometDreamsData(bool& IsValid)
{
    IsValid = false;

    UCometDreamsSingleton* DataInstance = Cast<UCometDreamsSingleton>(GEngine->GameSingleton);

    if (!DataInstance) return NULL;
    if (!DataInstance->IsValidLowLevel()) return NULL;

    IsValid = true;
    return DataInstance;
}

