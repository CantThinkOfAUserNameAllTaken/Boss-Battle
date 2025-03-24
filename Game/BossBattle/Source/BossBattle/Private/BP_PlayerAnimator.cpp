// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_PlayerAnimator.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "BP_Player.h"


void UBP_PlayerAnimator::UpdateSpeed()
{
	if (!m_PlayerMovementController) {
		return;
	}

	FVector velocity = m_PlayerMovementController->Velocity;
	//Set Z velocity to 0 so we are only messuring on a 2d plane
	velocity.Z = 0;

	const FVector forward = m_Player->GetActorForwardVector();

	//sets the speed to a percentage, as the animator takes a value between -100 and 100,
	// making it easier to change values without having to change everything
	SetSpeedAsPercentage();

	//if the player is moving backwards
	if (forward.Dot(velocity) < 0) {
		m_Speed = -m_Speed;
	}
	
}

void UBP_PlayerAnimator::SetSpeedAsPercentage()
{
	const float currentSpeed = m_PlayerMovementController->Velocity.Length();
	m_Speed = (currentSpeed / m_MaxPossibleSpeed) * 100;
}

void UBP_PlayerAnimator::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	UpdateSpeed();
}

