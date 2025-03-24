// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SwordEntity.h"
#include "BP_Player.generated.h"

class UCameraComponent;
class UInputComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UBP_PlayerAnimator;
class UCharacterStore;
class UComp_PlayerHealth;

UENUM(BlueprintType)
enum class EPlayerStates : uint8 {
	Moving,
	Jumping,
	Attacking,
	Parrying,
	Blocking,
	Dodging,
	Invincible,
	DodgeCooldown,
	Stunned
};

UCLASS()
class ABP_Player : public ASwordEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABP_Player();
	
	UFUNCTION()
	void UpdatePlayerState(const EPlayerStates InState);

	inline UComp_PlayerHealth* GetPlayerHealthManager() const {
		return m_PlayerHealth;
	}

	const inline EPlayerStates GetPlayerState() const { return m_PlayerState; }

	const inline float GetBlockingThresh() const { return m_BlockThresh; }

	inline UBP_PlayerAnimator* GetAnimator() const { return m_PlayerAnimations; }

	inline void SetStaminaDrained(const bool State) { m_StaminaDrained = State; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	void SetUpPlayer();

	void CreateShield();

	void SetUpDataAssests();

	void SetUpAnimator();

	void SetUpController();

	void SetUpInputMap();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* m_PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	const UInputAction* m_MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	const UInputAction* m_CameraRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	const UInputAction* m_JumpAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	const UInputAction* m_Running;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	const UInputAction* m_Attacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	const UInputAction* m_Dodging;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	const UInputAction* m_Blocking;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	const UInputMappingContext* m_ActionMap;




public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	UEnhancedInputComponent* GetEnhancedInput(UInputComponent* PlayerInputComponent);

	UFUNCTION()
	void ActionTriggers(UEnhancedInputComponent* EnhancedInput);

	void AbilityTriggers(UEnhancedInputComponent* EnhancedInput);

	void MovementTriggers(UEnhancedInputComponent* EnhancedInput);

	void RunningTriggers(UEnhancedInputComponent* EnhancedInput);

	UFUNCTION()
	void Walking(const FInputActionValue& Input);

	const bool IsParrying() const;

	const bool IsBlocking() const;

	const bool IsMoving() const;

	const void MovePlayer(const FVector2D MovementVector);

	UFUNCTION()
	void RotateCamera(const FInputActionValue& Input);

	void RotateAroundPlayer(const FVector2D& rotation);

	const bool IsInvincible() const;

	const bool IsDodging() const;

	UPROPERTY(EditAnywhere, Category = "Moveset|Movement")
	float m_MaxWalkSpeed = 1;

	UPROPERTY(EditAnywhere, Category = "Moveset|Movement")
	float m_MaxRunningSpeed;


	UPROPERTY(EditAnywhere, Category = "Moveset|Movement")
	float m_SpeedRateOfIncrease;

	UPROPERTY(EditAnywhere, Category = "Moveset|Movement")
	int m_DodgeSpeed;

	UPROPERTY(EditAnywhere, Category = "Data Assests")
	UCharacterStore* m_PlayerStore;

	UPROPERTY(EditAnywhere, Category = "Health")
	UComp_PlayerHealth* m_PlayerHealth;

	bool m_StaminaDrained = false;

	void IsRunning(const FInputActionValue& Input);

	UCharacterMovementComponent* m_MovementController;

	UBP_PlayerAnimator* m_PlayerAnimations;

	UPROPERTY(EditAnywhere, Category = "Moveset|Blocking")
	float m_ParryDuration;

	UPROPERTY(EditAnywhere, Category = "Moveset|Blocking")
	float m_BlockThresh;

	UPROPERTY(EditAnywhere, Category = "Moveset|Blocking")
	TSubclassOf<AActor> m_BPShield;

	AActor* m_Shield;

	EPlayerStates m_PlayerState = EPlayerStates::Moving;

	UEnhancedInputComponent* m_EnhancedInput;

	virtual void Landed(const FHitResult& Hit) override;

	virtual void Jump() override;

	void Attack();

	void Block();

	void Dodge();

	const FVector GetDodgeDirection()const;

	void SetMeshRotation(const FVector Dir);

	const bool IsDodgeOnCooldown() const;

	UFUNCTION()
	void DodgeMovement(const FVector OriginalCameraPosition, const FVector DIr);

	void SetTimerToRealignCamera(const FVector& OriginalCameraPosition, const FVector& Dir);

	void AlignControlRotationToCamera();

	UFUNCTION()
	void RealignCameraToPlayer(const FVector& OriginalCameraPosition);

	void Parry(const FInputActionValue& Input);


};
