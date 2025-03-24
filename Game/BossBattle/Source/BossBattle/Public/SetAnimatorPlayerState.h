// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "BP_Player.h"
#include "SetAnimatorPlayerState.generated.h"
class UBP_PlayerAnimator;
class ABP_Player;

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API USetAnimatorPlayerState : public UAnimNotify
{
	GENERATED_BODY()
public:
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;


private:

	UPROPERTY(EditAnywhere)
	EPlayerStates m_PlayerState = EPlayerStates::Moving;
		
};
