// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealSouls.h"
#include "UnrealSoulsCharacter.h"

AUnrealSoulsCharacter::AUnrealSoulsCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set player variables
	maxHealth = 100;
	currentHealth = maxHealth;
	maxStamina = 80;
	currentStamina = maxStamina;
	cameraDistance = 400.0f;
	newCameraDistance = cameraDistance;
	oldCameraDistance = cameraDistance;
	bIsChangingDistance = false;
	rateOfChange = 0.0f;
	bIsBlocking = false;

	defaultMovementSpeed = 400.0f;
	maxWalkSpeed = 125.0f;
	maxRunSpeed = 700.0f;

	sprintDrain = 16.0f;
	staminaRegenDefault = 40.0f;
	staminaRegenBlock = 10.0f;

	BaseLookUpRate = 100.0f;
	BaseTurnRate = 100.0f;

	timeSinceAction = 0.0f;

	bIsSprinting = false;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// Set up rotation for the character
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = defaultMovementSpeed;

	// Create camera boom
	CameraBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = cameraDistance;
	CameraBoom->bUsePawnControlRotation = true;

	// Follow camera
	FollowCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AUnrealSoulsCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	// Bind axes
	InputComponent->BindAxis("MoveForward", this, &AUnrealSoulsCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AUnrealSoulsCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &AUnrealSoulsCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AUnrealSoulsCharacter::AddControllerPitchInput);

	// Controller specific binds
	InputComponent->BindAxis("TurnRate", this, &AUnrealSoulsCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUpRate", this, &AUnrealSoulsCharacter::LookUpRate);

	// Bind actions
	InputComponent->BindAction("Walk", IE_Pressed, this, &AUnrealSoulsCharacter::OnWalkPressed);
	InputComponent->BindAction("Walk", IE_Released, this, &AUnrealSoulsCharacter::RevertToDefaultSpeed);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AUnrealSoulsCharacter::OnSprintPressed);
	InputComponent->BindAction("Sprint", IE_Released, this, &AUnrealSoulsCharacter::OnSprintReleased);
	InputComponent->BindAction("Block", IE_Pressed, this, &AUnrealSoulsCharacter::OnBlockPressed);
	InputComponent->BindAction("Block", IE_Released, this, &AUnrealSoulsCharacter::OnBlockReleased);
}

void AUnrealSoulsCharacter::Tick(float DeltaSeconds)
{
	HandleStaminaDrain(DeltaSeconds);

	HandleCameraDistanceChange(DeltaSeconds);
}

/************************************************************************/
/* INPUT                                                                */
/************************************************************************/
void AUnrealSoulsCharacter::MoveForward(float val)
{
	if ((Controller != NULL) && (val != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, val);
	}
}

void AUnrealSoulsCharacter::MoveRight(float val)
{
	if ((Controller != NULL) && (val != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, val);
	}
}

void AUnrealSoulsCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUnrealSoulsCharacter::LookUpRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AUnrealSoulsCharacter::OnWalkPressed()
{
	GetCharacterMovement()->MaxWalkSpeed = maxWalkSpeed;
}

void AUnrealSoulsCharacter::OnBlockPressed()
{
	bIsBlocking = true;
}

void AUnrealSoulsCharacter::OnBlockReleased()
{
	bIsBlocking = false;
}

/************************************************************************/
/* OTHER FUNCTIONS                                                      */
/************************************************************************/
void AUnrealSoulsCharacter::RevertToDefaultSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = defaultMovementSpeed;

	bIsSprinting = false;
}

void AUnrealSoulsCharacter::OnSprintPressed()
{
	if (!GetCharacterMovement()->Velocity.IsZero())
	{
		if (currentStamina != 0.0f)
			GetCharacterMovement()->MaxWalkSpeed = maxRunSpeed;

		bIsSprinting = true;
	}
		
}

void AUnrealSoulsCharacter::OnSprintReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = defaultMovementSpeed;

	if (!GetCharacterMovement()->Velocity.IsZero() && bIsSprinting)
	{
		bIsSprinting = false;

		timeSinceAction = 0.0f;
	}
}

void AUnrealSoulsCharacter::TickStamina(float amount)
{
	currentStamina += amount;

	if (currentStamina > maxStamina)
		currentStamina = maxStamina;

	if (currentStamina < 0.0f)
		currentStamina = 0.0f;
}

void AUnrealSoulsCharacter::setCameraDistance(float distance, float rate)
{
	newCameraDistance = distance;
	oldCameraDistance = cameraDistance;
	bIsChangingDistance = true;

	rateOfChange = rate;
}

void AUnrealSoulsCharacter::HandleStaminaDrain(float DeltaSeconds)
{
	// Drain stamina if sprinting
	if (bIsSprinting)
	{
		float staminaDrain = DeltaSeconds * sprintDrain;
		TickStamina(-staminaDrain);
	}

	// Stops player from sprinting once stamina is empty
	if (bIsSprinting && (currentStamina == 0.0f))
	{
		GetCharacterMovement()->MaxWalkSpeed = defaultMovementSpeed;
		bIsSprinting = false;
	}

	// Regain stamina if player isn't sprinting
	if (!bIsSprinting && (currentStamina != maxStamina))
	{
		if (timeSinceAction >= 2.0f)
		{
			float staminaDrain = 0.0f;

			if (bIsBlocking)
				staminaDrain = DeltaSeconds * staminaRegenBlock;
			else
				staminaDrain = DeltaSeconds * staminaRegenDefault;
			TickStamina(staminaDrain);
		}

		if (currentStamina != maxStamina)
			timeSinceAction += DeltaSeconds;
	}

	// Checks if the player has stopped running/moving but is still holding the button
	if (GetCharacterMovement()->Velocity.IsZero())
		bIsSprinting = false;
}

void AUnrealSoulsCharacter::HandleCameraDistanceChange(float DeltaSeconds)
{
	// Check to see if the camera has been requested to change
	if (bIsChangingDistance)
	{
		// First check to see if the flag has been set off for no reason
		if (cameraDistance == newCameraDistance)
			bIsChangingDistance = false;

		// Clamp if the value is bigger or smaller than intended
		if (((cameraDistance > newCameraDistance) && (newCameraDistance > oldCameraDistance))
			|| ((cameraDistance < newCameraDistance) && (newCameraDistance < oldCameraDistance)))
		{
			cameraDistance = newCameraDistance;
			oldCameraDistance = cameraDistance;
		}

		// Increase or decrease cameraDistance
		if (newCameraDistance < oldCameraDistance)
		{
			cameraDistance -= (DeltaSeconds * rateOfChange);
			CameraBoom->TargetArmLength -= (DeltaSeconds * rateOfChange);
		}
		else if (newCameraDistance > oldCameraDistance)
		{
			cameraDistance += (DeltaSeconds * rateOfChange);
			CameraBoom->TargetArmLength += (DeltaSeconds * rateOfChange);
		}
	}
}