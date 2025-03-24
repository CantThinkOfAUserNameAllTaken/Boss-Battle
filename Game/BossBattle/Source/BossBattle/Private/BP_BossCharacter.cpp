// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_BossCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Comp_BossHealth.h"
#include "ParticleStore.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ABP_BossCharacter::ABP_BossCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//creates the boss health component
	m_BossHealthManager = CreateDefaultSubobject<UComp_BossHealth>(TEXT("Boss Health"));

}

void ABP_BossCharacter::BeginPlay()
{
	Super::BeginPlay();

}


