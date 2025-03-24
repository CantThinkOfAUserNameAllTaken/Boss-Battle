// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SwordEntity.h"
#include "BP_BossCharacter.generated.h"

class UComp_BossHealth;
class UParticleStore;
class UNiagaraSystem;


UCLASS()
class BOSSBATTLE_API ABP_BossCharacter : public ASwordEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABP_BossCharacter();

	/// <summary>
	/// returns the BossHealth Component
	/// </summary>
	/// <returns></returns>
	inline UComp_BossHealth* GetBossHealthManager() const { return m_BossHealthManager; }

private:

	void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UComp_BossHealth* m_BossHealthManager;

};