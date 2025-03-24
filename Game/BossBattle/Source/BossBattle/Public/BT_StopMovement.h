// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_StopMovement.generated.h"

/**
 * Stops the movement of the entitiy, but only if the command is an aiController move function
 */
UCLASS()
class BOSSBATTLE_API UBT_StopMovement : public UBTTaskNode
{
	GENERATED_BODY()
	

private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
