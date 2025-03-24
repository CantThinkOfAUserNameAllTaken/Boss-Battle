// Fill out your copyright notice in the Description page of Project Settings.


#include "BUIUW_Options.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "HAL/PlatformMisc.h"
#include "Misc/Paths.h"
#include "BP_SceneManagerLibary.h"

#pragma region Resolution

void UBUIUW_Options::OnResolutionHigherClicked()
{
	SetNewResolution(1);
}

void UBUIUW_Options::OnResolutionLowerClicked()
{
	SetNewResolution(-1);
}

void UBUIUW_Options::SetNewResolution(int IndexChange)
{
	//check if the index is wihin array bounds
	m_CurrentResolutionIndex += IndexChange;
	if (m_CurrentResolutionIndex < 0 || m_CurrentResolutionIndex == m_Resolutions.Num()) {
		m_CurrentResolutionIndex -= IndexChange;
		return;
	}

	FIntPoint resolution = m_Resolutions[m_CurrentResolutionIndex];

	m_Settings->SetScreenResolution(resolution);

	FString resolutionDisplayText = FString::Printf(TEXT("%d x %d"), resolution.X, resolution.Y);

	m_ResolutionText->SetText(FText::FromString(resolutionDisplayText));

}
#pragma endregion

#pragma region windowMode




void UBUIUW_Options::OnWindowModeHigherClicked()
{
	SetNewWindowMode(1);
}

void UBUIUW_Options::OnWindowModeLowerClicked()
{
	SetNewWindowMode(-1);
}

void UBUIUW_Options::SetNewWindowMode(int IndexChange)
{
	//check if the index is wihin array bounds

	m_WindowModeIndex += IndexChange;
	if (m_WindowModeIndex < 0 || m_WindowModeIndex == EWindowMode::NumWindowModes) {
		m_WindowModeIndex -= IndexChange;
		return;
	}

	EWindowMode::Type currentMode = EWindowMode::ConvertIntToWindowMode(m_WindowModeIndex);
	
	m_Settings->SetFullscreenMode(currentMode);

	//get the enum as a string so we can display it

	const UEnum* windowMode = StaticEnum<EWindowMode::Type>();

	FString windowModeName = windowMode->GetNameStringByValue(m_WindowModeIndex);

	m_WindowModeText->SetText(FText::FromString(windowModeName));


}

#pragma endregion

#pragma region FrameRate




void UBUIUW_Options::OnFrameRateHigherClicked()
{
	SetNewFrameRate(1);
}

void UBUIUW_Options::OnFrameRateLowerClicked()
{
	SetNewFrameRate(-1);
}

void UBUIUW_Options::SetNewFrameRate(int IndexChange)
{

	//check if the index is wihin array bounds
	m_CurrentFrameRateIndex += IndexChange;
	if (m_CurrentFrameRateIndex < 0 || m_CurrentFrameRateIndex == m_FrameRates.Num()) {
		m_CurrentFrameRateIndex -= IndexChange;
		return;
	}

	int frameRateLock = m_FrameRates[m_CurrentFrameRateIndex];

	m_Settings->SetFrameRateLimit(frameRateLock);

	FString displayFrameRate = FString::FromInt(frameRateLock);

	m_FrameRateText->SetText(FText::FromString(displayFrameRate));
}
#pragma endregion

#pragma region ViewDistance


void UBUIUW_Options::OnViewDistanceHigherClicked()
{
	SetNewViewDistance(1);
}

void UBUIUW_Options::OnViewDistanceLowerClicked()
{
	SetNewViewDistance(-1);
}

void UBUIUW_Options::SetNewViewDistance(int IndexChange)
{
	//check if the index is wihin array bounds
	m_CurrentViewDistanceIndex += IndexChange;
	if (m_CurrentViewDistanceIndex < 0 || m_CurrentViewDistanceIndex == m_QualitySettings.Num()) {
		m_CurrentViewDistanceIndex -= IndexChange;
		return;
	}
	SettingsQuality quality = m_QualitySettings[m_CurrentViewDistanceIndex];
	m_Settings->SetViewDistanceQuality(quality.Quality);

	m_ViewDistanceText->SetText(FText::FromString(quality.DisplayName));

}
#pragma endregion

#pragma region PostProcessing


void UBUIUW_Options::OnPostProcessingHigherClicked()
{
	SetNewPostProcessing(1);
}

void UBUIUW_Options::OnPostProcessingLowerClicked()
{
	SetNewPostProcessing(-1);
}

