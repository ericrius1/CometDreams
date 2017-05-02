// Fill out your copyright notice in the Description page of Project Settings.

#include "CometDreams.h"
#include "Comet.h"


// Sets default values
AComet::AComet()
{
    RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene Component"));

    CometMesh = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Comet Mesh"));
    CometMesh->AttachToComponent(RootSceneComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AComet::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.Add("Comet");

    CometMaterial = UMaterialInstanceDynamic::Create(CometMesh->GetMaterial(0), this);
    CometMesh->SetMaterial(0, CometMaterial);

}

void AComet::ChangeMaterial(FLinearColor NewColor)
{
    CometMaterial->SetVectorParameterValue(FName("Comet Color"), NewColor);
}

void AComet::TakeHit()
{
    CometMesh->ApplyRadiusDamage(10.0f, CometMesh->GetComponentLocation(), 100.0f, 10.0f, true);
}



