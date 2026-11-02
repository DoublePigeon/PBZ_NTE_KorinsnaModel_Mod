# Stage a pruned cook directory into an IoStore container (native UE 5.7 pipeline).
# Usage: stage_iostore.ps1 -Project <uproject> -CookedRoot <.../Saved/Cooked/Windows> -OutDir <dir> -Name <container name> [-Drop <regex,...>]
param(
    [Parameter(Mandatory = $true)][string]$Project,
    [Parameter(Mandatory = $true)][string]$CookedRoot,
    [Parameter(Mandatory = $true)][string]$OutDir,
    [string]$Name = "ProjectPBZ-Korinsna-Windows_P",
    # Regular expressions matched against the cooked file path (relative to the project's cooked
    # folder). Regex rather than wildcards because some names are prefixes of others:
    # SkinParts/Hun_Head vs SkinParts/Hun_Head_New, which is the carrier mesh we *do* ship.
    [string[]]$Drop = @(
        # The game skeleton must never be overridden (it crashes the game). The blank part meshes
        # reference it, and that reference resolves to the copy already inside the game at runtime,
        # which is the one the hero's AnimBP was compiled against.
        "Hun_Skin_Skeleton",
        "Korinsna/Source/",           # authoring-only preview mesh + donor skeleton
        "MI_ZeroHun_",                # placeholder material instances used to author the slot order
        "MI_Korinsna_",               # legacy self-made instances (no shaders in this build)
        "M_Korinsna_Toon"             # ditto
    ),
    [string[]]$KeepContent = @("Korinsna", "PBZContent", "Test"),
    [string[]]$KeepPlugin = @("HuaShira", "AkashaEffects")
)

$ErrorActionPreference = "Stop"
$uat = "K:\UnrealEngine\UE_5.7\Engine\Build\BatchFiles\RunUAT.bat"
$unrealPak = "K:\UnrealEngine\UE_5.7\Engine\Binaries\Win64\UnrealPak.exe"
$retoc = "J:\retoc\retoc.exe"

$projDir = Split-Path $Project -Parent
$projContent = Join-Path $CookedRoot (Split-Path $Project -Leaf).Replace(".uproject", "")

# --- prune cooked output so staging only sees what we ship ---
if (Test-Path (Join-Path $CookedRoot "Engine")) {
    Remove-Item (Join-Path $CookedRoot "Engine") -Recurse -Force
}
if (Test-Path $projContent) {
    Get-ChildItem $projContent -File -Force | Remove-Item -Force -ErrorAction SilentlyContinue
    $contentDir = Join-Path $projContent "Content"
    if (Test-Path $contentDir) {
        Get-ChildItem $contentDir -Force | Where-Object { $KeepContent -notcontains $_.Name } | Remove-Item -Recurse -Force -ErrorAction SilentlyContinue
    }
    $pluginsDir = Join-Path $projContent "Plugins"
    if (Test-Path $pluginsDir) {
        Get-ChildItem $pluginsDir -Force | Where-Object { $KeepPlugin -notcontains $_.Name } | Remove-Item -Recurse -Force -ErrorAction SilentlyContinue
    }
    $shaderSrc = Join-Path $projContent "Metadata\ShaderLibrarySource"
    if (Test-Path $shaderSrc) { Remove-Item $shaderSrc -Recurse -Force }
    $projContentPrefix = $projContent.Replace('\', '/')
    Get-ChildItem $projContent -Recurse -File -ErrorAction SilentlyContinue | ForEach-Object {
        $rel = $_.FullName.Replace('\', '/')
        if ($rel.StartsWith($projContentPrefix)) { $rel = $rel.Substring($projContentPrefix.Length).TrimStart('/') }
        foreach ($pattern in $Drop) {
            if ($rel -match $pattern) {
                Remove-Item $_.FullName -Force
                break
            }
        }
    }
}

# --- clear staging state ---
Remove-Item (Join-Path $projDir "Saved\StagedBuilds") -Recurse -Force -ErrorAction SilentlyContinue
$stageOut = Join-Path $projDir "Saved\KorinsnaStage"
Remove-Item $stageOut -Recurse -Force -ErrorAction SilentlyContinue

& $uat BuildCookRun "-project=$Project" -noP4 -platform=Win64 -clientconfig=Development `
    -skipbuild -skipcook -stage -pak -iostore -unattended -nopause -utf8output `
    "-archive" "-archivedirectory=$stageOut" | Out-Host
if ($LASTEXITCODE -ne 0) { throw "UAT staging failed" }

$paks = Join-Path $stageOut "Windows\ProjectPBZ\Content\Paks"
$utoc = Join-Path $paks "ProjectPBZ-Windows.utoc"
$ucas = Join-Path $paks "ProjectPBZ-Windows.ucas"

New-Item -ItemType Directory -Force -Path $OutDir | Out-Null
$outUtoc = Join-Path $OutDir "$Name.utoc"
$outUcas = Join-Path $OutDir "$Name.ucas"
$outPak = Join-Path $OutDir "$Name.pak"
foreach ($p in @($outUtoc, $outUcas, $outPak)) { Remove-Item $p -Force -ErrorAction SilentlyContinue }

Copy-Item $utoc $outUtoc -Force
Copy-Item $ucas $outUcas -Force

$rsp = Join-Path $env:TEMP "korinsna_empty.rsp"
Set-Content -Path $rsp -Value "" -Encoding ASCII
& $unrealPak $outPak "-create=$rsp" | Out-Null

& $retoc info $outUtoc
Get-ChildItem $OutDir -Filter "$Name.*" | Format-Table Length, Name -AutoSize
