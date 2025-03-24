// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSword.h"
#include "BP_PlayerSword.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API ABP_PlayerSword : public ABaseSword
{
	GENERATED_BODY()

private:

	void DealDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
};
