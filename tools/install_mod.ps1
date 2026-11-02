<#
.SYNOPSIS
  Installs the Korinsna retarget mod: the IoStore container plus the UE4SS companion mod.

.DESCRIPTION
  Two pieces must be in place, because the mesh is not a replacement of a game asset any more:
    * the container ships the Korinsna mesh/IK rigs/retargeter/anim blueprint and blanks the
      hero's own parts,
    * the UE4SS mod adds the Korinsna component at runtime and points it at that anim blueprint.

  The game must be closed while copying; the containers are locked otherwise.
#>
param(
    [string]$GameRoot = "K:\SteamLibrary\steamapps\common\PBZ",
    [string]$RepoRoot = "J:\VS_Projects\PBZ_KorinsnaSkinMod",
    [string]$Name = "ProjectPBZ-Korinsna-Windows_P"
)

$ErrorActionPreference = "Stop"

$dist = Join-Path $RepoRoot "dist\Korinsna"
$mods = Join-Path $GameRoot "ProjectPBZ\Content\Paks\~mods"
$ue4ssMods = Join-Path $GameRoot "platform\steam\ue4ss\Mods"
$modSource = Join-Path $RepoRoot "ue4ss\KorinsnaRetarget"
$modTarget = Join-Path $ue4ssMods "KorinsnaRetarget"

# ---------------------------------------------------------------- container
if (-not (Test-Path $mods)) { New-Item -ItemType Directory -Force -Path $mods | Out-Null }
foreach ($ext in "pak", "utoc", "ucas") {
    $source = Join-Path $dist "$Name.$ext"
    if (-not (Test-Path $source)) { throw "missing build output: $source" }
    Copy-Item $source $mods -Force
}
Get-ChildItem $mods -Filter "$Name.*" | Format-Table Length, Name -AutoSize

# ---------------------------------------------------------------- ue4ss mod
if (-not (Test-Path $ue4ssMods)) { throw "UE4SS is not installed in $GameRoot" }
if (Test-Path $modTarget) { Remove-Item $modTarget -Recurse -Force }
New-Item -ItemType Directory -Force -Path $modTarget | Out-Null
Copy-Item (Join-Path $modSource "*") $modTarget -Recurse -Force
Get-ChildItem $modTarget -Recurse -File | Select-Object Length, FullName | Format-Table -AutoSize

# UE4SS reads mods.json; keep the existing entries and just make sure ours is enabled
$modsJson = Join-Path $ue4ssMods "mods.json"
$entries = New-Object System.Collections.ArrayList
if (Test-Path $modsJson) {
    $parsed = Get-Content $modsJson -Raw | ConvertFrom-Json
    foreach ($entry in $parsed) {
        if ($entry.mod_name -ne "KorinsnaRetarget") { [void]$entries.Add($entry) }
    }
}
[void]$entries.Add([pscustomobject]@{ mod_name = "KorinsnaRetarget"; mod_enabled = $true })
Set-Content -Path $modsJson -Value (ConvertTo-Json -InputObject @($entries) -Depth 4) -Encoding UTF8
Write-Host "mods.json updated:"
Get-Content $modsJson
