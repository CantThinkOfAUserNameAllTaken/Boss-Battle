// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Player.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterStore.h"
#include "Comp_PlayerHealth.h"
#include "Components/CapsuleComponent.h"
#include "BP_PlayerAnimator.h"
#include "InputMappingContext.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABP_Player::ABP_Player()
{
	//creating the camera and health
	m_PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	m_PlayerCamera->SetupAttachment(RootComponent);
	m_PlayerHealth = CreateDefaultSubobject<UComp_PlayerHealth>(TEXT("Health Manager"));

}

/// <summary>
/// Set the current state to the input, and updating other sources of the change as well
/// </summary>
/// <param name="State"></param>
void ABP_Player::UpdatePlayerState(const EPlayerStates InState)
{
	if (!m_PlayerAnimations) {
		return;
	}
	m_PlayerState = InState;
	m_PlayerAnimations->UpdatePlayerState(m_PlayerState);
}

// Called when the game starts or when spawned
void ABP_Player::BeginPlay()
{
	Super::BeginPlay();
	SetUpPlayer();

}

void ABP_Player::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	m_PlayerStore->Clear();
}

void ABP_Player::SetUpPlayer()
{
	SetUpInputMap();
	SetUpController();
	SetUpAnimator();
	SetUpDataAssests();
	CreateShield();
}

void ABP_Player::CreateShield()
{
	//create a shield on the left hand

	const FTransform handLocation = GetMesh()->GetSocketTransform(FName("LeftHandSocket"));

	m_Shield = GetWorld()->SpawnActor<AActor>(m_BPShield, handLocation);

	const FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);

	m_Shield->AttachToComponent(GetMesh(), rules, FName("LeftHandSocket"));
}

void ABP_Player::SetUpDataAssests()
{
	if (m_PlayerStore) {
		m_PlayerStore->SetObject(this);
	}

}

void ABP_Player::SetUpAnimator()
{
	m_PlayerAnimations = Cast<UBP_PlayerAnimator>(GetMesh()->GetAnimInstance());
	if (m_PlayerAnimations) {

		//set up the variables the animator needs to be able to animate properly
		m_PlayerAnimations->SetMovementController(m_MovementController);
		m_PlayerAnimations->SetMaxPossibleSpeed(m_MaxRunningSpeed);
		m_PlayerAnimations->SetPlayer(this);
		UpdatePlayerState(EPlayerStates::Moving);

	}

}

void ABP_Player::SetUpController()
{
	m_MovementController = GetCharacterMovement();
	m_MovementController->MaxAcceleration = m_SpeedRateOfIncrease;
}

/// <summary>
/// map the input map to this player
/// </summary>
void ABP_Player::SetUpInputMap()
{

	const APlayerController* playerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* input = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

	input->AddMappingContext(m_ActionMap, 0);
}

// Called to bind functionality to input
void ABP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    m_EnhancedInput =  GetEnhancedInput(PlayerInputComponent);
	if (m_EnhancedInput) {
		ActionTriggers(m_EnhancedInput);

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Failed to Get Enhanced Input"));
	}


}

/// <summary>
/// all action Input bindings are in here
/// </summary>
/// <param name="EnhancedInput"></param>
void ABP_Player::ActionTriggers(UEnhancedInputComponent* EnhancedInput)
{
	MovementTriggers(EnhancedInput);
	AbilityTriggers(EnhancedInput);

}

void ABP_Player::AbilityTriggers(UEnhancedInputComponent* EnhancedInput)
{

	EnhancedInput->BindAction(m_Attacking, ETriggerEvent::Triggered, this, &ABP_Player::Attack);
	EnhancedInput->BindAction(m_Dodging, ETriggerEvent::Triggered, this, &ABP_Player::Dodge);
	EnhancedInput->BindAction(m_Blocking, ETriggerEvent::Triggered, this, &ABP_Player::Parry);
}

void ABP_Player::MovementTriggers(UEnhancedInputComponent* EnhancedInput)
{
	EnhancedInput->BindAction(m_MovementAction, ETriggerEvent::Triggered, this, &ABP_Player::Walking);
	EnhancedInput->BindAction(m_CameraRotation, ETriggerEvent::Triggered, this, &ABP_Player::RotateCamera);
	EnhancedInput->BindAction(m_JumpAction, ETriggerEvent::Triggered, this, &ABP_Player::Jump);
	RunningTriggers(EnhancedInput);
}

