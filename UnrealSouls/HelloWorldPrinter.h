// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HelloWorldPrinter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSOULS_API AHelloWorldPrinter : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	int32 myNumber;

	AHelloWorldPrinter(const FObjectInitializer& ObjectInitializer);
	
	virtual void BeginPlay() override;
};
