// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_PlayParticleEffect.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "BP_SceneManagerLibary.h"
#include "AIController.h"
#include "GameFramework/Character.h"



UBT_PlayParticleEffect::UBT_PlayParticleEffect()
{
	bCreateNodeInstance = false;
	bNotifyTaskFinished = false;
	bNotifyTick = false;
}

EBTNodeResult::Type UBT_PlayParticleEffect::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const AAIController* aiController = OwnerComp.GetAIOwner()) {

		CreateParticleEffect(aiController);
	}

	return EBTNodeResult::Type();
}

void UBT_PlayParticleEffect::CreateParticleEffect(const AAIController* aiController)
{
	const ACharacter* controlledPawn = Cast<ACharacter>(aiController->GetPawn());
	UNiagaraComponent* particleManager = UNiagaraFunctionLibrary::SpawnSystemAtLocation(controlledPawn,
		m_LandingEffect,
		controlledPawn->GetActorLocation(),
		FRotator::ZeroRotator,
		FVector(1, 1, 1),
		true,
		true,
		ENCPoolMethod::AutoRelease);

}
