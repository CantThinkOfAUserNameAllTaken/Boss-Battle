// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackCollision.h"
#include "SwordEntity.h"
#include "Components/CapsuleComponent.h"

void UAttackCollision::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	//Toggle the collision of the sword, so it isnt always hitting the player, and to save performance

	const ASwordEntity* entity = Cast<ASwordEntity>(MeshComp->GetOwner());
	if (!entity) {
		return;
	}

	const AActor* sword = entity->GetSword();
	if (!sword) {
		return;
	}
	UCapsuleComponent* collision = sword->FindComponentByClass<UCapsuleComponent>();
	collision->SetCollisionEnabled(m_CollsionSetting);
	if (m_CollsionSetting == ECollisionEnabled::NoCollision) {
		collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	}
	else {
		collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	}

}
