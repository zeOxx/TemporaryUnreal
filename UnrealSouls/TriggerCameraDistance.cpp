// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealSouls.h"
#include "UnrealSoulsCharacter.h"
#include "TriggerCameraDistance.h"

ATriggerCameraDistance::ATriggerCameraDistance(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	FVector boxExtent = FVector(200, 200, 200);

	boundingBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoundingBox"));
	boundingBox->bGenerateOverlapEvents = true;
	boundingBox->SetBoxExtent(boxExtent, false);
	RootComponent = boundingBox;

	// Adding overlaps
	boundingBox->OnComponentBeginOverlap.AddDynamic(this, &ATriggerCameraDistance::TriggerEnter);
	boundingBox->OnComponentEndOverlap.AddDynamic(this, &ATriggerCameraDistance::TriggerExit);
}

void ATriggerCameraDistance::TriggerEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUnrealSoulsCharacter* PlayerController = Cast<AUnrealSoulsCharacter>(OtherActor);

	// Calls for a distance change if the cast is successful
	if (PlayerController)
		PlayerController->setCameraDistance(triggerEnterDistance, rateOfChange);
}

void ATriggerCameraDistance::TriggerExit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AUnrealSoulsCharacter* PlayerController = Cast<AUnrealSoulsCharacter>(OtherActor);

	// Calls for a distance change if the cast is successful
	if (PlayerController)
		PlayerController->setCameraDistance(triggerEndDistance, rateOfChange);
}