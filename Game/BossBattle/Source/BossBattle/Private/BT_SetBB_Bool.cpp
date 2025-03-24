// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_SetBB_Bool.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"

UBT_SetBB_Bool::UBT_SetBB_Bool()
{
	//Lock the key to only be a bool to prevent something unintended from being selected
	m_BoolKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBT_SetBB_Bool, m_BoolKey));
	bNotifyTaskFinished = false;
	bNotifyTick = false;
}

EBTNodeResult::Type UBT_SetBB_Bool::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	UBlackboardComponent* blackBoard = OwnerComp.GetBlackboardComponent();

	if (blackBoard) {
		blackBoard->SetValueAsBool(m_BoolKey.SelectedKeyName, m_NewValue);
		return::EBTNodeResult::Succeeded;
	}


	return EBTNodeResult::Failed;
}

void UBT_SetBB_Bool::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	//ensure the key is valid

	UBlackboardData* bBAsset = GetBlackboardAsset();
	if (ensure(bBAsset)) {
		m_BoolKey.ResolveSelectedKey(*bBAsset);
	}
}
