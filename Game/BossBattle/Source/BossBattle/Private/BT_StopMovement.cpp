// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_StopMovement.h"
#include "AIController.h"

EBTNodeResult::Type UBT_StopMovement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (AAIController* aiController = OwnerComp.GetAIOwner()) {
		aiController->StopMovement();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
