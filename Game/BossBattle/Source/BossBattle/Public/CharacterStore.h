// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseVariableStore.h"
#include "GameFramework/Character.h"
#include "CharacterStore.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UCharacterStore : public UPrimaryDataAsset, public BaseVariableStore<ACharacter*>
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Data Assets")
    virtual ACharacter* GetRegisteredObject() const override { return BaseVariableStore<ACharacter*>::GetRegisteredObject(); }

	virtual void Clear() override { m_Object = nullptr; }
};
