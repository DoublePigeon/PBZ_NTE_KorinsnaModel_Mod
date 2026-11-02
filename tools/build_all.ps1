# Full mod build: UE 5.7 native cook -> IoStore staging -> install (pak + UE4SS companion).
#
# Usage:
#   build_all.ps1              full rebuild
#   build_all.ps1 -SkipCpp     module already built
#   build_all.ps1 -SkipAssets  reuse the assets already in the project
#   build_all.ps1 -SkipCook    reuse the previous cook
#   build_all.ps1 -NoInstall   leave the output in dist/ only
param(
    [switch]$SkipCpp,
    [switch]$SkipAssets,
    [switch]$SkipCook,
    [switch]$NoInstall,
    [string]$Name = "ProjectPBZ-Korinsna-Windows_P"
)

$ErrorActionPreference = "Stop"
$root = "J:\VS_Projects\PBZ_KorinsnaSkinMod"
$ue = "K:\UnrealEngine\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
$uproject = Join-Path $root "ue\ProjectPBZ\ProjectPBZ.uproject"
$cookRoot = Join-Path $root "ue\ProjectPBZ\Saved\Cooked\Windows"
$dist = Join-Path $root "dist\Korinsna"
$extract = Join-Path $root "extract"

function Invoke-Python([string]$script, [string]$logName) {
    Write-Host "== python: $script"
    & $ue $uproject "-ExecutePythonScript=$root\ue\scripts\$script" -unattended -nopause -nosplash -nosound -stdout 2>&1 |
        Out-File (Join-Path $extract $logName) -Encoding utf8
    if ($LASTEXITCODE -ne 0) { throw "python failed: $script" }
}

# ---------------------------------------------------------------- C++ (editor helper for the anim bp)
if (-not $SkipCpp) {
    Write-Host "== build editor module"
    & (Join-Path $root "tools\patch_engine_swarm_sdk.ps1") | Out-Host
    $build = "K:\UnrealEngine\UE_5.7\Engine\Build\BatchFiles\Build.bat"
    & $build ProjectPBZEditor Win64 Development "-project=$uproject" -waitmutex 2>&1 |
        Out-File (Join-Path $extract "ue-build-module.log") -Encoding utf8
    if ($LASTEXITCODE -ne 0) { throw "editor module build failed" }
}

# ---------------------------------------------------------------- assets, in dependency order
if (-not $SkipAssets) {
    Invoke-Python "import_korinsna_sk.py" "ue-skimport.log"       # SK_Korinsna + its own skeleton
    Invoke-Python "build_mod_assets.py" "ue-buildassets.log"       # textures + material slots
    Invoke-Python "import_hun_preview.py" "ue-hunpreview.log"      # game-bone-name mesh for the source rig
    Invoke-Python "build_retarget_assets.py" "ue-retarget.log"     # IK rigs, retargeter, anim bp
    Invoke-Python "build_carrier_mesh.py" "ue-carrier.log"         # ships the mesh as SkinParts/Hun_Head_New
    # the hero's own outfit is blanked at asset level: the runtime script cannot hide the body mesh
    # (it is the retarget pose source and must keep animating), and the robe/hair live on it
    Invoke-Python "import_hun_skeleton.py" "ue-hunskeleton.log"    # editor-only copy of the game skeleton
    Invoke-Python "import_blank_parts.py" "ue-blankparts.log"      # zero-area meshes over the parts
    Invoke-Python "blank_cloth_assets.py" "ue-blankcloth.log"      # empty Chaos Cloth (robe/hair/cape)
    Invoke-Python "check_retarget_chain.py" "ue-checkchain.log"    # offline proof the retarget works
    Invoke-Python "verify_retarget_setup.py" "ue-verify-retarget.log"
}

# ---------------------------------------------------------------- cook + stage
if (-not $SkipCook) {
    Write-Host "== cook"
    & $ue $uproject -run=Cook -TargetPlatform=Windows -CookAll -SkipEditorContent -unattended -nopause -nosplash -nosound -stdout 2>&1 |
        Out-File (Join-Path $extract "ue-cook.log") -Encoding utf8
    if ($LASTEXITCODE -ne 0) { throw "cook failed" }
}

Write-Host "== stage"
& (Join-Path $root "tools\stage_iostore.ps1") -Project $uproject -CookedRoot $cookRoot -OutDir $dist -Name $Name 2>&1 |
    Out-File (Join-Path $extract "stage.log") -Encoding utf8
if (-not (Test-Path (Join-Path $dist "$Name.utoc"))) { throw "stage failed, see extract\stage.log" }

# ---------------------------------------------------------------- install
if (-not $NoInstall) {
    Write-Host "== install"
    & (Join-Path $root "tools\install_mod.ps1") -Name $Name | Out-Host
}

Write-Host "== done"
Get-ChildItem $dist -Filter "$Name.*" | Format-Table Length, Name -AutoSize
