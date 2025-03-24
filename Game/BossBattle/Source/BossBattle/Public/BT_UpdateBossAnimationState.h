// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_UpdateBossAnimationState.generated.h"


class UBP_BossAnimator;
enum class EAnimationStates : uint8;
/**
 * Updates the boss animators state to the input state
 */
UCLASS()
class BOSSBATTLE_API UBT_UpdateBossAnimationState : public UBTTaskNode
{
	GENERATED_BODY()

private:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Animator")
	EAnimationStates m_NewState;
};
