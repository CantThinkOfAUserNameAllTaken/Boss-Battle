// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_GetPlayerState.h"
#include "BP_Player.h"
#include "CharacterStore.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"

UBTS_GetPlayerState::UBTS_GetPlayerState()
{
	bNotifyBecomeRelevant = true;
	m_PlayerStateKey.AddEnumFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_GetPlayerState, m_PlayerStateKey), StaticEnum<EPlayerStates>());
}

void UBTS_GetPlayerState::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	m_Player = Cast<ABP_Player>(m_PlayerStore->GetRegisteredObject());
}

void UBTS_GetPlayerState::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	//ensure key exists

	UBlackboardData* bBAsset = GetBlackboardAsset();
	if (ensure(bBAsset)) {
		m_PlayerStateKey.ResolveSelectedKey(*bBAsset);
	}
}

void UBTS_GetPlayerState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* blackBoard = OwnerComp.GetBlackboardComponent();
	if (!m_Player || !blackBoard) {
		return;
	}
	blackBoard->SetValueAsEnum(m_PlayerStateKey.SelectedKeyName, static_cast<uint8>(m_Player->GetPlayerState()));
}
