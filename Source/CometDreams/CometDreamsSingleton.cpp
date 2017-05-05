// Fill out your copyright notice in the Description page of Project Settings.

#include "CometDreams.h"
#include "CometDreamsSingleton.h"




UCometDreamsSingleton::UCometDreamsSingleton()
{
    GlobalEventHandler = CreateDefaultSubobject<UGlobalEventHandler>(TEXT("EventHandler"));
}