void UBUIUW_Options::SetNewPostProcessing(int IndexChange)
{
	//check if the index is wihin array bounds
	m_CurrentPostProcessingIndex += IndexChange;
	if (m_CurrentPostProcessingIndex < 0 || m_CurrentPostProcessingIndex == m_QualitySettings.Num()) {
		m_CurrentPostProcessingIndex -= IndexChange;
		return;
	}
	SettingsQuality quality = m_QualitySettings[m_CurrentPostProcessingIndex];

	m_Settings->SetPostProcessingQuality(quality.Quality);

	m_PostProcessingText->SetText(FText::FromString(quality.DisplayName));
}
#pragma endregion

#pragma region AntiAliasing



void UBUIUW_Options::OnAntiAliasingHigherClicked()
{
	SetNewAntiAliasing(1);
}

void UBUIUW_Options::OnAntiAliasingLowerClicked()
{
	SetNewAntiAliasing(-1);
}

void UBUIUW_Options::SetNewAntiAliasing(int IndexChange)
{
	//check if the index is wihin array bounds
	m_CurrentAntiAliasingIndex += IndexChange;
	if (m_CurrentAntiAliasingIndex < 0 || m_CurrentAntiAliasingIndex == m_QualitySettings.Num()) {
		m_CurrentAntiAliasingIndex -= IndexChange;
		return;
	}
	SettingsQuality quality = m_QualitySettings[m_CurrentAntiAliasingIndex];
	m_Settings->SetAntiAliasingQuality(quality.Quality);

	m_AntiAliasingText->SetText(FText::FromString(quality.DisplayName));
}
#pragma endregion

#pragma region TextureQuality



void UBUIUW_Options::OnTextureQualityHigherClicked()
{
	SetNewTextureQuality(1);
}

void UBUIUW_Options::OnTextureQualityLowerClicked()
{
	SetNewTextureQuality(-1);
}

void UBUIUW_Options::SetNewTextureQuality(int IndexChange)
{
	//check if the index is wihin array bounds
	m_CurrentTextureQualityIndex += IndexChange;
	if (m_CurrentTextureQualityIndex < 0 || m_CurrentTextureQualityIndex == m_QualitySettings.Num()) {
		m_CurrentTextureQualityIndex -= IndexChange;
		return;
	}
	SettingsQuality quality = m_QualitySettings[m_CurrentTextureQualityIndex];
	m_Settings->SetTextureQuality(quality.Quality);

	m_TextureQualityText->SetText(FText::FromString(quality.DisplayName));
}
#pragma endregion

#pragma region ShadowQuality


void UBUIUW_Options::OnShadowQualityHigherClicked()
{
	SetNewShadowQuality(1);
}

void UBUIUW_Options::OnShadowQualityLowerClicked()
{
	SetNewShadowQuality(-1);
}

void UBUIUW_Options::SetNewShadowQuality(int IndexChange)
{
	//check if the index is wihin array bounds
	m_CurrentShadowQualityIndex += IndexChange;
	if (m_CurrentShadowQualityIndex < 0 || m_CurrentShadowQualityIndex == m_QualitySettings.Num()) {
		m_CurrentShadowQualityIndex -= IndexChange;
		return;
	}
	SettingsQuality quality = m_QualitySettings[m_CurrentShadowQualityIndex];
	m_Settings->SetShadowQuality(quality.Quality);

	m_ShadowQualityText->SetText(FText::FromString(quality.DisplayName));
}
#pragma endregion

#pragma region GlobalIllumination


void UBUIUW_Options::OnGlobalIlluminationHigherClicked()
{
	SetNewGlobalIllumination(1);
}

void UBUIUW_Options::OnGlobalIlluminationLowerClicked()
{
	SetNewGlobalIllumination(-1);
}

void UBUIUW_Options::SetNewGlobalIllumination(int IndexChange)
{
	//check if the index is wihin array bounds
	m_CurrentGlobalIlluminationIndex += IndexChange;
	if (m_CurrentGlobalIlluminationIndex < 0 || m_CurrentGlobalIlluminationIndex == m_QualitySettings.Num()) {
		m_CurrentGlobalIlluminationIndex -= IndexChange;
		return;
	}
	SettingsQuality quality = m_QualitySettings[m_CurrentGlobalIlluminationIndex];
	m_Settings->SetGlobalIlluminationQuality(quality.Quality);

	m_GlobalIlluminationText->SetText(FText::FromString(quality.DisplayName));
}
#pragma endregion

#pragma region Vsync


void UBUIUW_Options::OnVsyncDisabled()
{
	m_VSyncText->SetText(FText::FromString("Disabled"));
	SetVSync(false);
}

void UBUIUW_Options::OnVSyncEnabled()
{
	m_VSyncText->SetText(FText::FromString("Enabled"));
	SetVSync(true);
}

