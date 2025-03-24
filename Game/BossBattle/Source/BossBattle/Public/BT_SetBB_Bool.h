// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_SetBB_Bool.generated.h"


struct FBlackboardKeySelector;
class UBlackBoardComponent;
/**
 * Sets a BB key to the input value
 */
UCLASS()
class BOSSBATTLE_API UBT_SetBB_Bool : public UBTTaskNode
{
	GENERATED_BODY()

	UBT_SetBB_Bool();
	

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void InitializeFromAsset(UBehaviorTree& Asset) override;

	UPROPERTY(EditAnywhere, Category = "Changing")
	FBlackboardKeySelector m_BoolKey;

	UPROPERTY(EditAnywhere, Category = "Changing")
	bool m_NewValue;
};
