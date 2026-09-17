// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SurvivalCraft_PYPEditorTarget : TargetRules
{
    public SurvivalCraft_PYPEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V7;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8;
        ExtraModuleNames.Add("SurvivalCraft_PYP");

        // Global tanım değişikliklerine izin ver
        bOverrideBuildEnvironment = true;

        // C4668 uyarısını engeller
        GlobalDefinitions.Add("TEXTURESHARECORE_SDK=0");
        GlobalDefinitions.Add("TEXTURESHARECORE_DEBUGLOG=0");
        GlobalDefinitions.Add("TEXTURESHARECORE_BARRIER_DEBUGLOG=0");
    }
}