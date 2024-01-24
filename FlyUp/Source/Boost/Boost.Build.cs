using UnrealBuildTool;
using System;
using System.IO;

public class Boost : ModuleRules 
{ 
	public Boost(ReadOnlyTargetRules Target) : base(Target) 
	{ 
		Type = ModuleType.External;					
		PublicSystemIncludePaths.AddRange(
			new string[] {
				$"include"
			}
		);
	} 
}