// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_LeapToTarget.generated.h"

class  UCharacterStore;
class UCapsuleComponent;

/**
 * perfroms a leap to the target, with its maximum height being the highest it will go
 * WARNING: if Max height is less than the targets height, will not work
 */
UCLASS()
class BOSSBATTLE_API UBT_LeapToTarget : public UBTTaskNode
{
	GENERATED_BODY()

	UBT_LeapToTarget();
	

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	const void CalculateInitialVelocity(const FVector& LandingPosition, const FVector& StartPosition, float& OutTime, const float Gravity, FVector& OutVelocity) const;

	UPROPERTY(EditAnywhere, Category = "Data Assets")
	UCharacterStore* m_PlayerStore;

	UPROPERTY(EditAnywhere, Category = "Leap Parameters") 
	float m_MaxJumpHeight = 50;

	UPROPERTY(EditAnywhere, Category = "Leap Parameters")
	float m_DamageRadius;

	UPROPERTY(EditAnywhere, Category = "Leap Parameters")
	int m_LeapDamage;

	UPROPERTY(EditAnywhere, Category = "Leap Parameters")
	float m_LeapSpeed = 1;

	UPROPERTY(EditAnywhere, Category = "Leap Parameters")
	int m_DebugTrajectoryDetail = 100;

	UPROPERTY(EditAnywhere, Category = "Leap Parameters")
	float m_DamageKnockback;

	FTimerHandle DamageOnLandManager;

	struct FBTLeapMemory {
	public :
		double m_LandingTime;

		double m_TimeAtLeap;

		FVector m_InitialVelocity;

		FVector m_StartingPos;
		
		FBTLeapMemory(float InLandingTime, float InTime) : m_LandingTime(InLandingTime), m_TimeAtLeap(InTime){}

	};

	void SetUpMemory(UBT_LeapToTarget::FBTLeapMemory* LeapMemory, const float time, const FVector VelocityZ, const FVector& StartPosition);

	uint16 GetInstanceMemorySize()const override;

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void ApplyCorrectGravity(UCapsuleComponent* PawnCollision, const float Gravity);

	const void DrawTrajectory(const APawn* ControlledPawn, const UBT_LeapToTarget::FBTLeapMemory* LeapMemory, const float Gravity) const;

	const bool HasLanded(const UBT_LeapToTarget::FBTLeapMemory* LeapMemory) const;

	
};
