// Fill out your copyright notice in the Description page of Project Settings.


#include "BUIUW_MainMenu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "BP_SceneManagerLibary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TEXTStore.h"
#include "BUIUW_Options.h"
#include "BP_PersistantAssestsManager.h"

void UBUIUW_MainMenu::OnStartClicked()
{
	//disable the mouse cursor so it isnt visable whilst playing. 

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	controller->bShowMouseCursor = false;
	const FInputModeGameOnly gameOnly;

	controller->SetInputMode(gameOnly);

	UBP_SceneManagerLibary::LoadLevel(m_NextLevel, this);
}

void UBUIUW_MainMenu::OnQuitClicked()
{
	UBP_SceneManagerLibary::Quit(this);
}

void UBUIUW_MainMenu::OnOptionsClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
	
	
	BP_Options->SetPreviousMenu(this);
	BP_Options->SetVisibility(ESlateVisibility::Visible);
}

void UBUIUW_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	Cast< UBP_PersistantAssestsManager>(GetGameInstance())->UpdatePersistantAssets();
	if (!(m_Play && m_Quit)) {
		return;
	}

	SetUpButtonBindings();

	SetUpMenuControls();
	
	SetTitle();
	
}


void UBUIUW_MainMenu::NativeDestruct()
{
	Super::NativeDestruct();
	m_TitleText->SetObject(FText::FromString("Main Menu!"));

}
void UBUIUW_MainMenu::SetTitle()
{
	//Sets the title to what title text stores, so the menu can serve as the main menu, death, and victory menu. 
	//This is becuase the only change between them is what the title text displays, so,
	// we just change what title text stores when we get those outcomes.
	FText Title = m_TitleText->GetRegisteredObject();
	if (Title.IsEmpty()) {
		Title = FText::FromString("Boss Battle!");
	}

	m_TitleTextBlock->SetText(Title);
}

void UBUIUW_MainMenu::SetUpMenuControls() 
{
	//enable mouse cursor so user know where the mouse is.

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	Controller->bShowMouseCursor = true;
	FInputModeUIOnly UIOnly;
	UIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	Controller->SetInputMode(UIOnly);
}

void UBUIUW_MainMenu::SetUpButtonBindings()
{
	m_Play->OnClicked.AddDynamic(this, &UBUIUW_MainMenu::OnStartClicked);

	m_Quit->OnClicked.AddDynamic(this, &UBUIUW_MainMenu::OnQuitClicked);

	m_Options->OnClicked.AddDynamic(this, &UBUIUW_MainMenu::OnOptionsClicked);
}