void ABP_Player::RunningTriggers(UEnhancedInputComponent* EnhancedInput)
{

	// started to increase max movement speed, triggered to allow the player to still move,
	// and completed to reset movement speed back to normal
	EnhancedInput->BindAction(m_Running, ETriggerEvent::Started, this, &ABP_Player::IsRunning);
	EnhancedInput->BindAction(m_Running, ETriggerEvent::Triggered, this, &ABP_Player::Walking);
	EnhancedInput->BindAction(m_Running, ETriggerEvent::Completed, this, &ABP_Player::IsRunning);
}

UEnhancedInputComponent* ABP_Player::GetEnhancedInput(UInputComponent* PlayerInputComponent)
{
	return Cast<UEnhancedInputComponent>(PlayerInputComponent);
}

void ABP_Player::Walking(const FInputActionValue& Input)
{
	if (!(IsMoving() || IsBlocking() || IsParrying())) {
		return;
	}
	const FVector2D movementVector = Input.Get<FVector2D>();

	MovePlayer(movementVector);

}

const bool ABP_Player::IsParrying() const
{
	return m_PlayerState == EPlayerStates::Parrying;
}

const bool ABP_Player::IsBlocking() const 
{
	return m_PlayerState == EPlayerStates::Blocking;
}

const bool ABP_Player::IsMoving() const
{
	return m_PlayerState == EPlayerStates::Moving;
}

const void ABP_Player::MovePlayer(const FVector2D MovementVector)
{
	if (Controller != nullptr) {

		AddMovementInput(GetActorForwardVector(), MovementVector.X);
		AddMovementInput(GetActorRightVector(), MovementVector.Y);

	}
}

void ABP_Player::RotateCamera(const FInputActionValue& Input)
{
	const FVector2D rotation = Input.Get<FVector2D>();
	if (IsDodging() || IsInvincible()) {

		RotateAroundPlayer(rotation);
		return;

	}
	AddControllerYawInput(rotation.X);

}

void ABP_Player::RotateAroundPlayer(const FVector2D& rotation)
{
	//first we create a matrix to rotate the camera around the player on the yaw axis by the input amount
	// then set its rotation and location in relation to this transformation matrix
	// this enables the player camera to move around the player without effecting the player facing direction like 
	// AddControllerYawInput does. 
	//Im also aware you can do this with a spring arm, i didnt find out till after (RIP)

	const FRotationAboutPointMatrix rotateAroundPoint
		= FRotationAboutPointMatrix(FRotator(0, rotation.X, 0), GetActorLocation());

	const FVector newLocation
		= rotateAroundPoint.TransformPosition(m_PlayerCamera->GetComponentLocation());

	const FRotator newRotation
		= (rotateAroundPoint.ToQuat() * m_PlayerCamera->GetComponentRotation().Quaternion()).Rotator();

	m_PlayerCamera->SetWorldLocationAndRotation(newLocation, newRotation);
}

const bool ABP_Player::IsInvincible() const
{
	return m_PlayerState == EPlayerStates::Invincible;
}

const bool ABP_Player::IsDodging() const
{
	return m_PlayerState == EPlayerStates::Dodging;
}

void ABP_Player::IsRunning(const FInputActionValue& Input)
{
	if (m_StaminaDrained) {
		return;
	}

	const bool bIsRunning = Input.Get<bool>();

	//togle the speed the player moves at

	if (bIsRunning) {

		m_MovementController->MaxWalkSpeed = m_MaxRunningSpeed;
		return;
	}

	m_MovementController->MaxWalkSpeed = m_MaxWalkSpeed;
}

void ABP_Player::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	UpdatePlayerState(EPlayerStates::Moving);

}

void ABP_Player::Jump()
{
	if (m_PlayerAnimations->GetHit()) {
		return;
	}
	Super::Jump();
	UpdatePlayerState(EPlayerStates::Jumping);
}

