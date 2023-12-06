// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class FlyUpTarget : TargetRules
{
	public FlyUpTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
        
		ExtraModuleNames.Add("FlyUp");
        ExtraModuleNames.Add("Pathfinding");
        if (Type == TargetType.Editor)
        {
            ExtraModuleNames.Add("PathfindingEditor");
        }
	}
}
