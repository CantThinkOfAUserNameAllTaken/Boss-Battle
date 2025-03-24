// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BUIUW_PlayerHUD.generated.h"


class UProgressBar;

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UBUIUW_PlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	static UBUIUW_PlayerHUD* GetPlayerHUD(UBUIUW_PlayerHUD* BPClass);



	int PlayerMaxHealth;

	int PlayerMaxStamina;

	int BossMaxHealth;

	UFUNCTION()
	void UpdatePlayerHealthBar(const int CurrentHealth);

	UFUNCTION()
	void UpdatePlayerStaminaBar(const int CurrentStamina);

	UFUNCTION()
	void UpdateCurrentProgress(UProgressBar* DelayedBar, UProgressBar* HealthBar, FTimerHandle DelayManager);

	void SetDelayedBarFill(float& currentFillPercent, UProgressBar* DelayedBar, const UProgressBar* HealthBar);

	UFUNCTION()
	void UpdateBossHealthBar(const int CurrentHealth);





protected:
	UPROPERTY(EditAnywhere)
	float m_Speed;

	FTimerHandle m_PlayerHealthDelayManager;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* m_PlayerHealthBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* m_PlayerHealthDelayedBar;


	FTimerHandle m_PlayerStaminaDelayManager;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* m_PlayerStaminaBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* m_PlayerStaminaDelayedBar;



	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* m_BossHealthBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* m_BossDelayedBar;

	FTimerHandle m_BossDelayManager;


	void NativeDestruct() override;
	static UBUIUW_PlayerHUD* m_SPlayerHUD;

};

