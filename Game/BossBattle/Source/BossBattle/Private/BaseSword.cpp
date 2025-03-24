// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSword.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseSword::ABaseSword()
{

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword"));

	m_Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Sword Hit Box"));
	m_Collider->SetupAttachment(root);
	m_Mesh->SetupAttachment(root);



}

// Called when the game starts or when spawned
void ABaseSword::BeginPlay()
{
	Super::BeginPlay();
	
	m_Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//make it so damage is called on overlap
	m_Collider->OnComponentBeginOverlap.AddDynamic(this, &ABaseSword::DealDamage);
}

void ABaseSword::DealDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//To be implimented in child classes
}