void UBUIUW_Options::SetVSync(bool state)
{
	m_Settings->SetVSyncEnabled(state);

}

#pragma endregion

void UBUIUW_Options::UseOptimalSettings()
{
	m_Settings->RunHardwareBenchmark();
	m_Settings->ApplyHardwareBenchmarkResults();
	UpdateSettingsDisplayedText();
}

#pragma region Warning


void UBUIUW_Options::ShowWarning()
{
	m_OptionsCanvas->SetVisibility(ESlateVisibility::Hidden);
	m_WarningCanvas->SetVisibility(ESlateVisibility::Visible);
}

void UBUIUW_Options::HideWarning()
{
	m_OptionsCanvas->SetVisibility(ESlateVisibility::Visible);
	m_WarningCanvas->SetVisibility(ESlateVisibility::Hidden);
}

#pragma endregion

void UBUIUW_Options::SaveSettings()
{
	m_Settings->ApplySettings(false);
	m_Settings->SaveSettings();


	FString currentExe = FPlatformProcess::ExecutablePath();
	FString commandLine = FCommandLine::Get();

	UBP_SceneManagerLibary::Quit(this);

	//if in a build, restart the game instead of just quiting. Dont do this in editor, as there isnt a seperate process

#if !WITH_EDITOR
	FPlatformProcess::CreateProc(*currentExe, *commandLine, true, false, false, nullptr, 0, nullptr, nullptr);
#endif
}

void UBUIUW_Options::NativeConstruct()
{
	Super::NativeConstruct();
	if (!(m_ResolutionLower && m_ResolutionHigher)) {
		return;
	}
	SetUpButtonBindings();

	//get the saved settings
	m_Settings = UGameUserSettings::GetGameUserSettings();
	m_Settings->ApplySettings(false);

	UpdateSettingsDisplayedText();


}

#pragma region UpdateDisplayedText


void UBUIUW_Options::UpdateSettingsDisplayedText()
{
	UpdateResolutionText();

	UpdateWindowModeText();

	UpdateFrameRateText();

	UpdateViewDistanceText();

	UpdatePostProcessingText();

	UpdateAntiAliasingText();

	UpdateTextureQualityText();

	UpdateShadowQualityText();

	UpdateGlobalIlluminationText();

	UpdateVSyncText();
}

void UBUIUW_Options::UpdateVSyncText()
{
	bool bVSync = m_Settings->IsVSyncEnabled();
	m_VSyncText->SetText(FText::FromString(bVSync ? "Enabled" : "Disabled"));
}

void UBUIUW_Options::UpdateGlobalIlluminationText()
{
	m_CurrentGlobalIlluminationIndex = m_Settings->GetGlobalIlluminationQuality();

	m_GlobalIlluminationText->SetText(FText::FromString(m_QualitySettings[m_CurrentGlobalIlluminationIndex].DisplayName));
}

void UBUIUW_Options::UpdateShadowQualityText()
{
	m_CurrentShadowQualityIndex = m_Settings->GetShadowQuality();

	m_ShadowQualityText->SetText(FText::FromString(m_QualitySettings[m_CurrentShadowQualityIndex].DisplayName));
}

void UBUIUW_Options::UpdateTextureQualityText()
{
	m_CurrentTextureQualityIndex = m_Settings->GetTextureQuality();

	m_TextureQualityText->SetText(FText::FromString(m_QualitySettings[m_CurrentTextureQualityIndex].DisplayName));
}

void UBUIUW_Options::UpdateAntiAliasingText()
{
	m_CurrentAntiAliasingIndex = m_Settings->GetAntiAliasingQuality();

	m_AntiAliasingText->SetText(FText::FromString(m_QualitySettings[m_CurrentAntiAliasingIndex].DisplayName));
}

void UBUIUW_Options::UpdatePostProcessingText()
{
	m_CurrentPostProcessingIndex = m_Settings->GetPostProcessingQuality();

	m_PostProcessingText->SetText(FText::FromString(m_QualitySettings[m_CurrentPostProcessingIndex].DisplayName));
}

void UBUIUW_Options::UpdateViewDistanceText()
{
	m_CurrentViewDistanceIndex = m_Settings->GetViewDistanceQuality();

	m_ViewDistanceText->SetText(FText::FromString(m_QualitySettings[m_CurrentViewDistanceIndex].DisplayName));
}

void UBUIUW_Options::UpdateFrameRateText()
{
	int FrameRateLock = m_Settings->GetFrameRateLimit();

	FString DisplayFrameRate = FString::FromInt(FrameRateLock);

	m_FrameRates.Find(FrameRateLock, m_CurrentFrameRateIndex);

	m_FrameRateText->SetText(FText::FromString(DisplayFrameRate));
}

