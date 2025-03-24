// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundSlam.h"
#include "CharacterStore.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "BP_Player.h"
#include "Comp_PlayerHealth.h"
#include "NiagaraComponent.h"
#include "BP_SceneManagerLibary.h"

void UGroundSlam::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	const AActor* boss = MeshComp->GetOwner();
	if (!boss) {
		return;
	}
	const FVector bossLocation = boss->GetActorLocation();
	UNiagaraComponent* particleManager = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		boss,
		m_GroundBreakEffect,
		bossLocation,
		FRotator::ZeroRotator,
		FVector(1,1,1),
		true,
		true,
		ENCPoolMethod::AutoRelease);


	DamagePlayerIfWithinRadius(bossLocation);
	
}

const void UGroundSlam::DamagePlayerIfWithinRadius(const FVector& bossLocation)
{
	if (!m_PlayerStore) {
		return;
	}
	ACharacter* playerBase = m_PlayerStore->GetRegisteredObject();
	if (!playerBase)
	{
		return;
	}

	const ABP_Player* player = Cast<ABP_Player>(playerBase);

	const FVector bossToPlayer = bossLocation - player->GetActorLocation();
	const float distance = bossToPlayer.Length();

	if (IsWithinDamageRadius(distance)) {
		return;
	}

	player->GetPlayerHealthManager()->TakeDamageWithBlocking(Damage, m_StaminaCost, bossToPlayer.GetSafeNormal());
}

const bool UGroundSlam::IsWithinDamageRadius(const float distance) const
{
	return distance > m_DamageRadius;
}
