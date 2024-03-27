using System;
using System.IO;
using UnrealBuildTool;

public class GLM : ModuleRules
{
	private const string VERSION = "glm-1.0.1";
    public GLM(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, VERSION));
    }
}