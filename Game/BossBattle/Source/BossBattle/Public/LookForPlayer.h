// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "LookForPlayer.generated.h"

class  UCharacterStore;
/**
 * 
 */
UCLASS()
class BOSSBATTLE_API ULookForPlayer : public UBTTaskNode
{
	GENERATED_BODY()
	



private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	const bool IsWithinDetectionRadius(const float distanceToPlayer) const;

	UPROPERTY(EditAnywhere)
	UCharacterStore* m_PlayerStore;

	UPROPERTY(EditAnywhere)
	float m_DetectionRadius;
};
