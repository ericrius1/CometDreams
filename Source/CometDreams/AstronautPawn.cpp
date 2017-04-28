// Fill out your copyright notice in the Description page of Project Settings.

#include "CometDreams.h"
#include "AstronautPawn.h"


// Sets default values
AAstronautPawn::AAstronautPawn(const FObjectInitializer& OI) :
    Super(OI),
	bLockedOntoComet(false),
	TraceRangeForGaze(500),
	DisplayLaserTime(0.5),
	MovementSpeed(1)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene Component"));

	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Game Camera"));

	LaserChargeSound = CreateDefaultSubobject<UAudioComponent>(TEXT("Laser Charge Sound"));
	LaserChargeSound->AttachToComponent(MyCamera, FAttachmentTransformRules::KeepRelativeTransform); 

	LaserShootSound = CreateDefaultSubobject<UAudioComponent>(TEXT("Laser Shoot Sound"));
	LaserShootSound->AttachToComponent(MyCamera, FAttachmentTransformRules::KeepRelativeTransform);

	Laser = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser Effect"));
	Laser->AttachToComponent(MyCamera, FAttachmentTransformRules::KeepRelativeTransform);

 



	Cursor = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Cursor"));
	Cursor->AttachToComponent(MyCamera, FAttachmentTransformRules::KeepRelativeTransform);

    CometMaster = OI.CreateDefaultSubobject<UCometMasterComponent>(this, TEXT("CometMasterComponent"));
    CometMaster->AttachToComponent(MyCamera, FAttachmentTransformRules::KeepRelativeTransform);

    UIComet = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("UI Comet"));
    UIComet->AttachToComponent(CometMaster, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AAstronautPawn::BeginPlay()
{
	checkf(ChargeCurve && CursorColorCurve, TEXT("Charge Curve and CursorColorCurve not provided in AstronaughtPawn Blueprint!!"));

	Super::BeginPlay();


	// Initialize Timeline
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

	ChargingTimeline.SetTimelineFinishedFunc(FinishFunction);

	StartingCursorColor = CursorColorCurve->GetLinearColorValue(0.0);
	Cursor->SetColorParameter(FName("CursorColor"), StartingCursorColor);

    CometMaster->SetupUIComet(UIComet);



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

	InputComponent->BindAction("Increase Difficulty", IE_Pressed, this, &AAstronautPawn::IncreaseDifficulty);

}

void AAstronautPawn::ResetGame()
{   
    DifficultyLevel = 0;
    CometMaster->Reset();

}

void AAstronautPawn::IncreaseDifficulty()
{
    CometMaster->IncreaseDifficulty();
    CometMaster->NewRound();

    DifficultyLevel++;
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
		ECollisionChannel::ECC_Visibility)
		//CollisionParams)
		)
	{
		if (HitResult.Actor->Tags.Contains("Comet"))
		{
			if (!TargetedComet)
			{
				// We've locked onto a new comet after gazing into empty space
				//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("We are locked on to comet %s"), *HitResult.Actor.Get()->GetName()));
				bLockedOntoComet = true;
				LaserChargeSound->Play();

				ChargingTimeline.PlayFromStart();
			}

			// Either way we set a new targeted comet
			TargetedComet = HitResult.Actor.Get();

		}
	}

	// We were locked onto comet and now we looked away from it into space
	else if (bLockedOntoComet) {
		bLockedOntoComet = false;

		ChargingTimeline.Stop();

		TargetedComet = nullptr;

		LaserChargeSound->Stop();

		Cursor->SetColorParameter(FName("CursorColor"), StartingCursorColor);

	}

}

void AAstronautPawn::Fire()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Fire Laser!!"));
	bLockedOntoComet = false;

	Laser->ActivateSystem();

	LaserShootSound->Play();

	GetWorld()->GetTimerManager().SetTimer(ShowLaserTimerHandler, this, &AAstronautPawn::DeactivateLaser, DisplayLaserTime, false);

    CometMaster->DestroyComet(TargetedComet);
	TargetedComet = nullptr;

	Cursor->SetColorParameter(FName("CursorColor"), StartingCursorColor);

}

void AAstronautPawn::HandleChargingProgress(float value)
{

	FLinearColor CurrentCursorColor = CursorColorCurve->GetLinearColorValue(ChargingTimeline.GetPlaybackPosition());
	Cursor->SetColorParameter(FName("CursorColor"), CurrentCursorColor);

}

void AAstronautPawn::HandleChargingFinish()
{
	Fire();
}

void AAstronautPawn::DeactivateLaser()
{
	Laser->DeactivateSystem();
}

