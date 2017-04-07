// Fill out your copyright notice in the Description page of Project Settings.

#include "CometDreams.h"
#include "Comet.h"


// Sets default values
AComet::AComet() :
	IsUIComet(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AComet::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.Add("Comet");

	
}

// Called every frame
void AComet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

bool AComet::GetIsUIComet()
{
	return IsUIComet;
	
}

void AComet::SetIsUIComet(bool NewIsUIComet)
{
	IsUIComet = NewIsUIComet;

	if (IsUIComet)
	{
		
		// UI comets are not targetable or destroyable. They are just for showing player sequence
		Tags.Remove(FName("Comet"));
		Tags.Add(FName("UIComet"));
		
	}
}
