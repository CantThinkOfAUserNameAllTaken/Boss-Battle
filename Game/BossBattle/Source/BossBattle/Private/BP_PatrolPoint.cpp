// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_PatrolPoint.h"
#include "FVectorList.h"

//Define the statics
FColor ABP_PatrolPoint::SAllEditorSphereColor;
float ABP_PatrolPoint::SAllEditorSphereRadius;

// Sets default values
ABP_PatrolPoint::ABP_PatrolPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
#if WITH_EDITOR
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
#endif
	//Defualts
	ABP_PatrolPoint::SAllEditorSphereColor = FColor::Black;
	ABP_PatrolPoint::SAllEditorSphereRadius = 20;

}

// Called when the game starts or when spawned
void ABP_PatrolPoint::BeginPlay()
{
	Super::BeginPlay();

	//Register its location so the boss knows to patrol here
	FVector actorLocation = GetActorLocation();
	m_PatrolPoints->RegisterObject(actorLocation);
	
}

#if WITH_EDITOR

void ABP_PatrolPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if not currently in play mode,
	// share the color and size across all instances of this class, so editing one edits them all
	// We dont just use the statics, as statics cannot be UPROPERTYS
	if (!GWorld->HasBegunPlay()) {
		//A sphere for the editor only, to help with design
		DrawDebugSphere(GetWorld(), GetActorLocation(), ABP_PatrolPoint::SAllEditorSphereRadius, 32, ABP_PatrolPoint::SAllEditorSphereColor, false, 1, 1, 2);
		m_EditorSphereColor = SAllEditorSphereColor;
		m_EditorSphereRadius = SAllEditorSphereRadius;
	}


}


void ABP_PatrolPoint::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//if a property is changed, update the static so that all patrol points share the same size and color
	const FName propertyName = PropertyChangedEvent.GetPropertyName();

	if (propertyName == GET_MEMBER_NAME_CHECKED(ABP_PatrolPoint, m_EditorSphereRadius)) {
		ABP_PatrolPoint::SAllEditorSphereRadius = m_EditorSphereRadius;
	}
	else if (propertyName == GET_MEMBER_NAME_CHECKED(ABP_PatrolPoint, m_EditorSphereColor)) {
		ABP_PatrolPoint::SAllEditorSphereColor = m_EditorSphereColor;
	}
}
bool ABP_PatrolPoint::ShouldTickIfViewportsOnly() const
{
	return true;
}

#endif

void ABP_PatrolPoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//reset patrol points so we dont have a bunch of null references
	m_PatrolPoints->ClearList();
}


