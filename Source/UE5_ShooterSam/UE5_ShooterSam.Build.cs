// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE5_ShooterSam : ModuleRules
{
	public UE5_ShooterSam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"Niagara"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"UE5_ShooterSam",
			"UE5_ShooterSam/Variant_Platforming",
			"UE5_ShooterSam/Variant_Platforming/Animation",
			"UE5_ShooterSam/Variant_Combat",
			"UE5_ShooterSam/Variant_Combat/AI",
			"UE5_ShooterSam/Variant_Combat/Animation",
			"UE5_ShooterSam/Variant_Combat/Gameplay",
			"UE5_ShooterSam/Variant_Combat/Interfaces",
			"UE5_ShooterSam/Variant_Combat/UI",
			"UE5_ShooterSam/Variant_SideScrolling",
			"UE5_ShooterSam/Variant_SideScrolling/AI",
			"UE5_ShooterSam/Variant_SideScrolling/Gameplay",
			"UE5_ShooterSam/Variant_SideScrolling/Interfaces",
			"UE5_ShooterSam/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
