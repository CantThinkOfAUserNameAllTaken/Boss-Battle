// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_PlayParticleEffect.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UBT_PlayParticleEffect : public UBTTaskNode
{
	GENERATED_BODY()

	UBT_PlayParticleEffect();
private:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void CreateParticleEffect(const AAIController* aiController);

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* m_LandingEffect;

	UPROPERTY(EditAnywhere)
	float m_LifeSpan;

	
};
