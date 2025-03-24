// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_PlayStunnableMontage.generated.h"

class ABP_BossCharacter;
class UBP_BossAnimator;

/**
 * Plays a montage, that can be interrupted if boss aniimator state is set to stunned
 */
UCLASS()
class BOSSBATTLE_API UBT_PlayStunnableMontage : public UBTTaskNode
{
	GENERATED_BODY()

	UBT_PlayStunnableMontage();
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere) 
	UAnimMontage* m_AttackAnimation;


	UPROPERTY(EditAnywhere)
	UAnimMontage* m_StunAnimation;

	struct FBTMontageMemory {
	public:
		float m_Duration;

		ABP_BossCharacter* m_Boss;

		float m_StartTime;

		UBP_BossAnimator* m_Animator;
	};

	uint16 GetInstanceMemorySize()const override;

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	const bool MontageHasEnded(const UBT_PlayStunnableMontage::FBTMontageMemory* memory) const;
	const bool Stunned(const UBP_BossAnimator* animator) const ;
};
