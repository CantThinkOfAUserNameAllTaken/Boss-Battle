// Fill out your copyright notice in the Description page of Project Settings.


#include "Comp_BossHealth.h"
#include "BUIUW_PlayerHUD.h"
#include "TEXTStore.h"


void UComp_BossHealth::BeginPlay()
{
	Super::BeginPlay();
	if (!BP_PlayerHUD) {
		return;
	}

	UBUIUW_PlayerHUD* playerHUD = UBUIUW_PlayerHUD::GetPlayerHUD(BP_PlayerHUD);
	playerHUD->BossMaxHealth = m_MaxHealth;

	//update the boss health bar whenever its health changes
	OnHealthChanged.AddDynamic(playerHUD, &UBUIUW_PlayerHUD::UpdateBossHealthBar);

}

void UComp_BossHealth::TakeDamage(const int Damage)
{
	//have a damage immunity to ensure the boss get hit consecutivly by the same attack
	if (m_TimeLastDamaged + m_DamageImmunityTime > GetWorld()->GetTimeSeconds()) {
		return;
	}
	Super::TakeDamage(Damage);
}

const void UComp_BossHealth::Death()
{
	//update the title text for the main menu to turn it into a victory screen
	m_TitleText->SetObject(FText::FromString("You Won!"));
	Super::Death();
}
