// Fill out your copyright notice in the Description page of Project Settings.

#include "CometDreams.h"
#include "CPP_PlayerCharacter.h"


// Sets default values
ACPP_PlayerCharacter::ACPP_PlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ACPP_PlayerCharacter::Fire);

}

void ACPP_PlayerCharacter::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("FIRE!"))
}
