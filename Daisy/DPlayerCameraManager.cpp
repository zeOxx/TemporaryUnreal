// 2015, WeHeartGaming

#include "Daisy.h"
#include "DPlayerCameraManager.h"

ADPlayerCameraManager::ADPlayerCameraManager(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	normalFOV = 85.0f;

	ViewPitchMin = -80.0f;
	ViewPitchMax = 80.0f;
	bAlwaysApplyModifiers = true;
}

void ADPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	SetFOV(normalFOV);

	Super::UpdateCamera(DeltaTime);
}
