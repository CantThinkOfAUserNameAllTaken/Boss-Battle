// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHealth.h"
#include "Comp_BossHealth.generated.h"

class UBUIUW_PlayerHUD;

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UComp_BossHealth : public UBaseHealth
{
	GENERATED_BODY()


public:

	void TakeDamage(const int Damage) override;

private:

	virtual void BeginPlay() override;

	float m_TimeLastDamaged = -99999;

	UPROPERTY(EditAnywhere)
	float m_DamageImmunityTime;

	UPROPERTY(EditAnywhere)
	UBUIUW_PlayerHUD* BP_PlayerHUD;

	const virtual void Death() override;

	
};
