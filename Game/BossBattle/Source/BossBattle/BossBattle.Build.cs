// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BossBattle : ModuleRules
{
	public BossBattle(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "GameplayTasks", "NavigationSystem", "GameplayDebugger", "DeveloperSettings", "Niagara" });
	}
}