void UBUIUW_Options::UpdateWindowModeText()
{
	EWindowMode::Type CurrentMode = m_Settings->GetFullscreenMode();

	m_WindowModeIndex = static_cast<int64>(CurrentMode);

	const UEnum* WindowMode = StaticEnum<EWindowMode::Type>();

	FString WindowModeName = WindowMode->GetNameStringByValue(m_WindowModeIndex);

	m_WindowModeText->SetText(FText::FromString(WindowModeName));
}

void UBUIUW_Options::UpdateResolutionText()
{
	FIntPoint resolution = m_Settings->GetScreenResolution();

	m_Resolutions.Find(resolution, m_CurrentResolutionIndex);

	FString resolutionDisplayText = FString::Printf(TEXT("%d x %d"), resolution.X, resolution.Y);

	m_ResolutionText->SetText(FText::FromString(resolutionDisplayText));
}
#pragma endregion

void UBUIUW_Options::LoadPreviousMenu()
{
	//hide this menu, dont remove from viewport, as that will destroy it, resetting settings

	SetVisibility(ESlateVisibility::Hidden);
	if (m_PreviousMenu) {
		m_PreviousMenu->SetVisibility(ESlateVisibility::Visible);
	}
}

#pragma region ButtonBindings

void UBUIUW_Options::SetUpButtonBindings()
{
	m_ResolutionHigher->OnClicked.AddDynamic(this, &UBUIUW_Options::OnResolutionHigherClicked);
	m_ResolutionLower->OnClicked.AddDynamic(this, &UBUIUW_Options::OnResolutionLowerClicked);
	
	m_WindowModeHigher->OnClicked.AddDynamic(this, &UBUIUW_Options::OnWindowModeHigherClicked);
	m_WindowModeLower->OnClicked.AddDynamic(this, &UBUIUW_Options::OnWindowModeLowerClicked);

	m_FrameRateHigher->OnClicked.AddDynamic(this, &UBUIUW_Options::OnFrameRateHigherClicked);
	m_FrameRateLower->OnClicked.AddDynamic(this, &UBUIUW_Options::OnFrameRateLowerClicked);

	m_ViewDistanceHigher->OnClicked.AddDynamic(this, &UBUIUW_Options::OnViewDistanceHigherClicked);
	m_ViewDistanceLower->OnClicked.AddDynamic(this, &UBUIUW_Options::OnViewDistanceLowerClicked);

	m_PostProcessingHigher->OnClicked.AddDynamic(this, &UBUIUW_Options::OnPostProcessingHigherClicked);
	m_PostProcessingLower->OnClicked.AddDynamic(this, &UBUIUW_Options::OnPostProcessingLowerClicked);

	m_AntiAliasingHigher->OnClicked.AddDynamic(this, &UBUIUW_Options::OnAntiAliasingHigherClicked);
	m_AntiAliasingLower->OnClicked.AddDynamic(this, &UBUIUW_Options::OnAntiAliasingLowerClicked);

	m_TextureQualityHigher->OnClicked.AddDynamic(this, &UBUIUW_Options::OnTextureQualityHigherClicked);
	m_TextureQualityLower->OnClicked.AddDynamic(this, &UBUIUW_Options::OnTextureQualityLowerClicked);

	m_ShadowQualityHigher->OnClicked.AddDynamic(this, &UBUIUW_Options::OnShadowQualityHigherClicked);
	m_ShadowQualityLower->OnClicked.AddDynamic(this, &UBUIUW_Options::OnShadowQualityLowerClicked);

	m_GlobalIlluminationHigher->OnClicked.AddDynamic(this, &UBUIUW_Options::OnGlobalIlluminationHigherClicked);
	m_GlobalIlluminationLower->OnClicked.AddDynamic(this, &UBUIUW_Options::OnGlobalIlluminationLowerClicked);

	m_VSyncEnabled->OnClicked.AddDynamic(this, &UBUIUW_Options::OnVSyncEnabled);
	m_VSyncDisabled->OnClicked.AddDynamic(this, &UBUIUW_Options::OnVsyncDisabled);

	m_Optimal->OnClicked.AddDynamic(this, &UBUIUW_Options::UseOptimalSettings);

	m_Back->OnClicked.AddDynamic(this, &UBUIUW_Options::LoadPreviousMenu);

	m_ApplySettings->OnClicked.AddDynamic(this, &UBUIUW_Options::ShowWarning);

	m_ConfirmApply->OnClicked.AddDynamic(this, &UBUIUW_Options::SaveSettings);

	m_CancelApply->OnClicked.AddDynamic(this, &UBUIUW_Options::HideWarning);

}
#pragma endregion
