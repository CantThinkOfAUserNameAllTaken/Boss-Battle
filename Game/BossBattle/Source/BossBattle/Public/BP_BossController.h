// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BP_BossController.generated.h"


/**
 * 
 */
UCLASS()
class BOSSBATTLE_API ABP_BossController : public AAIController
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Set the blackboard variable Stunned. Will Stun the boss
	/// </summary>
	/// <param name="State"></param>
	inline void SetBBStunned(const bool State) {
		if (!Blackboard) {
			return;
		}
		Blackboard.Get()->SetValueAsBool(FName("Stunned"), State);
	}

};
