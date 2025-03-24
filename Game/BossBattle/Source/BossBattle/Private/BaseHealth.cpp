// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHealth.h"
#include "BP_SceneManagerLibary.h"
#include "TEXTStore.h"
#include "BP_PersistantAssestsManager.h"

// Sets default values for this component's properties
UBaseHealth::UBaseHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBaseHealth::BeginPlay()
{
	Super::BeginPlay();
	m_CurrentHealth = m_MaxHealth;

	// ...

}

void UBaseHealth::TakeDamage(const int Damage)
{
	m_CurrentHealth -= Damage;

	OnHealthDecreased.Broadcast(m_CurrentHealth);
	OnHealthChanged.Broadcast(m_CurrentHealth);

	if (m_CurrentHealth <= 0) {

		Death();
		return;

	}
}

void UBaseHealth::IncreaseHealth(const int HealAmount)
{
	m_CurrentHealth += HealAmount;

	OnHealthIncreased.Broadcast(m_CurrentHealth);
	OnHealthChanged.Broadcast(m_CurrentHealth);

	//Make sure Player Health doesnt go over max health
	if (m_CurrentHealth > m_MaxHealth) {

		m_CurrentHealth = m_MaxHealth;
	}
}

const void UBaseHealth::Death()
{
	OnDeath.Broadcast(m_CurrentHealth);

	Cast<UBP_PersistantAssestsManager>(GetWorld()->GetGameInstance())->SetPersistantTitle(m_TitleText->GetRegisteredObject());

	UBP_SceneManagerLibary::LoadLevel("MainMenu", this);

	GetOwner()->Destroy();

}


