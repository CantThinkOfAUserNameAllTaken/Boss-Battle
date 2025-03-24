// Fill out your copyright notice in the Description page of Project Settings.


#include "LookForPlayer.h"
#include "AIController.h"
#include "CharacterStore.h"

EBTNodeResult::Type ULookForPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (!m_PlayerStore) {
		return EBTNodeResult::Failed;
	}
	const AAIController* aIController = OwnerComp.GetAIOwner();
	const APawn* boss = aIController->GetPawn();

	const ACharacter* player = m_PlayerStore->GetRegisteredObject();

	if (!player) {
		return EBTNodeResult::Failed;
	}

	const float distanceToPlayer = (player->GetActorLocation() - boss->GetActorLocation()).Length();

#if WITH_EDITOR

	DrawDebugSphere(GetWorld(), boss->GetActorLocation(), m_DetectionRadius, 8, FColor::Black, true, 10.0f, 1, 3);

#endif

	if (IsWithinDetectionRadius(distanceToPlayer)) {

		return EBTNodeResult::Succeeded;

	}

	return EBTNodeResult::Failed;

}

const bool ULookForPlayer::IsWithinDetectionRadius(const float distanceToPlayer) const
{
	return distanceToPlayer < m_DetectionRadius;
}
