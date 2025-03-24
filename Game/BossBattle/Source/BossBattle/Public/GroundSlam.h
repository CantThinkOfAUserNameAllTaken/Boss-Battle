// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GroundSlam.generated.h"


class UCharacterStore;
class UNiagaraSystem;
class UNiagaraComponent;

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UGroundSlam : public UAnimNotify
{
	GENERATED_BODY()

private:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	const void DamagePlayerIfWithinRadius(const FVector& bossLocation);

	const bool IsWithinDamageRadius(const float distance) const;

	UPROPERTY(EditAnywhere)
	UCharacterStore* m_PlayerStore;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* m_GroundBreakEffect;

	UPROPERTY(EditAnywhere)
	float m_DamageRadius;

	UPROPERTY(EditAnywhere)
	int Damage;

	UPROPERTY(EditAnywhere)
	int m_StaminaCost;

	
	
};
