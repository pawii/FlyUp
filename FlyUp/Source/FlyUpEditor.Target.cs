// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class FlyUpEditorTarget : TargetRules
{
	public FlyUpEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
        
		ExtraModuleNames.Add("FlyUp");
        ExtraModuleNames.Add("Pathfinding");
        ExtraModuleNames.Add("PathfindingEditor");
	}
}
