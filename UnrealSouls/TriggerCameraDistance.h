// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TriggerCameraDistance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSOULS_API ATriggerCameraDistance : public AActor
{
	GENERATED_BODY()

	ATriggerCameraDistance(const class FObjectInitializer& ObjectInitializer);

	class UBoxComponent* boundingBox;
	
public:
	/*
	* These are not used atm.
	*/
	UPROPERTY(EditAnywhere, Category = "Trigger Properties")
		float triggerEnterDistance = 400.0f;
	UPROPERTY(EditAnywhere, Category = "Trigger Properties")
		float triggerEndDistance = 400.0f;
	UPROPERTY(EditAnywhere, Category = "Trigger Properties")
		float rateOfChange = 200.0f;

protected:
	UFUNCTION()
	void TriggerEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void TriggerExit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
