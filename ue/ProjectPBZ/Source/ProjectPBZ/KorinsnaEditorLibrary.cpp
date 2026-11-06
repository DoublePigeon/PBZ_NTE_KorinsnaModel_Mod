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

// Kawaii Physics (hair / skirt). The plugin's runtime module already ships inside the game, so the
// cooked asset only needs the anim node data - no extra runtime code has to reach the user.
#include "AnimGraphNode_KawaiiPhysics.h"
#include "AnimNode_KawaiiPhysics.h"
#include "KawaiiPhysicsCollisionLimits.h"
#include "KawaiiPhysicsTypes.h"

// RigidBody path: an engine-native simulation driven by a physics asset we author here. Everything it
// needs (the node class and the Chaos solver) is already inside the game, so this path adds no runtime
// code at all - which is the whole reason it replaced the KawaiiPhysics node (the game's copy of that
// plug-in is an old fork with no component-space simulation).
#include "AnimGraphNode_RigidBody.h"
#include "BoneControllers/AnimNode_RigidBody.h"
#include "PhysicsEngine/BodyInstance.h"
#include "PhysicsEngine/ConstraintInstance.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "PhysicsEngine/PhysicsConstraintTemplate.h"
#include "PhysicsEngine/RigidBodyIndexPair.h"
#include "PhysicsEngine/SkeletalBodySetup.h"
#include "PhysicsEngine/SphereElem.h"
#include "PhysicsAssetUtils.h"
#include "Engine/SkeletalMesh.h"
#include "AssetRegistry/AssetRegistryModule.h"

