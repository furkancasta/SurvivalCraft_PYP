// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SurvivalCraft_PYP : ModuleRules
{
	public SurvivalCraft_PYP(ReadOnlyTargetRules Target) : base(Target)
	{

        // C4668 uyarısının derlemeyi kitlemesini engeller
        bEnableUndefinedIdentifierWarnings = false;

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
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"SurvivalCraft_PYP",
			"SurvivalCraft_PYP/Variant_Horror",
			"SurvivalCraft_PYP/Variant_Horror/UI",
			"SurvivalCraft_PYP/Variant_Shooter",
			"SurvivalCraft_PYP/Variant_Shooter/AI",
			"SurvivalCraft_PYP/Variant_Shooter/UI",
			"SurvivalCraft_PYP/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
