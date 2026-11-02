# Build the PBZ Korinsna mod container from a UE cook output.
# Usage: build_pak.ps1 -CookedDir <Saved/Cooked/Windows/ProjectPBZ> -OutDir <dist> -Name ProjectPBZ-Korinsna-Windows_P [-Only <regex,...>]
param(
    [Parameter(Mandatory = $true)][string]$CookedDir,
    [Parameter(Mandatory = $true)][string]$OutDir,
    [string]$Name = "ProjectPBZ-Korinsna-Windows_P",
    [string[]]$Include = @("Content/Korinsna/", "Plugins/HuaShira/"),
    [string[]]$Exclude = @("Hun_Skin_Skeleton", "PA_Hun")
)

$ErrorActionPreference = "Stop"
$retoc = "J:\retoc\retoc.exe"
$unrealPak = "K:\UnrealEngine\UE_5.7\Engine\Binaries\Win64\UnrealPak.exe"

New-Item -ItemType Directory -Force -Path $OutDir | Out-Null
$stage = Join-Path $env:TEMP ("korinsna_stage_" + [guid]::NewGuid().ToString("N"))
New-Item -ItemType Directory -Force -Path $stage | Out-Null

$files = Get-ChildItem $CookedDir -Recurse -File | Where-Object {
    $rel = $_.FullName.Substring($CookedDir.Length).TrimStart('\').Replace('\', '/')
    $keep = $false
    foreach ($inc in $Include) { if ($rel.StartsWith($inc)) { $keep = $true } }
    foreach ($exc in $Exclude) { if ($rel -like "*$exc*") { $keep = $false } }
    $keep -and $_.Extension -in ".uasset", ".uexp", ".ubulk"
}

if ($files.Count -eq 0) { throw "no cooked files matched in $CookedDir" }

foreach ($f in $files) {
    $rel = $f.FullName.Substring($CookedDir.Length).TrimStart('\')
    $dst = Join-Path (Join-Path $stage "ProjectPBZ") $rel
    New-Item -ItemType Directory -Force -Path (Split-Path $dst) | Out-Null
    Copy-Item $f.FullName $dst -Force
}

$utoc = Join-Path $OutDir "$Name.utoc"
$ucas = Join-Path $OutDir "$Name.ucas"
$pak = Join-Path $OutDir "$Name.pak"
foreach ($p in @($utoc, $ucas, $pak)) { Remove-Item $p -Force -ErrorAction SilentlyContinue }

& $retoc to-zen $stage $utoc --version UE5_7
if ($LASTEXITCODE -ne 0) { throw "retoc to-zen failed" }

# stub pak so the engine mounts the IoStore container next to it
$rsp = Join-Path $stage "empty.rsp"
Set-Content -Path $rsp -Value "" -Encoding ASCII
& $unrealPak $pak "-create=$rsp" | Out-Null

Remove-Item $stage -Recurse -Force -ErrorAction SilentlyContinue

Get-ChildItem $OutDir -Filter "$Name.*" | Format-Table Length, Name -AutoSize
& $retoc info $utoc
