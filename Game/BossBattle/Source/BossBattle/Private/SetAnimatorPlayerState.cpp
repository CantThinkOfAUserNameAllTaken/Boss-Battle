// Fill out your copyright notice in the Description page of Project Settings.


#include "SetAnimatorPlayerState.h"
#include "BP_PlayerAnimator.h"


void USetAnimatorPlayerState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	ABP_Player* player = Cast<ABP_Player>(MeshComp->GetOwner());

	if (player) {
		player->UpdatePlayerState(m_PlayerState);
	}


}
