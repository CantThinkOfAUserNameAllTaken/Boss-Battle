// Fill out your copyright notice in the Description page of Project Settings.


#include "TogglePlayerHit.h"
#include "BP_Player.h"

void UTogglePlayerHit::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	const ABP_Player* player = Cast<ABP_Player>(MeshComp->GetOwner());
	if (player) {

		UBP_PlayerAnimator* animator = player->GetAnimator();
		animator->ToggleHit(false);

	}


}
