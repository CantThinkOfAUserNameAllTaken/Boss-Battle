// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BUIUW_Options.generated.h"

class UButton;
class UTextBlock;
class UImage;
class UCanvasPanel;

/**
 * 
 */
UCLASS()
class BOSSBATTLE_API UBUIUW_Options : public UUserWidget
{
	GENERATED_BODY()

public:
	inline void SetPreviousMenu(UUserWidget* PreviousMenu) { m_PreviousMenu = PreviousMenu; }

private:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* m_OptionsCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* m_WarningCanvas;

	struct SettingsQuality {
		FString DisplayName;
		float Quality;

		SettingsQuality(FString Name, float InQuality) : DisplayName(Name), Quality(InQuality) {};
	};

	TArray<SettingsQuality>  m_QualitySettings = { SettingsQuality("Low", 0), SettingsQuality("Medium", 1), SettingsQuality("High", 2)  ,SettingsQuality("Far", 3), SettingsQuality("SuperFar", 4) };

#pragma region Resolution



	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_ResolutionHigher;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_ResolutionLower;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_ResolutionText;

	int m_CurrentResolutionIndex = 0;

	TArray<FIntPoint> m_Resolutions = {FIntPoint(720, 480), FIntPoint(1280, 720), FIntPoint(1920, 1080), FIntPoint(2560, 1440) };

	UFUNCTION()
	void OnResolutionHigherClicked();

	UFUNCTION()
	void OnResolutionLowerClicked();
	void SetNewResolution(int IndexChange);

	void UpdateResolutionText();
#pragma endregion

#pragma region WindowMode




	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_WindowModeHigher;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_WindowModeLower;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_WindowModeText;

	UFUNCTION()
	void OnWindowModeHigherClicked();

	UFUNCTION()
	void OnWindowModeLowerClicked();
	void SetNewWindowMode(int IndexChange);

	void UpdateWindowModeText();

	int m_WindowModeIndex = 0;
#pragma endregion

#pragma region FrameRate



	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_FrameRateHigher;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_FrameRateLower;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_FrameRateText;

	int m_CurrentFrameRateIndex = 0;

	TArray<int> m_FrameRates = { 30, 60, 120, 240 };

	UFUNCTION()
	void OnFrameRateHigherClicked();

	UFUNCTION()
	void OnFrameRateLowerClicked();
	void SetNewFrameRate(int IndexChange);

	void UpdateFrameRateText();

#pragma endregion

#pragma region ViewDistance


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_ViewDistanceHigher;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_ViewDistanceLower;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_ViewDistanceText;

	int m_CurrentViewDistanceIndex = 0;	

	UFUNCTION()
	void OnViewDistanceHigherClicked();

	UFUNCTION()
	void OnViewDistanceLowerClicked();
	void SetNewViewDistance(int IndexChange);

	void UpdateViewDistanceText();

#pragma endregion

#pragma region PostProcessing

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_PostProcessingHigher;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_PostProcessingLower;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_PostProcessingText;

	int m_CurrentPostProcessingIndex = 0;

	UFUNCTION()
	void OnPostProcessingHigherClicked();

	UFUNCTION()
	void OnPostProcessingLowerClicked();
	void SetNewPostProcessing(int IndexChange);

	void UpdatePostProcessingText();

#pragma endregion

#pragma region Anti-Aliasing
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_AntiAliasingHigher;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_AntiAliasingLower;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_AntiAliasingText;

	int m_CurrentAntiAliasingIndex = 0;

	UFUNCTION()
	void OnAntiAliasingHigherClicked();

	UFUNCTION()
	void OnAntiAliasingLowerClicked();
	void SetNewAntiAliasing(int IndexChange);

	void UpdateAntiAliasingText();
#pragma endregion

#pragma region TextureQuality

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_TextureQualityHigher;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_TextureQualityLower;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_TextureQualityText;

	int m_CurrentTextureQualityIndex = 0;

	UFUNCTION()
	void OnTextureQualityHigherClicked();

	UFUNCTION()
	void OnTextureQualityLowerClicked();
	void SetNewTextureQuality(int IndexChange);

	void UpdateTextureQualityText();
#pragma endregion

#pragma region ShadowQuality



	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_ShadowQualityHigher;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_ShadowQualityLower;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_ShadowQualityText;

	int m_CurrentShadowQualityIndex = 0;

	UFUNCTION()
	void OnShadowQualityHigherClicked();

	UFUNCTION()
	void OnShadowQualityLowerClicked();
	void SetNewShadowQuality(int IndexChange);

	void UpdateShadowQualityText();
#pragma endregion

#pragma region GlobalIllumination

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_GlobalIlluminationHigher;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_GlobalIlluminationLower;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_GlobalIlluminationText;

	int m_CurrentGlobalIlluminationIndex = 0;

	UFUNCTION()
	void OnGlobalIlluminationHigherClicked();

	UFUNCTION()
	void OnGlobalIlluminationLowerClicked();
	void SetNewGlobalIllumination(int IndexChange);

	void UpdateGlobalIlluminationText();

#pragma endregion


#pragma region VSync




	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_VSyncEnabled;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_VSyncDisabled;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_VSyncText;

	UFUNCTION()
	void OnVsyncDisabled();

	UFUNCTION()
	void OnVSyncEnabled();
	void SetVSync(bool state);


	void UpdateVSyncText();
#pragma endregion

#pragma region Optimal



	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_Optimal;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_OptimalText;

	UFUNCTION()
	void UseOptimalSettings();
#pragma endregion


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_CancelApply;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_ConfirmApply;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* m_WarningImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* m_WarningText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_ApplySettings;
	
	UGameUserSettings* m_Settings;


	UFUNCTION() 
	void ShowWarning();

	UFUNCTION()
	void HideWarning();

	UFUNCTION()
	void SaveSettings();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* m_Back;

	UPROPERTY()
	UUserWidget* m_PreviousMenu;

	void NativeConstruct() override;

	void UpdateSettingsDisplayedText();

	UFUNCTION()
	void LoadPreviousMenu();

	void SetUpButtonBindings();


};
