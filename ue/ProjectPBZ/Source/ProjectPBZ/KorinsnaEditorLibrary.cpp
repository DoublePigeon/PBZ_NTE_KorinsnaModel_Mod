#include "KorinsnaEditorLibrary.h"

#if WITH_EDITOR

#include "Animation/AnimBlueprint.h"
#include "Animation/AnimInstance.h"
#include "Animation/Skeleton.h"
#include "Factories/AnimBlueprintFactory.h"
#include "AnimGraphNode_Base.h"
#include "AnimGraphNode_Root.h"
#include "AnimGraphNode_RetargetPoseFromMesh.h"
#include "AnimationGraph.h"
#include "AnimNodes/AnimNode_RetargetPoseFromMesh.h"
#include "AssetToolsModule.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphPin.h"
#include "FileHelpers.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Logging/LogMacros.h"
#include "ObjectTools.h"
#include "Retargeter/IKRetargeter.h"

DEFINE_LOG_CATEGORY_STATIC(LogKorinsnaAuthoring, Log, All);

namespace
{
	/** The anim node lives in a private UPROPERTY on the graph node, so go through reflection. */
	FAnimNode_RetargetPoseFromMesh* GetAnimNode(UAnimGraphNode_RetargetPoseFromMesh* GraphNode)
	{
		FStructProperty* NodeProperty = FindFProperty<FStructProperty>(
			UAnimGraphNode_RetargetPoseFromMesh::StaticClass(), TEXT("Node"));
		if (NodeProperty == nullptr || NodeProperty->Struct != FAnimNode_RetargetPoseFromMesh::StaticStruct())
		{
			return nullptr;
		}
		return NodeProperty->ContainerPtrToValuePtr<FAnimNode_RetargetPoseFromMesh>(GraphNode);
	}

	UEdGraphPin* FirstPin(UEdGraphNode* Node, EEdGraphPinDirection Direction)
	{
		for (UEdGraphPin* Pin : Node->Pins)
		{
			if (Pin != nullptr && Pin->Direction == Direction)
			{
				return Pin;
			}
		}
		return nullptr;
	}
}

