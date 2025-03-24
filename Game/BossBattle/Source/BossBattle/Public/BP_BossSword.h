// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSword.h"
#include "BP_BossSword.generated.h"

class ABP_Player;
class ABP_BossCharacter;

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API ABP_BossSword : public ABaseSword
{
	GENERATED_BODY()
	
private:

	void DealDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	void DisableCollision() const;

	void SetBossStunned(const ABP_BossCharacter* boss) const;

	const bool IsAttackParried(const ABP_Player* player) const;

	UPROPERTY(EditAnywhere)
	float m_StaminaCost;

};
