// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_PlayerSword.h"
#include "Comp_BossHealth.h"
#include "BP_BossCharacter.h"

void ABP_PlayerSword::DealDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const ABP_BossCharacter* boss = Cast<ABP_BossCharacter>(OtherActor);
	if (!boss) {
		return;
	}

	if (UComp_BossHealth* bossHealth = boss->GetBossHealthManager()) {
		bossHealth->TakeDamage(m_Damage);
	}
}
