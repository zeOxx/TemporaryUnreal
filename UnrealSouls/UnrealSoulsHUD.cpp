// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealSouls.h"
#include "UnrealSoulsHUD.h"
#include "UnrealSoulsCharacter.h"

AUnrealSoulsHUD::AUnrealSoulsHUD(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	/*
		THIS CLASS IS CURRENLTY NOT IN USE, AS THE HUD IS HANDELED VIA BLUEPRINTS IN THE EDITOR
	*/
}

void AUnrealSoulsHUD::DrawHUD() 
{
	drawHealthBar();
	drawStaminaBar();
	//drawPlayerIcon();
}

void AUnrealSoulsHUD::drawHealthBar()
{
	DrawRect(FLinearColor::Red, 50.0f, 30.0f, 300.0f, 15.0f);
}

void AUnrealSoulsHUD::drawStaminaBar()
{
	DrawRect(FLinearColor::Green, 50.0f, 50.0f, 280.0f, 15.0f);
}

void AUnrealSoulsHUD::drawPlayerIcon()
{
	// DO STUFF
}