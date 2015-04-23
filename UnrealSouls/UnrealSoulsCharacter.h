// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "UnrealSoulsCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSOULS_API AUnrealSoulsCharacter : public ACharacter
{
	GENERATED_BODY()

	// Camera vars
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

public:
	AUnrealSoulsCharacter(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(BlueprintReadWrite, Category = PlayerVariable)
		float currentHealth;
	UPROPERTY(BlueprintReadWrite, Category = PlayerVariable)
		float maxHealth;
	UPROPERTY(BlueprintReadWrite, Category = PlayerVariable)
		float currentStamina;
	UPROPERTY(BlueprintReadWrite, Category = PlayerVariable)
		float maxStamina;
	UPROPERTY(BlueprintReadWrite, Category = PlayerVariable)
		bool bIsBlocking;
	UPROPERTY(BlueprintReadWrite, Category = Camera)
		float cameraDistance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UFUNCTION()
		void setCameraDistance(float distance, float rate);

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual void Tick(float DeltaSeconds) override;

	// Movement
	void MoveForward(float val);
	void MoveRight(float val);
	void TurnAtRate(float Rate);
	void LookUpRate(float Rate);
	void OnWalkPressed();
	void RevertToDefaultSpeed();
	void OnSprintPressed();
	void OnSprintReleased();
	void OnBlockPressed();
	void OnBlockReleased();

	void TickStamina(float amount);

	void HandleStaminaDrain(float DeltaSeconds);
	void HandleCameraDistanceChange(float DeltaSeconds);

	float defaultMovementSpeed;
	float maxWalkSpeed;
	float maxRunSpeed;

	float sprintDrain;
	float staminaRegenDefault;
	float staminaRegenBlock;

	float newCameraDistance;
	float oldCameraDistance;
	float rateOfChange;
	bool bIsChangingDistance;

	float timeSinceAction;

	bool bIsSprinting;
};
