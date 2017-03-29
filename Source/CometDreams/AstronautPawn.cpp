// Fill out your copyright notice in the Description page of Project Settings.

#include "CometDreams.h"
#include "AstronautPawn.h"


// Sets default values
AAstronautPawn::AAstronautPawn() : 
	bLockedOnToComet(false),
	ChargeTime(1100),
	TraceRangeForGaze(500)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));


}

// Called when the game starts or when spawned
void AAstronautPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAstronautPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GazeCheck();

}

// Called to bind functionality to input
void AAstronautPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AAstronautPawn::Fire);

}

void AAstronautPawn::GazeCheck()
{
	FHitResult HitResult;
	
	
	const FName TraceTag("MyTraceTag");
	GetWorld()->DebugDrawTraceTag = TraceTag;
	FCollisionQueryParams CollisionParams;
	CollisionParams.TraceTag = TraceTag;


	auto StartLocation = MyCamera->K2_GetComponentLocation();
	auto EndLocation = StartLocation + (MyCamera->GetForwardVector() * TraceRangeForGaze);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility,
		CollisionParams)
		)
	{
		if (HitResult.Actor->Tags.Contains("Comet") && !bLockedOnToComet)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("We are locked on to a comet!"));
			GetWorld()->GetTimerManager().SetTimer(ChargeLaserTimerHandler, this, &AAstronautPawn::Fire, ChargeTime, false);
			bLockedOnToComet = true;

		}
	}

}

void AAstronautPawn::Fire()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Fire Laser!!"));
}

