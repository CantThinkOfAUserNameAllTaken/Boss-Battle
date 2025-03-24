// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordEntity.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ASwordEntity::ASwordEntity()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASwordEntity::BeginPlay()
{
	Super::BeginPlay();
	
	CreateAndAttachSword();


}

void ASwordEntity::CreateAndAttachSword()
{
	const FTransform handLocation = GetMesh()->GetSocketTransform(FName("RightHandSocket"));

	m_Sword = GetWorld()->SpawnActor<AActor>(BP_SwordBlueprint, handLocation);

	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);

	m_Sword->AttachToComponent(GetMesh(), rules, FName("RightHandSocket"));

	m_Sword->FindComponentByClass<UCapsuleComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

