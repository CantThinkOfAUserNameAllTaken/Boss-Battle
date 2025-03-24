// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_UpdateBossAnimationState.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BP_BossAnimator.h"

EBTNodeResult::Type UBT_UpdateBossAnimationState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const ACharacter* controlledPawn = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());

	UBP_BossAnimator* bossAnimator = Cast<UBP_BossAnimator>(controlledPawn->GetMesh()->GetAnimInstance());
	if (bossAnimator) {
		bossAnimator->UpdateCurrentState(m_NewState);
	}

	return EBTNodeResult::Succeeded;
}
