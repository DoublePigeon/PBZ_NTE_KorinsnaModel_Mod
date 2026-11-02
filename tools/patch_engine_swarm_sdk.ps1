<#
.SYNOPSIS
  Lets the editor target build on machines without the .NET Framework SDK.

.DESCRIPTION
  Every UE editor target pulls in UnrealEd -> SwarmInterface. SwarmInterface.Build.cs throws
  if the .NET Framework SDK (NETFXSDK, mscoree.h) is missing, even though the C++ in that module
  never touches it - the SDK is only used to install the C# AgentInterface and to add include
  paths nothing includes. Without this patch UnrealBuildTool fails with
    "Unable to instantiate module 'SwarmInterface': Could not find NetFxSDK install dir"
  for every editor build, which blocks compiling the Korinsna authoring helpers.

  The patch is idempotent and only downgrades the hard failure to a warning.

.NOTES
  Run it again after an engine update (it only edits the UBT rules file of the given engine).
#>
param(
    [string]$Engine = "K:\UnrealEngine\UE_5.7"
)

$ErrorActionPreference = "Stop"
$file = Join-Path $Engine "Engine\Source\Editor\SwarmInterface\SwarmInterface.Build.cs"

if (-not (Test-Path $file)) {
    throw "engine rules file not found: $file"
}

$text = Get-Content $file -Raw
if ($text -match "PBZ_MOD_NO_NETFXSDK") {
    Write-Host "already patched: $file"
    exit 0
}

$old = @'
			string NetFxSdkDir = Target.WindowsPlatform.NetFxSdkDir;
			if (NetFxSdkDir == null)
			{
				throw new BuildException("Could not find NetFxSDK install dir; this will prevent SwarmInterface from installing.  Install a version of .NET Framework SDK at 4.6.0 or higher.");
			}

			ExtraRootPath = ("NetFxSdk", NetFxSdkDir);

			string ArchFolder = Target.WindowsPlatform.Architecture.WindowsLibDir;

			PrivateIncludePaths.Add(Path.Combine(NetFxSdkDir, "include", "um"));
			PublicSystemLibraryPaths.Add(Path.Combine(NetFxSdkDir, "lib", "um", ArchFolder));
			bHasSwarm = true;
'@

$new = @'
			// PBZ_MOD_NO_NETFXSDK: the .NET Framework SDK is only needed to install the C# agent
			// interface and to add include paths no C++ in this module uses, so a missing SDK is a
			// warning instead of a hard failure. Revert by deleting this block's marker.
			string NetFxSdkDir = Target.WindowsPlatform.NetFxSdkDir;
			if (NetFxSdkDir == null)
			{
				System.Console.WriteLine("SwarmInterface: no NetFxSDK install dir, building without the .NET agent interface.");
			}
			else
			{
				ExtraRootPath = ("NetFxSdk", NetFxSdkDir);

				string ArchFolder = Target.WindowsPlatform.Architecture.WindowsLibDir;

				PrivateIncludePaths.Add(Path.Combine(NetFxSdkDir, "include", "um"));
				PublicSystemLibraryPaths.Add(Path.Combine(NetFxSdkDir, "lib", "um", ArchFolder));
				bHasSwarm = true;
			}
'@

if (-not $text.Contains($old)) {
    throw "unexpected SwarmInterface.Build.cs layout, refusing to patch blindly"
}

$text = $text.Replace($old, $new)
# engine installations are shipped read-only; only lift the flag for the write itself
$wasReadOnly = (Get-ItemProperty -Path $file).IsReadOnly
if ($wasReadOnly) { Set-ItemProperty -Path $file -Name IsReadOnly -Value $false }
Set-Content -Path $file -Value $text -Encoding UTF8 -NoNewline
if ($wasReadOnly) { Set-ItemProperty -Path $file -Name IsReadOnly -Value $true }
Write-Host "patched: $file"
