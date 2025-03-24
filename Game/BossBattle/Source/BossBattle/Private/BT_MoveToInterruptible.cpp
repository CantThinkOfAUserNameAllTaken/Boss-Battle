// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_MoveToInterruptible.h"
#include "AIController.h"
#include "CharacterStore.h"

UBT_MoveToInterruptible::UBT_MoveToInterruptible()
{
	bCreateNodeInstance = false;
	bNotifyTick = false;
	bNotifyTaskFinished = false;
}

EBTNodeResult::Type UBT_MoveToInterruptible::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner()) {
		return EBTNodeResult::Failed;
	}

	//moves towards the actor normally, but as this isnt a latent task, allows it to be interrupted if conditions are met
	//though moveTo still needs to be canceled with BT_StopMovement

	AAIController* pawnController = OwnerComp.GetAIOwner();
	if (m_Target) {
		
		pawnController->MoveToActor(m_Target->GetRegisteredObject(), m_AcceptenceRadius, m_bStopOnOverlap, m_bUsePathFinding, m_bCanStrafe);
		return EBTNodeResult::Succeeded;
	}


	return EBTNodeResult::Failed;
}
