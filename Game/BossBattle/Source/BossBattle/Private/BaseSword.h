// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSword.generated.h"


class UCapsuleComponent;


UCLASS(Abstract)
class ABaseSword : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSword();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Damage")
	int m_Damage;

	UFUNCTION()
	virtual void DealDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* m_Mesh;

	UPROPERTY(EditAnywhere, Category = "Collsion")
	UCapsuleComponent* m_Collider;


};
