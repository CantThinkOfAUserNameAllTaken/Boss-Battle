// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SwordEntity.generated.h"

UCLASS()
class ASwordEntity : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASwordEntity();

	const inline AActor* GetSword() const { return m_Sword; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CreateAndAttachSword();


	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AActor> BP_SwordBlueprint;

	AActor* m_Sword;

};
