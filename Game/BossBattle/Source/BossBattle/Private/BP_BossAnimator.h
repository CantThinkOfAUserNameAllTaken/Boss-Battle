// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BP_BossAnimator.generated.h"

UENUM(BlueprintType)
enum class EAnimationStates : uint8 {
	Idle,
	Running,
	SwordAttack,
	Charging,
	Jumping,
	Stunned
};


/**
 * 
 */
UCLASS()
class UBP_BossAnimator : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Boss Animator")
	const EAnimationStates GetCurrentState() const {
		return m_CurrentState;
	}

	UFUNCTION(BlueprintCallable, Category = "Boss Animator")
	void UpdateCurrentState(const EAnimationStates NewState) {
		m_CurrentState = NewState;
	}

private:
	EAnimationStates m_CurrentState = EAnimationStates::Idle;

};
