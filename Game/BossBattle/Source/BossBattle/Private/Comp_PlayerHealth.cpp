// Fill out your copyright notice in the Description page of Project Settings.


#include "Comp_PlayerHealth.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "BP_Player.h"
#include "BP_PlayerAnimator.h"
#include "BUIUW_PlayerHUD.h"
#include "TEXTStore.h"


void UComp_PlayerHealth::BeginPlay()
{
	Super::BeginPlay();
	if (!BP_PlayerHUD) {
		return;
	}

	UBUIUW_PlayerHUD* playerHUD = UBUIUW_PlayerHUD::GetPlayerHUD(BP_PlayerHUD);

	SetUpHUDBindings(playerHUD);


}
void UComp_PlayerHealth::SetUpHUDBindings(UBUIUW_PlayerHUD*& playerHUD)
{
	playerHUD->PlayerMaxHealth = m_MaxHealth;
	playerHUD->PlayerMaxStamina = m_MaxStamina;

	//Bind health and stamina bars to change with health and stamina
	OnHealthChanged.AddDynamic(playerHUD, &UBUIUW_PlayerHUD::UpdatePlayerHealthBar);
	OnStaminaChanged.AddDynamic(playerHUD, &UBUIUW_PlayerHUD::UpdatePlayerStaminaBar);


	OnHealthDecreased.AddDynamic(this, &UComp_PlayerHealth::UpdateTimeLastDamaged);
	m_CurrentStamina = m_MaxStamina;
}




void UComp_PlayerHealth::UpdateTimeLastDamaged(const int Damage)
{
	m_TimeDamagedLast = GetWorld()->GetTimeSeconds();
}



UComp_PlayerHealth::UComp_PlayerHealth()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UComp_PlayerHealth::TakeDamage(const int CurrentHealth)
{
	Super::TakeDamage(CurrentHealth);

}

void UComp_PlayerHealth::TakeDamageWithBlocking(const int Damage, const float StaminaCost, const FVector EnemyDir)
{
	const ABP_Player* player = Cast<ABP_Player>(GetOwner());
	if (IsInvincible(player)) {
		return;
	}

#if WITH_EDITOR

	DrawDebugLine(GetWorld(), player->GetActorLocation(), player->GetActorLocation() + (EnemyDir * 10000), FColor::Black, true, 20, 1, 3);

#endif

	//Checking if the player is facing in a similar direction to the boss,
	// so your still hit if you arent actually blocking the attacks
	const FVector forwardDir = player->GetActorForwardVector();
	const float similarity = EnemyDir.Dot(forwardDir);

	if (Blocked(player, similarity)) {

		player->GetAnimator()->ToggleHit(true);

		ReduceStamina(StaminaCost);

		OnHealthDecreased.Broadcast(m_CurrentHealth);

		return;
	}
	Super::TakeDamage(Damage);
}

const bool UComp_PlayerHealth::IsInvincible(const ABP_Player* player) const
{
	return player->GetPlayerState() == EPlayerStates::Invincible;
}

const bool UComp_PlayerHealth::Blocked(const ABP_Player* Player, const float Similarity) const
{
	const bool bPlayerBlocking = Player->GetPlayerState() == EPlayerStates::Blocking || Player->GetPlayerState() == EPlayerStates::Parrying;
	const bool bWithinThresh = Similarity > Player->GetBlockingThresh();
	return bPlayerBlocking && bWithinThresh;
}

void UComp_PlayerHealth::TakeDamage(const int Damage, const float KnockBackAmount, const FVector KnockBackDir)
{


	Super::TakeDamage(Damage);
	const ABP_Player* player = Cast<ABP_Player>(GetOwner());
	if (IsInvincible(player)) {
		return;
	}

	ApplyKnockBack(KnockBackDir, KnockBackAmount);
	


}

void UComp_PlayerHealth::ApplyKnockBack(const FVector& KnockBackDir, const float KnockBackAmount)
{
	const ACharacter* Owner = Cast<ACharacter>(GetOwner());
	UCharacterMovementComponent* ForceController = Owner->GetCharacterMovement();
	
	//launch the player in the given direction with the given force

	ForceController->Launch(KnockBackDir * KnockBackAmount);
}

void UComp_PlayerHealth::ReduceStamina(const int ReductionAmount)
{
	if (m_CurrentStamina <= 0) {
		m_CurrentStamina = 0;
		return;
	}

	//reset the cooldown so stamina only regenerates when you havent blocked anything for that period of time
	ResetStaminaCooldown();

	m_CurrentStamina -= ReductionAmount;

	if (m_CurrentStamina <= 0) {
		
		//reset stamina to zero so it cant go below it, so the progress bar cannot go into negative amounts
		m_CurrentStamina = 0;
		ABP_Player* player = Cast<ABP_Player>(GetOwner());
		player->UpdatePlayerState(EPlayerStates::Stunned);
		player->GetAnimator()->ToggleHit(false);
		player->SetStaminaDrained(true);
		SetStunTimer(player);

	}
	OnStaminaChanged.Broadcast(m_CurrentStamina);
}

void UComp_PlayerHealth::SetStunTimer(ABP_Player* player)
{

	FTimerHandle delayHandler;

	FTimerDelegate delayTimerParams;
	delayTimerParams.BindUFunction(player, FName("UpdatePlayerState"), EPlayerStates::Moving);
	GetWorld()->GetTimerManager().SetTimer(delayHandler, delayTimerParams, m_StunDuration, false);
}

void UComp_PlayerHealth::ResetStaminaCooldown()
{
	//clear the previous timer so it stamina wont regen if its used whilst regenerating
	GetWorld()->GetTimerManager().ClearTimer(m_StaminaCooldownHandler);

	FTimerDelegate staminaCooldownTimerParams;
	staminaCooldownTimerParams.BindUFunction(this, FName("IncreaseStamina"), m_StaminaRecoveryRate);
	GetWorld()->GetTimerManager().SetTimer(m_StaminaCooldownHandler, staminaCooldownTimerParams, m_RecoveryTimeInterval, false);
}

void UComp_PlayerHealth::IncreaseStamina(const float IncreaseAmount)
{

	//ensure stamina doesnt go above max stamina
	if (m_CurrentStamina >= m_MaxStamina) {
		m_CurrentStamina = m_MaxStamina;
		return;
	}
	ABP_Player* player = Cast<ABP_Player>(GetOwner());
	player->SetStaminaDrained(false);
	m_CurrentStamina += IncreaseAmount;
	OnStaminaChanged.Broadcast(m_CurrentStamina);

	//recursivly trigger this function till stamina is full, to save from having to use a tick
	SetStaminaIncreaseForNextFrame();

}

void UComp_PlayerHealth::SetStaminaIncreaseForNextFrame()
{
	FTimerDelegate staminaIncreaseTimerParams;

	staminaIncreaseTimerParams.BindUFunction(this, FName("IncreaseStamina"), m_StaminaRecoveryRate);
	GetWorld()->GetTimerManager().SetTimer(m_StaminaCooldownHandler, staminaIncreaseTimerParams, 0.01f, false);
}

const void UComp_PlayerHealth::Death()
{
	m_TitleText->SetObject(FText::FromString("You Died!"));
	Super::Death();

}