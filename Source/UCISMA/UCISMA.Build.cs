// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UCISMA : ModuleRules
{
	public UCISMA(ReadOnlyTargetRules Target) : base(Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] {
    "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
    "UMG", "Niagara", "Slate", "SlateCore", "GeometryCollectionEngine", "ChaosSolverEngine"
    });

        // ������ ���� ����� �̷��� ���� �и�
        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "LevelEditor" });
        }
    }
}
