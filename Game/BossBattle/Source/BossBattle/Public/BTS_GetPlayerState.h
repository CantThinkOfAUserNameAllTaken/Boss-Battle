// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_GetPlayerState.generated.h"

class UCharacterStore;
class ABP_Player;
struct FBlackboardKeySelector;

/**
 * Gets the current player state, and updates the BB key to store it
 */
UCLASS()
class BOSSBATTLE_API UBTS_GetPlayerState : public UBTService
{
	GENERATED_BODY()

	UBTS_GetPlayerState();

private:

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void InitializeFromAsset(UBehaviorTree& Asset) override;

	UPROPERTY(EditAnywhere)
	UCharacterStore* m_PlayerStore;

	ABP_Player* m_Player;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector m_PlayerStateKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
