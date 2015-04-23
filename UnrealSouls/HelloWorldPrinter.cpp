// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealSouls.h"
#include "HelloWorldPrinter.h"

AHelloWorldPrinter::AHelloWorldPrinter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	myNumber = 17;
}

void AHelloWorldPrinter::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello world!"));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(myNumber));
	}
}