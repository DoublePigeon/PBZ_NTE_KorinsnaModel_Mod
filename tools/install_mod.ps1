<#
.SYNOPSIS
  Installs the Korinsna retarget mod: the IoStore container plus the UE4SS companion mod.

.DESCRIPTION
  Two pieces must be in place, because the mesh is not a replacement of a game asset any more:
    * the container ships the Korinsna mesh/IK rigs/retargeter/anim blueprint and blanks the
      hero's own parts,
    * the UE4SS mod adds the Korinsna component at runtime and points it at that anim blueprint.

  The Lua half comes in two flavours (see tools/install_lua.ps1): `release` (default, no object
  listeners) and `dev` (adds the listeners and the verbose diagnostics).

  The game must be closed while copying; the containers are locked otherwise.
#>
param(
    [string]$GameRoot = "K:\SteamLibrary\steamapps\common\PBZ",
    [string]$RepoRoot = "J:\VS_Projects\PBZ_KorinsnaSkinMod",
    [string]$Name = "ProjectPBZ-Korinsna-Windows_P",
    [ValidateSet("release", "dev")][string]$Profile = "release"
)

$ErrorActionPreference = "Stop"

$dist = Join-Path $RepoRoot "dist\Korinsna"
$mods = Join-Path $GameRoot "ProjectPBZ\Content\Paks\~mods"

# ---------------------------------------------------------------- container
if (-not (Test-Path $mods)) { New-Item -ItemType Directory -Force -Path $mods | Out-Null }
foreach ($ext in "pak", "utoc", "ucas") {
    $source = Join-Path $dist "$Name.$ext"
    if (-not (Test-Path $source)) { throw "missing build output: $source" }
    Copy-Item $source $mods -Force
}
Get-ChildItem $mods -Filter "$Name.*" | Format-Table Length, Name -AutoSize

# ---------------------------------------------------------------- ue4ss mod
# Same folder for both flavours; the script removes the previous flavour's extra files.
& (Join-Path $RepoRoot "tools\install_lua.ps1") -Profile $Profile -GameRoot $GameRoot -RepoRoot $RepoRoot
