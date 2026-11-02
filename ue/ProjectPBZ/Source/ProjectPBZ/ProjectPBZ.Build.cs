using UnrealBuildTool;

public class ProjectPBZ : ModuleRules
{
	public ProjectPBZ(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });

		// authoring helpers only (KorinsnaEditorLibrary): never part of a packaged build
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[]
			{
				"UnrealEd",
				"AssetTools",
				"BlueprintGraph",
				"Kismet",
				"KismetCompiler",
				"AnimGraph",
				"AnimGraphRuntime",
				"IKRig",
				"IKRigDeveloper",
			});
		}
	}
}
