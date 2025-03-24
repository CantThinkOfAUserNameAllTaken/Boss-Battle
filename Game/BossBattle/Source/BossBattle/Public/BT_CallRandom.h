// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BT_CallRandom.generated.h"

/**
* Random Composite Node
* Calls a random child node, Will continue calling until a node is successful, upon which it returns success
*/
UCLASS(Blueprintable, meta = (DisplayName = "Random"))
class UBT_CallRandom : public UBTCompositeNode
{
	GENERATED_BODY()

public:
	UBT_CallRandom();

	virtual void InitializeMemory(UBehaviorTreeComponent&, uint8*, EBTMemoryInit::Type) const override;
	virtual void CleanupMemory(UBehaviorTreeComponent&, uint8*, EBTMemoryClear::Type) const override;

	virtual int32 GetNextChildHandler(FBehaviorTreeSearchData&, int32, EBTNodeResult::Type) const override;

};
