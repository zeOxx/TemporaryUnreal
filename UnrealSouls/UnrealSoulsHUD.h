// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "UnrealSoulsHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSOULS_API AUnrealSoulsHUD : public AHUD
{
	GENERATED_BODY()

	virtual void DrawHUD() override;

public:
	AUnrealSoulsHUD(const class FObjectInitializer& ObjectInitializer);
	
protected:
	void drawHealthBar();
	void drawStaminaBar();
	void drawPlayerIcon();
};
