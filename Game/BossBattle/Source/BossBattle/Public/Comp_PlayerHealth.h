// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHealth.h"
#include "Comp_PlayerHealth.generated.h"


class UBUIUW_PlayerHUD;
class ABP_Player;
/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UComp_PlayerHealth : public UBaseHealth
{
	GENERATED_BODY()

public:

	UComp_PlayerHealth();

	void TakeDamage(const int Damage) override;

	void TakeDamageWithBlocking(const int Damage, const float StaminaCost, const FVector EnemyDir);

	const bool IsInvincible(const ABP_Player* player) const;

	void TakeDamage(const int Damage, const float KnockBackAmount, const FVector KnockBackDir);

	const bool Blocked(const ABP_Player* Player, const float Similarity) const;

	void ApplyKnockBack(const FVector& KnockBackDir, const float KnockBackAmount);

	void ReduceStamina(const int ReductionAmount);

	void SetStunTimer(ABP_Player* player);

	void ResetStaminaCooldown();

	UFUNCTION()
	void IncreaseStamina(const float IncreaseAmount);

	void SetStaminaIncreaseForNextFrame();

private:
	virtual void BeginPlay() override;

	void SetUpHUDBindings(UBUIUW_PlayerHUD*& playerHUD);

	const virtual void Death() override;

	UFUNCTION()
	void UpdateTimeLastDamaged(const int Damage);

	UPROPERTY(EditAnywhere)
	UBUIUW_PlayerHUD* BP_PlayerHUD;

	UPROPERTY(EditAnywhere)
	float m_MaxStamina;

	float m_CurrentStamina;

	float m_TimeDamagedLast = -1;

	UPROPERTY(EditAnywhere)
	float m_RecoveryTimeInterval;

	UPROPERTY(EditAnywhere)
	float m_StaminaRecoveryRate;

	UPROPERTY(EditAnywhere)
	float m_StunDuration;


	FTimerHandle m_StaminaCooldownHandler;



};