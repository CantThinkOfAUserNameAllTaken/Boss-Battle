// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "BP_PlayerAnimator.h"
#include "TogglePlayerHit.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UTogglePlayerHit : public UAnimNotify
{
	GENERATED_BODY()

private:
	
	
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

};