bool UKorinsnaEditorLibrary::CreateRetargetAnimBlueprint(const FString& AssetPath, const FString& SkeletonPath, const FString& RetargeterPath)
{
	USkeleton* Skeleton = LoadObject<USkeleton>(nullptr, *SkeletonPath);
	if (Skeleton == nullptr)
	{
		UE_LOG(LogKorinsnaAuthoring, Error, TEXT("skeleton not found: %s"), *SkeletonPath);
		return false;
	}

	UIKRetargeter* Retargeter = LoadObject<UIKRetargeter>(nullptr, *RetargeterPath);
	if (Retargeter == nullptr)
	{
		UE_LOG(LogKorinsnaAuthoring, Error, TEXT("IK retargeter not found: %s"), *RetargeterPath);
		return false;
	}

	FString PackagePath, AssetName;
	if (!AssetPath.Split(TEXT("/"), &PackagePath, &AssetName, ESearchCase::IgnoreCase, ESearchDir::FromEnd))
	{
		UE_LOG(LogKorinsnaAuthoring, Error, TEXT("asset path must be a package path: %s"), *AssetPath);
		return false;
	}

	if (UObject* Existing = LoadObject<UObject>(nullptr, *AssetPath))
	{
		TArray<UObject*> ObjectsToDelete;
		ObjectsToDelete.Add(Existing);
		ObjectTools::ForceDeleteObjects(ObjectsToDelete, false);
	}

	UAnimBlueprintFactory* Factory = NewObject<UAnimBlueprintFactory>();
	Factory->TargetSkeleton = Skeleton;
	Factory->ParentClass = UAnimInstance::StaticClass();

	UAnimBlueprint* Blueprint = Cast<UAnimBlueprint>(
		FAssetToolsModule::GetModule().Get().CreateAsset(AssetName, PackagePath, UAnimBlueprint::StaticClass(), Factory));
	if (Blueprint == nullptr)
	{
		UE_LOG(LogKorinsnaAuthoring, Error, TEXT("could not create anim blueprint %s"), *AssetPath);
		return false;
	}

	UAnimationGraph* AnimGraph = nullptr;
	for (UEdGraph* Graph : Blueprint->FunctionGraphs)
	{
		AnimGraph = Cast<UAnimationGraph>(Graph);
		if (AnimGraph != nullptr)
		{
			break;
		}
	}
	if (AnimGraph == nullptr)
	{
		UE_LOG(LogKorinsnaAuthoring, Error, TEXT("anim blueprint has no animation graph"));
		return false;
	}

	UAnimGraphNode_Root* RootNode = Cast<UAnimGraphNode_Root>(FBlueprintEditorUtils::GetAnimGraphRoot(AnimGraph));
	if (RootNode == nullptr)
	{
		UE_LOG(LogKorinsnaAuthoring, Error, TEXT("anim graph has no root node"));
		return false;
	}

	FGraphNodeCreator<UAnimGraphNode_RetargetPoseFromMesh> NodeCreator(*AnimGraph);
	UAnimGraphNode_RetargetPoseFromMesh* RetargetNode = NodeCreator.CreateNode();
	RetargetNode->NodePosX = RootNode->NodePosX - 400;
	RetargetNode->NodePosY = RootNode->NodePosY;
	NodeCreator.Finalize();

	FAnimNode_RetargetPoseFromMesh* AnimNode = GetAnimNode(RetargetNode);
	if (AnimNode == nullptr)
	{
		UE_LOG(LogKorinsnaAuthoring, Error, TEXT("retarget node does not expose FAnimNode_RetargetPoseFromMesh"));
		return false;
	}
	AnimNode->RetargetFrom = ERetargetSourceMode::ParentSkeletalMeshComponent;
	AnimNode->IKRetargeterAsset = Retargeter;

	UEdGraphPin* OutputPin = FirstPin(RetargetNode, EGPD_Output);
	UEdGraphPin* InputPin = FirstPin(RootNode, EGPD_Input);
	if (OutputPin == nullptr || InputPin == nullptr)
	{
		UE_LOG(LogKorinsnaAuthoring, Error, TEXT("retarget node or root node has no pose pin"));
		return false;
	}
	if (!AnimGraph->GetSchema()->TryCreateConnection(OutputPin, InputPin))
	{
		UE_LOG(LogKorinsnaAuthoring, Error, TEXT("could not connect retarget node to the output pose"));
		return false;
	}

	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);
	FKismetEditorUtilities::CompileBlueprint(Blueprint);

	UPackage* Package = Blueprint->GetOutermost();
	Package->MarkPackageDirty();
	UEditorLoadingAndSavingUtils::SavePackages({Package}, false);

	UE_LOG(LogKorinsnaAuthoring, Log, TEXT("created %s (graph %s, retargeter %s)"),
		*AssetPath, *AnimGraph->GetName(), *Retargeter->GetName());
	return true;
}

FString UKorinsnaEditorLibrary::InspectRetargetAnimBlueprint(const FString& AssetPath)
{
	TStringBuilder<2048> Report;

	UAnimBlueprint* Blueprint = LoadObject<UAnimBlueprint>(nullptr, *AssetPath);
	if (Blueprint == nullptr)
	{
		return FString::Printf(TEXT("missing anim blueprint %s"), *AssetPath);
	}

	UClass* GeneratedClass = Blueprint->GeneratedClass;
	Report.Appendf(TEXT("generated=%s\n"), GeneratedClass ? *GeneratedClass->GetPathName() : TEXT("None"));

	if (const USkeleton* TargetSkeleton = Blueprint->TargetSkeleton)
	{
		Report.Appendf(TEXT("target skeleton=%s\n"), *TargetSkeleton->GetPathName());
	}
	else
	{
		Report.Append(TEXT("target skeleton=None\n"));
	}

	for (UEdGraph* Graph : Blueprint->FunctionGraphs)
	{
		if (Cast<UAnimationGraph>(Graph) == nullptr)
		{
			continue;
		}
		Report.Appendf(TEXT("graph %s\n"), *Graph->GetName());
		for (UEdGraphNode* GraphNode : Graph->Nodes)
		{
			Report.Appendf(TEXT("  node %s class=%s\n"), *GraphNode->GetName(),
				*GraphNode->GetClass()->GetName());

			if (UAnimGraphNode_RetargetPoseFromMesh* RetargetNode = Cast<UAnimGraphNode_RetargetPoseFromMesh>(GraphNode))
			{
				if (const FAnimNode_RetargetPoseFromMesh* AnimNode = GetAnimNode(RetargetNode))
				{
					Report.Appendf(TEXT("    source mode=%s\n"),
						AnimNode->RetargetFrom == ERetargetSourceMode::ParentSkeletalMeshComponent ? TEXT("parent component")
						: AnimNode->RetargetFrom == ERetargetSourceMode::CustomSkeletalMeshComponent ? TEXT("custom component")
						: TEXT("source pose pin"));
					Report.Appendf(TEXT("    retargeter=%s\n"),
						AnimNode->IKRetargeterAsset ? *AnimNode->IKRetargeterAsset->GetPathName() : TEXT("None"));
				}
				else
				{
					Report.Append(TEXT("    could not read the anim node\n"));
				}
			}
		}
	}

	return Report.ToString();
}

