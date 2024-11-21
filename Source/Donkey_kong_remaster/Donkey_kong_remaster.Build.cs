// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Donkey_kong_remaster : ModuleRules
{
	public Donkey_kong_remaster(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
