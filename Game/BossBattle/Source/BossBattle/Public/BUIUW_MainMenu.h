// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BUIUW_MainMenu.generated.h"

class UButton;
class UTextBlock;
class UTEXTStore;
class UBUIUW_Options;

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UBUIUW_MainMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetOptionsMenu(UBUIUW_Options* Menu) { BP_Options = Menu; }

private:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_Play;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_Quit;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_Options;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_TitleTextBlock;

	UPROPERTY(EditAnywhere) 
	FName m_NextLevel;

	UBUIUW_Options* BP_Options;

	UPROPERTY(EditAnywhere)
	UTEXTStore* m_TitleText;

	UFUNCTION()
	void OnStartClicked();

	UFUNCTION()
	void OnQuitClicked();

	UFUNCTION()
	void OnOptionsClicked();

	void NativeConstruct() override;

	void NativeDestruct() override;

	void SetTitle();

	void SetUpMenuControls();

	void SetUpButtonBindings();
	
};
