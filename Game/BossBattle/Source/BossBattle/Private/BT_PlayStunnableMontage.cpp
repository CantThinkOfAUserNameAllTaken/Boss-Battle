// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_PlayStunnableMontage.h"
#include "AIController.h"
#include "BP_BossCharacter.h"
#include "BP_BossAnimator.h"

UBT_PlayStunnableMontage::UBT_PlayStunnableMontage()
{
	bCreateNodeInstance = false;
	bNotifyTaskFinished = false;
	bNotifyTick = true;
}

EBTNodeResult::Type UBT_PlayStunnableMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	ABP_BossCharacter* boss = Cast<ABP_BossCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	FBTMontageMemory* memory = reinterpret_cast<FBTMontageMemory*>(NodeMemory);
	UBP_BossAnimator* animator = Cast<UBP_BossAnimator>(boss->GetMesh()->GetAnimInstance());

	//get the duration and time of start of the montage so we know when to finish the task
	memory->m_Duration = animator->Montage_Play(m_AttackAnimation, 1);
	memory->m_Boss = boss;
	memory->m_StartTime = GetWorld()->GetTimeSeconds();
	memory->m_Animator = animator;
	

	return EBTNodeResult::InProgress;
}

uint16 UBT_PlayStunnableMontage::GetInstanceMemorySize() const
{
	return sizeof(FBTMontageMemory);
}

void UBT_PlayStunnableMontage::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const FBTMontageMemory* memory = reinterpret_cast<FBTMontageMemory*>(NodeMemory);

	const ABP_BossCharacter* boss = memory->m_Boss;
	UBP_BossAnimator* animator = memory->m_Animator;
	
	//stops the current animation to ensure it switches, 
	// as if it isnt stopped, can result in it not playing the next montage until the current one has finished

	if (Stunned(animator)) {

		animator->Montage_Stop(0.2);
		animator->Montage_Play(m_StunAnimation);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	}

	if (MontageHasEnded(memory)) {

		animator->UpdateCurrentState(EAnimationStates::Idle);
		animator->Montage_Stop(0.2);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	}
}

const bool UBT_PlayStunnableMontage::MontageHasEnded(const UBT_PlayStunnableMontage::FBTMontageMemory* memory) const
{

	return memory->m_StartTime + memory->m_Duration < GetWorld()->GetTimeSeconds();
}

const bool UBT_PlayStunnableMontage::Stunned(const UBP_BossAnimator* animator) const 
{
	return animator->GetCurrentState() == EAnimationStates::Stunned;
}
