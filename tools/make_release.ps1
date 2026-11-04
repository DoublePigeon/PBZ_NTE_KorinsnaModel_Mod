<#
.SYNOPSIS
  Assembles the release folders: Release\KorinsnaModel (the IoStore container) and
  Release\KorinsnaRetarget (the UE4SS Lua half).

.DESCRIPTION
  Copies the two halves out of their build locations into a `Release` folder that can be handed to a
  user as-is (no archive):

    Release\KorinsnaModel\      <- dist\Korinsna\ProjectPBZ-Korinsna-Windows_P.{pak,utoc,ucas}
    Release\KorinsnaRetarget\   <- ue4ss\KorinsnaRetarget\ (release profile: no config.dev.lua)

  The user ends up copying `KorinsnaModel\*` into `<game>\ProjectPBZ\Content\Paks\~mods\` and
  `KorinsnaRetarget\` into `<game>\platform\steam\ue4ss\Mods\`.

  Before copying, the Lua half is checked (`tools\luacheck.py`, `tools\check_forward_refs.py` and the
  `tools\smoke_lua.py` worlds). `-SkipChecks` bypasses that - only for re-packaging something that was
  already validated.

.PARAMETER OutDir
  Where the two folders are written. Default: <repo>\Release.

.PARAMETER Name
  Container basename produced by tools\stage_iostore.ps1.

.EXAMPLE
  powershell -File tools\make_release.ps1
  powershell -File tools\make_release.ps1 -OutDir D:\PBZ-Korinsna-Release -SkipChecks
#>
param(
    [string]$OutDir = "",
    [string]$RepoRoot = "J:\VS_Projects\PBZ_KorinsnaSkinMod",
    [string]$Name = "ProjectPBZ-Korinsna-Windows_P",
    [switch]$SkipChecks
)

$ErrorActionPreference = "Stop"

if ([string]::IsNullOrWhiteSpace($OutDir)) { $OutDir = Join-Path $RepoRoot "Release" }

$containerSource = Join-Path $RepoRoot "dist\Korinsna"
$luaSource = Join-Path $RepoRoot "ue4ss\KorinsnaRetarget"
$containerTarget = Join-Path $OutDir "KorinsnaModel"
$luaTarget = Join-Path $OutDir "KorinsnaRetarget"

# ---------------------------------------------------------------- validate the Lua half first
if (-not $SkipChecks) {
    Write-Host "== checks"
    foreach ($script in "luacheck.py", "check_forward_refs.py") {
        & python (Join-Path $RepoRoot "tools\$script")
        if ($LASTEXITCODE -ne 0) { throw "$script failed - not packaging" }
    }
    & python (Join-Path $RepoRoot "tools\smoke_lua.py")
    if ($LASTEXITCODE -ne 0) { throw "smoke_lua.py failed - not packaging" }
}

# ---------------------------------------------------------------- container
foreach ($ext in "pak", "utoc", "ucas") {
    $file = Join-Path $containerSource "$Name.$ext"
    if (-not (Test-Path $file)) {
        throw "missing $file - run tools\build_all.ps1 (or stage_iostore.ps1) first"
    }
}
if (Test-Path $containerTarget) { Remove-Item $containerTarget -Recurse -Force }
New-Item -ItemType Directory -Force -Path $containerTarget | Out-Null
foreach ($ext in "pak", "utoc", "ucas") {
    Copy-Item (Join-Path $containerSource "$Name.$ext") $containerTarget -Force
}

# ---------------------------------------------------------------- ue4ss companion (release profile)
if (-not (Test-Path (Join-Path $luaSource "scripts\main.lua"))) {
    throw "missing $luaSource\scripts\main.lua"
}
if (Test-Path $luaTarget) { Remove-Item $luaTarget -Recurse -Force }
New-Item -ItemType Directory -Force -Path $luaTarget | Out-Null
Copy-Item (Join-Path $luaSource "*") $luaTarget -Recurse -Force

# A dev overlay or a stale log must never ship: `config.dev.lua` turns the verbose log on, and the log
# itself is a runtime artefact.
foreach ($stale in "config.dev.lua", "KorinsnaRetarget.log") {
    $path = Join-Path $luaTarget $stale
    if (Test-Path $path) { Remove-Item $path -Force }
}

# ---------------------------------------------------------------- report
Write-Host ""
Write-Host "== $OutDir"
Get-ChildItem $OutDir -Recurse -File |
    Where-Object { $_.FullName -like "$containerTarget*" -or $_.FullName -like "$luaTarget*" } |
    Select-Object @{n = "Size"; e = { $_.Length } },
                  @{n = "File"; e = { $_.FullName.Substring($OutDir.Length + 1) } } |
    Format-Table -AutoSize

Write-Host "install:"
Write-Host "  $containerTarget\*  ->  <game>\ProjectPBZ\Content\Paks\~mods\"
Write-Host "  $luaTarget\         ->  <game>\platform\steam\ue4ss\Mods\KorinsnaRetarget\"
