// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_PatrolPoints.generated.h"

class UFVectorList;
class AAIController;
struct FPathFollowingRequestResult;

/**
 * Moves between a set of given points, Will repeat this indefinetly
 */
UCLASS()
class BOSSBATTLE_API UBT_PatrolPoints : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	const bool HasReachedLastPatrolPoint() const;

	const bool HasReachTarget(const AAIController* aiController) const;

	UPROPERTY(EditAnywhere, Category = "Patrol")
	UFVectorList* m_PatrolPoints;

	int m_CurrentPatrolPoint = 0;
};
