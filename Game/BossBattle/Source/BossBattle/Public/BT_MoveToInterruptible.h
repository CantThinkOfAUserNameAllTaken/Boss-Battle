// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_MoveToInterruptible.generated.h"

class UCharacterStore;

/**
 * A Move to node that can be interrupted, as its not a latent task, 
 * but movement still needs to be canceled if you want it to stop.
 */
UCLASS()
class BOSSBATTLE_API UBT_MoveToInterruptible : public UBTTaskNode
{
	GENERATED_BODY()

	UBT_MoveToInterruptible();
	

private:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Movement Parameters")
	UCharacterStore* m_Target;

	UPROPERTY(EditAnywhere, Category = "Movement Parameters")
	float m_AcceptenceRadius;

	UPROPERTY(EditAnywhere, Category = "Movement Parameters")
	bool m_bStopOnOverlap;

	UPROPERTY(EditAnywhere, Category = "Movement Parameters")
	bool m_bUsePathFinding;

	UPROPERTY(EditAnywhere, Category = "Movement Parameters")
	bool m_bCanStrafe;
};