FString UKorinsnaEditorLibrary::ValidateRetargeter(const FString& SourceMeshPath, const FString& TargetMeshPath, const FString& RetargeterPath)
{
	TStringBuilder<2048> Report;

	USkeletalMesh* SourceMesh = LoadObject<USkeletalMesh>(nullptr, *SourceMeshPath);
	USkeletalMesh* TargetMesh = LoadObject<USkeletalMesh>(nullptr, *TargetMeshPath);
	UIKRetargeter* Retargeter = LoadObject<UIKRetargeter>(nullptr, *RetargeterPath);
	if (SourceMesh == nullptr || TargetMesh == nullptr || Retargeter == nullptr)
	{
		return FString::Printf(TEXT("missing asset: source=%s target=%s retargeter=%s"),
			SourceMesh ? TEXT("ok") : TEXT("MISSING"),
			TargetMesh ? TEXT("ok") : TEXT("MISSING"),
			Retargeter ? TEXT("ok") : TEXT("MISSING"));
	}

	Report.Appendf(TEXT("source %s bones=%d\n"), *SourceMesh->GetName(), SourceMesh->GetRefSkeleton().GetNum());
	Report.Appendf(TEXT("target %s bones=%d\n"), *TargetMesh->GetName(), TargetMesh->GetRefSkeleton().GetNum());

	FRetargetProfile Profile;
	Profile.FillProfileWithAssetSettings(Retargeter);

	FIKRetargetProcessor Processor;
	Processor.Initialize(SourceMesh, TargetMesh, Retargeter, Profile);
	Report.Appendf(TEXT("processor initialized=%s\n"), Processor.IsInitialized() ? TEXT("true") : TEXT("false"));
	if (Processor.IsInitialized())
	{
		Report.Appendf(TEXT("source skeleton bones=%d target skeleton bones=%d\n"),
			Processor.GetSkeleton(ERetargetSourceOrTarget::Source).BoneNames.Num(),
			Processor.GetSkeleton(ERetargetSourceOrTarget::Target).BoneNames.Num());
	}

	return Report.ToString();
}

FString UKorinsnaEditorLibrary::SyncReferencePose(const FString& MeshPath)
{
	USkeletalMesh* Mesh = LoadObject<USkeletalMesh>(nullptr, *MeshPath);
	if (Mesh == nullptr)
	{
		return FString::Printf(TEXT("missing mesh %s"), *MeshPath);
	}
	USkeleton* Skeleton = Mesh->GetSkeleton();
	if (Skeleton == nullptr)
	{
		return FString::Printf(TEXT("%s has no skeleton"), *MeshPath);
	}

	const int32 Before = Skeleton->GetReferenceSkeleton().GetNum();
	Skeleton->UpdateReferencePoseFromMesh(Mesh);
	const int32 After = Skeleton->GetReferenceSkeleton().GetNum();

	Skeleton->MarkPackageDirty();
	return FString::Printf(TEXT("synced %s <- %s (bones %d -> %d)"),
		*Skeleton->GetPathName(), *Mesh->GetName(), Before, After);
}

#endif // WITH_EDITOR