void ABP_Player::Attack()
{
	if (!IsMoving() || m_PlayerAnimations->GetHit()) {
		return;
	}
	UpdatePlayerState(EPlayerStates::Attacking);
}

void ABP_Player::Block()
{
	if (!IsParrying()) {
		return;
	}
	UpdatePlayerState(EPlayerStates::Blocking);

}

void ABP_Player::Dodge()
{
	if (IsDodging() || IsDodgeOnCooldown() || IsInvincible()
		|| !m_MovementController->IsMovingOnGround()
		|| m_StaminaDrained
		|| m_PlayerAnimations->GetHit()) {
		return;
	}

	UpdatePlayerState(EPlayerStates::Dodging);

	const FVector origialCameraPosition = m_PlayerCamera->GetRelativeLocation();

	const FVector dir = GetDodgeDirection();

	SetMeshRotation(dir);

	DodgeMovement(origialCameraPosition, dir);
}

const FVector ABP_Player::GetDodgeDirection() const
{
	FVector dir = m_MovementController->Velocity.GetSafeNormal();

	//if not moving, roll forward
	if (dir == FVector::ZeroVector) {
		dir = GetActorForwardVector();
	}
	return dir;
}

void ABP_Player::SetMeshRotation(const FVector Dir)
{
	FRotator dirToMesh = Dir.ToOrientationRotator();
	//rotate it by -90 degress to account for the meshes original rotation
	dirToMesh.Yaw -= 90;
	GetMesh()->SetWorldRotation(dirToMesh);
}

const bool ABP_Player::IsDodgeOnCooldown() const
{
	return m_PlayerState == EPlayerStates::DodgeCooldown;
}

void ABP_Player::DodgeMovement(const FVector OriginalCameraPosition,const FVector Dir)
{
	//moves the player at a constant speed in the moving direction;
	const FVector newLocation = GetActorLocation() + (Dir * m_DodgeSpeed) * GetWorld()->GetDeltaSeconds();
	SetActorLocation(newLocation, true);

	//if the dodge is over
	if (!IsDodging() && !IsInvincible()) {

		AlignControlRotationToCamera();

		//we're setting a timer for the next frame, as realining it now causes the view to snap for a frame
		SetTimerToRealignCamera(OriginalCameraPosition, Dir);

		//reset mesh rotation
		GetMesh()->SetRelativeRotation(FRotator(0,-90,0));
	
		return;
	}

	//recursivly call this until dodge is over, the animation is what sets its end
	FTimerDelegate Params;
	Params.BindUFunction(this, FName("DodgeMovement"),OriginalCameraPosition, Dir);
	GetWorld()->GetTimerManager().SetTimerForNextTick(Params);
}

void ABP_Player::SetTimerToRealignCamera(const FVector& OriginalCameraPosition, const FVector& Dir)
{
	//Reset Camera to locked view
	FTimerDelegate params;
	params.BindUFunction(this, FName("RealignCameraToPlayer"), OriginalCameraPosition, Dir);
	GetWorld()->GetTimerManager().SetTimerForNextTick(params);
}

void ABP_Player::AlignControlRotationToCamera()
{
	// align control rotation to new camera rotation
	const FRotator cameraRotation = m_PlayerCamera->GetComponentRotation();
	GetController()->SetControlRotation(cameraRotation);
}

void ABP_Player::RealignCameraToPlayer(const FVector& OriginalCameraPosition)
{
	m_PlayerCamera->SetRelativeLocationAndRotation
	(OriginalCameraPosition, FRotator::ZeroRotator, false, nullptr, ETeleportType::TeleportPhysics);
}

void ABP_Player::Parry(const FInputActionValue& Input)
{
	if (!IsMoving() && !IsBlocking() && !IsParrying() || m_StaminaDrained) {
		return;
	}
	//Block is released
	else if (!Input.Get<bool>()) {
		UpdatePlayerState(EPlayerStates::Moving);
		return;
	}
	UpdatePlayerState(EPlayerStates::Parrying);

	//Set the parry window
	FTimerHandle ParryManager;
	GetWorldTimerManager().SetTimer(ParryManager, this, &ABP_Player::Block, m_ParryDuration, false);
}


 