// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_CallRandom.h"

UBT_CallRandom::UBT_CallRandom()
{
	NodeName = "Random";
}

//Initialize memory and cleanupMemory need to be implimented,
// as UBTCompositeNode markes them as virtual,
// but they are private, so their base functunality cant be inherited
void UBT_CallRandom::InitializeMemory(UBehaviorTreeComponent&, uint8*, EBTMemoryInit::Type) const
{
}

void UBT_CallRandom::CleanupMemory(UBehaviorTreeComponent&, uint8*, EBTMemoryClear::Type) const
{
}

int32 UBT_CallRandom::GetNextChildHandler(FBehaviorTreeSearchData&, int32 PrevChild, EBTNodeResult::Type Result) const
{
	//return success when child succeeds, and a child node has been selected
	if (Result == EBTNodeResult::Succeeded && PrevChild != BTSpecialChild::NotInitialized) {
		return BTSpecialChild::ReturnToParent;
	}

	//call one of the random child nodes
	return FMath::RandRange(0, GetChildrenNum());;
}
