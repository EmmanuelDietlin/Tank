// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TanksGame : ModuleRules
{
	public TanksGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "RawInput", "InputDevice", "ApplicationCore" });
	}
}
