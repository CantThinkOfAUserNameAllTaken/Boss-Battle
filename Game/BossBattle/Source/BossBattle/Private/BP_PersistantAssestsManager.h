// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TEXTStore.h"
#include "BP_PersistantAssestsManager.generated.h"

/**
 * 
 */
UCLASS()
class UBP_PersistantAssestsManager : public UGameInstance
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere)
	UTEXTStore* Titletext;

	inline void UpdatePersistantAssets() { Titletext->SetObject(m_CurrentTitle); }

	inline void SetPersistantTitle(FText Title) { m_CurrentTitle = Title; }

private:
	FText m_CurrentTitle;
};
