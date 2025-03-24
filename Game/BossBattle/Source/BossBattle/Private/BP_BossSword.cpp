// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_BossSword.h"
#include "Comp_PlayerHealth.h"
#include "BP_Player.h"
#include "BP_BossCharacter.h"
#include "BP_BossController.h"
#include "BP_BossAnimator.h"
#include "Components/CapsuleComponent.h"

void ABP_BossSword::DealDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const ABP_Player* player = Cast<ABP_Player>(OtherActor);
	if (!player || m_Collider->GetCollisionEnabled() == ECollisionEnabled::NoCollision) {
		return;
	}
	const ABP_BossCharacter* boss = Cast<ABP_BossCharacter>(GetAttachParentActor());

	//if parrying, dont deal any damage, and update the animation state to show the boss is stunned.
	if (IsAttackParried(player)) {

		SetBossStunned(boss);

		//Collsion is normally disabled through anim-notifys,
		// but as the animation is interrupted, we disable it early here.
		DisableCollision();
		return;

	}


	if (UComp_PlayerHealth* playerHealth = player->GetPlayerHealthManager()) {

		// We need the direction here to check if the player is facing within the thresh hold to block
		UE_LOG(LogTemp, Warning, TEXT("BossSword"));
		const FVector dirToEnemy = (player->GetActorLocation() - boss->GetActorLocation()).GetSafeNormal();
		playerHealth->TakeDamageWithBlocking(m_Damage, m_StaminaCost, -dirToEnemy);
	}
}

void ABP_BossSword::DisableCollision() const
{

	m_Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABP_BossSword::SetBossStunned(const ABP_BossCharacter* boss) const
{
	//Update the controller for the Behaviour tree, and animations for the animator

	ABP_BossController* controller = Cast<ABP_BossController>(boss->GetController());

	controller->SetBBStunned(true);

	UBP_BossAnimator* animator = Cast<UBP_BossAnimator>(boss->GetMesh()->GetAnimInstance());

	animator->UpdateCurrentState(EAnimationStates::Stunned);
}

const bool ABP_BossSword::IsAttackParried(const ABP_Player* player) const 
{
	return player->GetPlayerState() == EPlayerStates::Parrying;
}
