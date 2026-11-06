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
				// Kawaii Physics: the runtime anim node (hair / skirt physics) plus its graph node, which
				// only the editor module provides. The game already ships the runtime half, so the cooked
				// asset needs nothing else at run time.
				"KawaiiPhysics",
				"KawaiiPhysicsEd",
				// physics asset generation for the RigidBody cloth path
				"PhysicsUtilities",
				"Json",
			});
		}
	}
}
