// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_PatrolPoints.h"
#include "FVectorList.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"

EBTNodeResult::Type UBT_PatrolPoints::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (!m_PatrolPoints) {
		UE_LOG(LogTemp, Error, TEXT("Patrol Points is not Set!"));
		return EBTNodeResult::Aborted;
	}

	const FVector patrolPoint = m_PatrolPoints->GetRegisteredObjects()[m_CurrentPatrolPoint];

	AAIController* aiController = OwnerComp.GetAIOwner();


	if (aiController && !patrolPoint.IsZero()) {
		
		aiController->MoveToLocation(patrolPoint);
		//if the Pawn has reached the target, next patrol point
		if (HasReachTarget(aiController)) {

			m_CurrentPatrolPoint++;

			//wrap so it patrols each point, then goes back to the start
			if (HasReachedLastPatrolPoint()) {

				m_CurrentPatrolPoint = 0;

			}
			return EBTNodeResult::Succeeded;
		}



	}

	return EBTNodeResult::Failed;
}

const bool UBT_PatrolPoints::HasReachedLastPatrolPoint() const
{
	return m_CurrentPatrolPoint >= m_PatrolPoints->GetRegisteredObjects().Num();
}

const bool UBT_PatrolPoints::HasReachTarget(const AAIController* aiController) const 
{
	return aiController->GetMoveStatus() == EPathFollowingStatus::Idle;
}
