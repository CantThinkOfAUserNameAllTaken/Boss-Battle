// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BP_SceneManagerLibary.generated.h"

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UBP_SceneManagerLibary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/// <summary>
	/// A list of UObjects with timers on them, timers arent destroyed when loading levels,
	/// so this is needed to prevent tier trying to modify destroyed objects
	/// </summary>
	static TArray<UObject*> m_SObjectsWithTimers;
	
	UFUNCTION(BlueprintCallable, Category = "SceneManager|Level Loading")
	static void LoadLevel(const FName Level, const UObject* WorldContextObject);

	static void ClearAllRegisteredTimers(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "SceneManager|Level Loading")
	static void Quit(const UObject* WorldContextObject, APlayerController* Controller = nullptr);
	
	
};
