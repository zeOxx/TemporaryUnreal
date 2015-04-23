// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealSouls.h"
#include "UnrealSoulsGameMode.h"
#include "UnrealSoulsCharacter.h"
#include "UnrealSoulsHUD.h"

AUnrealSoulsGameMode::AUnrealSoulsGameMode(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Setting the player character
	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerCharacter(TEXT("/Game/Blueprints/PlayerCharacter/BP_PlayerCharacter.BP_PlayerCharacter"));
	if (PlayerCharacter.Object != NULL)
		DefaultPawnClass = (UClass*)PlayerCharacter.Object->GeneratedClass;
}
