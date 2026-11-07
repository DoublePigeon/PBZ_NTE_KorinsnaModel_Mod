<#
.SYNOPSIS
  Installs the UE4SS Lua half of the mod, in either the release or the dev flavour.

.DESCRIPTION
  The two profiles share one code base (ue4ss/KorinsnaRetarget). They differ only in logging and
  diagnostics: the dev profile adds ue4ss/dev/config.dev.lua, which main.lua merges over config.lua and
  which sets log_level=2 plus the read-only probes. Behaviour is identical - what you see in dev is what
  the game does in release.

  release (default): log_level=1, so a healthy session writes no log file at all; only a failing engine
  call or a scan error is written. Use it for playing.
  dev: log_level=2, every line plus the censuses. Use it for diagnosing.
  perf: release behaviour (log_level=1, no per-component logging) plus the scan timer, so a freeze can be
  measured without the logger itself being the cost. Writes `profile:` lines only.

  All three are installed into the same mod folder, so installing one removes the other's extra file.

.PARAMETER Profile
  release (default), dev or perf.

.EXAMPLE
  powershell -File tools\install_lua.ps1
  powershell -File tools\install_lua.ps1 -Profile dev
  powershell -File tools\install_lua.ps1 -Profile perf
#>
param(
    [ValidateSet("release", "dev", "perf")][string]$Profile = "release",
    [string]$GameRoot = "K:\SteamLibrary\steamapps\common\PBZ",
    [string]$RepoRoot = "J:\VS_Projects\PBZ_KorinsnaSkinMod",
    [switch]$KeepLog
)

$ErrorActionPreference = "Stop"

$source = Join-Path $RepoRoot "ue4ss\KorinsnaRetarget"
$devSource = Join-Path $RepoRoot "ue4ss\dev"
$ue4ssMods = Join-Path $GameRoot "platform\steam\ue4ss\Mods"
$target = Join-Path $ue4ssMods "KorinsnaRetarget"
$log = Join-Path $target "KorinsnaRetarget.log"

if (-not (Test-Path $source)) { throw "missing $source" }
if (-not (Test-Path $ue4ssMods)) { throw "UE4SS is not installed in $GameRoot" }

if (Test-Path $target) { Remove-Item $target -Recurse -Force }
New-Item -ItemType Directory -Force -Path $target | Out-Null
Copy-Item (Join-Path $source "*") $target -Recurse -Force

if ($Profile -eq "dev") {
    $devConfig = Join-Path $devSource "config.dev.lua"
    if (-not (Test-Path $devConfig)) { throw "missing $devConfig" }
    Copy-Item $devConfig (Join-Path $target "config.dev.lua") -Force
} elseif ($Profile -eq "perf") {
    $perfConfig = Join-Path $devSource "config.perf.lua"
    if (-not (Test-Path $perfConfig)) { throw "missing $perfConfig" }
    Copy-Item $perfConfig (Join-Path $target "config.dev.lua") -Force
}

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

Write-Host "== installed $Profile flavour into $target"
$list = Get-ChildItem $target -Recurse -File | Select-Object Length, FullName
$list | Format-Table -AutoSize
if ($Profile -eq "release") {
    Write-Host "   (release profile: log_level=1, only problems are written)"
} elseif ($Profile -eq "perf") {
    Write-Host "   (perf profile: log_level=1 + scan timer, writes 'profile:' lines only)"
} else {
    Write-Host "   (dev profile: log_level=2, full log + diagnostics)"
}
if (-not $KeepLog -and (Test-Path $log)) { Remove-Item $log -Force }
