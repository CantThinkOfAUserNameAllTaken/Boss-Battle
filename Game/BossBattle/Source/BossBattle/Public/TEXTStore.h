// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseVariableStore.h"
#include "TEXTStore.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UTEXTStore : public UPrimaryDataAsset, public BaseVariableStore<FText>
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Data Assets")
	void SetObject(FText Object) override { BaseVariableStore<FText>::SetObject(Object); }


	UFUNCTION(BlueprintCallable, Category = "Data Assets")
	virtual FText GetRegisteredObject() const override { return BaseVariableStore<FText>::GetRegisteredObject(); }

	virtual void Clear() override { m_Object = FText(); }


};
