// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseHealth.generated.h"

class UTEXTStore;


UCLASS(ClassGroup = (Health), meta = (IsBlueprintBase = "True"))
class UBaseHealth : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseHealth();

	int inline GetCurrentHealth() { return m_CurrentHealth; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	int m_CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health", meta = (DisplayName = "Max Health"))
	int m_MaxHealth;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIntPropertyChangedSignature, int, CurrentHealth);

	const virtual void Death();

public:

	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void TakeDamage(const int Damage);

	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void IncreaseHealth(const int HealAmount);


	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Health")
	FOnIntPropertyChangedSignature OnHealthIncreased;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Health")
	FOnIntPropertyChangedSignature OnHealthDecreased;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Health")
	FOnIntPropertyChangedSignature OnDeath;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Health")
	FOnIntPropertyChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Health")
	FOnIntPropertyChangedSignature OnStaminaChanged;

	UPROPERTY(EditAnywhere)
	UTEXTStore* m_TitleText;

};
