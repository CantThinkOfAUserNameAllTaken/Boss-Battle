// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseVariableStore.h"
#include "NiagaraComponent.h"
#include "ParticleStore.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UParticleStore : public UPrimaryDataAsset, public BaseVariableStore<UNiagaraComponent*>
{
	GENERATED_BODY()

public:
	virtual void Clear() override { m_Object = nullptr; }
	
};
