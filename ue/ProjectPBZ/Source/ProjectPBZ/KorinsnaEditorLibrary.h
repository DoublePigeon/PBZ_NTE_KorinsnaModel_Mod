// Editor-only authoring helpers for the Korinsna retarget mod.
//
// The Python asset pipeline can create IK Rigs and IK Retargeters through their
// BlueprintCallable controllers, but it cannot add nodes to an animation graph: anim graph
// nodes are only creatable through FGraphNodeCreator in C++. This library exposes that one
// missing step so the whole build stays scriptable.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KorinsnaEditorLibrary.generated.h"

UCLASS()
class PROJECTPBZ_API UKorinsnaEditorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Creates (or recreates) an animation blueprint whose graph is a
	 * "Retarget Pose From Mesh" node wired into the output pose, optionally followed by a chain of
	 * KawaiiPhysics nodes (hair / skirt physics) configured from a JSON file.
	 *
	 * The node reads its source pose from the skeletal mesh component it is attached to, so
	 * the runtime mod only has to parent the Korinsna component under the game's own body
	 * component - no runtime property setup is needed.
	 *
	 * @param AssetPath         object path of the anim blueprint to create, e.g. /Game/Korinsna/ABP_Korinsna_Retarget
	 * @param SkeletonPath      object path of the target (Korinsna) skeleton
	 * @param RetargeterPath    object path of the IK Retargeter asset
	 * @param PhysicsConfigPath absolute path of ue/kawaii_config.json; empty = retarget only
	 */
	UFUNCTION(BlueprintCallable, Category = "Korinsna")
	static bool CreateRetargetAnimBlueprint(const FString& AssetPath, const FString& SkeletonPath,
		const FString& RetargeterPath, const FString& PhysicsConfigPath);

	/**
	 * Describes the KawaiiPhysics nodes of an already saved blueprint: graph order, root bone of each
	 * node, the physics settings that were applied, and how many collision spheres each carries.
	 *
	 * The runtime log cannot show any of this, and a node whose RootBone did not resolve looks exactly
	 * like a node whose settings are wrong - so the build has to prove what it authored.
	 */
	UFUNCTION(BlueprintCallable, Category = "Korinsna")
	static FString DescribeKawaiiPhysics(const FString& AssetPath);

	/**
	 * Describes the anim graph of an already saved retarget blueprint: node classes, the retarget
	 * node's source mode and the retargeter it points at, plus whether the skeleton of the target
	 * mesh is the one the blueprint was compiled against.
	 *
	 * The runtime side can only see "an anim instance exists", so this is the only way to tell a
	 * mis-authored graph from a runtime problem.
	 */
	UFUNCTION(BlueprintCallable, Category = "Korinsna")
	static FString InspectRetargetAnimBlueprint(const FString& AssetPath);

	/**
	 * Runs the IK Retargeter's processor once, in the editor, against the two meshes used in game.
	 *
	 * This is the same initialization the "Retarget Pose From Mesh" node performs at runtime; if it
	 * fails there the node silently outputs the reference pose (an unanimated A-pose) and the game
	 * logs nothing we can read.
	 */
	UFUNCTION(BlueprintCallable, Category = "Korinsna")
	static FString ValidateRetargeter(const FString& SourceMeshPath, const FString& TargetMeshPath, const FString& RetargeterPath);

	/**
	 * Copies the mesh's reference pose onto its own skeleton.
	 *
	 * The retargeter only transfers a rotation delta relative to the reference pose, so the skeleton's
	 * reference pose has to match the mesh's bind pose exactly. If they drift apart the error is a
	 * constant offset on every bone - invisible on large bones, but on fingers a few degrees is enough
	 * to read as curled, deformed fingers. `USkeleton::UpdateReferencePoseFromMesh` is not exposed to
	 * Python, which is why this wrapper exists.
	 */
	UFUNCTION(BlueprintCallable, Category = "Korinsna")
	static FString SyncReferencePose(const FString& MeshPath);
};
