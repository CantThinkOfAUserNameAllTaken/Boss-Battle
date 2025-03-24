// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_PatrolPoint.generated.h"

class UFVectorList;

UCLASS()
class ABP_PatrolPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_PatrolPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Data Assets")
	UFVectorList* m_PatrolPoints;

	UPROPERTY(EditAnywhere, Category = "Editor Details")
	float m_EditorSphereRadius;

	UPROPERTY(EditAnywhere, Category = "Editor Details")
	FColor m_EditorSphereColor;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual bool ShouldTickIfViewportsOnly() const override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
#endif

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


public:	


	static float SAllEditorSphereRadius;

	static FColor SAllEditorSphereColor;

};
