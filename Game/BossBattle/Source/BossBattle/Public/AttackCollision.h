// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AttackCollision.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UAttackCollision : public UAnimNotify
{
	GENERATED_BODY()

private:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, Category = "Collsion");
	TEnumAsByte<ECollisionEnabled::Type> m_CollsionSetting;
	
};
