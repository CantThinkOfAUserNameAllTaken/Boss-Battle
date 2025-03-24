// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_SceneManagerLibary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

TArray<UObject*> UBP_SceneManagerLibary::m_SObjectsWithTimers;




void UBP_SceneManagerLibary::LoadLevel(const FName Level, const UObject* WorldContextObject)
{
	ClearAllRegisteredTimers(WorldContextObject);

	UGameplayStatics::OpenLevel(WorldContextObject, Level, true);
}

void UBP_SceneManagerLibary::ClearAllRegisteredTimers(const UObject* WorldContextObject)
{
	for (UObject* object : m_SObjectsWithTimers) {
		WorldContextObject->GetWorld()->GetTimerManager().ClearAllTimersForObject(object);
	}
}

void UBP_SceneManagerLibary::Quit(const UObject* WorldContextObject, APlayerController* Controller)
{
	UKismetSystemLibrary::QuitGame(WorldContextObject, Controller, EQuitPreference::Quit, true);
}