#include "Dom/JsonObject.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

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

	UEdGraphPin* NamedPin(UEdGraphNode* Node, const TCHAR* PinName, EEdGraphPinDirection Direction)
	{
		for (UEdGraphPin* Pin : Node->Pins)
		{
			if (Pin != nullptr && Pin->Direction == Direction && Pin->PinName == FName(PinName))
			{
				return Pin;
			}
		}
		return FirstPin(Node, Direction);
	}

	/** The anim node lives in a private UPROPERTY on the graph node, so go through reflection. */
	FAnimNode_KawaiiPhysics* GetKawaiiAnimNode(UAnimGraphNode_KawaiiPhysics* GraphNode)
	{
		FStructProperty* NodeProperty = FindFProperty<FStructProperty>(
			UAnimGraphNode_KawaiiPhysics::StaticClass(), TEXT("Node"));
		if (NodeProperty == nullptr || NodeProperty->Struct != FAnimNode_KawaiiPhysics::StaticStruct())
		{
			return nullptr;
		}
		return NodeProperty->ContainerPtrToValuePtr<FAnimNode_KawaiiPhysics>(GraphNode);
	}

	// ---------------------------------------------------------------- Kawaii physics authoring
	//
	// ue/kawaii_config.json is the single source of truth (see its `_readme`): which bone chains get
	// physics, with which profile, and which collision spheres each node carries. Everything is looked
	// up by name, so adding a hair chain or retuning a value is a config edit + rebuild, never a code
	// change - the same rule the retarget chains follow (ue/retarget_config.json).

	struct FPhysicsProfile
	{
		FKawaiiPhysicsSettings Settings;
		float DummyBoneLength = 3.0f;
		int32 TargetFramerate = 60;
		bool bEnableWind = false;
		bool bAllowWorldCollision = false;
		bool bIgnoreSelfComponent = true;
		bool bUpdateSettingsInGame = true;
		bool bResetWhenBoneMissing = false;
		float TeleportDistanceThreshold = 200.0f;
		float TeleportRotationThreshold = 45.0f;
		float Alpha = 1.0f;
		EKawaiiPhysicsSimulationSpace SimulationSpace = EKawaiiPhysicsSimulationSpace::ComponentSpace;
		/** Constrains the bone motion to a plane whose normal is one of the parent bone's axes. "X" is
		 *  the setting that removed the left-right lurch on this rig while keeping forward/back sway. */
		EPlanarConstraint PlanarConstraint = EPlanarConstraint::None;
		TArray<FSphericalLimit> Spheres;
		TArray<FCapsuleLimit> Capsules;

		FString Describe() const
		{
			return FString::Printf(
				TEXT("damping=%.2f stiffness=%.2f worldDampLoc=%.2f worldDampRot=%.2f limitAngle=%.1f"
					 " boneRadius=%.2f dummy=%.1f fps=%d spheres=%d"),
				Settings.Damping, Settings.Stiffness, Settings.WorldDampingLocation,
				Settings.WorldDampingRotation, Settings.LimitAngle, Settings.Radius,
				DummyBoneLength, TargetFramerate, Spheres.Num());
		}
	};

	struct FPhysicsChainDefinition
	{
		FString RootBone;
		FString ProfileName;
		FString Note;
		/** Simulation anchor for BaseBoneSpace; empty means "the root bone". */
		FString BaseBone;
		/** Subtrees the node must not touch. A node simulates everything below its root, so a chain
		 * that hangs from the pelvis would otherwise also simulate the spine and both legs - and the
		 * root bone itself stays kinematic, which is why the anchor has to be the shared parent (the
		 * first skirt bone then becomes a simulated child instead of a frozen root). */
		TArray<FString> ExcludeBones;
	};

	FString JsonString(const TSharedPtr<FJsonObject>& Object, const TCHAR* Field, const FString& Fallback)
	{
		FString Value;
		if (Object.IsValid() && Object->TryGetStringField(Field, Value))
		{
			return Value;
		}
		return Fallback;
	}

	double JsonNumber(const TSharedPtr<FJsonObject>& Object, const TCHAR* Field, double Fallback)
	{
		double Value = Fallback;
		if (Object.IsValid())
		{
			Object->TryGetNumberField(Field, Value);
		}
		return Value;
	}

	bool JsonBool(const TSharedPtr<FJsonObject>& Object, const TCHAR* Field, bool bFallback)
	{
		bool bValue = bFallback;
		if (Object.IsValid())
		{
			Object->TryGetBoolField(Field, bValue);
		}
		return bValue;
	}

	void ApplyPhysicsSettings(FPhysicsProfile& Profile, const TSharedPtr<FJsonObject>& Object)
	{
		if (!Object.IsValid())
		{
			return;
		}
		Profile.Settings.Damping = static_cast<float>(JsonNumber(Object, TEXT("damping"), Profile.Settings.Damping));
		Profile.Settings.Stiffness = static_cast<float>(JsonNumber(Object, TEXT("stiffness"), Profile.Settings.Stiffness));
		Profile.Settings.WorldDampingLocation = static_cast<float>(
			JsonNumber(Object, TEXT("world_damping_location"), Profile.Settings.WorldDampingLocation));
		Profile.Settings.WorldDampingRotation = static_cast<float>(
			JsonNumber(Object, TEXT("world_damping_rotation"), Profile.Settings.WorldDampingRotation));
		Profile.Settings.LimitAngle = static_cast<float>(JsonNumber(Object, TEXT("limit_angle"), Profile.Settings.LimitAngle));
		Profile.Settings.Radius = static_cast<float>(JsonNumber(Object, TEXT("radius"), Profile.Settings.Radius));
		Profile.DummyBoneLength = static_cast<float>(
			JsonNumber(Object, TEXT("dummy_bone_length"), Profile.DummyBoneLength));
		Profile.TargetFramerate = static_cast<int32>(JsonNumber(Object, TEXT("target_framerate"), Profile.TargetFramerate));
		Profile.bEnableWind = JsonBool(Object, TEXT("enable_wind"), Profile.bEnableWind);
		Profile.bAllowWorldCollision = JsonBool(Object, TEXT("allow_world_collision"), Profile.bAllowWorldCollision);
		Profile.bIgnoreSelfComponent = JsonBool(Object, TEXT("ignore_self_component"), Profile.bIgnoreSelfComponent);
		Profile.bUpdateSettingsInGame = JsonBool(Object, TEXT("update_settings_in_game"), Profile.bUpdateSettingsInGame);
		Profile.bResetWhenBoneMissing = JsonBool(Object, TEXT("reset_when_bone_missing"), Profile.bResetWhenBoneMissing);
		Profile.TeleportDistanceThreshold = static_cast<float>(
			JsonNumber(Object, TEXT("teleport_distance_threshold"), Profile.TeleportDistanceThreshold));
		Profile.TeleportRotationThreshold = static_cast<float>(
			JsonNumber(Object, TEXT("teleport_rotation_threshold"), Profile.TeleportRotationThreshold));
		Profile.Alpha = static_cast<float>(JsonNumber(Object, TEXT("alpha"), Profile.Alpha));

		const FString PlanarName = JsonString(Object, TEXT("planar_constraint"), FString());
		if (PlanarName.Equals(TEXT("X"), ESearchCase::IgnoreCase))
		{
			Profile.PlanarConstraint = EPlanarConstraint::X;
		}
		else if (PlanarName.Equals(TEXT("Y"), ESearchCase::IgnoreCase))
		{
			Profile.PlanarConstraint = EPlanarConstraint::Y;
		}
		else if (PlanarName.Equals(TEXT("Z"), ESearchCase::IgnoreCase))
		{
			Profile.PlanarConstraint = EPlanarConstraint::Z;
		}
		else
		{
			Profile.PlanarConstraint = EPlanarConstraint::None;
		}

		const FString SpaceName = JsonString(Object, TEXT("simulation_space"), FString());
		if (SpaceName.Equals(TEXT("WorldSpace"), ESearchCase::IgnoreCase))
		{
			Profile.SimulationSpace = EKawaiiPhysicsSimulationSpace::WorldSpace;
		}
		else if (SpaceName.Equals(TEXT("BaseBoneSpace"), ESearchCase::IgnoreCase))
		{
			Profile.SimulationSpace = EKawaiiPhysicsSimulationSpace::BaseBoneSpace;
		}
		else if (!SpaceName.IsEmpty())
		{
			Profile.SimulationSpace = EKawaiiPhysicsSimulationSpace::ComponentSpace;
		}
	}

	/** Component-space transform of a bone, accumulated from its root. GetRefBonePose() itself stores
	 * each bone's transform *relative to its parent*, which is why reading it as a position silently
	 * produced points a few centimetres from the hip instead of on the thigh. */
	FTransform ComponentTransformOf(const FReferenceSkeleton& RefSkeleton, int32 Index,
		bool bChildFirst = true)
	{
		TArray<FTransform, TInlineAllocator<64>> Chain;
		for (int32 Walk = Index; Walk != INDEX_NONE; Walk = RefSkeleton.GetParentIndex(Walk))
		{
			Chain.Add(RefSkeleton.GetRefBonePose()[Walk]);
		}
		FTransform Accum = FTransform::Identity;
		for (int32 Walk = Chain.Num() - 1; Walk >= 0; --Walk)
		{
			Accum = bChildFirst ? (Chain[Walk] * Accum) : (Accum * Chain[Walk]);
			Accum.NormalizeRotation();
		}
		return Accum;
	}

	/**
	 * Resolves a collision sphere pinned between two bones: "point": [ BoneA, BoneB, alpha ] is alpha of
	 * the way from BoneA's origin to BoneB's origin, converted into the frame the KawaiiPhysics node
	 * applies OffsetLocation in. Measured against a real run (sphere Location read back from the loaded
	 * node): an offset of (-0.5, 2.1, 1.1) on the thigh moved the sphere by a vector of the same length,
	 * rotated by the *driving bone's* orientation - so the offset is expressed in that bone's own frame,
	 * and the bone-chain point has to be rotated into it here. Authoring that by hand is guesswork: on
	 * this rig no single local axis of a Bip001 bone runs along the limb.
	 */
	bool ReadOffsetPoint(const FJsonObject& Definition, const FReferenceSkeleton& RefSkeleton,
		const FString& DrivingBone, FVector& OutLocalOffset)
	{
		const TArray<TSharedPtr<FJsonValue>>* PointArray = nullptr;
		if (!Definition.TryGetArrayField(TEXT("point"), PointArray) || PointArray == nullptr
			|| PointArray->Num() < 3)
		{
			return false;
		}
		const FString BoneA = (*PointArray)[0]->AsString();
		const FString BoneB = (*PointArray)[1]->AsString();
		const double Alpha = (*PointArray)[2]->AsNumber();

		const int32 IndexA = RefSkeleton.FindBoneIndex(FName(*BoneA));
		const int32 IndexB = RefSkeleton.FindBoneIndex(FName(*BoneB));
		const int32 IndexDriving = RefSkeleton.FindBoneIndex(FName(*DrivingBone));
		if (IndexA == INDEX_NONE || IndexB == INDEX_NONE || IndexDriving == INDEX_NONE)
		{
			UE_LOG(LogKorinsnaAuthoring, Warning,
				TEXT("limit point %s -> %s: bone missing (driving %s) - falling back to the offset"),
				*BoneA, *BoneB, *DrivingBone);
			return false;
		}

		const FVector Point = FMath::Lerp(ComponentTransformOf(RefSkeleton, IndexA).GetLocation(),
			ComponentTransformOf(RefSkeleton, IndexB).GetLocation(), static_cast<float>(Alpha));
		const FTransform Driving = ComponentTransformOf(RefSkeleton, IndexDriving);
		OutLocalOffset = Driving.GetRotation().UnrotateVector(Point - Driving.GetLocation())
			/ Driving.GetScale3D();
		return true;
	}

	/**
	 * Reads one capsule collider. Kawaii's capsule extends along the driving bone's local Z axis, and on
	 * this rig no local axis of a Bip001 bone runs along the limb - so the capsule is described the way it
	 * is meant geometrically ("from this bone to that one") and the frame is derived here: the midpoint
	 * becomes OffsetLocation and the Z axis is rotated onto the limb direction.
	 */
	bool ReadCapsuleLimit(const TSharedPtr<FJsonObject>& Definition, const FReferenceSkeleton& RefSkeleton,
		FCapsuleLimit& OutLimit)
	{
		if (!Definition.IsValid())
		{
			return false;
		}
		const FString Bone = JsonString(Definition, TEXT("bone"), FString());
		const TArray<TSharedPtr<FJsonValue>>* FromArray = nullptr;
		if (Bone.IsEmpty()
			|| !Definition->TryGetArrayField(TEXT("from"), FromArray) || FromArray == nullptr
			|| FromArray->Num() < 2)
		{
			return false;
		}
		const int32 BoneIndex = RefSkeleton.FindBoneIndex(FName(*Bone));
		const int32 FromIndex = RefSkeleton.FindBoneIndex(FName(*(*FromArray)[0]->AsString()));
		const int32 ToIndex = RefSkeleton.FindBoneIndex(FName(*(*FromArray)[1]->AsString()));
		if (BoneIndex == INDEX_NONE || FromIndex == INDEX_NONE || ToIndex == INDEX_NONE)
		{
			UE_LOG(LogKorinsnaAuthoring, Warning, TEXT("capsule %s: bone missing - ignored"), *Bone);
			return false;
		}
		const double Alpha0 = FromArray->Num() >= 3 ? (*FromArray)[2]->AsNumber() : 0.0;
		const double Alpha1 = FromArray->Num() >= 4 ? (*FromArray)[3]->AsNumber() : 1.0;

		const FVector From = ComponentTransformOf(RefSkeleton, FromIndex).GetLocation();
		const FVector To = ComponentTransformOf(RefSkeleton, ToIndex).GetLocation();
		const FVector Start = FMath::Lerp(From, To, static_cast<float>(Alpha0));
		const FVector End = FMath::Lerp(From, To, static_cast<float>(Alpha1));
		const FVector Axis = End - Start;
		if (Axis.SizeSquared() < 1.0f)
		{
			UE_LOG(LogKorinsnaAuthoring, Warning, TEXT("capsule %s is degenerate - ignored"), *Bone);
			return false;
		}

		const FTransform Driving = ComponentTransformOf(RefSkeleton, BoneIndex);
		const FVector Center = (Start + End) * 0.5f;
		const FVector LocalDir = Driving.GetRotation().UnrotateVector(Axis.GetSafeNormal());

		OutLimit = FCapsuleLimit();
		OutLimit.DrivingBone = FBoneReference(FName(*Bone));
		OutLimit.DrivingBone.InvalidateCachedBoneIndex();
		OutLimit.OffsetLocation = Driving.GetRotation().UnrotateVector(Center - Driving.GetLocation())
			/ Driving.GetScale3D();
		// the capsule runs along +Z after this rotation
		OutLimit.OffsetRotation = FQuat::FindBetweenNormals(FVector::ZAxisVector, LocalDir).Rotator();
		OutLimit.Length = Axis.Size();
		OutLimit.Radius = static_cast<float>(JsonNumber(Definition, TEXT("radius"), 8.0));
		OutLimit.bEnable = true;
		OutLimit.SourceType = ECollisionSourceType::AnimNode;
		return true;
	}

	bool ReadSphereLimit(const TSharedPtr<FJsonObject>& Definition, const FReferenceSkeleton* RefSkeleton,
		FSphericalLimit& OutLimit)
	{
		if (!Definition.IsValid())
		{
			return false;
		}
		const FString Bone = JsonString(Definition, TEXT("bone"), FString());
		if (Bone.IsEmpty())
		{
			return false;
		}

		FVector Offset = FVector::ZeroVector;
		const TArray<TSharedPtr<FJsonValue>>* OffsetArray = nullptr;
		if (Definition->TryGetArrayField(TEXT("offset"), OffsetArray) && OffsetArray != nullptr
			&& OffsetArray->Num() >= 3)
		{
			Offset = FVector((*OffsetArray)[0]->AsNumber(), (*OffsetArray)[1]->AsNumber(),
				(*OffsetArray)[2]->AsNumber());
		}
		if (RefSkeleton != nullptr)
		{
			ReadOffsetPoint(*Definition, *RefSkeleton, Bone, Offset);
		}

		OutLimit = FSphericalLimit();
		OutLimit.DrivingBone = FBoneReference(FName(*Bone));
		// the cached index belongs to whatever skeleton it was resolved against; force a re-resolve
		OutLimit.DrivingBone.InvalidateCachedBoneIndex();
		OutLimit.OffsetLocation = Offset;
		OutLimit.Radius = static_cast<float>(JsonNumber(Definition, TEXT("radius"), 5.0));
		// "Outer" = bodies are pushed out of the sphere, which is what a head or a thigh collider needs
		OutLimit.LimitType = ESphericalLimitType::Outer;
		OutLimit.bEnable = true;
		OutLimit.SourceType = ECollisionSourceType::AnimNode;
		return true;
	}

	/** Every value the runtime cares about, taken from the profile. */
	void ConfigureKawaiiNode(FAnimNode_KawaiiPhysics& Node, const FPhysicsProfile& Profile,
		const FString& RootBone, const FString& BaseBone)
	{
		Node.RootBone = FBoneReference(FName(*RootBone));
		Node.RootBone.InvalidateCachedBoneIndex();

		// BaseBoneSpace simulates relative to this bone, so the bone turning (which is how this game
		// changes direction: the whole character is rotated inside the component in a single frame)
		// stops being an inertia impulse for the cloth. The kinematic root is the natural anchor.
		const FString Anchor = BaseBone.IsEmpty() ? RootBone : BaseBone;
		Node.SimulationBaseBone = FBoneReference(FName(*Anchor));
		Node.SimulationBaseBone.InvalidateCachedBoneIndex();

		Node.PhysicsSettings = Profile.Settings;
		Node.SimulationSpace = Profile.SimulationSpace;
		Node.PlanarConstraint = Profile.PlanarConstraint;
		Node.DummyBoneLength = Profile.DummyBoneLength;
		Node.TargetFramerate = Profile.TargetFramerate;
		Node.bUpdatePhysicsSettingsInGame = Profile.bUpdateSettingsInGame;
		Node.bEnableWind = Profile.bEnableWind;
		Node.WindScale = 0.0f;
		Node.bAllowWorldCollision = Profile.bAllowWorldCollision;
		Node.bIgnoreSelfComponent = Profile.bIgnoreSelfComponent;
		Node.ResetBoneTransformWhenBoneNotFound = Profile.bResetWhenBoneMissing;
		Node.TeleportDistanceThreshold = Profile.TeleportDistanceThreshold;
		Node.TeleportRotationThreshold = Profile.TeleportRotationThreshold;
		Node.SphericalLimits = Profile.Spheres;
		Node.CapsuleLimits = Profile.Capsules;
		Node.Alpha = Profile.Alpha;
		Node.bAlphaBoolEnabled = false;

		// runtime state that the editor fills in during a preview; a fresh node must not carry it
		Node.ModifyBones.Reset();
	}

	/**
	 * Reads ue/kawaii_config.json into chain definitions plus the profile each chain refers to.
	 *
	 * A missing or malformed file is reported through OutError and yields no chains: the blueprint is
	 * then exactly the retarget-only blueprint it used to be, so a physics mistake can never take the
	 * animation down with it.
	 */
	bool LoadPhysicsConfig(const FString& Path, const FReferenceSkeleton* RefSkeleton,
		TArray<FPhysicsChainDefinition>& OutChains, TMap<FString, FPhysicsProfile>& OutProfiles,
		FString& OutError)
	{
		FString RawText;
		if (!FFileHelper::LoadFileToString(RawText, *Path))
		{
			OutError = FString::Printf(TEXT("cannot read %s"), *Path);
			return false;
		}

		TSharedPtr<FJsonObject> RootObject;
		const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(RawText);
		if (!FJsonSerializer::Deserialize(Reader, RootObject) || !RootObject.IsValid())
		{
			OutError = TEXT("not valid JSON");
			return false;
		}

		if (!JsonBool(RootObject, TEXT("enabled"), true))
		{
			OutError = TEXT("disabled in the config");
			return false;
		}

		const TSharedPtr<FJsonObject>* Defaults = nullptr;
		RootObject->TryGetObjectField(TEXT("defaults"), Defaults);

		// --- shared collision spheres, by name
		TMap<FString, FSphericalLimit> SphereLibrary;
		const TSharedPtr<FJsonObject>* LimitsObject = nullptr;
		if (RootObject->TryGetObjectField(TEXT("limits"), LimitsObject) && LimitsObject != nullptr)
		{
			for (const TPair<FString, TSharedPtr<FJsonValue>>& Entry : (*LimitsObject)->Values)
			{
				const TSharedPtr<FJsonObject>* SphereObject = nullptr;
				if (!Entry.Value.IsValid() || !Entry.Value->TryGetObject(SphereObject) || SphereObject == nullptr)
				{
					continue;
				}
				FSphericalLimit Limit;
				if (ReadSphereLimit(*SphereObject, RefSkeleton, Limit))
				{
					SphereLibrary.Add(Entry.Key, Limit);
				}
				else
				{
					UE_LOG(LogKorinsnaAuthoring, Warning, TEXT("limit %s has no usable bone - ignored"), *Entry.Key);
				}
			}
		}

		TMap<FString, FCapsuleLimit> CapsuleLibrary;
		const TSharedPtr<FJsonObject>* CapsuleObject = nullptr;
		if (RootObject->TryGetObjectField(TEXT("capsules"), CapsuleObject) && CapsuleObject != nullptr)
		{
			for (const TPair<FString, TSharedPtr<FJsonValue>>& Entry : (*CapsuleObject)->Values)
			{
				const TSharedPtr<FJsonObject>* Definition = nullptr;
				if (!Entry.Value.IsValid() || !Entry.Value->TryGetObject(Definition) || Definition == nullptr)
				{
					continue;
				}
				FCapsuleLimit Limit;
				if (ReadCapsuleLimit(*Definition, *RefSkeleton, Limit))
				{
					CapsuleLibrary.Add(Entry.Key, Limit);
				}
			}
		}

		// --- profiles
		const TSharedPtr<FJsonObject>* ProfilesObject = nullptr;
		if (RootObject->TryGetObjectField(TEXT("profiles"), ProfilesObject) && ProfilesObject != nullptr)
		{
			for (const TPair<FString, TSharedPtr<FJsonValue>>& Entry : (*ProfilesObject)->Values)
			{
				const TSharedPtr<FJsonObject>* ProfileObject = nullptr;
				if (!Entry.Value.IsValid() || !Entry.Value->TryGetObject(ProfileObject) || ProfileObject == nullptr)
				{
					continue;
				}
				FPhysicsProfile Profile;
				ApplyPhysicsSettings(Profile, Defaults ? *Defaults : nullptr);
				const TSharedPtr<FJsonObject>* SettingsObject = nullptr;
				if ((*ProfileObject)->TryGetObjectField(TEXT("settings"), SettingsObject))
				{
					ApplyPhysicsSettings(Profile, *SettingsObject);
				}

				const TArray<TSharedPtr<FJsonValue>>* SphereNames = nullptr;
				if ((*ProfileObject)->TryGetArrayField(TEXT("spheres"), SphereNames) && SphereNames != nullptr)
				{
					for (const TSharedPtr<FJsonValue>& NameValue : *SphereNames)
					{
						const FString Name = NameValue.IsValid() ? NameValue->AsString() : FString();
						const FSphericalLimit* Found = SphereLibrary.Find(Name);
						if (Found == nullptr)
						{
							UE_LOG(LogKorinsnaAuthoring, Warning,
								TEXT("profile %s refers to unknown sphere %s"), *Entry.Key, *Name);
							continue;
						}
						Profile.Spheres.Add(*Found);
					}
				}
				const TArray<TSharedPtr<FJsonValue>>* CapsuleNames = nullptr;
				if ((*ProfileObject)->TryGetArrayField(TEXT("capsules"), CapsuleNames) && CapsuleNames != nullptr)
				{
					for (const TSharedPtr<FJsonValue>& NameValue : *CapsuleNames)
					{
						const FString Name = NameValue.IsValid() ? NameValue->AsString() : FString();
						const FCapsuleLimit* Found = CapsuleLibrary.Find(Name);
						if (Found == nullptr)
						{
							UE_LOG(LogKorinsnaAuthoring, Warning,
								TEXT("profile %s refers to unknown capsule %s"), *Entry.Key, *Name);
							continue;
						}
						Profile.Capsules.Add(*Found);
					}
				}
				OutProfiles.Add(Entry.Key, Profile);
			}
		}

		// --- chains
		const TArray<TSharedPtr<FJsonValue>>* ChainArray = nullptr;
		if (!RootObject->TryGetArrayField(TEXT("chains"), ChainArray) || ChainArray == nullptr)
		{
			OutError = TEXT("no chains array");
			return false;
		}
		for (const TSharedPtr<FJsonValue>& ChainValue : *ChainArray)
		{
			const TSharedPtr<FJsonObject>* ChainObject = nullptr;
			if (!ChainValue.IsValid() || !ChainValue->TryGetObject(ChainObject) || ChainObject == nullptr)
			{
				continue;
			}
			FPhysicsChainDefinition Chain;
			Chain.RootBone = JsonString(*ChainObject, TEXT("root"), FString());
			Chain.ProfileName = JsonString(*ChainObject, TEXT("profile"), FString());
			Chain.Note = JsonString(*ChainObject, TEXT("note"), FString());
			Chain.BaseBone = JsonString(*ChainObject, TEXT("base_bone"), FString());
			const TArray<TSharedPtr<FJsonValue>>* ExcludeArray = nullptr;
			if ((*ChainObject)->TryGetArrayField(TEXT("exclude"), ExcludeArray) && ExcludeArray != nullptr)
			{
				for (const TSharedPtr<FJsonValue>& NameValue : *ExcludeArray)
				{
					const FString Name = NameValue.IsValid() ? NameValue->AsString() : FString();
					if (!Name.IsEmpty())
					{
						Chain.ExcludeBones.Add(Name);
					}
				}
			}
			if (Chain.RootBone.IsEmpty() || Chain.ProfileName.IsEmpty())
			{
				UE_LOG(LogKorinsnaAuthoring, Warning, TEXT("a chain entry has no root/profile - ignored"));
				continue;
			}
			if (!OutProfiles.Contains(Chain.ProfileName))
			{
				UE_LOG(LogKorinsnaAuthoring, Warning, TEXT("chain %s uses unknown profile %s - ignored"),
					*Chain.RootBone, *Chain.ProfileName);
				continue;
			}
			OutChains.Add(Chain);
		}

		if (OutChains.Num() == 0)
		{
			OutError = TEXT("no usable chains");
			return false;
		}
		return true;
	}

	// ------------------------------------------------------------------ RigidBody path
	//
	// Instead of KawaiiPhysics (whose copy inside this game is an old fork without component-space
	// simulation), the cloth is driven by the engine's own FAnimNode_RigidBody, which is a skeletal
	// control node that reads a physics asset. Two consequences make this the better fit:
	//   * SimulationSpace can be set to ComponentSpace, so the character's world movement - the fast
	//     direction changes that made the cloth lurch - does not enter the solver at all;
	//   * the bodies that push the cloth (pelvis, thighs, calves) can be authored as kinematics, exactly
	//     like the doc describes.
	// Everything here is asset data, so the shipped mod still contains no code.

	struct FRigidShape
	{
		FString Bone;
		/** Torso / limb colliders: (boneA, boneB, alpha) pairs, converted into the bone's local frame. */
		TArray<FString> PadFrom;
	};

	struct FRigidBodyConfig
	{
		FString PhysicsAssetPath;
		/** The physics asset factory needs a mesh; it also seeds the bone list. */
		FString SkeletalMeshPath;
		FString Mode;

		/** Bones whose bodies are kinematic: they push the cloth but never move themselves. */
		TArray<FString> KinematicBones;
		float KinematicRadius = 9.0f;
		int32 KinematicSteps = 3;
		float KinematicPad = 0.0f;

		/** Cloth chains, as the bone the simulated subtree hangs from. */
		TArray<FString> ClothRoots;
		float ClothRadius = 3.0f;
		float ClothRadiusOfBoneLength = 0.28f;
		float ClothMass = 1.0f;
		float ClothLinearDamping = 1.0f;
		float ClothAngularDamping = 2.0f;

		/** Per-axis freedom: "limited" (angle below), "locked" (no rotation at all) or "free". */
		FString Swing1Motion = TEXT("limited");
		FString Swing2Motion = TEXT("limited");
		FString TwistMotion = TEXT("limited");
		float Swing1Limit = 25.0f;
		float Swing2Limit = 25.0f;
		float TwistLimit = 15.0f;
		/** Bones with this prefix get their own collider radius (the head has to be big enough to keep
		 *  the bangs out of the face, while the legs must not inflate the skirt). */
		FString HeadBonePrefix = TEXT("head_Bone");
		float HeadRadius = 13.0f;

		FVector Gravity = FVector(0.0f, 0.0f, -980.0f);
		float MaxLinearVelocity = 400.0f;
		float MaxAngularVelocity = 900.0f;
		int32 PositionIterations = 8;
		int32 VelocityIterations = 8;
	};

	bool LoadRigidBodyConfig(const FString& Path, FRigidBodyConfig& Out)
	{
		FString RawText;
		if (!FFileHelper::LoadFileToString(RawText, *Path))
		{
			return false;
		}
		TSharedPtr<FJsonObject> Root;
		const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(RawText);
		if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
		{
			return false;
		}

		Out.Mode = JsonString(Root, TEXT("mode"), FString());
		Out.PhysicsAssetPath = JsonString(Root, TEXT("physics_asset"), FString());
		Out.SkeletalMeshPath = JsonString(Root, TEXT("skeletal_mesh"), FString());
		Out.KinematicRadius = static_cast<float>(JsonNumber(Root, TEXT("kinematic_radius"), Out.KinematicRadius));
		Out.KinematicSteps = static_cast<int32>(JsonNumber(Root, TEXT("kinematic_steps"), Out.KinematicSteps));
		Out.KinematicPad = static_cast<float>(JsonNumber(Root, TEXT("kinematic_pad"), Out.KinematicPad));
		Out.ClothRadius = static_cast<float>(JsonNumber(Root, TEXT("cloth_radius"), Out.ClothRadius));
		Out.ClothRadiusOfBoneLength = static_cast<float>(
			JsonNumber(Root, TEXT("cloth_radius_of_bone_length"), Out.ClothRadiusOfBoneLength));
		Out.ClothMass = static_cast<float>(JsonNumber(Root, TEXT("cloth_mass"), Out.ClothMass));
		Out.ClothLinearDamping = static_cast<float>(
			JsonNumber(Root, TEXT("cloth_linear_damping"), Out.ClothLinearDamping));
		Out.ClothAngularDamping = static_cast<float>(
			JsonNumber(Root, TEXT("cloth_angular_damping"), Out.ClothAngularDamping));
		Out.Swing1Motion = JsonString(Root, TEXT("swing1_motion"), Out.Swing1Motion);
		Out.Swing2Motion = JsonString(Root, TEXT("swing2_motion"), Out.Swing2Motion);
		Out.TwistMotion = JsonString(Root, TEXT("twist_motion"), Out.TwistMotion);
		Out.HeadBonePrefix = JsonString(Root, TEXT("head_bone_prefix"), Out.HeadBonePrefix);
		Out.HeadRadius = static_cast<float>(JsonNumber(Root, TEXT("head_radius"), Out.HeadRadius));
		Out.Swing1Limit = static_cast<float>(JsonNumber(Root, TEXT("swing1_limit"), Out.Swing1Limit));
		Out.Swing2Limit = static_cast<float>(JsonNumber(Root, TEXT("swing2_limit"), Out.Swing2Limit));
		Out.TwistLimit = static_cast<float>(JsonNumber(Root, TEXT("twist_limit"), Out.TwistLimit));
		Out.MaxLinearVelocity = static_cast<float>(
			JsonNumber(Root, TEXT("max_linear_velocity"), Out.MaxLinearVelocity));
		Out.MaxAngularVelocity = static_cast<float>(
			JsonNumber(Root, TEXT("max_angular_velocity"), Out.MaxAngularVelocity));
		Out.PositionIterations = static_cast<int32>(
			JsonNumber(Root, TEXT("position_iterations"), Out.PositionIterations));
		Out.VelocityIterations = static_cast<int32>(
			JsonNumber(Root, TEXT("velocity_iterations"), Out.VelocityIterations));

		const TArray<TSharedPtr<FJsonValue>>* GravityArray = nullptr;
		if (Root->TryGetArrayField(TEXT("gravity"), GravityArray) && GravityArray != nullptr
			&& GravityArray->Num() >= 3)
		{
			Out.Gravity = FVector((*GravityArray)[0]->AsNumber(), (*GravityArray)[1]->AsNumber(),
				(*GravityArray)[2]->AsNumber());
		}

		const TArray<TSharedPtr<FJsonValue>>* Kinematic = nullptr;
		if (Root->TryGetArrayField(TEXT("kinematic"), Kinematic) && Kinematic != nullptr)
		{
			for (const TSharedPtr<FJsonValue>& Value : *Kinematic)
			{
				const FString Bone = Value.IsValid() ? Value->AsString() : FString();
				if (!Bone.IsEmpty())
				{
					Out.KinematicBones.Add(Bone);
				}
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* Cloth = nullptr;
		if (Root->TryGetArrayField(TEXT("cloth_roots"), Cloth) && Cloth != nullptr)
		{
			for (const TSharedPtr<FJsonValue>& Value : *Cloth)
			{
				const FString Bone = Value.IsValid() ? Value->AsString() : FString();
				if (!Bone.IsEmpty())
				{
					Out.ClothRoots.Add(Bone);
				}
			}
		}
		return !Out.ClothRoots.IsEmpty();
	}

	EAngularConstraintMotion ParseMotion(const FString& Name, EAngularConstraintMotion Fallback)
	{
		if (Name.Equals(TEXT("locked"), ESearchCase::IgnoreCase))
		{
			return ACM_Locked;
		}
		if (Name.Equals(TEXT("free"), ESearchCase::IgnoreCase))
		{
			return ACM_Free;
		}
		if (Name.Equals(TEXT("limited"), ESearchCase::IgnoreCase))
		{
			return ACM_Limited;
		}
		return Fallback;
	}

	/** Bone index -> every descendant index, depth first, in skeleton order. */
	void CollectSubtree(const FReferenceSkeleton& RefSkeleton, int32 RootIndex, TArray<int32>& Out)
	{
		for (int32 Index = 0; Index < RefSkeleton.GetNum(); ++Index)
		{
			int32 Walk = RefSkeleton.GetParentIndex(Index);
			while (Walk != INDEX_NONE)
			{
				if (Walk == RootIndex)
				{
					Out.Add(Index);
					break;
				}
				Walk = RefSkeleton.GetParentIndex(Walk);
			}
		}
	}

	/** Point between two bones, expressed the way a body's shapes are: in the driving bone's own frame. */




	/**
	 * Builds (or rebuilds) the physics asset the RigidBody node reads.
	 *
	 * Shape layout was measured, not guessed: a body's shapes are written in the driving bone's own
	 * frame, and on this rig no local axis of a Bip001 bone runs along the limb (the same finding as the
	 * Kawaii collision spheres, see TECHNICAL-GUIDE 鎼?). So every offset is generated from the
	 * reference pose and rotated into the bone frame here.
	 */
	UPhysicsAsset* BuildPhysicsAsset(const FString& AssetPath, USkeleton* Skeleton, const FRigidBodyConfig& Config)
	{
		const FReferenceSkeleton& RefSkeleton = Skeleton->GetReferenceSkeleton();
		// AssetPath is an object path ("/Game/X/PA_Y.PA_Y"), so the package name has to be derived with
		// FPackageName - splitting on "/" leaves the ".PA_Y" suffix in the asset name and CreatePackage
		// then rejects the dotted package name.
		const FString PackageName = FPackageName::ObjectPathToPackageName(AssetPath);
		const FString AssetName = FPackageName::GetShortName(PackageName);
		const FString PackagePath = FPackageName::GetLongPackagePath(PackageName);
		if (AssetName.IsEmpty() || PackagePath.IsEmpty())
		{
			UE_LOG(LogKorinsnaAuthoring, Error, TEXT("physics asset path must be a package path: %s"), *AssetPath);
			return nullptr;
		}

		UPhysicsAsset* Asset = LoadObject<UPhysicsAsset>(nullptr, *AssetPath);
		if (Asset != nullptr)
		{
			// Regenerating into a populated asset asserts inside the engine's generator (stale body and
			// constraint indices), so every run starts from a fresh object.
			TArray<UObject*> ToDelete;
			ToDelete.Add(Asset);
			ObjectTools::ForceDeleteObjects(ToDelete, false);
			Asset = nullptr;
		}
		if (Asset == nullptr)
		{
			// Create the package by hand with an explicit "/" join (FString's `/` operator is not a path
			// join; it produced a doubled name, CreatePackage then failed and the object ended up in the
			// transient package - which is what made saving fatal).
			const FString FullPackageName = PackagePath + TEXT("/") + AssetName;
			UPackage* Package = CreatePackage(*FullPackageName);
			if (Package == nullptr)
			{
				UE_LOG(LogKorinsnaAuthoring, Error, TEXT("could not create package %s"), *FullPackageName);
				return nullptr;
			}
			Asset = NewObject<UPhysicsAsset>(Package, *AssetName, RF_Public | RF_Standalone | RF_Transactional);
			if (Asset != nullptr)
			{
				FAssetRegistryModule::AssetCreated(Asset);
			}
		}
		if (Asset == nullptr)
		{
			UE_LOG(LogKorinsnaAuthoring, Error, TEXT("could not create physics asset %s"), *AssetPath);
			return nullptr;
		}

		Asset->SkeletalBodySetups.Reset();
		Asset->ConstraintSetup.Reset();
		Asset->CollisionDisableTable.Reset();

		USkeletalMesh* Mesh = LoadObject<USkeletalMesh>(nullptr, *Config.SkeletalMeshPath);
		if (Mesh == nullptr)
		{
			UE_LOG(LogKorinsnaAuthoring, Error, TEXT("physics asset needs a skeletal mesh: %s"),
				*Config.SkeletalMeshPath);
			return nullptr;
		}

		// Bodies AND constraints come from the engine's own generator. Hand-written constraints have no
		// joint frames (Pos1/PriAxis1/Pos2/...), so they constrain nothing and the simulated hair simply
		// falls - measured in game as hair stretched to the floor and a collapsed skirt.
		FPhysAssetCreateParams Params;
		Params.MinBoneSize = 1.0f;
		Params.bWalkPastSmall = false;
		Params.bBodyForAll = true;          // every cloth bone must have a body, or a strand stays rigid
		Params.GeomType = EFG_Sphere;       // orientation-free, and this rig's local axes are not limbs
		Params.bAutoOrientToBone = true;
		Params.bCreateConstraints = true;
		Params.AngularConstraintMode = ACM_Limited;
		// collisions start enabled: the import of the doc is "legs push cloth"; only cloth-vs-cloth is
		// disabled below
		Params.bDisableCollisionsByDefault = false;
		Params.LodIndex = 0;

		FText CreateError;
		if (!FPhysicsAssetUtils::CreateFromSkeletalMesh(Asset, Mesh, Params, CreateError, false, false))
		{
			UE_LOG(LogKorinsnaAuthoring, Error, TEXT("physics asset generation failed: %s"),
				*CreateError.ToString());
			return nullptr;
		}

		// --- classify the generated bodies
		TSet<FName> ClothBones;
		for (const FString& RootName : Config.ClothRoots)
		{
			const int32 RootIndex = RefSkeleton.FindBoneIndex(FName(*RootName));
			if (RootIndex == INDEX_NONE)
			{
				UE_LOG(LogKorinsnaAuthoring, Warning, TEXT("cloth root %s not in the skeleton"), *RootName);
				continue;
			}
			ClothBones.Add(FName(*RootName));
			TArray<int32> Bones;
			CollectSubtree(RefSkeleton, RootIndex, Bones);
			for (int32 BoneIndex : Bones)
			{
				ClothBones.Add(RefSkeleton.GetBoneName(BoneIndex));
			}
		}

		TSet<FName> KinematicBones;
		for (const FString& BoneName : Config.KinematicBones)
		{
			KinematicBones.Add(FName(*BoneName));
		}

		int32 ClothCount = 0;
		for (USkeletalBodySetup* Body : Asset->SkeletalBodySetups)
		{
			if (Body == nullptr)
			{
				continue;
			}
			const bool bCloth = ClothBones.Contains(Body->BoneName);
			const bool bKinematic = KinematicBones.Contains(Body->BoneName);
			if (bCloth)
			{
				++ClothCount;
				Body->PhysicsType = PhysType_Simulated;
				Body->bConsiderForBounds = true;
				Body->DefaultInstance.LinearDamping = Config.ClothLinearDamping;
				Body->DefaultInstance.AngularDamping = Config.ClothAngularDamping;
				Body->DefaultInstance.MassScale = Config.ClothMass;
				Body->DefaultInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				Body->DefaultInstance.SetObjectType(ECC_PhysicsBody);
				// keep the cloth thin: the generated spheres are fitted to the mesh and would otherwise
				// push the strands apart
				for (FKSphereElem& Sphere : Body->AggGeom.SphereElems)
				{
					Sphere.Radius = FMath::Min(Sphere.Radius, Config.ClothRadius * 2.0f);
				}
			}
			else if (bKinematic)
			{
				Body->PhysicsType = PhysType_Kinematic;
				Body->bConsiderForBounds = false;
				Body->DefaultInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				Body->DefaultInstance.SetObjectType(ECC_PhysicsBody);
				const bool bHead = !Config.HeadBonePrefix.IsEmpty()
					&& Body->BoneName.ToString().StartsWith(Config.HeadBonePrefix, ESearchCase::IgnoreCase);
				const float Radius = bHead ? Config.HeadRadius
					: Config.KinematicRadius + Config.KinematicPad;
				for (FKSphereElem& Sphere : Body->AggGeom.SphereElems)
				{
					Sphere.Radius = Radius;
				}
			}
			else
			{
				// everything else (spine, arms, fingers, feet) neither moves nor pushes the cloth
				Body->PhysicsType = PhysType_Kinematic;
				Body->bConsiderForBounds = false;
				Body->DefaultInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
		}

		// --- angular limits on the cloth chains, and cloth-vs-cloth collision off
		for (UPhysicsConstraintTemplate* Template : Asset->ConstraintSetup)
		{
			if (Template == nullptr)
			{
				continue;
			}
			FConstraintInstance& Instance = Template->DefaultInstance;
			const bool bClothPair = ClothBones.Contains(Instance.ConstraintBone1);
			if (!bClothPair)
			{
				continue;
			}
			// Locking one swing axis is the RigidBody equivalent of the planar constraint that fixed the
			// left-right lurch with Kawaii: it removes the freedom the fast direction change excites.
			Instance.SetAngularSwing1Limit(ParseMotion(Config.Swing1Motion, ACM_Limited),
				Config.Swing1Limit);
			Instance.SetAngularSwing2Limit(ParseMotion(Config.Swing2Motion, ACM_Limited),
				Config.Swing2Limit);
			Instance.SetAngularTwistLimit(ParseMotion(Config.TwistMotion, ACM_Limited),
				Config.TwistLimit);
		}

		Asset->UpdateBodySetupIndexMap();
		Asset->UpdateBoundsBodiesArray();
		TArray<FName> ClothNameList = ClothBones.Array();
		for (int32 A = 0; A < ClothNameList.Num(); ++A)
		{
			const int32 IndexA = Asset->FindBodyIndex(ClothNameList[A]);
			if (IndexA == INDEX_NONE)
			{
				continue;
			}
			for (int32 B = A + 1; B < ClothNameList.Num(); ++B)
			{
				const int32 IndexB = Asset->FindBodyIndex(ClothNameList[B]);
				if (IndexB != INDEX_NONE)
				{
					Asset->CollisionDisableTable.Add(FRigidBodyIndexPair(IndexA, IndexB), false);
				}
			}
		}

		Asset->MarkPackageDirty();
		UEditorLoadingAndSavingUtils::SavePackages({Asset->GetOutermost()}, false);
		UE_LOG(LogKorinsnaAuthoring, Log,
			TEXT("physics asset %s: %d body(ies) (%d cloth, %d kinematic) and %d constraint(s)"),
			*AssetPath, Asset->SkeletalBodySetups.Num(), ClothCount, KinematicBones.Num(),
			Asset->ConstraintSetup.Num());
		return Asset;
	}

	FAnimNode_RigidBody* GetRigidBodyAnimNode(UAnimGraphNode_RigidBody* GraphNode)
	{
		FStructProperty* NodeProperty = FindFProperty<FStructProperty>(
			UAnimGraphNode_RigidBody::StaticClass(), TEXT("Node"));
		if (NodeProperty == nullptr || NodeProperty->Struct != FAnimNode_RigidBody::StaticStruct())
		{
			return nullptr;
		}
		return NodeProperty->ContainerPtrToValuePtr<FAnimNode_RigidBody>(GraphNode);
	}
}

bool UKorinsnaEditorLibrary::CreateRetargetAnimBlueprint(const FString& AssetPath, const FString& SkeletonPath,
	const FString& RetargeterPath, const FString& PhysicsConfigPath)
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

	// ---------------------------------------------------------------- hair / skirt physics
	//
	// Two implementations live behind this config file, selected by its "mode" key:
	//   * "rigidbody": the engine's own FAnimNode_RigidBody driving a physics asset authored below. The
	//     simulation runs in component space, so the character's world movement never enters the solver.
	//   * anything else: the KawaiiPhysics chain (kept as a fallback - the game's copy of that plug-in is
	//     an old fork, see TECHNICAL-GUIDE).
	FRigidBodyConfig RigidConfig;
	const bool bRigidBodyMode = !PhysicsConfigPath.IsEmpty()
		&& LoadRigidBodyConfig(PhysicsConfigPath, RigidConfig)
		&& RigidConfig.Mode.Equals(TEXT("rigidbody"), ESearchCase::IgnoreCase);

	TArray<FPhysicsChainDefinition> PhysicsChains;
	TMap<FString, FPhysicsProfile> PhysicsProfiles;
	FString PhysicsError;
	if (!bRigidBodyMode && !PhysicsConfigPath.IsEmpty()
		&& !LoadPhysicsConfig(PhysicsConfigPath, &Skeleton->GetReferenceSkeleton(), PhysicsChains,
			PhysicsProfiles, PhysicsError))
	{
		// Not fatal: without a config the blueprint is exactly the retarget blueprint it used to be, so
		// a broken physics config can never cost the mod its animation.
		UE_LOG(LogKorinsnaAuthoring, Error, TEXT("physics config %s rejected: %s - building without physics"),
			*PhysicsConfigPath, *PhysicsError);
		PhysicsChains.Reset();
	}

	// Lay the graph out right-to-left in execution order: retarget, then the physics node, then root.
	const int32 PhysicsCount = bRigidBodyMode ? 1 : PhysicsChains.Num();
	RetargetNode->NodePosX = RootNode->NodePosX - 320 * (PhysicsCount + 1);
	RetargetNode->NodePosY = RootNode->NodePosY;

	TArray<UAnimGraphNode_Base*> PoseChain;
	PoseChain.Add(RetargetNode);

	if (bRigidBodyMode)
	{
		UPhysicsAsset* PhysicsAsset = BuildPhysicsAsset(RigidConfig.PhysicsAssetPath, Skeleton, RigidConfig);
		if (PhysicsAsset == nullptr)
		{
			UE_LOG(LogKorinsnaAuthoring, Error, TEXT("physics asset could not be built - no cloth simulation"));
		}
		else
		{
			FGraphNodeCreator<UAnimGraphNode_RigidBody> Creator(*AnimGraph);
			UAnimGraphNode_RigidBody* RigidNode = Creator.CreateNode();
			RigidNode->NodePosX = RootNode->NodePosX - 320;
			RigidNode->NodePosY = RootNode->NodePosY;
			Creator.Finalize();

			FAnimNode_RigidBody* RigidAnimNode = GetRigidBodyAnimNode(RigidNode);
			if (RigidAnimNode == nullptr)
			{
				UE_LOG(LogKorinsnaAuthoring, Error,
					TEXT("rigid body node does not expose FAnimNode_RigidBody"));
				return false;
			}
			RigidAnimNode->OverridePhysicsAsset = PhysicsAsset;
			RigidAnimNode->bDefaultToSkeletalMeshPhysicsAsset = false;
			// The one setting that matters most: a component-space simulation ignores the character
			// moving through the world, which is what made the old node lurch on a fast direction change.
			RigidAnimNode->SimulationSpace = ESimulationSpace::ComponentSpace;
			RigidAnimNode->bOverrideWorldGravity = true;
			RigidAnimNode->OverrideWorldGravity = RigidConfig.Gravity;
			// no interaction with walls / water / wind - the user asked for a self-contained simulation
			RigidAnimNode->bEnableWorldGeometry = false;
			RigidAnimNode->bForceDisableCollisionBetweenConstraintBodies = true;
			// these live on the sim-space settings block, not on the node itself
			RigidAnimNode->SimSpaceSettings.MaxLinearVelocity = RigidConfig.MaxLinearVelocity;
			RigidAnimNode->SimSpaceSettings.MaxAngularVelocity = RigidConfig.MaxAngularVelocity;
			RigidNode->NodeComment = FString::Printf(TEXT("rigidbody - %s (component space)"),
				*PhysicsAsset->GetName());
			UE_LOG(LogKorinsnaAuthoring, Log,
				TEXT("rigidbody: asset=%s space=%d gravity=(%.0f, %.0f, %.0f) worldGeom=%s bodies=%d"),
				*PhysicsAsset->GetName(), static_cast<int32>(RigidAnimNode->SimulationSpace),
				RigidAnimNode->OverrideWorldGravity.X, RigidAnimNode->OverrideWorldGravity.Y,
				RigidAnimNode->OverrideWorldGravity.Z,
				RigidAnimNode->bEnableWorldGeometry ? TEXT("on") : TEXT("off"),
				PhysicsAsset->SkeletalBodySetups.Num());
			PoseChain.Add(RigidNode);
		}
	}
	else
	{
		for (int32 Index = 0; Index < PhysicsCount; ++Index)
		{
			const FPhysicsChainDefinition& Chain = PhysicsChains[Index];
			const FPhysicsProfile* Profile = PhysicsProfiles.Find(Chain.ProfileName);
			if (Profile == nullptr)
			{
				UE_LOG(LogKorinsnaAuthoring, Error, TEXT("chain %s wants unknown profile %s - skipped"),
					*Chain.RootBone, *Chain.ProfileName);
				continue;
			}

			FGraphNodeCreator<UAnimGraphNode_KawaiiPhysics> KawaiiCreator(*AnimGraph);
			UAnimGraphNode_KawaiiPhysics* KawaiiNode = KawaiiCreator.CreateNode();
			KawaiiNode->NodePosX = RootNode->NodePosX - 320 * (PhysicsCount - Index);
			KawaiiNode->NodePosY = RootNode->NodePosY + 180 * (Index + 1);
			KawaiiCreator.Finalize();

			FAnimNode_KawaiiPhysics* KawaiiAnimNode = GetKawaiiAnimNode(KawaiiNode);
			if (KawaiiAnimNode == nullptr)
			{
				UE_LOG(LogKorinsnaAuthoring, Error, TEXT("kawaii node does not expose FAnimNode_KawaiiPhysics"));
				return false;
			}
			ConfigureKawaiiNode(*KawaiiAnimNode, *Profile, Chain.RootBone, Chain.BaseBone);
			// Everything below the root is simulated, so the subtrees that must keep following the retarget
			// (spine, legs, skull) are excluded by name. Excluding a bone also prunes its whole subtree.
			KawaiiAnimNode->ExcludeBones.Reset();
			for (const FString& Bone : Chain.ExcludeBones)
			{
				// (assign, do not construct with an FName: that parses as a function declaration and the
				// member calls below then fail to compile)
				FBoneReference Excluded;
				Excluded.BoneName = FName(*Bone);
				Excluded.InvalidateCachedBoneIndex();
				KawaiiAnimNode->ExcludeBones.Add(Excluded);
			}
			KawaiiNode->NodeComment = Chain.Note.IsEmpty()
				? FString::Printf(TEXT("%s - %s"), *Chain.RootBone, *Chain.ProfileName)
				: FString::Printf(TEXT("%s - %s (%s)"), *Chain.RootBone, *Chain.ProfileName, *Chain.Note);
			PoseChain.Add(KawaiiNode);
		}
	}

	// Wire the chain: each node's pose output feeds the next node's component-pose input, and the last
	// one feeds the output pose. Every connection is logged, so a graph that ends up mis-wired is
	// visible in the build log instead of only in game.
	UEdGraphPin* RootInputPin = NamedPin(RootNode, TEXT("Result"), EGPD_Input);
	if (RootInputPin == nullptr)
	{
		UE_LOG(LogKorinsnaAuthoring, Error, TEXT("root node has no pose input pin"));
		return false;
	}
	for (int32 Index = 0; Index < PoseChain.Num(); ++Index)
	{
		UEdGraphPin* SourcePin = NamedPin(PoseChain[Index], TEXT("Pose"), EGPD_Output);
		UEdGraphPin* TargetPin = (Index + 1 < PoseChain.Num())
			? NamedPin(PoseChain[Index + 1], TEXT("Component Pose"), EGPD_Input)
			: RootInputPin;
		if (SourcePin == nullptr || TargetPin == nullptr)
		{
			UE_LOG(LogKorinsnaAuthoring, Error, TEXT("could not find the pose pins for %s"),
				*PoseChain[Index]->GetClass()->GetName());
			return false;
		}
		if (!AnimGraph->GetSchema()->TryCreateConnection(SourcePin, TargetPin))
		{
			UE_LOG(LogKorinsnaAuthoring, Error, TEXT("could not connect %s -> %s"),
				*PoseChain[Index]->GetClass()->GetName(), *TargetPin->GetOwningNode()->GetClass()->GetName());
			return false;
		}
		UE_LOG(LogKorinsnaAuthoring, Log, TEXT("wired %s.%s -> %s.%s"),
			*PoseChain[Index]->GetClass()->GetName(), *SourcePin->PinName.ToString(),
			*TargetPin->GetOwningNode()->GetClass()->GetName(), *TargetPin->PinName.ToString());
	}
	UE_LOG(LogKorinsnaAuthoring, Log, TEXT("graph: retarget + %d physics node(s)"), PhysicsCount);

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

FString UKorinsnaEditorLibrary::DescribeKawaiiPhysics(const FString& AssetPath)
{
	TStringBuilder<4096> Report;

	UAnimBlueprint* Blueprint = LoadObject<UAnimBlueprint>(nullptr, *AssetPath);
	if (Blueprint == nullptr)
	{
		return FString::Printf(TEXT("missing anim blueprint %s"), *AssetPath);
	}

	// Reference-pose geometry of the skeleton these nodes drive. A collision sphere is offset in its
	// driving bone's own space, so "15% of the way down the thigh" only means the right thing if the
	// units of this reference pose are known - and this skeleton's are not centimetres (the animated
	// pose is scaled up relative to it). Printing the numbers keeps that checkable from the log.
	if (const USkeleton* TargetSkeleton = Blueprint->TargetSkeleton)
	{
		const FReferenceSkeleton& RefSkeleton = TargetSkeleton->GetReferenceSkeleton();
		Report.Appendf(TEXT("skeleton %s refbones=%d\n"), *TargetSkeleton->GetName(),
			RefSkeleton.GetNum());
		for (const TCHAR* Bone : { TEXT("Bip001-Pelvis"), TEXT("Bip001-L-Thigh"), TEXT("Bip001-L-Calf"),
			TEXT("Bip001-L-Foot"), TEXT("Bip001-L-Forearm"), TEXT("Bip001-L-Hand"),
			TEXT("head_Bone001"), TEXT("head_Bone003"), TEXT("liuhai_1"), TEXT("b_skirt_1"),
			TEXT("l_skirt_5") })
		{
			const int32 Index = RefSkeleton.FindBoneIndex(FName(Bone));
			if (Index == INDEX_NONE)
			{
				Report.Appendf(TEXT("  ref %-18s MISSING\n"), Bone);
				continue;
			}
			const FTransform& Transform = RefSkeleton.GetRefBonePose()[Index];
			const FTransform Component = ComponentTransformOf(RefSkeleton, Index);
			const FTransform Other = ComponentTransformOf(RefSkeleton, Index, false);
			Report.Appendf(
				TEXT("  ref %-18s local=(%.2f, %.2f, %.2f) component=(%.2f, %.2f, %.2f)"
					 " alt=(%.2f, %.2f, %.2f) scale=(%.2f)\n"),
				Bone,
				Transform.GetLocation().X, Transform.GetLocation().Y, Transform.GetLocation().Z,
				Component.GetLocation().X, Component.GetLocation().Y, Component.GetLocation().Z,
				Other.GetLocation().X, Other.GetLocation().Y, Other.GetLocation().Z,
				Component.GetScale3D().X);
		}
	}

	for (UEdGraph* Graph : Blueprint->FunctionGraphs)
	{
		if (Cast<UAnimationGraph>(Graph) == nullptr)
		{
			continue;
		}
		Report.Appendf(TEXT("graph %s: %d node(s)\n"), *Graph->GetName(), Graph->Nodes.Num());
		int32 KawaiiCount = 0;
		for (UEdGraphNode* GraphNode : Graph->Nodes)
		{
			UAnimGraphNode_KawaiiPhysics* KawaiiNode = Cast<UAnimGraphNode_KawaiiPhysics>(GraphNode);
			if (KawaiiNode == nullptr)
			{
				continue;
			}
			++KawaiiCount;
			const FAnimNode_KawaiiPhysics* AnimNode = GetKawaiiAnimNode(KawaiiNode);
			if (AnimNode == nullptr)
			{
				Report.Appendf(TEXT("  kawaii node: could not read FAnimNode_KawaiiPhysics\n"));
				continue;
			}
			Report.Appendf(TEXT("  kawaii[%d] root=%-14s hasBone=%s settings: damping=%.2f stiffness=%.2f"
								 " worldDampLoc=%.2f worldDampRot=%.2f limitAngle=%.1f boneRadius=%.2f"
								 " dummy=%.1f fps=%d space=%d wind=%s worldCol=%s ignoreSelf=%s"
								 " base=%s spheres=%d exclude=%d capsules=%d alpha=%.2f\n"),
				KawaiiCount - 1,
				*AnimNode->RootBone.BoneName.ToString(),
				AnimNode->RootBone.BoneName.IsNone() ? TEXT("NO") : TEXT("yes"),
				AnimNode->PhysicsSettings.Damping, AnimNode->PhysicsSettings.Stiffness,
				AnimNode->PhysicsSettings.WorldDampingLocation, AnimNode->PhysicsSettings.WorldDampingRotation,
				AnimNode->PhysicsSettings.LimitAngle, AnimNode->PhysicsSettings.Radius,
				AnimNode->DummyBoneLength, AnimNode->TargetFramerate,
				static_cast<int32>(AnimNode->SimulationSpace),
				AnimNode->bEnableWind ? TEXT("ON") : TEXT("off"),
				AnimNode->bAllowWorldCollision ? TEXT("ON") : TEXT("off"),
				AnimNode->bIgnoreSelfComponent ? TEXT("yes") : TEXT("NO"),
				*AnimNode->SimulationBaseBone.BoneName.ToString(),
				AnimNode->SphericalLimits.Num(), AnimNode->ExcludeBones.Num(), AnimNode->CapsuleLimits.Num(),
			AnimNode->Alpha);

			for (const FSphericalLimit& Limit : AnimNode->SphericalLimits)
			{
				Report.Appendf(TEXT("      sphere bone=%-20s offset=(%.1f, %.1f, %.1f) radius=%.1f enabled=%s\n"),
					*Limit.DrivingBone.BoneName.ToString(), Limit.OffsetLocation.X, Limit.OffsetLocation.Y,
					Limit.OffsetLocation.Z, Limit.Radius, Limit.bEnable ? TEXT("yes") : TEXT("no"));
			}
		}
		Report.Appendf(TEXT("  kawaii nodes: %d\n"), KawaiiCount);

		// wiring, in graph order: which node feeds which
		for (UEdGraphNode* GraphNode : Graph->Nodes)
		{
			for (UEdGraphPin* Pin : GraphNode->Pins)
			{
				if (Pin == nullptr || Pin->Direction != EGPD_Output || Pin->LinkedTo.Num() == 0)
				{
					continue;
				}
				for (UEdGraphPin* Linked : Pin->LinkedTo)
				{
					if (Linked == nullptr)
					{
						continue;
					}
					Report.Appendf(TEXT("  link %s.%s -> %s.%s\n"),
						*GraphNode->GetClass()->GetName(), *Pin->PinName.ToString(),
						*Linked->GetOwningNode()->GetClass()->GetName(), *Linked->PinName.ToString());
				}
			}
		}
	}

	return Report.ToString();
}

#endif // WITH_EDITOR
