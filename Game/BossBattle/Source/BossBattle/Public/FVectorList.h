// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseRunTimeSet.h"
#include "FVectorList.generated.h"

/**
 * A list of fvectors, so you can just reference this list instead of having to reference the object that holds them
 */
UCLASS()
class BOSSBATTLE_API UFVectorList : public UPrimaryDataAsset, public BaseRunTimeSet<FVector>
{
	GENERATED_BODY()
	
};
