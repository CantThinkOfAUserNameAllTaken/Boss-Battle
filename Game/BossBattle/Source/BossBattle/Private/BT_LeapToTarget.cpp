// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_LeapToTarget.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Comp_PlayerHealth.h"
#include "BP_Player.h"
#include "CharacterStore.h"

UBT_LeapToTarget::UBT_LeapToTarget()
{
	bCreateNodeInstance = false;
	bNotifyTaskFinished = false;
	bNotifyTick = true;

}

EBTNodeResult::Type UBT_LeapToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (const AAIController* aiController = OwnerComp.GetAIOwner()) {

		//set up local variables

		const ACharacter* controlledPawn = Cast<ACharacter>(aiController->GetPawn());

		const ACharacter* target = m_PlayerStore->GetRegisteredObject();

		const FVector landingPosition = target->GetActorLocation();

		const FVector startPosition = controlledPawn->GetActorLocation();

		const float gravity = GetWorld()->GetDefaultGravityZ();

		float time;

		FVector velocity;

		//if the players position is higher than the maximum jump height, it cannot be reached, so we abort
		if (landingPosition.Z - startPosition.Z > m_MaxJumpHeight) {
			return EBTNodeResult::Aborted;
		}

		CalculateInitialVelocity(landingPosition, startPosition, time, gravity, velocity);


		//Set Simulate Physics to true so its actually effected by the velocity.
		// its set back to false later as it needs to be for the pathfinding to work
		UCapsuleComponent* pawnCollision = controlledPawn->FindComponentByClass<UCapsuleComponent>();
		pawnCollision->SetSimulatePhysics(true);

		FBTLeapMemory* leapMemory = reinterpret_cast<FBTLeapMemory*>(NodeMemory);

		SetUpMemory(leapMemory, time, velocity, startPosition);

		pawnCollision->SetPhysicsLinearVelocity(leapMemory->m_InitialVelocity, false);

		//In progress because i dont want anything else to happen in the BT whilst this is ongoing
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

const void UBT_LeapToTarget::CalculateInitialVelocity(const FVector& LandingPosition, const FVector& StartPosition, float& OutTime, const float Gravity, FVector& OutVelocity) const
{
	//Using the SUVAT equations to calculate the Initial velocity needed to land at our target.
	//Also need time taken to land, as i use this to trigger a damage effect on landing
	const float displacementZ = LandingPosition.Z - StartPosition.Z;

	const FVector displacementXY = FVector(LandingPosition.X - StartPosition.X, LandingPosition.Y - StartPosition.Y, 0);

	OutTime = (sqrt(-2 * m_MaxJumpHeight / Gravity) + sqrt(2 * (displacementZ - m_MaxJumpHeight) / Gravity));

	const FVector velocityZ = FVector::UpVector * sqrt(-2 * Gravity * m_MaxJumpHeight);

	const FVector velocityXY = displacementXY / OutTime;

	OutVelocity = velocityXY + velocityZ;
}

void UBT_LeapToTarget::SetUpMemory(UBT_LeapToTarget::FBTLeapMemory* LeapMemory, const float time, const FVector Velocity, const FVector& StartPosition)
{
	//Velocity is timesed by our speed so we can increase the speed it travels the trajectory, without effecting the trajectory itelf.
	//As just increasing the velocity would break the trajectory, in the Tick we disable gravity,
	//adding a new constant downwards force (Gravity) that counteracts the increased velocity, just making the speed it travels faster
	//As this messses up the time, we also divide time by the speed;
	LeapMemory->m_LandingTime = time / m_LeapSpeed;
	LeapMemory->m_TimeAtLeap = GetWorld()->GetTimeSeconds();
	LeapMemory->m_InitialVelocity = Velocity * m_LeapSpeed;
	LeapMemory->m_StartingPos = StartPosition;
}

uint16 UBT_LeapToTarget::GetInstanceMemorySize() const
{
	return sizeof(FBTLeapMemory);
}

void UBT_LeapToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	if (!OwnerComp.GetAIOwner()) {
		return;
	}

	const FBTLeapMemory* leapMemory = reinterpret_cast<FBTLeapMemory*>(NodeMemory);

	APawn* controlledPawn = OwnerComp.GetAIOwner()->GetPawn();



	//Times Gravity by Speed Squared so trajetory isnt off
	const float gravity = GetWorld()->GetDefaultGravityZ() * (m_LeapSpeed * m_LeapSpeed);


	UCapsuleComponent* pawnCollision = controlledPawn->FindComponentByClass<UCapsuleComponent>();

	ApplyCorrectGravity(pawnCollision, gravity);
	

#if WITH_EDITOR

	DrawTrajectory(controlledPawn, leapMemory, gravity);

#endif

	if (HasLanded(leapMemory)) {

		pawnCollision->SetSimulatePhysics(false);
		pawnCollision->SetEnableGravity(true);

		ACharacter* targetAsCharacter = m_PlayerStore->GetRegisteredObject();
		if (!targetAsCharacter) {
			return;
		}
		const ABP_Player* target = Cast<ABP_Player>(targetAsCharacter);

		//used for both distance and direction check
		FVector targetToPawn = controlledPawn->GetActorLocation() - target->GetActorLocation();

		if (targetToPawn.Length() < m_DamageRadius && ensure(target)) {
			UComp_PlayerHealth* targetHealth =  target->GetPlayerHealthManager();
			//make the direction point up more so it launches the player in the right direction
			//and reverse the direction its pointing away from the boss
			targetToPawn.Z += 20;
			targetHealth->TakeDamage(m_LeapDamage, m_DamageKnockback, -(targetToPawn.GetSafeNormal()));
		}
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	

}

void UBT_LeapToTarget::ApplyCorrectGravity(UCapsuleComponent* PawnCollision, const float Gravity)
{
	//Disable gravity so there isnt excess downward force
	PawnCollision->SetEnableGravity(false);
	PawnCollision->AddForce(FVector(0, 0, Gravity), NAME_None, true);
}

const void UBT_LeapToTarget::DrawTrajectory(const APawn* ControlledPawn, const UBT_LeapToTarget::FBTLeapMemory* LeapMemory, const float Gravity) const
{
	FVector lastDrawPoint = ControlledPawn->GetActorLocation();

	for (int i = 0; i < m_DebugTrajectoryDetail; i++) {

		//cast to float so it returns a float
		const float simulationTime = i / (float)m_DebugTrajectoryDetail * LeapMemory->m_LandingTime;
		const FVector displacement = LeapMemory->m_InitialVelocity * simulationTime + FVector::UpVector * Gravity * simulationTime * simulationTime / 2.0f;
		const FVector drawPoint = LeapMemory->m_StartingPos + displacement;

		DrawDebugLine(GetWorld(), lastDrawPoint, drawPoint, FColor::Red, false, 100, 1, 3);
		lastDrawPoint = drawPoint;

	}
}

const bool UBT_LeapToTarget::HasLanded(const UBT_LeapToTarget::FBTLeapMemory* LeapMemory) const
{
	return GetWorld()->GetTimeSeconds() - LeapMemory->m_LandingTime > LeapMemory->m_TimeAtLeap;
}

