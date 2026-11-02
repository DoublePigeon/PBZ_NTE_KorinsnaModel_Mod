using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectPBZEditorTarget : TargetRules
{
	public ProjectPBZEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("ProjectPBZ");
	}
}
