// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_InterruptibleWait.h"
#include "Operator.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"

UBT_InterruptibleWait::UBT_InterruptibleWait()
{
	//Its a latent task, so enable tick, and make sure the key can only be a float

	bCreateNodeInstance = false;
	bNotifyTaskFinished = false;
	bNotifyTick = true;
	m_FloatKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBT_InterruptibleWait, m_FloatKey));
}

EBTNodeResult::Type UBT_InterruptibleWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get the start time so we know how long the wait has been active
	FWaitMemory* waitMemory = reinterpret_cast<FWaitMemory*>(NodeMemory);
	waitMemory->m_StartTime = GetWorld()->GetTimeSeconds();

	return EBTNodeResult::InProgress;
}

uint16 UBT_InterruptibleWait::GetInstanceMemorySize() const
{
	return sizeof(FWaitMemory);
}

void UBT_InterruptibleWait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const FWaitMemory* waitMemory = reinterpret_cast<FWaitMemory*>(NodeMemory);
	//checks if the required wait time has passed, or if the interrupt condition has been met

	if (WaitTimePassed(waitMemory)) {

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	}

	const UBlackboardComponent* blackBoard = OwnerComp.GetBlackboardComponent();
	const float keyValue = blackBoard->GetValueAsFloat(m_FloatKey.SelectedKeyName);

	ShouldInterruptWait(keyValue, OwnerComp);

}

const void UBT_InterruptibleWait::ShouldInterruptWait(const float keyValue, UBehaviorTreeComponent& OwnerComp) const
{
	if (!m_Operator) {
		return;
	}

	if (m_Operator->Compare(keyValue, m_ComparedValue)) {
		UE_LOG(LogTemp, Warning, TEXT("Succeded"));
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
}

const bool UBT_InterruptibleWait::WaitTimePassed(const UBT_InterruptibleWait::FWaitMemory* waitMemory) const
{
	return GetWorld()->GetTimeSeconds() - m_WaitTime > waitMemory->m_StartTime;
}

void UBT_InterruptibleWait::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	//ensures the selected key exists

	const UBlackboardData* bBAsset = GetBlackboardAsset();
	if (ensure(bBAsset)) {
		m_FloatKey.ResolveSelectedKey(*bBAsset);
	}
}
