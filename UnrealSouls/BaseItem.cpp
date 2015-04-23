// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealSouls.h"
#include "BaseItem.h"


// Sets default values
ABaseItem::ABaseItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionComponent = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollisionComponent"));
	collisionComponent->SetSphereRadius(64.0f, true);

	itemName = "DEFAULT ITEM NAME";
	itemDesc = "DEFAULT ITEM DESC";
	itemID = 0;			// This is not used at the moment
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

