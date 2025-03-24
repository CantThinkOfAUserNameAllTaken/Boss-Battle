// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_InterruptibleWait.generated.h"


struct FBlackboardKeySelector;
class UBlackBoardComponent;
class UOperator;
/**
 * A wait that can have a float interrupt condition, causing it to end early
 */
UCLASS()
class BOSSBATTLE_API UBT_InterruptibleWait : public UBTTaskNode
{
	GENERATED_BODY()

	UBT_InterruptibleWait();

private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	struct FWaitMemory {
		float m_StartTime;
	};

	uint16 GetInstanceMemorySize()const override;

	UPROPERTY(EditAnywhere, Category = "Wait Parameters")
	float m_WaitTime;

	UPROPERTY(EditAnywhere, Category = "Wait Parameters")
	FBlackboardKeySelector m_FloatKey;

	UPROPERTY(EditAnywhere, Category = "Wait Parameters")
	UOperator* m_Operator;

	UPROPERTY(EditAnywhere, Category = "Wait Parameters")
	float m_ComparedValue;

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	const void ShouldInterruptWait(const float keyValue, UBehaviorTreeComponent& OwnerComp) const;

	const bool WaitTimePassed(const UBT_InterruptibleWait::FWaitMemory* waitMemory) const;

	void InitializeFromAsset(UBehaviorTree& Asset) override;
};
