using UnrealBuildTool; 

public class PathfindingEditor : ModuleRules 
{ 
	public PathfindingEditor(ReadOnlyTargetRules Target) : base(Target) 
	{ 
        PublicDependencyModuleNames.AddRange(new string[] {"FlyUp"}); 
		PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine"}); 
	} 
}