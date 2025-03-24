// Fill out your copyright notice in the Description page of Project Settings.


#include "BUIUW_PlayerHUD.h"
#include "Components/ProgressBar.h"


UBUIUW_PlayerHUD*  UBUIUW_PlayerHUD::m_SPlayerHUD = nullptr;


UBUIUW_PlayerHUD* UBUIUW_PlayerHUD::GetPlayerHUD(UBUIUW_PlayerHUD* BP_PlayerHUD)
{
	//this needs to be static, as I reference this across both boss health and player health,
	// and need them to be referencing the same one, i.e. its a singleton
	if (!m_SPlayerHUD) {
		m_SPlayerHUD = BP_PlayerHUD;
		m_SPlayerHUD->AddToViewport();

	}
	return m_SPlayerHUD;
}

void UBUIUW_PlayerHUD::UpdatePlayerHealthBar(const int CurrentHealth)
{
	if (!m_PlayerHealthBar || !m_PlayerHealthDelayedBar)
	{
		return;
	}
	//Gets the current health as a percent and sets health bar to it
	m_PlayerHealthBar->SetPercent((float)CurrentHealth / PlayerMaxHealth);

	//clears the previous timer if there is one, so the delay doesnt drain instantly
	if (GetWorld()->GetTimerManager().IsTimerActive(m_PlayerHealthDelayManager)) {
		GetWorld()->GetTimerManager().ClearTimer(m_PlayerHealthDelayManager);
	}

	FTimerDelegate playerTimerParams;
	playerTimerParams.BindUFunction(this, FName("UpdateCurrentProgress"), m_PlayerHealthDelayedBar, m_PlayerHealthBar, m_PlayerHealthDelayManager);

	GetWorld()->GetTimerManager().SetTimer(m_PlayerHealthDelayManager, playerTimerParams, 1, false);
}

void UBUIUW_PlayerHUD::UpdatePlayerStaminaBar(const int CurrentStamina)
{
	if (!m_PlayerStaminaBar || !m_PlayerStaminaDelayedBar)
	{
		return;
	}
	//Gets the current health as a percent and sets health bar to it
	m_PlayerStaminaBar->SetPercent((float)CurrentStamina/ PlayerMaxStamina);

	//clears the previous timer if there is one, so the delay doesnt drain instantly
	if (GetWorld()->GetTimerManager().IsTimerActive(m_PlayerStaminaDelayManager)) {
		GetWorld()->GetTimerManager().ClearTimer(m_PlayerStaminaDelayManager);
	}

	FTimerDelegate playerTimerParams;
	playerTimerParams.BindUFunction(this, FName("UpdateCurrentProgress"), m_PlayerStaminaDelayedBar, m_PlayerStaminaBar, m_PlayerStaminaDelayManager);

	GetWorld()->GetTimerManager().SetTimer(m_PlayerStaminaDelayManager, playerTimerParams, 1, false);
}



void UBUIUW_PlayerHUD::UpdateCurrentProgress(UProgressBar* DelayedBar, UProgressBar* HealthBar, FTimerHandle DelayManager)
{
	float currentFillPercent;
	SetDelayedBarFill(currentFillPercent, DelayedBar, HealthBar);

	//if the fill amount isnt equal to current health, 
	// recursivly set a timer for 0.01 seconds so that the delayed bar decreased at a stable rate
	if (currentFillPercent == HealthBar->GetPercent()) {
		return;
	}

	FTimerDelegate timerParams;
	timerParams.BindUFunction(this, FName("UpdateCurrentProgress"), DelayedBar, HealthBar, DelayManager);

	GetWorld()->GetTimerManager().SetTimer(DelayManager, timerParams, 0.01, false);
}

void UBUIUW_PlayerHUD::SetDelayedBarFill(float& currentFillPercent, UProgressBar* DelayedBar, const UProgressBar* HealthBar)
{
	currentFillPercent = DelayedBar->GetPercent();
	currentFillPercent = FMath::FInterpConstantTo(currentFillPercent, HealthBar->GetPercent(), GetWorld()->GetDeltaSeconds(), m_Speed);
	DelayedBar->SetPercent(currentFillPercent);
}

void UBUIUW_PlayerHUD::UpdateBossHealthBar(const int CurrentHealth)
{
	if (!m_BossHealthBar || !m_BossDelayedBar)
	{
		return;
	}


	m_BossHealthBar->SetPercent((float)CurrentHealth / BossMaxHealth);


	//clear the timer if it is active, 
	// so that it doesnt start decreasing till 1 second has passed without taking damage
	if (GetWorld()->GetTimerManager().IsTimerActive(m_BossDelayManager)) {
		GetWorld()->GetTimerManager().ClearTimer(m_BossDelayManager);
	}

	FTimerDelegate bossTimerParams;
	bossTimerParams.BindUFunction(this, FName("UpdateCurrentProgress"), m_BossDelayedBar, m_BossHealthBar, m_BossDelayManager);

	GetWorld()->GetTimerManager().SetTimer(m_BossDelayManager, bossTimerParams, 1, false);
}

void UBUIUW_PlayerHUD::NativeDestruct()
{
	Super::NativeDestruct();
	m_SPlayerHUD = nullptr;
}
