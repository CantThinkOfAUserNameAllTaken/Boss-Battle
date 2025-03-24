// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BP_PlayerAnimator.generated.h"

class UCharacterMovementComponent;
class ACharacter;

/**
 * 
 */
UCLASS()
class UBP_PlayerAnimator : public UAnimInstance
{
	GENERATED_BODY()

public:



	UFUNCTION(BlueprintCallable)
	float const GetSpeed() const { return m_Speed; }

	UFUNCTION(BlueprintCallable)
	bool const GetHit() const { return m_Hit; }

	UFUNCTION(BlueprintCallable)
	EPlayerStates const GetPlayerState() const { return m_PlayerState; }


	void inline SetMovementController(UCharacterMovementComponent* InMovementController) { m_PlayerMovementController = InMovementController; }

	void inline SetMaxPossibleSpeed(const float InMaxPossibleSpeed) { m_MaxPossibleSpeed = InMaxPossibleSpeed; }

	void inline SetPlayer(AActor* Player) { m_Player = Player; }

	void inline UpdatePlayerState(const EPlayerStates State) { m_PlayerState = State; };

	void inline ToggleHit(const bool Value) 
	{
		m_TimeSinceLastHit = GetWorld()->GetTimeSeconds();
		m_Hit = Value;
	}

private:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UCharacterMovementComponent* m_PlayerMovementController;

	float m_Speed;

	void UpdateSpeed();

	void SetSpeedAsPercentage();

	float m_MaxPossibleSpeed;

	AActor* m_Player;

	EPlayerStates m_PlayerState;

	bool m_Hit = false;

	float m_TimeSinceLastHit = -1;
};
