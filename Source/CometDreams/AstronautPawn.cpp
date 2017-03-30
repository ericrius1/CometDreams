// Fill out your copyright notice in the Description page of Project Settings.

#include "CometDreams.h"
#include "AstronautPawn.h"


// Sets default values
AAstronautPawn::AAstronautPawn() :
	bLockedOntoComet(false),
	ChargeTime(2),
	TraceRangeForGaze(500)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene Component"));

	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Game Camera"));

	LaserChargeSound = CreateDefaultSubobject<UAudioComponent>( TEXT("Laser Charge Sound"));
	LaserChargeSound->AttachToComponent(MyCamera, FAttachmentTransformRules::KeepRelativeTransform);

	Laser = CreateDefaultSubobject<UParticleSystemComponent>( TEXT("Laser Effect"));
	Laser->AttachToComponent(MyCamera, FAttachmentTransformRules::KeepRelativeTransform);



}

// Called when the game starts or when spawned
void AAstronautPawn::BeginPlay()
{
 	Super::BeginPlay();

	// Initialize Timeline
	if (ChargeCurve)
	{
		/* Contains the signature of the function that is going to 
		execute every time we tick our timeline. Think of this like a delegate*/
		FOnTimelineFloat ProgressFunction;


		/* Contains the signature of the function that is going to
		execute when the timeline finishes.*/
		FOnTimelineEvent FinishFunction;

		/* In order to bind the function to our ufunction we need to create an FName which contains the
		name of the function we want to call every time the timeline advances*/
		ProgressFunction.BindUFunction(this, FName("HandleChargingProgress"));

		FinishFunction.BindUFunction(this, FName("HandleChargingFinish"));


		ChargingTimeline.AddInterpFloat(ChargeCurve, ProgressFunction);
		ChargingTimeline.SetTimelineLength(ChargeTime);

		ChargingTimeline.SetTimelineFinishedFunc(FinishFunction);


	}

}

// Called every frame
void AAstronautPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GazeCheck();

	ChargingTimeline.TickTimeline(DeltaTime);


}

// Called to bind functionality to input
void AAstronautPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//InputComponent->BindAction("Fire", IE_Pressed, this, &AAstronautPawn::Fire);

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
		if (HitResult.Actor->Tags.Contains("Comet") && !bLockedOntoComet)
		{
			// We've locked onto a new comet!
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("We are locked on to a comet!"));
			bLockedOntoComet = true;

			LaserChargeSound->Play();

			// TIMELINE
			ChargingTimeline.PlayFromStart();
		}
	}
	else if (bLockedOntoComet) {
		bLockedOntoComet = false;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("We lost tracking on target	!"));

		ChargingTimeline.Stop();

	}


}

void AAstronautPawn::Fire()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Fire Laser!!"));
	bLockedOntoComet = false;

}

void AAstronautPawn::HandleChargingProgress(float value)
{
	// GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::SanitizeFloat(value));


}

void AAstronautPawn::HandleChargingFinish()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Charging Finished"));
	Fire();
}

