// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnimNode_KawaiiPhysics.h"
#include "Animation/BoneReference.h"
#include "Curves/CurveFloat.h"
#include "GameplayTagContainer.h"
#include "KawaiiPhysicsBoneConstraintTypes.h"
#include "KawaiiPhysicsCollisionLimits.h"
#include "KawaiiPhysicsSyncBone.h"
#include "KawaiiPhysicsTypes.h"
#include "PhysicsEngine/BodyInstance.h"
#include "StructUtils/InstancedStruct.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeAnimNode_KawaiiPhysics() {}

// ********** Begin Cross Module References ********************************************************
ANIMGRAPHRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_SkeletalControlBase();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FInstancedStruct();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_UPhysicsAsset_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FBodyInstance();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FBoneReference();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FRuntimeFloatCurve();
GAMEPLAYTAGS_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayTag();
KAWAIIPHYSICS_API UClass* Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_NoRegister();
KAWAIIPHYSICS_API UClass* Z_Construct_UClass_UKawaiiPhysicsBoneConstraintsDataAsset_NoRegister();
KAWAIIPHYSICS_API UClass* Z_Construct_UClass_UKawaiiPhysicsLimitsDataAsset_NoRegister();
KAWAIIPHYSICS_API UEnum* Z_Construct_UEnum_KawaiiPhysics_EBoneForwardAxis();
KAWAIIPHYSICS_API UEnum* Z_Construct_UEnum_KawaiiPhysics_EKawaiiPhysicsSimulationSpace();
KAWAIIPHYSICS_API UEnum* Z_Construct_UEnum_KawaiiPhysics_EPlanarConstraint();
KAWAIIPHYSICS_API UEnum* Z_Construct_UEnum_KawaiiPhysics_EXPBDComplianceType();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FBoxLimit();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FCapsuleLimit();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FKawaiiPhysicsSettings();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FModifyBoneConstraint();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FPlanarLimit();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FSphericalLimit();
UPackage* Z_Construct_UPackage__Script_KawaiiPhysics();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FAnimNode_KawaiiPhysics *******************************************
struct Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FAnimNode_KawaiiPhysics); }
	static inline consteval int16 GetStructAlignment() { return alignof(FAnimNode_KawaiiPhysics); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RootBone_MetaData[] = {
		{ "Category", "Bones" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe6\x8c\x87\xe5\xae\x9a\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xa8\xe3\x81\x9d\xe3\x82\x8c\xe4\xbb\xa5\xe4\xb8\x8b\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe5\x88\xb6\xe5\xbe\xa1\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xab\n\x09* Control the specified bone and the bones below it\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x8c\x87\xe5\xae\x9a\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xa8\xe3\x81\x9d\xe3\x82\x8c\xe4\xbb\xa5\xe4\xb8\x8b\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe5\x88\xb6\xe5\xbe\xa1\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xab\nControl the specified bone and the bones below it" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExcludeBones_MetaData[] = {
		{ "Category", "Bones" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe6\x8c\x87\xe5\xae\x9a\xe3\x81\x97\xe3\x81\x9f\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xa8\xe3\x81\x9d\xe3\x82\x8c\xe4\xbb\xa5\xe4\xb8\x8b\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe5\x88\xb6\xe5\xbe\xa1\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\x8b\xe3\x82\x89\xe9\x99\xa4\xe5\x8e\xbb\n\x09* Do NOT control the specified bone and the bones below it\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x8c\x87\xe5\xae\x9a\xe3\x81\x97\xe3\x81\x9f\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xa8\xe3\x81\x9d\xe3\x82\x8c\xe4\xbb\xa5\xe4\xb8\x8b\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe5\x88\xb6\xe5\xbe\xa1\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\x8b\xe3\x82\x89\xe9\x99\xa4\xe5\x8e\xbb\nDo NOT control the specified bone and the bones below it" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AdditionalRootBones_MetaData[] = {
		{ "Category", "Bones" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe6\x8c\x87\xe5\xae\x9a\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xa8\xe3\x81\x9d\xe3\x82\x8c\xe4\xbb\xa5\xe4\xb8\x8b\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe5\x88\xb6\xe5\xbe\xa1\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xab(\xe8\xbf\xbd\xe5\x8a\xa0\xe7\x94\xa8)\n\x09* Control the specified bone and the bones below it (For Addition)\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "TitleProperty", "RootBone" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x8c\x87\xe5\xae\x9a\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xa8\xe3\x81\x9d\xe3\x82\x8c\xe4\xbb\xa5\xe4\xb8\x8b\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe5\x88\xb6\xe5\xbe\xa1\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xab(\xe8\xbf\xbd\xe5\x8a\xa0\xe7\x94\xa8)\nControl the specified bone and the bones below it (For Addition)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DummyBoneLength_MetaData[] = {
		{ "Category", "Bones" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* 0\xe3\x82\x88\xe3\x82\x8a\xe5\xa4\xa7\xe3\x81\x8d\xe3\x81\x84\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe3\x80\x81\xe5\x88\xb6\xe5\xbe\xa1\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe6\x9c\xab\xe7\xab\xaf\xe3\x81\xab\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe8\xbf\xbd\xe5\x8a\xa0\xe3\x80\x82\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe8\xbf\xbd\xe5\x8a\xa0\xe3\x81\x99\xe3\x82\x8b\xe3\x81\x93\xe3\x81\xa8\xe3\x81\xa7\xe3\x80\x81\xe6\x9c\xab\xe7\xab\xaf\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe7\x89\xa9\xe7\x90\x86\xe5\x88\xb6\xe5\xbe\xa1\xe3\x82\x92\xe6\x94\xb9\xe5\x96\x84\n\x09* Add a dummy bone to the end bone if it's above 0. It affects end bone rotation. \n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "0\xe3\x82\x88\xe3\x82\x8a\xe5\xa4\xa7\xe3\x81\x8d\xe3\x81\x84\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe3\x80\x81\xe5\x88\xb6\xe5\xbe\xa1\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe6\x9c\xab\xe7\xab\xaf\xe3\x81\xab\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe8\xbf\xbd\xe5\x8a\xa0\xe3\x80\x82\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe8\xbf\xbd\xe5\x8a\xa0\xe3\x81\x99\xe3\x82\x8b\xe3\x81\x93\xe3\x81\xa8\xe3\x81\xa7\xe3\x80\x81\xe6\x9c\xab\xe7\xab\xaf\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe7\x89\xa9\xe7\x90\x86\xe5\x88\xb6\xe5\xbe\xa1\xe3\x82\x92\xe6\x94\xb9\xe5\x96\x84\nAdd a dummy bone to the end bone if it's above 0. It affects end bone rotation." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoneSubdivisionCount_MetaData[] = {
		{ "Category", "Bones|Bone Subdivision" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* \xe9\x9a\xa3\xe6\x8e\xa5\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x81\xab\xe6\x8c\xbf\xe5\x85\xa5\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe6\x9c\x80\xe5\xb0\x8f\xe5\x88\x86\xe5\x89\xb2\xe6\x95\xb0\xe3\x80\x82\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe6\xa4\x9c\xe5\x87\xba\xe3\x81\xae\xe7\xb2\xbe\xe5\xba\xa6\xe3\x82\x92\xe5\x90\x91\xe4\xb8\x8a\xe3\x81\x95\xe3\x81\x9b\xe3\x82\x8b\xef\xbc\x88\xe4\xbe\x8b: \xe3\x82\xb9\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x88\xe3\x81\xae\xe8\xb6\xb3\xe8\xb2\xab\xe9\x80\x9a\xe9\x98\xb2\xe6\xad\xa2\xef\xbc\x89\xe3\x80\x82""0\xe3\x81\xa7\xe7\x84\xa1\xe5\x8a\xb9\xe3\x80\x82\n\x09* bBoneSubdivisionDensifyByRadius \xe3\x81\x8c\xe6\x9c\x89\xe5\x8a\xb9\xe3\x81\xaa\xe3\x81\xa8\xe3\x81\x8d\xe3\x81\xaf\xe3\x80\x81\xe3\x81\x93\xe3\x82\x8c\xe3\x82\x92\xe6\x9c\x80\xe5\xb0\x8f\xe3\x81\xa8\xe3\x81\x97\xe3\x81\xa6\xe5\x8d\x8a\xe5\xbe\x84\xe3\x81\xab\xe5\xbf\x9c\xe3\x81\x98\xe8\xbf\xbd\xe5\x8a\xa0\xe9\x85\x8d\xe7\xbd\xae\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b\xe3\x80\x82\n\x09* Minimum number of DummyBone subdivisions to insert between adjacent physics bones.\n\x09* Improves collision detection (e.g., prevents skirts from penetrating legs). Set to 0 to disable.\n\x09* When bBoneSubdivisionDensifyByRadius is enabled, this acts as a floor and more are added based on radius.\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x9a\xa3\xe6\x8e\xa5\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x81\xab\xe6\x8c\xbf\xe5\x85\xa5\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe6\x9c\x80\xe5\xb0\x8f\xe5\x88\x86\xe5\x89\xb2\xe6\x95\xb0\xe3\x80\x82\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe6\xa4\x9c\xe5\x87\xba\xe3\x81\xae\xe7\xb2\xbe\xe5\xba\xa6\xe3\x82\x92\xe5\x90\x91\xe4\xb8\x8a\xe3\x81\x95\xe3\x81\x9b\xe3\x82\x8b\xef\xbc\x88\xe4\xbe\x8b: \xe3\x82\xb9\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x88\xe3\x81\xae\xe8\xb6\xb3\xe8\xb2\xab\xe9\x80\x9a\xe9\x98\xb2\xe6\xad\xa2\xef\xbc\x89\xe3\x80\x82""0\xe3\x81\xa7\xe7\x84\xa1\xe5\x8a\xb9\xe3\x80\x82\nbBoneSubdivisionDensifyByRadius \xe3\x81\x8c\xe6\x9c\x89\xe5\x8a\xb9\xe3\x81\xaa\xe3\x81\xa8\xe3\x81\x8d\xe3\x81\xaf\xe3\x80\x81\xe3\x81\x93\xe3\x82\x8c\xe3\x82\x92\xe6\x9c\x80\xe5\xb0\x8f\xe3\x81\xa8\xe3\x81\x97\xe3\x81\xa6\xe5\x8d\x8a\xe5\xbe\x84\xe3\x81\xab\xe5\xbf\x9c\xe3\x81\x98\xe8\xbf\xbd\xe5\x8a\xa0\xe9\x85\x8d\xe7\xbd\xae\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b\xe3\x80\x82\nMinimum number of DummyBone subdivisions to insert between adjacent physics bones.\nImproves collision detection (e.g., prevents skirts from penetrating legs). Set to 0 to disable.\nWhen bBoneSubdivisionDensifyByRadius is enabled, this acts as a floor and more are added based on radius." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bBoneSubdivisionCollisionOnly_MetaData[] = {
		{ "Category", "Bones|Bone Subdivision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* \xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe9\x80\x9f\xe5\xba\xa6\xe7\xa9\x8d\xe5\x88\x86\xef\xbc\x88\xe9\x87\x8d\xe5\x8a\x9b\xe3\x83\xbb\xe9\xa2\xa8\xe3\x81\xaa\xe3\x81\xa9\xef\xbc\x89\xe3\x82\x92\xe3\x82\xb9\xe3\x82\xad\xe3\x83\x83\xe3\x83\x97\xe3\x81\x97\xe3\x80\x81\xe5\xae\x9f\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x81\xae\xe8\xa3\x9c\xe9\x96\x93\xe4\xbd\x8d\xe7\xbd\xae\xe3\x81\x8b\xe3\x82\x89\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x83\xbb\xe5\x88\xb6\xe7\xb4\x84\xe3\x81\xab\xe5\x8f\x82\xe5\x8a\xa0\xef\xbc\x88\xe9\x85\x8d\xe7\xbd\xae\xe6\x95\xb0\xe3\x81\xab\xe3\x81\xaf\xe5\xbd\xb1\xe9\x9f\xbf\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xef\xbc\x89\xe3\x80\x82\n\x09* When true, inter-bone dummy bones skip velocity integration (gravity/wind/etc.) and participate in collision and constraints from interpolated positions. Does not affect the number of dummies.\n\x09*/" },
#endif
		{ "EditCondition", "BoneSubdivisionCount > 0" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe9\x80\x9f\xe5\xba\xa6\xe7\xa9\x8d\xe5\x88\x86\xef\xbc\x88\xe9\x87\x8d\xe5\x8a\x9b\xe3\x83\xbb\xe9\xa2\xa8\xe3\x81\xaa\xe3\x81\xa9\xef\xbc\x89\xe3\x82\x92\xe3\x82\xb9\xe3\x82\xad\xe3\x83\x83\xe3\x83\x97\xe3\x81\x97\xe3\x80\x81\xe5\xae\x9f\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x81\xae\xe8\xa3\x9c\xe9\x96\x93\xe4\xbd\x8d\xe7\xbd\xae\xe3\x81\x8b\xe3\x82\x89\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x83\xbb\xe5\x88\xb6\xe7\xb4\x84\xe3\x81\xab\xe5\x8f\x82\xe5\x8a\xa0\xef\xbc\x88\xe9\x85\x8d\xe7\xbd\xae\xe6\x95\xb0\xe3\x81\xab\xe3\x81\xaf\xe5\xbd\xb1\xe9\x9f\xbf\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xef\xbc\x89\xe3\x80\x82\nWhen true, inter-bone dummy bones skip velocity integration (gravity/wind/etc.) and participate in collision and constraints from interpolated positions. Does not affect the number of dummies." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bBoneSubdivisionDensifyByRadius_MetaData[] = {
		{ "Category", "Bones|Bone Subdivision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* \xe5\x8d\x8a\xe5\xbe\x84\xe3\x81\xab\xe5\xbf\x9c\xe3\x81\x98\xe3\x81\xa6\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x82\x92\xe8\xbf\xbd\xe5\x8a\xa0\xe9\x85\x8d\xe7\xbd\xae\xe3\x81\x97\xe3\x80\x81\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe7\x90\x83\xe3\x81\xa7\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x82\x92\xe6\xa6\x82\xe3\x81\xad\xe9\x9a\x99\xe9\x96\x93\xe3\x81\xaa\xe3\x81\x8f\xe8\xa2\xab\xe8\xa6\x86\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82""BoneSubdivisionCount \xe3\x82\x92\xe6\x9c\x80\xe5\xb0\x8f\xe3\x81\xa8\xe3\x81\x97\xe3\x81\xa6\xe3\x80\x81\n\x09* \xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x81\x8c\xe5\x8d\x8a\xe5\xbe\x84\xe3\x81\xab\xe5\xaf\xbe\xe3\x81\x97\xe3\x81\xa6\xe9\x9b\xa2\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe5\x8c\xba\xe9\x96\x93\xe3\x81\xbb\xe3\x81\xa9\xe5\xa4\x9a\xe3\x81\x8f\xe9\x85\x8d\xe7\xbd\xae\xe3\x81\x99\xe3\x82\x8b\xef\xbc\x88\xe8\xbf\x91\xe6\x8e\xa5\xe5\x8c\xba\xe9\x96\x93\xe3\x81\xaf\xe6\x9c\x80\xe5\xb0\x8f\xe3\x81\xae\xe3\x81\xbe\xe3\x81\xbe\xe3\x80\x82""1\xe5\x8c\xba\xe9\x96\x93\xe3\x81\x82\xe3\x81\x9f\xe3\x82\x8a\xe6\x9c\x80\xe5\xa4\xa7""50\xe6\x9c\xac\xef\xbc\x89\xe3\x80\x82\n\x09* \xe6\x9c\x89\xe5\x8a\xb9\xe4\xb8\xad\xe3\x81\xab Radius / RadiusCurve \xe3\x82\x92\xe5\xa4\x89\xe6\x9b\xb4\xe3\x81\x97\xe3\x81\x9f\xe5\xa0\xb4\xe5\x90\x88\xe3\x80\x81\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe6\x95\xb0\xe3\x81\xae\xe5\x86\x8d\xe8\xa8\x88\xe7\xae\x97\xe3\x81\xab\xe3\x81\xaf\xe5\x86\x8d\xe5\x88\x9d\xe6\x9c\x9f\xe5\x8c\x96\xef\xbc\x88""ABP\xe5\x86\x8d\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x91\xe3\x82\xa4\xe3\x83\xab\xe7\xad\x89\xef\xbc\x89\xe3\x81\x8c\xe5\xbf\x85\xe8\xa6\x81\xe3\x81\xaa\xe3\x81\x93\xe3\x81\xa8\xe3\x81\x8c\xe3\x81\x82\xe3\x82\x8b\xe3\x80\x82\n\x09* Add dummies based on radius so collision spheres roughly cover the gap between bones. Uses BoneSubdivisionCount as the\n\x09* minimum and places more where bones are far apart relative to their radius (close segments keep the minimum; up to 50 per segment).\n\x09* While enabled, changing Radius / RadiusCurve may need a re-init (e.g. recompiling the ABP) for the dummy count to update.\n\x09*/" },
#endif
		{ "EditCondition", "BoneSubdivisionCount > 0" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8d\x8a\xe5\xbe\x84\xe3\x81\xab\xe5\xbf\x9c\xe3\x81\x98\xe3\x81\xa6\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x82\x92\xe8\xbf\xbd\xe5\x8a\xa0\xe9\x85\x8d\xe7\xbd\xae\xe3\x81\x97\xe3\x80\x81\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe7\x90\x83\xe3\x81\xa7\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x82\x92\xe6\xa6\x82\xe3\x81\xad\xe9\x9a\x99\xe9\x96\x93\xe3\x81\xaa\xe3\x81\x8f\xe8\xa2\xab\xe8\xa6\x86\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82""BoneSubdivisionCount \xe3\x82\x92\xe6\x9c\x80\xe5\xb0\x8f\xe3\x81\xa8\xe3\x81\x97\xe3\x81\xa6\xe3\x80\x81\n\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x81\x8c\xe5\x8d\x8a\xe5\xbe\x84\xe3\x81\xab\xe5\xaf\xbe\xe3\x81\x97\xe3\x81\xa6\xe9\x9b\xa2\xe3\x82\x8c\xe3\x81\xa6\xe3\x81\x84\xe3\x82\x8b\xe5\x8c\xba\xe9\x96\x93\xe3\x81\xbb\xe3\x81\xa9\xe5\xa4\x9a\xe3\x81\x8f\xe9\x85\x8d\xe7\xbd\xae\xe3\x81\x99\xe3\x82\x8b\xef\xbc\x88\xe8\xbf\x91\xe6\x8e\xa5\xe5\x8c\xba\xe9\x96\x93\xe3\x81\xaf\xe6\x9c\x80\xe5\xb0\x8f\xe3\x81\xae\xe3\x81\xbe\xe3\x81\xbe\xe3\x80\x82""1\xe5\x8c\xba\xe9\x96\x93\xe3\x81\x82\xe3\x81\x9f\xe3\x82\x8a\xe6\x9c\x80\xe5\xa4\xa7""50\xe6\x9c\xac\xef\xbc\x89\xe3\x80\x82\n\xe6\x9c\x89\xe5\x8a\xb9\xe4\xb8\xad\xe3\x81\xab Radius / RadiusCurve \xe3\x82\x92\xe5\xa4\x89\xe6\x9b\xb4\xe3\x81\x97\xe3\x81\x9f\xe5\xa0\xb4\xe5\x90\x88\xe3\x80\x81\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe6\x95\xb0\xe3\x81\xae\xe5\x86\x8d\xe8\xa8\x88\xe7\xae\x97\xe3\x81\xab\xe3\x81\xaf\xe5\x86\x8d\xe5\x88\x9d\xe6\x9c\x9f\xe5\x8c\x96\xef\xbc\x88""ABP\xe5\x86\x8d\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x91\xe3\x82\xa4\xe3\x83\xab\xe7\xad\x89\xef\xbc\x89\xe3\x81\x8c\xe5\xbf\x85\xe8\xa6\x81\xe3\x81\xaa\xe3\x81\x93\xe3\x81\xa8\xe3\x81\x8c\xe3\x81\x82\xe3\x82\x8b\xe3\x80\x82\nAdd dummies based on radius so collision spheres roughly cover the gap between bones. Uses BoneSubdivisionCount as the\nminimum and places more where bones are far apart relative to their radius (close segments keep the minimum; up to 50 per segment).\nWhile enabled, changing Radius / RadiusCurve may need a re-init (e.g. recompiling the ABP) for the dummy count to update." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoneConstraintSubdivisionCount_MetaData[] = {
		{ "Category", "Bones|Bone Subdivision" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* \xe6\xa8\xaa\xe6\x96\xb9\xe5\x90\x91""BoneConstraint\xe3\x81\xab\xe6\xb2\xbf\xe3\x81\xa3\xe3\x81\xa6\xe6\x8c\xbf\xe5\x85\xa5\xe3\x81\x99\xe3\x82\x8b\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe4\xbb\xa3\xe7\x90\x86\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x81\xae\xe5\x88\x86\xe5\x89\xb2\xe6\x95\xb0\xe3\x80\x82\xe9\x9a\xa3\xe6\x8e\xa5\xe3\x83\x81\xe3\x82\xa7\xe3\x83\xbc\xe3\x83\xb3\xef\xbc\x88\xe5\x88\x97\xef\xbc\x89\xe9\x96\x93\xe3\x81\xae\xe9\x9a\x99\xe9\x96\x93\xe3\x82\x92\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe7\x82\xb9\xe3\x81\xa7\xe5\x9f\x8b\xe3\x82\x81\xe3\x81\xa6\xe8\xb2\xab\xe9\x80\x9a\xe3\x82\x92\xe9\x98\xb2\xe3\x81\x90\xe3\x80\x82\n\x09* Number of collision-proxy dummies to insert along each horizontal BoneConstraint. Fills horizontal gaps between adjacent chains (columns) to prevent penetration.\n\x09* BoneSubdivisionCount\xe3\x81\xa8\xe7\xb5\x84\xe3\x81\xbf\xe5\x90\x88\xe3\x82\x8f\xe3\x81\x9b\xe3\x82\x8b\xe3\x81\xa8\xe5\xb8\x83\xe9\x9d\xa2\xe3\x81\xab""2D\xe3\x82\xb0\xe3\x83\xaa\xe3\x83\x83\xe3\x83\x89\xe7\x8a\xb6\xe3\x81\xae\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe7\x82\xb9\xe3\x81\x8c\xe4\xb8\xa6\xe3\x81\xb6\xe3\x80\x82""0\xe3\x81\xa7\xe7\x84\xa1\xe5\x8a\xb9\xe3\x80\x82\xe7\xab\xaf\xe7\x82\xb9\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x81\x8c\xe6\x97\xa2\xe3\x81\xab\xe9\x87\x8d\xe3\x81\xaa\xe3\x82\x8b\xe6\x8e\xa5\xe7\xb6\x9a(\xe9\x96\x93\xe9\x9a\x94<=2*\xe5\x8d\x8a\xe5\xbe\x84)\xe3\x81\xab\xe3\x81\xaf\xe6\x8c\xbf\xe5\x85\xa5\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xe3\x80\x82""BoneSubdivisionCount\xe3\x81\xa8\xe3\x81\xaf\xe7\x8b\xac\xe7\xab\x8b\xe3\x80\x82\n\x09* Combine with BoneSubdivisionCount for a 2D grid of collision points. 0 to disable. Skipped where the endpoint collisions already overlap (spacing <= 2*radius). Independent of BoneSubdivisionCount.\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xa8\xaa\xe6\x96\xb9\xe5\x90\x91""BoneConstraint\xe3\x81\xab\xe6\xb2\xbf\xe3\x81\xa3\xe3\x81\xa6\xe6\x8c\xbf\xe5\x85\xa5\xe3\x81\x99\xe3\x82\x8b\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe4\xbb\xa3\xe7\x90\x86\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x81\xae\xe5\x88\x86\xe5\x89\xb2\xe6\x95\xb0\xe3\x80\x82\xe9\x9a\xa3\xe6\x8e\xa5\xe3\x83\x81\xe3\x82\xa7\xe3\x83\xbc\xe3\x83\xb3\xef\xbc\x88\xe5\x88\x97\xef\xbc\x89\xe9\x96\x93\xe3\x81\xae\xe9\x9a\x99\xe9\x96\x93\xe3\x82\x92\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe7\x82\xb9\xe3\x81\xa7\xe5\x9f\x8b\xe3\x82\x81\xe3\x81\xa6\xe8\xb2\xab\xe9\x80\x9a\xe3\x82\x92\xe9\x98\xb2\xe3\x81\x90\xe3\x80\x82\nNumber of collision-proxy dummies to insert along each horizontal BoneConstraint. Fills horizontal gaps between adjacent chains (columns) to prevent penetration.\nBoneSubdivisionCount\xe3\x81\xa8\xe7\xb5\x84\xe3\x81\xbf\xe5\x90\x88\xe3\x82\x8f\xe3\x81\x9b\xe3\x82\x8b\xe3\x81\xa8\xe5\xb8\x83\xe9\x9d\xa2\xe3\x81\xab""2D\xe3\x82\xb0\xe3\x83\xaa\xe3\x83\x83\xe3\x83\x89\xe7\x8a\xb6\xe3\x81\xae\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe7\x82\xb9\xe3\x81\x8c\xe4\xb8\xa6\xe3\x81\xb6\xe3\x80\x82""0\xe3\x81\xa7\xe7\x84\xa1\xe5\x8a\xb9\xe3\x80\x82\xe7\xab\xaf\xe7\x82\xb9\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x81\x8c\xe6\x97\xa2\xe3\x81\xab\xe9\x87\x8d\xe3\x81\xaa\xe3\x82\x8b\xe6\x8e\xa5\xe7\xb6\x9a(\xe9\x96\x93\xe9\x9a\x94<=2*\xe5\x8d\x8a\xe5\xbe\x84)\xe3\x81\xab\xe3\x81\xaf\xe6\x8c\xbf\xe5\x85\xa5\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xe3\x80\x82""BoneSubdivisionCount\xe3\x81\xa8\xe3\x81\xaf\xe7\x8b\xac\xe7\xab\x8b\xe3\x80\x82\nCombine with BoneSubdivisionCount for a 2D grid of collision points. 0 to disable. Skipped where the endpoint collisions already overlap (spacing <= 2*radius). Independent of BoneSubdivisionCount." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoneConstraintSubdivisionFeedbackScale_MetaData[] = {
		{ "Category", "Bones|Bone Subdivision" },
		{ "ClampMax", "2.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* bridge dummy\xe3\x81\x8c\xe5\x8f\x97\xe3\x81\x91\xe3\x81\x9f\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe5\xa4\x89\xe4\xbd\x8d\xe3\x82\x92\xe7\xab\xaf\xe7\x82\xb9\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xb8\xe8\xbb\xa2\xe9\x80\x81\xe3\x81\x99\xe3\x82\x8b\xe5\xbc\xb7\xe3\x81\x95\xe3\x80\x82""0=\xe8\xbb\xa2\xe9\x80\x81\xe3\x81\xaa\xe3\x81\x97\xe3\x80\x81""1=\xe7\xab\xaf\xe7\x82\xb9\xe3\x81\xa8\xe3\x81\xae\xe8\xb7\x9d\xe9\x9b\xa2\xe6\xaf\x94\xe3\x81\xab\xe5\xbf\x9c\xe3\x81\x98\xe3\x81\x9f\xe6\xa8\x99\xe6\xba\x96\xe7\x9a\x84\xe3\x81\xaa\xe6\x8a\xbc\xe3\x81\x97\xe5\x87\xba\xe3\x81\x97\xe3\x80\x82\n\x09* \xe3\x81\x93\xe3\x82\x8c\xe3\x81\xab\xe3\x82\x88\xe3\x82\x8a\xe5\x88\x97\xe3\x81\xae\xe9\x96\x93\xe3\x81\xa7\xe5\x8b\x95\xe3\x81\x8f\xe3\x82\xb3\xe3\x83\xa9\xe3\x82\xa4\xe3\x83\x80\xe3\x83\xbc\xe3\x81\x8c\xe5\xae\x9f\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe6\x8a\xbc\xe3\x81\x97\xe5\x87\xba\xe3\x81\x9b\xe3\x82\x8b\xef\xbc\x88\xe8\xb2\xab\xe9\x80\x9a\xe9\x98\xb2\xe6\xad\xa2\xe3\x83\x95\xe3\x82\xa3\xe3\x83\xbc\xe3\x83\x89\xe3\x83\x90\xe3\x83\x83\xe3\x82\xaf\xe3\x81\xae\xe6\x9c\xac\xe4\xbd\x93\xef\xbc\x89\xe3\x80\x82\xe5\x89\x9b\xe6\x80\xa7\xe3\x81\x8c\xe5\xbc\xb7\xe3\x81\x99\xe3\x81\x8e\xe3\x82\x8b\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe4\xb8\x8b\xe3\x81\x92\xe3\x82\x8b\xe3\x80\x82\n\x09* Strength of transferring a bridge dummy's collision displacement to its endpoint bones (0 = none, 1 = standard\n\x09* push weighted by proximity). This is what lets a collider moving between columns actually push the real bones.\n\x09*/" },
#endif
		{ "EditCondition", "BoneConstraintSubdivisionCount > 0" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "bridge dummy\xe3\x81\x8c\xe5\x8f\x97\xe3\x81\x91\xe3\x81\x9f\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe5\xa4\x89\xe4\xbd\x8d\xe3\x82\x92\xe7\xab\xaf\xe7\x82\xb9\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xb8\xe8\xbb\xa2\xe9\x80\x81\xe3\x81\x99\xe3\x82\x8b\xe5\xbc\xb7\xe3\x81\x95\xe3\x80\x82""0=\xe8\xbb\xa2\xe9\x80\x81\xe3\x81\xaa\xe3\x81\x97\xe3\x80\x81""1=\xe7\xab\xaf\xe7\x82\xb9\xe3\x81\xa8\xe3\x81\xae\xe8\xb7\x9d\xe9\x9b\xa2\xe6\xaf\x94\xe3\x81\xab\xe5\xbf\x9c\xe3\x81\x98\xe3\x81\x9f\xe6\xa8\x99\xe6\xba\x96\xe7\x9a\x84\xe3\x81\xaa\xe6\x8a\xbc\xe3\x81\x97\xe5\x87\xba\xe3\x81\x97\xe3\x80\x82\n\xe3\x81\x93\xe3\x82\x8c\xe3\x81\xab\xe3\x82\x88\xe3\x82\x8a\xe5\x88\x97\xe3\x81\xae\xe9\x96\x93\xe3\x81\xa7\xe5\x8b\x95\xe3\x81\x8f\xe3\x82\xb3\xe3\x83\xa9\xe3\x82\xa4\xe3\x83\x80\xe3\x83\xbc\xe3\x81\x8c\xe5\xae\x9f\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe6\x8a\xbc\xe3\x81\x97\xe5\x87\xba\xe3\x81\x9b\xe3\x82\x8b\xef\xbc\x88\xe8\xb2\xab\xe9\x80\x9a\xe9\x98\xb2\xe6\xad\xa2\xe3\x83\x95\xe3\x82\xa3\xe3\x83\xbc\xe3\x83\x89\xe3\x83\x90\xe3\x83\x83\xe3\x82\xaf\xe3\x81\xae\xe6\x9c\xac\xe4\xbd\x93\xef\xbc\x89\xe3\x80\x82\xe5\x89\x9b\xe6\x80\xa7\xe3\x81\x8c\xe5\xbc\xb7\xe3\x81\x99\xe3\x81\x8e\xe3\x82\x8b\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe4\xb8\x8b\xe3\x81\x92\xe3\x82\x8b\xe3\x80\x82\nStrength of transferring a bridge dummy's collision displacement to its endpoint bones (0 = none, 1 = standard\npush weighted by proximity). This is what lets a collider moving between columns actually push the real bones." },
#endif
		{ "UIMax", "2.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoneForwardAxis_MetaData[] = {
		{ "Category", "Bones" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* \xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe5\x89\x8d\xe6\x96\xb9\xe3\x80\x82\xe7\x89\xa9\xe7\x90\x86\xe5\x88\xb6\xe5\xbe\xa1\xe3\x82\x84\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe9\x85\x8d\xe7\xbd\xae\xe4\xbd\x8d\xe7\xbd\xae\xe3\x81\xab\xe5\xbd\xb1\xe9\x9f\xbf\n\x09* Bone forward direction. Affects the placement of physical controls and dummy bones\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe5\x89\x8d\xe6\x96\xb9\xe3\x80\x82\xe7\x89\xa9\xe7\x90\x86\xe5\x88\xb6\xe5\xbe\xa1\xe3\x82\x84\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe9\x85\x8d\xe7\xbd\xae\xe4\xbd\x8d\xe7\xbd\xae\xe3\x81\xab\xe5\xbd\xb1\xe9\x9f\xbf\nBone forward direction. Affects the placement of physical controls and dummy bones" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PhysicsSettings_MetaData[] = {
		{ "Category", "Physics Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe7\x89\xa9\xe7\x90\x86\xe5\x88\xb6\xe5\xbe\xa1\xe3\x81\xae\xe5\x9f\xba\xe6\x9c\xac\xe8\xa8\xad\xe5\xae\x9a\n\x09* Basic physics settings\n\x09*/" },
#endif
		{ "DisplayPriority", "0" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x89\xa9\xe7\x90\x86\xe5\x88\xb6\xe5\xbe\xa1\xe3\x81\xae\xe5\x9f\xba\xe6\x9c\xac\xe8\xa8\xad\xe5\xae\x9a\nBasic physics settings" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SimulationSpace_MetaData[] = {
		{ "Category", "Physics Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* \xe7\x89\xa9\xe7\x90\x86\xe5\x88\xb6\xe5\xbe\xa1\xe3\x82\x92\xe8\xa1\x8c\xe3\x81\x86\xe5\xba\xa7\xe6\xa8\x99\xe7\xb3\xbb\xef\xbc\x88""Component\xe4\xbb\xa5\xe5\xa4\x96\xe3\x81\xae\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe5\xbe\xae\xe5\xb0\x8f\xe3\x81\xae\xe3\x83\x91\xe3\x83\x95\xe3\x82\xa9\xe3\x83\xbc\xe3\x83\x9e\xe3\x83\xb3\xe3\x82\xb9\xe4\xbd\x8e\xe4\xb8\x8b\xe3\x81\x8c\xe7\x99\xba\xe7\x94\x9f\xe3\x81\x97\xe3\x81\xbe\xe3\x81\x99\xe3\x81\x8c\xe3\x80\x81\xe6\x80\xa5\xe6\xbf\x80\xe3\x81\xaaRoot\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe3\x83\xbb\xe5\x9b\x9e\xe8\xbb\xa2\xe3\x81\xae\xe5\xbd\xb1\xe9\x9f\xbf\xe3\x82\x92\xe5\x9b\x9e\xe9\x81\xbf\xe3\x81\x99\xe3\x82\x8b\xe3\x81\x93\xe3\x81\xa8\xe3\x81\x8c\xe3\x81\xa7\xe3\x81\x8d\xe3\x81\xbe\xe3\x81\x99\xef\xbc\x89\n\x09* Simulation space for physics control (Using anything other than ComponentSpace may cause a slight performance drop, but it can avoid the impact of sudden Root bone movement and rotation)\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x89\xa9\xe7\x90\x86\xe5\x88\xb6\xe5\xbe\xa1\xe3\x82\x92\xe8\xa1\x8c\xe3\x81\x86\xe5\xba\xa7\xe6\xa8\x99\xe7\xb3\xbb\xef\xbc\x88""Component\xe4\xbb\xa5\xe5\xa4\x96\xe3\x81\xae\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe5\xbe\xae\xe5\xb0\x8f\xe3\x81\xae\xe3\x83\x91\xe3\x83\x95\xe3\x82\xa9\xe3\x83\xbc\xe3\x83\x9e\xe3\x83\xb3\xe3\x82\xb9\xe4\xbd\x8e\xe4\xb8\x8b\xe3\x81\x8c\xe7\x99\xba\xe7\x94\x9f\xe3\x81\x97\xe3\x81\xbe\xe3\x81\x99\xe3\x81\x8c\xe3\x80\x81\xe6\x80\xa5\xe6\xbf\x80\xe3\x81\xaaRoot\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe3\x83\xbb\xe5\x9b\x9e\xe8\xbb\xa2\xe3\x81\xae\xe5\xbd\xb1\xe9\x9f\xbf\xe3\x82\x92\xe5\x9b\x9e\xe9\x81\xbf\xe3\x81\x99\xe3\x82\x8b\xe3\x81\x93\xe3\x81\xa8\xe3\x81\x8c\xe3\x81\xa7\xe3\x81\x8d\xe3\x81\xbe\xe3\x81\x99\xef\xbc\x89\nSimulation space for physics control (Using anything other than ComponentSpace may cause a slight performance drop, but it can avoid the impact of sudden Root bone movement and rotation)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SimulationBaseBone_MetaData[] = {
		{ "Category", "Physics Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* BaseBone\xe5\xba\xa7\xe6\xa8\x99\xe7\xb3\xbb\xe6\x99\x82\xe3\x81\xae\xe5\x9f\xba\xe6\xba\x96\xe3\x81\xa8\xe3\x81\xaa\xe3\x82\x8b\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\n\x09* BaseBone coordinate system reference bone\n\x09*/" },
#endif
		{ "EditCondition", "SimulationSpace == EKawaiiPhysicsSimulationSpace::BaseBoneSpace" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "BaseBone\xe5\xba\xa7\xe6\xa8\x99\xe7\xb3\xbb\xe6\x99\x82\xe3\x81\xae\xe5\x9f\xba\xe6\xba\x96\xe3\x81\xa8\xe3\x81\xaa\xe3\x82\x8b\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\nBaseBone coordinate system reference bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetFramerate_MetaData[] = {
		{ "Category", "Physics Settings" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe3\x82\xbf\xe3\x83\xbc\xe3\x82\xb2\xe3\x83\x83\xe3\x83\x88\xe3\x81\xa8\xe3\x81\xaa\xe3\x82\x8b\xe3\x83\x95\xe3\x83\xac\xe3\x83\xbc\xe3\x83\xa0\xe3\x83\xac\xe3\x83\xbc\xe3\x83\x88\n\x09* Target Frame Rate\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xbf\xe3\x83\xbc\xe3\x82\xb2\xe3\x83\x83\xe3\x83\x88\xe3\x81\xa8\xe3\x81\xaa\xe3\x82\x8b\xe3\x83\x95\xe3\x83\xac\xe3\x83\xbc\xe3\x83\xa0\xe3\x83\xac\xe3\x83\xbc\xe3\x83\x88\nTarget Frame Rate" },
#endif
		{ "UIMin", "1" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarmUpFrames_MetaData[] = {
		{ "Category", "Physics Settings" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe7\x89\xa9\xe7\x90\x86\xe3\x81\xae\xe7\xa9\xba\xe5\x9b\x9e\xe3\x81\x97\xe5\x9b\x9e\xe6\x95\xb0\xe3\x80\x82\xe7\x89\xa9\xe7\x90\x86\xe5\x87\xa6\xe7\x90\x86\xe3\x81\x8c\xe8\x90\xbd\xe3\x81\xa1\xe7\x9d\x80\xe3\x81\x84\xe3\x81\xa6\xe3\x81\x8b\xe3\x82\x89\xe9\x96\x8b\xe5\xa7\x8b\xe3\x83\xbb\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x97\xe3\x81\x9f\xe3\x81\x84\xe9\x9a\x9b\xe3\x81\xab\xe4\xbd\xbf\xe7\x94\xa8\n\x09* Number of times physics has been idle. Used when you want to start/display after physics processing has settled down\n\x09*/" },
#endif
		{ "EditCondition", "bNeedWarmUp" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x89\xa9\xe7\x90\x86\xe3\x81\xae\xe7\xa9\xba\xe5\x9b\x9e\xe3\x81\x97\xe5\x9b\x9e\xe6\x95\xb0\xe3\x80\x82\xe7\x89\xa9\xe7\x90\x86\xe5\x87\xa6\xe7\x90\x86\xe3\x81\x8c\xe8\x90\xbd\xe3\x81\xa1\xe7\x9d\x80\xe3\x81\x84\xe3\x81\xa6\xe3\x81\x8b\xe3\x82\x89\xe9\x96\x8b\xe5\xa7\x8b\xe3\x83\xbb\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x97\xe3\x81\x9f\xe3\x81\x84\xe9\x9a\x9b\xe3\x81\xab\xe4\xbd\xbf\xe7\x94\xa8\nNumber of times physics has been idle. Used when you want to start/display after physics processing has settled down" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseWarmUpWhenResetDynamics_MetaData[] = {
		{ "Category", "Physics Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* ResetDynamics\xe6\x99\x82\xe3\x81\xab\xe7\x89\xa9\xe7\x90\x86\xe3\x81\xae\xe7\xa9\xba\xe5\x9b\x9e\xe3\x81\x97\xe3\x82\x92\xe8\xa1\x8c\xe3\x81\x86\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\n\x09* Flags to use warmup physics when ResetDynamics\n\x09*/" },
#endif
		{ "EditCondition", "bNeedWarmUp" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "ResetDynamics\xe6\x99\x82\xe3\x81\xab\xe7\x89\xa9\xe7\x90\x86\xe3\x81\xae\xe7\xa9\xba\xe5\x9b\x9e\xe3\x81\x97\xe3\x82\x92\xe8\xa1\x8c\xe3\x81\x86\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\nFlags to use warmup physics when ResetDynamics" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bNeedWarmUp_MetaData[] = {
		{ "Category", "Physics Settings" },
		{ "InlineEditConditionToggle", "" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TeleportDistanceThreshold_MetaData[] = {
		{ "Category", "Physics Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* 1\xe3\x83\x95\xe3\x83\xac\xe3\x83\xbc\xe3\x83\xa0\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8bSkeletalMeshComponent\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe9\x87\x8f\xe3\x81\x8c\xe8\xa8\xad\xe5\xae\x9a\xe5\x80\xa4\xe3\x82\x92\xe8\xb6\x85\xe3\x81\x88\xe3\x81\x9f\xe5\xa0\xb4\xe5\x90\x88\xe3\x80\x81\xe3\x81\x9d\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe9\x87\x8f\xe3\x82\x92\xe7\x89\xa9\xe7\x90\x86\xe5\x88\xb6\xe5\xbe\xa1\xe3\x81\xab\xe5\x8f\x8d\xe6\x98\xa0\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\n\x09* If the amount of movement of a SkeletalMeshComponent in one frame exceeds the set value, that amount of movement will not be reflected in the physics control.\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "1\xe3\x83\x95\xe3\x83\xac\xe3\x83\xbc\xe3\x83\xa0\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8bSkeletalMeshComponent\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe9\x87\x8f\xe3\x81\x8c\xe8\xa8\xad\xe5\xae\x9a\xe5\x80\xa4\xe3\x82\x92\xe8\xb6\x85\xe3\x81\x88\xe3\x81\x9f\xe5\xa0\xb4\xe5\x90\x88\xe3\x80\x81\xe3\x81\x9d\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe9\x87\x8f\xe3\x82\x92\xe7\x89\xa9\xe7\x90\x86\xe5\x88\xb6\xe5\xbe\xa1\xe3\x81\xab\xe5\x8f\x8d\xe6\x98\xa0\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\nIf the amount of movement of a SkeletalMeshComponent in one frame exceeds the set value, that amount of movement will not be reflected in the physics control." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TeleportRotationThreshold_MetaData[] = {
		{ "Category", "Physics Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* 1\xe3\x83\x95\xe3\x83\xac\xe3\x83\xbc\xe3\x83\xa0\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8bSkeletalMeshComponent\xe3\x81\xae\xe5\x9b\x9e\xe8\xbb\xa2\xe9\x87\x8f\xe3\x81\x8c\xe8\xa8\xad\xe5\xae\x9a\xe5\x80\xa4\xe3\x82\x92\xe8\xb6\x85\xe3\x81\x88\xe3\x81\x9f\xe5\xa0\xb4\xe5\x90\x88\xe3\x80\x81\xe3\x81\x9d\xe3\x81\xae\xe5\x9b\x9e\xe8\xbb\xa2\xe9\x87\x8f\xe3\x82\x92\xe7\x89\xa9\xe7\x90\x86\xe5\x88\xb6\xe5\xbe\xa1\xe3\x81\xab\xe5\x8f\x8d\xe6\x98\xa0\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\n\x09* If the rotation amount of SkeletalMeshComponent in one frame exceeds the set value, the rotation amount will not be reflected in the physics control.\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "1\xe3\x83\x95\xe3\x83\xac\xe3\x83\xbc\xe3\x83\xa0\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8bSkeletalMeshComponent\xe3\x81\xae\xe5\x9b\x9e\xe8\xbb\xa2\xe9\x87\x8f\xe3\x81\x8c\xe8\xa8\xad\xe5\xae\x9a\xe5\x80\xa4\xe3\x82\x92\xe8\xb6\x85\xe3\x81\x88\xe3\x81\x9f\xe5\xa0\xb4\xe5\x90\x88\xe3\x80\x81\xe3\x81\x9d\xe3\x81\xae\xe5\x9b\x9e\xe8\xbb\xa2\xe9\x87\x8f\xe3\x82\x92\xe7\x89\xa9\xe7\x90\x86\xe5\x88\xb6\xe5\xbe\xa1\xe3\x81\xab\xe5\x8f\x8d\xe6\x98\xa0\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\nIf the rotation amount of SkeletalMeshComponent in one frame exceeds the set value, the rotation amount will not be reflected in the physics control." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlanarConstraint_MetaData[] = {
		{ "Category", "Physics Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe6\x8c\x87\xe5\xae\x9a\xe3\x81\x97\xe3\x81\x9f\xe8\xbb\xb8\xe3\x81\xab\xe5\xbf\x9c\xe3\x81\x98\xe3\x81\x9f\xe5\xb9\xb3\xe9\x9d\xa2\xe4\xb8\x8a\xe3\x81\xab\xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe5\x9b\xba\xe5\xae\x9a\n\x09* Fix the bone on the specified plane \n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x8c\x87\xe5\xae\x9a\xe3\x81\x97\xe3\x81\x9f\xe8\xbb\xb8\xe3\x81\xab\xe5\xbf\x9c\xe3\x81\x98\xe3\x81\x9f\xe5\xb9\xb3\xe9\x9d\xa2\xe4\xb8\x8a\xe3\x81\xab\xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe5\x9b\xba\xe5\xae\x9a\nFix the bone on the specified plane" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkelCompMoveScale_MetaData[] = {
		{ "Category", "Physics Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* SkeletalMeshComponent\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe9\x87\x8f\xe3\x82\x92\xe7\x89\xa9\xe7\x90\x86\xe6\x8c\x99\xe5\x8b\x95\xe3\x81\xab\xe5\x8f\x8d\xe6\x98\xa0\xe3\x81\x99\xe3\x82\x8b\xe9\x9a\x9b\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b\xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xbc\xe3\x83\xab\xe3\x80\x82\n\x09* Scale to apply when reflecting the movement of the SkeletalMeshComponent in physical behavior.\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "SkeletalMeshComponent\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe9\x87\x8f\xe3\x82\x92\xe7\x89\xa9\xe7\x90\x86\xe6\x8c\x99\xe5\x8b\x95\xe3\x81\xab\xe5\x8f\x8d\xe6\x98\xa0\xe3\x81\x99\xe3\x82\x8b\xe9\x9a\x9b\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b\xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xbc\xe3\x83\xab\xe3\x80\x82\nScale to apply when reflecting the movement of the SkeletalMeshComponent in physical behavior." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUpdatePhysicsSettingsInGame_MetaData[] = {
		{ "Category", "Physics Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n \x09* \xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe7\x89\xa9\xe7\x90\x86\xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe6\xaf\x8e\xe3\x83\x95\xe3\x83\xac\xe3\x83\xbc\xe3\x83\xa0\xe6\x9b\xb4\xe6\x96\xb0\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\xe3\x80\x82\n \x09* \xe7\x84\xa1\xe5\x8a\xb9\xe3\x81\xab\xe3\x81\x99\xe3\x82\x8b\xe3\x81\xa8\xe3\x83\x91\xe3\x83\x95\xe3\x82\xa9\xe3\x83\xbc\xe3\x83\x9e\xe3\x83\xb3\xe3\x82\xb9\xe3\x81\x8c\xe5\x83\x85\xe3\x81\x8b\xe3\x81\xab\xe6\x94\xb9\xe5\x96\x84\xe3\x81\x99\xe3\x82\x8b\xe3\x81\x8c\xe3\x80\x81\xe5\xae\x9f\xe8\xa1\x8c\xe4\xb8\xad\xe3\x81\xab\xe7\x89\xa9\xe7\x90\x86\xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe5\xa4\x89\xe6\x9b\xb4\xe3\x81\x99\xe3\x82\x8b\xe3\x81\x93\xe3\x81\xa8\xe3\x81\x8c\xe4\xb8\x8d\xe5\x8f\xaf\xe8\x83\xbd\xe3\x81\xab\n\x09* Flag to update the physics parameters of each bone every frame.\n\x09* Disabling this will slightly improve performance, but it will make it impossible to change physics parameters during execution.\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe7\x89\xa9\xe7\x90\x86\xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe6\xaf\x8e\xe3\x83\x95\xe3\x83\xac\xe3\x83\xbc\xe3\x83\xa0\xe6\x9b\xb4\xe6\x96\xb0\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\xe3\x80\x82\n\xe7\x84\xa1\xe5\x8a\xb9\xe3\x81\xab\xe3\x81\x99\xe3\x82\x8b\xe3\x81\xa8\xe3\x83\x91\xe3\x83\x95\xe3\x82\xa9\xe3\x83\xbc\xe3\x83\x9e\xe3\x83\xb3\xe3\x82\xb9\xe3\x81\x8c\xe5\x83\x85\xe3\x81\x8b\xe3\x81\xab\xe6\x94\xb9\xe5\x96\x84\xe3\x81\x99\xe3\x82\x8b\xe3\x81\x8c\xe3\x80\x81\xe5\xae\x9f\xe8\xa1\x8c\xe4\xb8\xad\xe3\x81\xab\xe7\x89\xa9\xe7\x90\x86\xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe5\xa4\x89\xe6\x9b\xb4\xe3\x81\x99\xe3\x82\x8b\xe3\x81\x93\xe3\x81\xa8\xe3\x81\x8c\xe4\xb8\x8d\xe5\x8f\xaf\xe8\x83\xbd\xe3\x81\xab\nFlag to update the physics parameters of each bone every frame.\nDisabling this will slightly improve performance, but it will make it impossible to change physics parameters during execution." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResetBoneTransformWhenBoneNotFound_MetaData[] = {
		{ "Category", "Physics Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe5\x88\xb6\xe5\xbe\xa1\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\x8c\xe8\xa6\x8b\xe3\x81\xa4\xe3\x81\x8b\xe3\x82\x89\xe3\x81\xaa\xe3\x81\x84\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xabTransform\xe3\x82\x92\xe3\x83\xaa\xe3\x82\xbb\xe3\x83\x83\xe3\x83\x88\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\xe3\x80\x82\xe5\x9f\xba\xe6\x9c\xac\xe7\x9a\x84\xe3\x81\xab\xe3\x81\xaf\xe7\x84\xa1\xe5\x8a\xb9\xe3\x82\x92\xe6\x8e\xa8\xe5\xa5\xa8\n\x09* Flag to reset Transform when the controlled bone is not found. It is generally recommended to disable this.\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x88\xb6\xe5\xbe\xa1\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\x8c\xe8\xa6\x8b\xe3\x81\xa4\xe3\x81\x8b\xe3\x82\x89\xe3\x81\xaa\xe3\x81\x84\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xabTransform\xe3\x82\x92\xe3\x83\xaa\xe3\x82\xbb\xe3\x83\x83\xe3\x83\x88\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\xe3\x80\x82\xe5\x9f\xba\xe6\x9c\xac\xe7\x9a\x84\xe3\x81\xab\xe3\x81\xaf\xe7\x84\xa1\xe5\x8a\xb9\xe3\x82\x92\xe6\x8e\xa8\xe5\xa5\xa8\nFlag to reset Transform when the controlled bone is not found. It is generally recommended to disable this." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DampingCurveData_MetaData[] = {
		{ "Category", "Physics Settings|Curves" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8bPhysics Settings/ Damping \xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe8\xa3\x9c\xe6\xad\xa3\xe3\x80\x82\n\x09* \xe3\x80\x8cRootBone\xe3\x81\x8b\xe3\x82\x89\xe7\x89\xb9\xe5\xae\x9a\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95 / RootBone\xe3\x81\x8b\xe3\x82\x89\xe6\x9c\xab\xe7\xab\xaf\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95\xe3\x80\x8d(0.0~1.0)\xe3\x81\xae\xe5\x80\xa4\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x96\xe3\x81\xae\xe5\x80\xa4\xe3\x82\x92\xe5\x90\x84\xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x81\xab\xe4\xb9\x97\xe7\xae\x97\n\x09* Corrects the Physics Settings/Damping parameters applied to each bone.\n\x09* Multiplies each parameter by the curve value for \"Length from RootBone to specific bone / Length from RootBone to end bone\" (0.0~1.0).\n\x09*/" },
#endif
		{ "DisplayName", "Damping Rate by Bone Length Rate" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8bPhysics Settings/ Damping \xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe8\xa3\x9c\xe6\xad\xa3\xe3\x80\x82\n\xe3\x80\x8cRootBone\xe3\x81\x8b\xe3\x82\x89\xe7\x89\xb9\xe5\xae\x9a\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95 / RootBone\xe3\x81\x8b\xe3\x82\x89\xe6\x9c\xab\xe7\xab\xaf\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95\xe3\x80\x8d(0.0~1.0)\xe3\x81\xae\xe5\x80\xa4\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x96\xe3\x81\xae\xe5\x80\xa4\xe3\x82\x92\xe5\x90\x84\xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x81\xab\xe4\xb9\x97\xe7\xae\x97\nCorrects the Physics Settings/Damping parameters applied to each bone.\nMultiplies each parameter by the curve value for \"Length from RootBone to specific bone / Length from RootBone to end bone\" (0.0~1.0)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StiffnessCurveData_MetaData[] = {
		{ "Category", "Physics Settings|Curves" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8bPhysics Settings/ Stiffness \xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe8\xa3\x9c\xe6\xad\xa3\xe3\x80\x82\n\x09* \xe3\x80\x8cRootBone\xe3\x81\x8b\xe3\x82\x89\xe7\x89\xb9\xe5\xae\x9a\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95 / RootBone\xe3\x81\x8b\xe3\x82\x89\xe6\x9c\xab\xe7\xab\xaf\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95\xe3\x80\x8d(0.0~1.0)\xe3\x81\xae\xe5\x80\xa4\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x96\xe3\x81\xae\xe5\x80\xa4\xe3\x82\x92\xe5\x90\x84\xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x81\xab\xe4\xb9\x97\xe7\xae\x97\n\x09* Corrects the Physics Settings/Stiffness parameters applied to each bone.\n\x09* Multiplies each parameter by the curve value for \"Length from RootBone to specific bone / Length from RootBone to end bone\" (0.0~1.0).\n\x09*/" },
#endif
		{ "DisplayName", "Stiffness Rate by Bone Length Rate" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8bPhysics Settings/ Stiffness \xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe8\xa3\x9c\xe6\xad\xa3\xe3\x80\x82\n\xe3\x80\x8cRootBone\xe3\x81\x8b\xe3\x82\x89\xe7\x89\xb9\xe5\xae\x9a\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95 / RootBone\xe3\x81\x8b\xe3\x82\x89\xe6\x9c\xab\xe7\xab\xaf\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95\xe3\x80\x8d(0.0~1.0)\xe3\x81\xae\xe5\x80\xa4\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x96\xe3\x81\xae\xe5\x80\xa4\xe3\x82\x92\xe5\x90\x84\xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x81\xab\xe4\xb9\x97\xe7\xae\x97\nCorrects the Physics Settings/Stiffness parameters applied to each bone.\nMultiplies each parameter by the curve value for \"Length from RootBone to specific bone / Length from RootBone to end bone\" (0.0~1.0)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldDampingLocationCurveData_MetaData[] = {
		{ "Category", "Physics Settings|Curves" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8bPhysics Settings/ WorldDampingLocation \xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe8\xa3\x9c\xe6\xad\xa3\xe3\x80\x82\n\x09* \xe3\x80\x8cRootBone\xe3\x81\x8b\xe3\x82\x89\xe7\x89\xb9\xe5\xae\x9a\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95 / RootBone\xe3\x81\x8b\xe3\x82\x89\xe6\x9c\xab\xe7\xab\xaf\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95\xe3\x80\x8d(0.0~1.0)\xe3\x81\xae\xe5\x80\xa4\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x96\xe3\x81\xae\xe5\x80\xa4\xe3\x82\x92\xe5\x90\x84\xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x81\xab\xe4\xb9\x97\xe7\xae\x97\n\x09* Corrects the Physics Settings/WorldDampingLocation parameters applied to each bone.\n\x09* Multiplies each parameter by the curve value for \"Length from RootBone to specific bone / Length from RootBone to end bone\" (0.0~1.0).\n\x09* \xe2\x80\xbb\xe5\x9f\xba\xe3\x81\xa8\xe3\x81\xaa\xe3\x82\x8b\xe5\x80\xa4\xe3\x81\xae\xe6\x84\x8f\xe5\x91\xb3\xe3\x81\xaf WorldDampingLocation \xe3\x82\x92\xe5\x8f\x82\xe7\x85\xa7\xef\xbc\x88\xe5\xa4\xa7\xe3\x81\x8d\xe3\x81\x84\xe3\x81\xbb\xe3\x81\xa9\xe7\xa7\xbb\xe5\x8b\x95\xe9\x87\x8f\xe3\x82\x92\xe6\x8a\x91\xe5\x88\xb6 = \xe5\x8f\x8d\xe6\x98\xa0\xe7\x8e\x87\xe3\x81\xaf 1 - \xe5\x80\xa4\xef\xbc\x89\n\x09* Note: see WorldDampingLocation for the base value's meaning (higher = more suppression; reflection factor = 1 - value).\n\x09*/" },
#endif
		{ "DisplayName", "World Damping Location Rate by Bone Length Rate" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8bPhysics Settings/ WorldDampingLocation \xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe8\xa3\x9c\xe6\xad\xa3\xe3\x80\x82\n\xe3\x80\x8cRootBone\xe3\x81\x8b\xe3\x82\x89\xe7\x89\xb9\xe5\xae\x9a\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95 / RootBone\xe3\x81\x8b\xe3\x82\x89\xe6\x9c\xab\xe7\xab\xaf\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95\xe3\x80\x8d(0.0~1.0)\xe3\x81\xae\xe5\x80\xa4\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x96\xe3\x81\xae\xe5\x80\xa4\xe3\x82\x92\xe5\x90\x84\xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x81\xab\xe4\xb9\x97\xe7\xae\x97\nCorrects the Physics Settings/WorldDampingLocation parameters applied to each bone.\nMultiplies each parameter by the curve value for \"Length from RootBone to specific bone / Length from RootBone to end bone\" (0.0~1.0).\n\xe2\x80\xbb\xe5\x9f\xba\xe3\x81\xa8\xe3\x81\xaa\xe3\x82\x8b\xe5\x80\xa4\xe3\x81\xae\xe6\x84\x8f\xe5\x91\xb3\xe3\x81\xaf WorldDampingLocation \xe3\x82\x92\xe5\x8f\x82\xe7\x85\xa7\xef\xbc\x88\xe5\xa4\xa7\xe3\x81\x8d\xe3\x81\x84\xe3\x81\xbb\xe3\x81\xa9\xe7\xa7\xbb\xe5\x8b\x95\xe9\x87\x8f\xe3\x82\x92\xe6\x8a\x91\xe5\x88\xb6 = \xe5\x8f\x8d\xe6\x98\xa0\xe7\x8e\x87\xe3\x81\xaf 1 - \xe5\x80\xa4\xef\xbc\x89\nNote: see WorldDampingLocation for the base value's meaning (higher = more suppression; reflection factor = 1 - value)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldDampingRotationCurveData_MetaData[] = {
		{ "Category", "Physics Settings|Curves" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8bPhysics Settings/ WorldDampingRotation \xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe8\xa3\x9c\xe6\xad\xa3\xe3\x80\x82\n\x09* \xe3\x80\x8cRootBone\xe3\x81\x8b\xe3\x82\x89\xe7\x89\xb9\xe5\xae\x9a\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95 / RootBone\xe3\x81\x8b\xe3\x82\x89\xe6\x9c\xab\xe7\xab\xaf\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95\xe3\x80\x8d(0.0~1.0)\xe3\x81\xae\xe5\x80\xa4\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x96\xe3\x81\xae\xe5\x80\xa4\xe3\x82\x92\xe5\x90\x84\xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x81\xab\xe4\xb9\x97\xe7\xae\x97\n\x09* Corrects the Physics Settings/WorldDampingRotation parameters applied to each bone.\n\x09* Multiplies each parameter by the curve value for \"Length from RootBone to specific bone / Length from RootBone to end bone\" (0.0~1.0).\n\x09* \xe2\x80\xbb\xe5\x9f\xba\xe3\x81\xa8\xe3\x81\xaa\xe3\x82\x8b\xe5\x80\xa4\xe3\x81\xae\xe6\x84\x8f\xe5\x91\xb3\xe3\x81\xaf WorldDampingRotation \xe3\x82\x92\xe5\x8f\x82\xe7\x85\xa7\xef\xbc\x88\xe5\xa4\xa7\xe3\x81\x8d\xe3\x81\x84\xe3\x81\xbb\xe3\x81\xa9\xe5\x9b\x9e\xe8\xbb\xa2\xe9\x87\x8f\xe3\x82\x92\xe6\x8a\x91\xe5\x88\xb6 = \xe5\x8f\x8d\xe6\x98\xa0\xe7\x8e\x87\xe3\x81\xaf 1 - \xe5\x80\xa4\xef\xbc\x89\n\x09* Note: see WorldDampingRotation for the base value's meaning (higher = more suppression; reflection factor = 1 - value).\n\x09*/" },
#endif
		{ "DisplayName", "World Damping Rotation Rate by Bone Length Rate" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8bPhysics Settings/ WorldDampingRotation \xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe8\xa3\x9c\xe6\xad\xa3\xe3\x80\x82\n\xe3\x80\x8cRootBone\xe3\x81\x8b\xe3\x82\x89\xe7\x89\xb9\xe5\xae\x9a\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95 / RootBone\xe3\x81\x8b\xe3\x82\x89\xe6\x9c\xab\xe7\xab\xaf\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95\xe3\x80\x8d(0.0~1.0)\xe3\x81\xae\xe5\x80\xa4\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x96\xe3\x81\xae\xe5\x80\xa4\xe3\x82\x92\xe5\x90\x84\xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x81\xab\xe4\xb9\x97\xe7\xae\x97\nCorrects the Physics Settings/WorldDampingRotation parameters applied to each bone.\nMultiplies each parameter by the curve value for \"Length from RootBone to specific bone / Length from RootBone to end bone\" (0.0~1.0).\n\xe2\x80\xbb\xe5\x9f\xba\xe3\x81\xa8\xe3\x81\xaa\xe3\x82\x8b\xe5\x80\xa4\xe3\x81\xae\xe6\x84\x8f\xe5\x91\xb3\xe3\x81\xaf WorldDampingRotation \xe3\x82\x92\xe5\x8f\x82\xe7\x85\xa7\xef\xbc\x88\xe5\xa4\xa7\xe3\x81\x8d\xe3\x81\x84\xe3\x81\xbb\xe3\x81\xa9\xe5\x9b\x9e\xe8\xbb\xa2\xe9\x87\x8f\xe3\x82\x92\xe6\x8a\x91\xe5\x88\xb6 = \xe5\x8f\x8d\xe6\x98\xa0\xe7\x8e\x87\xe3\x81\xaf 1 - \xe5\x80\xa4\xef\xbc\x89\nNote: see WorldDampingRotation for the base value's meaning (higher = more suppression; reflection factor = 1 - value)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RadiusCurveData_MetaData[] = {
		{ "Category", "Physics Settings|Curves" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8bPhysics Settings/ CollisionRadius \xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe8\xa3\x9c\xe6\xad\xa3\xe3\x80\x82\n\x09* \xe3\x80\x8cRootBone\xe3\x81\x8b\xe3\x82\x89\xe7\x89\xb9\xe5\xae\x9a\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95 / RootBone\xe3\x81\x8b\xe3\x82\x89\xe6\x9c\xab\xe7\xab\xaf\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95\xe3\x80\x8d(0.0~1.0)\xe3\x81\xae\xe5\x80\xa4\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x96\xe3\x81\xae\xe5\x80\xa4\xe3\x82\x92\xe5\x90\x84\xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x81\xab\xe4\xb9\x97\xe7\xae\x97\n\x09* Corrects the Physics Settings/CollisionRadius parameters applied to each bone.\n\x09* Multiplies each parameter by the curve value for \"Length from RootBone to specific bone / Length from RootBone to end bone\" (0.0~1.0).\n\x09*/" },
#endif
		{ "DisplayName", "Radius Rate by Bone Length Rate" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8bPhysics Settings/ CollisionRadius \xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe8\xa3\x9c\xe6\xad\xa3\xe3\x80\x82\n\xe3\x80\x8cRootBone\xe3\x81\x8b\xe3\x82\x89\xe7\x89\xb9\xe5\xae\x9a\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95 / RootBone\xe3\x81\x8b\xe3\x82\x89\xe6\x9c\xab\xe7\xab\xaf\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95\xe3\x80\x8d(0.0~1.0)\xe3\x81\xae\xe5\x80\xa4\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x96\xe3\x81\xae\xe5\x80\xa4\xe3\x82\x92\xe5\x90\x84\xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x81\xab\xe4\xb9\x97\xe7\xae\x97\nCorrects the Physics Settings/CollisionRadius parameters applied to each bone.\nMultiplies each parameter by the curve value for \"Length from RootBone to specific bone / Length from RootBone to end bone\" (0.0~1.0)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LimitAngleCurveData_MetaData[] = {
		{ "Category", "Physics Settings|Curves" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8bPhysics Settings/ LimitAngle \xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe8\xa3\x9c\xe6\xad\xa3\xe3\x80\x82\n\x09* \xe3\x80\x8cRootBone\xe3\x81\x8b\xe3\x82\x89\xe7\x89\xb9\xe5\xae\x9a\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95 / RootBone\xe3\x81\x8b\xe3\x82\x89\xe6\x9c\xab\xe7\xab\xaf\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95\xe3\x80\x8d(0.0~1.0)\xe3\x81\xae\xe5\x80\xa4\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x96\xe3\x81\xae\xe5\x80\xa4\xe3\x82\x92\xe5\x90\x84\xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x81\xab\xe4\xb9\x97\xe7\xae\x97\n\x09* Corrects the Physics Settings/LimitAngle parameters applied to each bone.\n\x09* Multiplies each parameter by the curve value for \"Length from RootBone to specific bone / Length from RootBone to end bone\" (0.0~1.0).\n\x09*/" },
#endif
		{ "DisplayName", "LimitAngle Rate by Bone Length Rate" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8bPhysics Settings/ LimitAngle \xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe8\xa3\x9c\xe6\xad\xa3\xe3\x80\x82\n\xe3\x80\x8cRootBone\xe3\x81\x8b\xe3\x82\x89\xe7\x89\xb9\xe5\xae\x9a\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95 / RootBone\xe3\x81\x8b\xe3\x82\x89\xe6\x9c\xab\xe7\xab\xaf\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xbe\xe3\x81\xa7\xe3\x81\xae\xe9\x95\xb7\xe3\x81\x95\xe3\x80\x8d(0.0~1.0)\xe3\x81\xae\xe5\x80\xa4\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x96\xe3\x81\xae\xe5\x80\xa4\xe3\x82\x92\xe5\x90\x84\xe3\x83\x91\xe3\x83\xa9\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xbf\xe3\x81\xab\xe4\xb9\x97\xe7\xae\x97\nCorrects the Physics Settings/LimitAngle parameters applied to each bone.\nMultiplies each parameter by the curve value for \"Length from RootBone to specific bone / Length from RootBone to end bone\" (0.0~1.0)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SphericalLimits_MetaData[] = {
		{ "Category", "Limits" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xef\xbc\x88\xe7\x90\x83\xef\xbc\x89\n\x09* Spherical Collision\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xef\xbc\x88\xe7\x90\x83\xef\xbc\x89\nSpherical Collision" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CapsuleLimits_MetaData[] = {
		{ "Category", "Limits" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xef\xbc\x88\xe3\x82\xab\xe3\x83\x97\xe3\x82\xbb\xe3\x83\xab\xef\xbc\x89\n\x09* Capsule Collision\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xef\xbc\x88\xe3\x82\xab\xe3\x83\x97\xe3\x82\xbb\xe3\x83\xab\xef\xbc\x89\nCapsule Collision" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoxLimits_MetaData[] = {
		{ "Category", "Limits" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xef\xbc\x88\xe3\x83\x9c\xe3\x83\x83\xe3\x82\xaf\xe3\x82\xb9\xef\xbc\x89\n\x09* Box Collision\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xef\xbc\x88\xe3\x83\x9c\xe3\x83\x83\xe3\x82\xaf\xe3\x82\xb9\xef\xbc\x89\nBox Collision" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlanarLimits_MetaData[] = {
		{ "Category", "Limits" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xef\xbc\x88\xe5\xb9\xb3\xe9\x9d\xa2\xef\xbc\x89\n\x09* Planar Collision\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xef\xbc\x88\xe5\xb9\xb3\xe9\x9d\xa2\xef\xbc\x89\nPlanar Collision" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LimitsDataAsset_MetaData[] = {
		{ "Category", "Limits" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88""DataAsset\xe7\x89\x88\xef\xbc\x89\xe3\x80\x82\xe5\x88\xa5""AnimNode\xe3\x83\xbb""ABP\xe3\x81\xa7\xe8\xa8\xad\xe5\xae\x9a\xe3\x82\x92\xe6\xb5\x81\xe7\x94\xa8\xe3\x81\x97\xe3\x81\x9f\xe3\x81\x84\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe3\x81\x93\xe3\x81\xa1\xe3\x82\x89\xe3\x82\x92\xe6\x8e\xa8\xe5\xa5\xa8\n\x09* Collision settings (DataAsset version). This is recommended if you want to reuse the settings for another AnimNode or ABP.\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88""DataAsset\xe7\x89\x88\xef\xbc\x89\xe3\x80\x82\xe5\x88\xa5""AnimNode\xe3\x83\xbb""ABP\xe3\x81\xa7\xe8\xa8\xad\xe5\xae\x9a\xe3\x82\x92\xe6\xb5\x81\xe7\x94\xa8\xe3\x81\x97\xe3\x81\x9f\xe3\x81\x84\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe3\x81\x93\xe3\x81\xa1\xe3\x82\x89\xe3\x82\x92\xe6\x8e\xa8\xe5\xa5\xa8\nCollision settings (DataAsset version). This is recommended if you want to reuse the settings for another AnimNode or ABP." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PhysicsAssetForLimits_MetaData[] = {
		{ "Category", "Limits" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88PhysicsAsset\xe7\x89\x88\xef\xbc\x89\xe3\x80\x82\xe5\x88\xa5""AnimNode\xe3\x83\xbb""ABP\xe3\x81\xa7\xe8\xa8\xad\xe5\xae\x9a\xe3\x82\x92\xe6\xb5\x81\xe7\x94\xa8\xe3\x81\x97\xe3\x81\x9f\xe3\x81\x84\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe3\x81\x93\xe3\x81\xa1\xe3\x82\x89\xe3\x82\x92\xe6\x8e\xa8\xe5\xa5\xa8\n\x09* Collision settings (PhysicsAsset). This is recommended if you want to reuse the settings for another AnimNode or ABP.\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88PhysicsAsset\xe7\x89\x88\xef\xbc\x89\xe3\x80\x82\xe5\x88\xa5""AnimNode\xe3\x83\xbb""ABP\xe3\x81\xa7\xe8\xa8\xad\xe5\xae\x9a\xe3\x82\x92\xe6\xb5\x81\xe7\x94\xa8\xe3\x81\x97\xe3\x81\x9f\xe3\x81\x84\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe3\x81\x93\xe3\x81\xa1\xe3\x82\x89\xe3\x82\x92\xe6\x8e\xa8\xe5\xa5\xa8\nCollision settings (PhysicsAsset). This is recommended if you want to reuse the settings for another AnimNode or ABP." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SphericalLimitsData_MetaData[] = {
		{ "Category", "Limits" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88""DataAsset\xe7\x89\x88\xef\xbc\x89\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe7\x90\x83\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x81\xae\xe3\x83\x97\xe3\x83\xac\xe3\x83\x93\xe3\x83\xa5\xe3\x83\xbc\n\x09* Preview of sphere collision in collision settings (DataAsset version)\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88""DataAsset\xe7\x89\x88\xef\xbc\x89\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe7\x90\x83\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x81\xae\xe3\x83\x97\xe3\x83\xac\xe3\x83\x93\xe3\x83\xa5\xe3\x83\xbc\nPreview of sphere collision in collision settings (DataAsset version)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CapsuleLimitsData_MetaData[] = {
		{ "Category", "Limits" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88""DataAsset\xe7\x89\x88\xef\xbc\x89\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe3\x82\xab\xe3\x83\x97\xe3\x82\xbb\xe3\x83\xab\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x81\xae\xe3\x83\x97\xe3\x83\xac\xe3\x83\x93\xe3\x83\xa5\xe3\x83\xbc\n\x09* Preview of capsule collision in collision settings (DataAsset version)\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88""DataAsset\xe7\x89\x88\xef\xbc\x89\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe3\x82\xab\xe3\x83\x97\xe3\x82\xbb\xe3\x83\xab\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x81\xae\xe3\x83\x97\xe3\x83\xac\xe3\x83\x93\xe3\x83\xa5\xe3\x83\xbc\nPreview of capsule collision in collision settings (DataAsset version)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoxLimitsData_MetaData[] = {
		{ "Category", "Limits" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88""DataAsset\xe7\x89\x88\xef\xbc\x89\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe3\x83\x9c\xe3\x83\x83\xe3\x82\xaf\xe3\x82\xb9\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x81\xae\xe3\x83\x97\xe3\x83\xac\xe3\x83\x93\xe3\x83\xa5\xe3\x83\xbc\n\x09* Preview of box collision in collision settings (DataAsset version)\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88""DataAsset\xe7\x89\x88\xef\xbc\x89\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe3\x83\x9c\xe3\x83\x83\xe3\x82\xaf\xe3\x82\xb9\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x81\xae\xe3\x83\x97\xe3\x83\xac\xe3\x83\x93\xe3\x83\xa5\xe3\x83\xbc\nPreview of box collision in collision settings (DataAsset version)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlanarLimitsData_MetaData[] = {
		{ "Category", "Limits" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88""DataAsset\xe7\x89\x88\xef\xbc\x89\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe5\xb9\xb3\xe9\x9d\xa2\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x81\xae\xe3\x83\x97\xe3\x83\xac\xe3\x83\x93\xe3\x83\xa5\xe3\x83\xbc\n\x09* Preview of planar collision in collision settings (DataAsset version)\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88""DataAsset\xe7\x89\x88\xef\xbc\x89\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b\xe5\xb9\xb3\xe9\x9d\xa2\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x81\xae\xe3\x83\x97\xe3\x83\xac\xe3\x83\x93\xe3\x83\xa5\xe3\x83\xbc\nPreview of planar collision in collision settings (DataAsset version)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSharedCollisionSource_MetaData[] = {
		{ "Category", "Limits|Shared Collision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x82\x92\xe5\x90\x8c\xe3\x81\x98""Actor/ChildActor\xe3\x83\x95\xe3\x82\xa1\xe3\x83\x9f\xe3\x83\xaa\xe3\x83\xbc\xe5\x86\x85\xe3\x81\xaeKawaiiPhysics\xe3\x81\xab\xe5\x85\xb1\xe6\x9c\x89\xe3\x81\x99\xe3\x82\x8b\n\x09 * Provide this node's collision limits to KawaiiPhysics nodes in the same attached actor family\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x82\x92\xe5\x90\x8c\xe3\x81\x98""Actor/ChildActor\xe3\x83\x95\xe3\x82\xa1\xe3\x83\x9f\xe3\x83\xaa\xe3\x83\xbc\xe5\x86\x85\xe3\x81\xaeKawaiiPhysics\xe3\x81\xab\xe5\x85\xb1\xe6\x9c\x89\xe3\x81\x99\xe3\x82\x8b\nProvide this node's collision limits to KawaiiPhysics nodes in the same attached actor family" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseSharedCollision_MetaData[] = {
		{ "Category", "Limits|Shared Collision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\x90\x8c\xe3\x81\x98""Actor/ChildActor\xe3\x83\x95\xe3\x82\xa1\xe3\x83\x9f\xe3\x83\xaa\xe3\x83\xbc\xe5\x86\x85\xe3\x81\xaeKawaiiPhysics\xe3\x81\x8b\xe3\x82\x89\xe5\x85\xb1\xe6\x9c\x89\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x82\x92\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\n\x09 * \xe5\x90\x8c\xe3\x81\x98""AnimGraph\xe5\x86\x85\xe3\x81\xa7\xe5\x90\x8c\xe4\xb8\x80\xe3\x83\x95\xe3\x83\xac\xe3\x83\xbc\xe3\x83\xa0\xe3\x81\xae\xe7\xb5\x90\xe6\x9e\x9c\xe3\x82\x92\xe4\xbd\xbf\xe3\x81\x86\xe3\x81\xab\xe3\x81\xaf\xe3\x80\x81Source\xe3\x83\x8e\xe3\x83\xbc\xe3\x83\x89\xe3\x82\x92Target\xe3\x83\x8e\xe3\x83\xbc\xe3\x83\x89\xe3\x82\x88\xe3\x82\x8a\xe5\x85\x88\xe3\x81\xab\xe8\xa9\x95\xe4\xbe\xa1\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b\xe4\xbd\x8d\xe7\xbd\xae\xe3\x81\xb8\xe9\x85\x8d\xe7\xbd\xae\xe3\x81\x97\xe3\x81\xa6\xe3\x81\x8f\xe3\x81\xa0\xe3\x81\x95\xe3\x81\x84\xe3\x80\x82\n\x09 * Use shared collision limits from source KawaiiPhysics nodes in the same attached actor family.\n\x09 * To use same-frame data in one AnimGraph, place the source node so it evaluates before the target node.\n\x09 */" },
#endif
		{ "EditCondition", "!bSharedCollisionSource" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x90\x8c\xe3\x81\x98""Actor/ChildActor\xe3\x83\x95\xe3\x82\xa1\xe3\x83\x9f\xe3\x83\xaa\xe3\x83\xbc\xe5\x86\x85\xe3\x81\xaeKawaiiPhysics\xe3\x81\x8b\xe3\x82\x89\xe5\x85\xb1\xe6\x9c\x89\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x82\x92\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\n\xe5\x90\x8c\xe3\x81\x98""AnimGraph\xe5\x86\x85\xe3\x81\xa7\xe5\x90\x8c\xe4\xb8\x80\xe3\x83\x95\xe3\x83\xac\xe3\x83\xbc\xe3\x83\xa0\xe3\x81\xae\xe7\xb5\x90\xe6\x9e\x9c\xe3\x82\x92\xe4\xbd\xbf\xe3\x81\x86\xe3\x81\xab\xe3\x81\xaf\xe3\x80\x81Source\xe3\x83\x8e\xe3\x83\xbc\xe3\x83\x89\xe3\x82\x92Target\xe3\x83\x8e\xe3\x83\xbc\xe3\x83\x89\xe3\x82\x88\xe3\x82\x8a\xe5\x85\x88\xe3\x81\xab\xe8\xa9\x95\xe4\xbe\xa1\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b\xe4\xbd\x8d\xe7\xbd\xae\xe3\x81\xb8\xe9\x85\x8d\xe7\xbd\xae\xe3\x81\x97\xe3\x81\xa6\xe3\x81\x8f\xe3\x81\xa0\xe3\x81\x95\xe3\x81\x84\xe3\x80\x82\nUse shared collision limits from source KawaiiPhysics nodes in the same attached actor family.\nTo use same-frame data in one AnimGraph, place the source node so it evaluates before the target node." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SharedCollisionGroupTag_MetaData[] = {
		{ "Category", "Limits|Shared Collision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe5\x85\xb1\xe6\x9c\x89\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x81\xae\xe3\x82\xb0\xe3\x83\xab\xe3\x83\xbc\xe3\x83\x97\xe3\x82\xbf\xe3\x82\xb0\xef\xbc\x88\xe5\x90\x8c\xe3\x81\x98""Actor/ChildActor\xe3\x83\x95\xe3\x82\xa1\xe3\x83\x9f\xe3\x83\xaa\xe3\x83\xbc\xe5\x86\x85\xe3\x81\xaeSource/Target\xe4\xb8\xa1\xe6\x96\xb9\xe3\x81\xa7\xe4\xbd\xbf\xe7\x94\xa8\xef\xbc\x89\n\x09 * Group tag for shared collision (used by both source and target in the same attached actor family)\n\x09 */" },
#endif
		{ "EditCondition", "bSharedCollisionSource || bUseSharedCollision" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x85\xb1\xe6\x9c\x89\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x81\xae\xe3\x82\xb0\xe3\x83\xab\xe3\x83\xbc\xe3\x83\x97\xe3\x82\xbf\xe3\x82\xb0\xef\xbc\x88\xe5\x90\x8c\xe3\x81\x98""Actor/ChildActor\xe3\x83\x95\xe3\x82\xa1\xe3\x83\x9f\xe3\x83\xaa\xe3\x83\xbc\xe5\x86\x85\xe3\x81\xaeSource/Target\xe4\xb8\xa1\xe6\x96\xb9\xe3\x81\xa7\xe4\xbd\xbf\xe7\x94\xa8\xef\xbc\x89\nGroup tag for shared collision (used by both source and target in the same attached actor family)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoneConstraintGlobalComplianceType_MetaData[] = {
		{ "Category", "Limits|Bone Constraint" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* Bone Constraint\xe3\x81\xa7\xe7\x94\xa8\xe3\x81\x84\xe3\x82\x8b\xe5\x89\x9b\xe6\x80\xa7\xe3\x82\xbf\xe3\x82\xa4\xe3\x83\x97\n\x09* Stiffness type to use in Bone Constraint\n\x09* http://blog.mmacklin.com/2016/10/12/xpbd-slides-and-stiffness/\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Bone Constraint\xe3\x81\xa7\xe7\x94\xa8\xe3\x81\x84\xe3\x82\x8b\xe5\x89\x9b\xe6\x80\xa7\xe3\x82\xbf\xe3\x82\xa4\xe3\x83\x97\nStiffness type to use in Bone Constraint\nhttp://blog.mmacklin.com/2016/10/12/xpbd-slides-and-stiffness/" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoneConstraintIterationCountBeforeCollision_MetaData[] = {
		{ "Category", "Limits|Bone Constraint" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* Bone Constraint\xe3\x81\xae\xe5\x87\xa6\xe7\x90\x86\xe5\x9b\x9e\xe6\x95\xb0\xef\xbc\x88\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe5\x87\xa6\xe7\x90\x86\xe5\x89\x8d\xef\xbc\x89\n\x09* Number of Bone Constraints processed before collision processing\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Bone Constraint\xe3\x81\xae\xe5\x87\xa6\xe7\x90\x86\xe5\x9b\x9e\xe6\x95\xb0\xef\xbc\x88\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe5\x87\xa6\xe7\x90\x86\xe5\x89\x8d\xef\xbc\x89\nNumber of Bone Constraints processed before collision processing" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoneConstraintIterationCountAfterCollision_MetaData[] = {
		{ "Category", "Limits|Bone Constraint" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* Bone Constraint\xe3\x81\xae\xe5\x87\xa6\xe7\x90\x86\xe5\x9b\x9e\xe6\x95\xb0\xef\xbc\x88\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe5\x87\xa6\xe7\x90\x86\xe5\xbe\x8c\xef\xbc\x89\n\x09* Number of Bone Constraints processed after collision processing\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Bone Constraint\xe3\x81\xae\xe5\x87\xa6\xe7\x90\x86\xe5\x9b\x9e\xe6\x95\xb0\xef\xbc\x88\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe5\x87\xa6\xe7\x90\x86\xe5\xbe\x8c\xef\xbc\x89\nNumber of Bone Constraints processed after collision processing" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutoAddChildDummyBoneConstraint_MetaData[] = {
		{ "Category", "Limits|Bone Constraint" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe6\x9c\xab\xe7\xab\xaf\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92""BoneConstraint\xe5\x87\xa6\xe7\x90\x86\xe3\x81\xae\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xab\xe3\x81\x97\xe3\x81\x9f\xe5\xa0\xb4\xe5\x90\x88\xe3\x80\x81\xe8\x87\xaa\xe5\x8b\x95\xe7\x9a\x84\xe3\x81\xab\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x82\xe5\x87\xa6\xe7\x90\x86\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xab\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\n\x09* Flag to automatically processes dummy bones when the end bones are subject to BoneConstraint processing.\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x9c\xab\xe7\xab\xaf\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92""BoneConstraint\xe5\x87\xa6\xe7\x90\x86\xe3\x81\xae\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xab\xe3\x81\x97\xe3\x81\x9f\xe5\xa0\xb4\xe5\x90\x88\xe3\x80\x81\xe8\x87\xaa\xe5\x8b\x95\xe7\x9a\x84\xe3\x81\xab\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x82\xe5\x87\xa6\xe7\x90\x86\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xab\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\nFlag to automatically processes dummy bones when the end bones are subject to BoneConstraint processing." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoneConstraints_MetaData[] = {
		{ "Category", "Limits|Bone Constraint" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* BoneConstraint\xe5\x87\xa6\xe7\x90\x86\xe3\x81\xae\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xa8\xe3\x81\xaa\xe3\x82\x8b\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe3\x83\x9a\xe3\x82\xa2\xe3\x82\x92\xe8\xa8\xad\xe5\xae\x9a\xe3\x80\x82\xe3\x82\xb9\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x88\xe3\x81\xae\xe3\x82\x88\xe3\x81\x86\xe3\x81\xab\xe3\x80\x81\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x81\xae\xe8\xb7\x9d\xe9\x9b\xa2\xe3\x82\x92\xe7\xb6\xad\xe6\x8c\x81\xe3\x81\x97\xe3\x81\x9f\xe3\x81\x84\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xab\xe4\xbd\xbf\xe7\x94\xa8\n\x09* Sets the bone pair to be processed by BoneConstraint. Used when you want to maintain the distance between bones, such as a skirt.\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "TitleProperty", "{Bone1} - {Bone2}" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "BoneConstraint\xe5\x87\xa6\xe7\x90\x86\xe3\x81\xae\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xa8\xe3\x81\xaa\xe3\x82\x8b\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe3\x83\x9a\xe3\x82\xa2\xe3\x82\x92\xe8\xa8\xad\xe5\xae\x9a\xe3\x80\x82\xe3\x82\xb9\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x88\xe3\x81\xae\xe3\x82\x88\xe3\x81\x86\xe3\x81\xab\xe3\x80\x81\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x81\xae\xe8\xb7\x9d\xe9\x9b\xa2\xe3\x82\x92\xe7\xb6\xad\xe6\x8c\x81\xe3\x81\x97\xe3\x81\x9f\xe3\x81\x84\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xab\xe4\xbd\xbf\xe7\x94\xa8\nSets the bone pair to be processed by BoneConstraint. Used when you want to maintain the distance between bones, such as a skirt." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoneConstraintsDataAsset_MetaData[] = {
		{ "Category", "Limits|Bone Constraint" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* BoneConstraint\xe5\x87\xa6\xe7\x90\x86\xe3\x81\xae\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xa8\xe3\x81\xaa\xe3\x82\x8b\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe3\x83\x9a\xe3\x82\xa2\xe3\x82\x92\xe8\xa8\xad\xe5\xae\x9a (DataAsset\xe7\x89\x88\xef\xbc\x89\xe3\x80\x82\xe5\x88\xa5""AnimNode\xe3\x83\xbb""ABP\xe3\x81\xa7\xe8\xa8\xad\xe5\xae\x9a\xe3\x82\x92\xe6\xb5\x81\xe7\x94\xa8\xe3\x81\x97\xe3\x81\x9f\xe3\x81\x84\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe3\x81\x93\xe3\x81\xa1\xe3\x82\x89\xe3\x82\x92\xe6\x8e\xa8\xe5\xa5\xa8\n\x09* Set the bone pairs to be processed by BoneConstraint (DataAsset version). If you want to reuse the settings for another AnimNode or another ABP, this is recommended.\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "BoneConstraint\xe5\x87\xa6\xe7\x90\x86\xe3\x81\xae\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xa8\xe3\x81\xaa\xe3\x82\x8b\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe3\x83\x9a\xe3\x82\xa2\xe3\x82\x92\xe8\xa8\xad\xe5\xae\x9a (DataAsset\xe7\x89\x88\xef\xbc\x89\xe3\x80\x82\xe5\x88\xa5""AnimNode\xe3\x83\xbb""ABP\xe3\x81\xa7\xe8\xa8\xad\xe5\xae\x9a\xe3\x82\x92\xe6\xb5\x81\xe7\x94\xa8\xe3\x81\x97\xe3\x81\x9f\xe3\x81\x84\xe5\xa0\xb4\xe5\x90\x88\xe3\x81\xaf\xe3\x81\x93\xe3\x81\xa1\xe3\x82\x89\xe3\x82\x92\xe6\x8e\xa8\xe5\xa5\xa8\nSet the bone pairs to be processed by BoneConstraint (DataAsset version). If you want to reuse the settings for another AnimNode or another ABP, this is recommended." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoneConstraintsData_MetaData[] = {
		{ "Category", "Limits|Bone Constraint" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* BoneConstraint\xe5\x87\xa6\xe7\x90\x86\xe3\x81\xae\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xa8\xe3\x81\xaa\xe3\x82\x8b\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe3\x83\x9a\xe3\x82\xa2\xe3\x81\xae\xe3\x83\x97\xe3\x83\xac\xe3\x83\x93\xe3\x83\xa5\xe3\x83\xbc\n\x09* Preview of bone pairs that will be processed by BoneConstraint\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "TitleProperty", "{Bone1} - {Bone2}" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "BoneConstraint\xe5\x87\xa6\xe7\x90\x86\xe3\x81\xae\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xa8\xe3\x81\xaa\xe3\x82\x8b\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe3\x83\x9a\xe3\x82\xa2\xe3\x81\xae\xe3\x83\x97\xe3\x83\xac\xe3\x83\x93\xe3\x83\xa5\xe3\x83\xbc\nPreview of bone pairs that will be processed by BoneConstraint" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MergedBoneConstraints_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xbf\xe3\x82\xa4\xe3\x83\xa0\xe3\x82\xad\xe3\x83\xa3\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5(BoneConstraints + BoneConstraintsData)\xe3\x80\x82InitBoneConstraints \xe3\x81\xa7\xe5\x86\x8d\xe6\xa7\x8b\xe7\xaf\x89\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b\xe3\x81\x9f\xe3\x82\x81\xe9\x9d\x9e\xe3\x82\xb7\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xa9\xe3\x82\xa4\xe3\x82\xba\xe3\x80\x82\n// Runtime cache rebuilt in InitBoneConstraints; not serialized.\n" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xbf\xe3\x82\xa4\xe3\x83\xa0\xe3\x82\xad\xe3\x83\xa3\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5(BoneConstraints + BoneConstraintsData)\xe3\x80\x82InitBoneConstraints \xe3\x81\xa7\xe5\x86\x8d\xe6\xa7\x8b\xe7\xaf\x89\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b\xe3\x81\x9f\xe3\x82\x81\xe9\x9d\x9e\xe3\x82\xb7\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xa9\xe3\x82\xa4\xe3\x82\xba\xe3\x80\x82\nRuntime cache rebuilt in InitBoneConstraints; not serialized." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SyncBones_MetaData[] = {
		{ "Category", "Force|Sync Bone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* \xe5\x90\x8c\xe6\x9c\x9f\xe5\x85\x83\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe3\x83\xbb\xe5\x9b\x9e\xe8\xbb\xa2\xe3\x82\x92\xe7\x89\xa9\xe7\x90\x86\xe5\x88\xb6\xe5\xbe\xa1\xe4\xb8\x8b\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x97\xe3\x81\xbe\xe3\x81\x99\xe3\x80\x82\xe3\x82\xb9\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x88\xe3\x81\x8c\xe8\xb6\xb3\xe3\x81\xaa\xe3\x81\xa9\xe3\x82\x92\xe8\xb2\xab\xe9\x80\x9a\xe3\x81\x99\xe3\x82\x8b\xe3\x81\xae\xe3\x82\x92\xe9\x98\xb2\xe3\x81\x90\xe3\x81\xae\xe3\x81\xab\xe5\xbd\xb9\xe7\xab\x8b\xe3\x81\xa1\xe3\x81\xbe\xe3\x81\x99\n\x09* Applies the movement and rotation of the sync source bone to the bone under physics control. Helps prevent skirts from penetrating legs, etc.\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "TitleProperty", "{Bone}" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x90\x8c\xe6\x9c\x9f\xe5\x85\x83\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe3\x83\xbb\xe5\x9b\x9e\xe8\xbb\xa2\xe3\x82\x92\xe7\x89\xa9\xe7\x90\x86\xe5\x88\xb6\xe5\xbe\xa1\xe4\xb8\x8b\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x97\xe3\x81\xbe\xe3\x81\x99\xe3\x80\x82\xe3\x82\xb9\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x88\xe3\x81\x8c\xe8\xb6\xb3\xe3\x81\xaa\xe3\x81\xa9\xe3\x82\x92\xe8\xb2\xab\xe9\x80\x9a\xe3\x81\x99\xe3\x82\x8b\xe3\x81\xae\xe3\x82\x92\xe9\x98\xb2\xe3\x81\x90\xe3\x81\xae\xe3\x81\xab\xe5\xbd\xb9\xe7\xab\x8b\xe3\x81\xa1\xe3\x81\xbe\xe3\x81\x99\nApplies the movement and rotation of the sync source bone to the bone under physics control. Helps prevent skirts from penetrating legs, etc." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Gravity_MetaData[] = {
		{ "Category", "Force" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* \xe9\x87\x8d\xe5\x8a\x9b\n\x09* Gravity\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x87\x8d\xe5\x8a\x9b\nGravity" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseLegacyGravity_MetaData[] = {
		{ "Category", "Force" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* Gravity\xe3\x81\xae\xe9\x81\xa9\xe7\x94\xa8\xe6\x96\xb9\xe5\xbc\x8f\xef\xbc\x88\xe3\x83\xac\xe3\x82\xac\xe3\x82\xb7\xe3\x83\xbc\xe4\xba\x92\xe6\x8f\x9b\xef\xbc\x89\n\x09* true : \xe5\xbe\x93\xe6\x9d\xa5\xe4\xba\x92\xe6\x8f\x9b\xef\xbc\x88\xe4\xbd\x8d\xe7\xbd\xae\xe3\x81\xab 0.5 * Gravity * dt^2 \xe3\x82\x92\xe5\x8a\xa0\xe7\xae\x97\xef\xbc\x89\n\x09* false: AnimDynamics\xe4\xba\x92\xe6\x8f\x9b\xef\xbc\x88\xe9\x80\x9f\xe5\xba\xa6\xe3\x81\xab Gravity * dt \xe3\x82\x92\xe5\x8a\xa0\xe7\xae\x97\xe3\x81\x97\xe3\x81\xa6\xe3\x81\x8b\xe3\x82\x89\xe4\xbd\x8d\xe7\xbd\xae\xe6\x9b\xb4\xe6\x96\xb0\xef\xbc\x89\n\x09* Gravity application method (legacy compatibility)\n\x09* true : Legacy compatibility (add 0.5 * Gravity * dt^2 to position)\n\x09* false: AnimDynamics compatibility (add Gravity * dt to velocity before updating position)\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Gravity\xe3\x81\xae\xe9\x81\xa9\xe7\x94\xa8\xe6\x96\xb9\xe5\xbc\x8f\xef\xbc\x88\xe3\x83\xac\xe3\x82\xac\xe3\x82\xb7\xe3\x83\xbc\xe4\xba\x92\xe6\x8f\x9b\xef\xbc\x89\ntrue : \xe5\xbe\x93\xe6\x9d\xa5\xe4\xba\x92\xe6\x8f\x9b\xef\xbc\x88\xe4\xbd\x8d\xe7\xbd\xae\xe3\x81\xab 0.5 * Gravity * dt^2 \xe3\x82\x92\xe5\x8a\xa0\xe7\xae\x97\xef\xbc\x89\nfalse: AnimDynamics\xe4\xba\x92\xe6\x8f\x9b\xef\xbc\x88\xe9\x80\x9f\xe5\xba\xa6\xe3\x81\xab Gravity * dt \xe3\x82\x92\xe5\x8a\xa0\xe7\xae\x97\xe3\x81\x97\xe3\x81\xa6\xe3\x81\x8b\xe3\x82\x89\xe4\xbd\x8d\xe7\xbd\xae\xe6\x9b\xb4\xe6\x96\xb0\xef\xbc\x89\nGravity application method (legacy compatibility)\ntrue : Legacy compatibility (add 0.5 * Gravity * dt^2 to position)\nfalse: AnimDynamics compatibility (add Gravity * dt to velocity before updating position)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseDefaultGravityZProjectSetting_MetaData[] = {
		{ "Category", "Force" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* Gravity\xe3\x83\x99\xe3\x82\xaf\xe3\x83\x88\xe3\x83\xab\xe3\x81\xab\xe3\x83\x97\xe3\x83\xad\xe3\x82\xb8\xe3\x82\xa7\xe3\x82\xaf\xe3\x83\x88\xe8\xa8\xad\xe5\xae\x9a\xe3\x81\xae DefaultGravityZ\xef\xbc\x88\xe7\xb5\xb6\xe5\xaf\xbe\xe5\x80\xa4\xef\xbc\x89\xe3\x82\x92\xe4\xb9\x97\xe7\xae\x97\xe3\x81\x99\xe3\x82\x8b\xe5\x87\xa6\xe7\x90\x86\xe3\x81\xae\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\n\x09* Flag to multiply the DefaultGravityZ (absolute value) of the project settings to the Gravity vector\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Gravity\xe3\x83\x99\xe3\x82\xaf\xe3\x83\x88\xe3\x83\xab\xe3\x81\xab\xe3\x83\x97\xe3\x83\xad\xe3\x82\xb8\xe3\x82\xa7\xe3\x82\xaf\xe3\x83\x88\xe8\xa8\xad\xe5\xae\x9a\xe3\x81\xae DefaultGravityZ\xef\xbc\x88\xe7\xb5\xb6\xe5\xaf\xbe\xe5\x80\xa4\xef\xbc\x89\xe3\x82\x92\xe4\xb9\x97\xe7\xae\x97\xe3\x81\x99\xe3\x82\x8b\xe5\x87\xa6\xe7\x90\x86\xe3\x81\xae\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\nFlag to multiply the DefaultGravityZ (absolute value) of the project settings to the Gravity vector" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseWorldSpaceGravity_MetaData[] = {
		{ "Category", "Force" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe9\x87\x8d\xe5\x8a\x9b\xe3\x82\x92\xe3\x83\xaf\xe3\x83\xbc\xe3\x83\xab\xe3\x83\x89\xe5\xba\xa7\xe6\xa8\x99\xe7\xb3\xbb\xe3\x81\xa7\xe6\x89\xb1\xe3\x81\x86\xe3\x81\x8b\xe3\x81\xa9\xe3\x81\x86\xe3\x81\x8b\xe3\x81\xae\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\n// Flag to handle gravity in world coordinate system\n" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x87\x8d\xe5\x8a\x9b\xe3\x82\x92\xe3\x83\xaf\xe3\x83\xbc\xe3\x83\xab\xe3\x83\x89\xe5\xba\xa7\xe6\xa8\x99\xe7\xb3\xbb\xe3\x81\xa7\xe6\x89\xb1\xe3\x81\x86\xe3\x81\x8b\xe3\x81\xa9\xe3\x81\x86\xe3\x81\x8b\xe3\x81\xae\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\nFlag to handle gravity in world coordinate system" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableWind_MetaData[] = {
		{ "Category", "Force" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\xa4\x96\xe5\x8a\x9b\xe3\x81\xa8\xe3\x81\x97\xe3\x81\xa6WindDirectionalSource\xe3\x81\xae\xe5\xbd\xb1\xe9\x9f\xbf\xe3\x82\x92\xe5\x8f\x97\xe3\x81\x91\xe3\x82\x8b\xe3\x81\x8b\xe3\x81\xa9\xe3\x81\x86\xe3\x81\x8b\xe3\x81\xae\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\n// Flag to receive the influence of WindDirectionalSource as an external force\n" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xa4\x96\xe5\x8a\x9b\xe3\x81\xa8\xe3\x81\x97\xe3\x81\xa6WindDirectionalSource\xe3\x81\xae\xe5\xbd\xb1\xe9\x9f\xbf\xe3\x82\x92\xe5\x8f\x97\xe3\x81\x91\xe3\x82\x8b\xe3\x81\x8b\xe3\x81\xa9\xe3\x81\x86\xe3\x81\x8b\xe3\x81\xae\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\nFlag to receive the influence of WindDirectionalSource as an external force" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WindScale_MetaData[] = {
		{ "Category", "Force" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* WindDirectionalSource\xe3\x81\xab\xe3\x82\x88\xe3\x82\x8b\xe9\xa2\xa8\xe3\x81\xae\xe5\xbd\xb1\xe9\x9f\xbf\xe5\xba\xa6\xe3\x80\x82""Cloth\xe3\x82\x84SpeedTree\xe3\x81\xa8\xe3\x81\xae\xe4\xbd\xb5\xe7\x94\xa8\xe7\x9b\xae\xe7\x9a\x84\n\x09* Influence of wind by WindDirectionalSource. For use with Cloth and SpeedTree\n\x09*/" },
#endif
		{ "EditCondition", "bEnableWind" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "WindDirectionalSource\xe3\x81\xab\xe3\x82\x88\xe3\x82\x8b\xe9\xa2\xa8\xe3\x81\xae\xe5\xbd\xb1\xe9\x9f\xbf\xe5\xba\xa6\xe3\x80\x82""Cloth\xe3\x82\x84SpeedTree\xe3\x81\xa8\xe3\x81\xae\xe4\xbd\xb5\xe7\x94\xa8\xe7\x9b\xae\xe7\x9a\x84\nInfluence of wind by WindDirectionalSource. For use with Cloth and SpeedTree" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WindDirectionNoiseAngle_MetaData[] = {
		{ "Category", "Force" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n    * WindDirectionalSource\xe3\x81\xab\xe3\x82\x88\xe3\x82\x8b\xe9\xa2\xa8\xe6\x96\xb9\xe5\x90\x91\xe3\x81\xab\xe4\xb8\x8e\xe3\x81\x88\xe3\x82\x8b\xe3\x83\x8e\xe3\x82\xa4\xe3\x82\xba\xef\xbc\x88\xe8\xa7\x92\xe5\xba\xa6\xef\xbc\x89\n    * Noise(Degree) of wind by WindDirectionalSource. For use with Cloth and SpeedTree\n    */" },
#endif
		{ "EditCondition", "bEnableWind" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "WindDirectionalSource\xe3\x81\xab\xe3\x82\x88\xe3\x82\x8b\xe9\xa2\xa8\xe6\x96\xb9\xe5\x90\x91\xe3\x81\xab\xe4\xb8\x8e\xe3\x81\x88\xe3\x82\x8b\xe3\x83\x8e\xe3\x82\xa4\xe3\x82\xba\xef\xbc\x88\xe8\xa7\x92\xe5\xba\xa6\xef\xbc\x89\nNoise(Degree) of wind by WindDirectionalSource. For use with Cloth and SpeedTree" },
#endif
		{ "Units", "Degrees" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SimpleExternalForce_MetaData[] = {
		{ "Category", "Force|External Force" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x8d\x98\xe7\xb4\x94\xe3\x81\xaa\xe5\xa4\x96\xe5\x8a\x9b\xe3\x83\x99\xe3\x82\xaf\xe3\x83\x88\xe3\x83\xab\n// Simple external force vector\n" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8d\x98\xe7\xb4\x94\xe3\x81\xaa\xe5\xa4\x96\xe5\x8a\x9b\xe3\x83\x99\xe3\x82\xaf\xe3\x83\x88\xe3\x83\xab\nSimple external force vector" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseWorldSpaceSimpleExternalForce_MetaData[] = {
		{ "Category", "Force|External Force" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x8d\x98\xe7\xb4\x94\xe3\x81\xaa\xe5\xa4\x96\xe5\x8a\x9b\xe3\x82\x92\xe3\x83\xaf\xe3\x83\xbc\xe3\x83\xab\xe3\x83\x89\xe5\xba\xa7\xe6\xa8\x99\xe7\xb3\xbb\xe3\x81\xa7\xe6\x89\xb1\xe3\x81\x86\xe3\x81\x8b\xe3\x81\xa9\xe3\x81\x86\xe3\x81\x8b\xe3\x81\xae\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\n// Flag to handle simple external forces in world coordinate system\n" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8d\x98\xe7\xb4\x94\xe3\x81\xaa\xe5\xa4\x96\xe5\x8a\x9b\xe3\x82\x92\xe3\x83\xaf\xe3\x83\xbc\xe3\x83\xab\xe3\x83\x89\xe5\xba\xa7\xe6\xa8\x99\xe7\xb3\xbb\xe3\x81\xa7\xe6\x89\xb1\xe3\x81\x86\xe3\x81\x8b\xe3\x81\xa9\xe3\x81\x86\xe3\x81\x8b\xe3\x81\xae\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\nFlag to handle simple external forces in world coordinate system" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExternalForces_MetaData[] = {
		{ "BaseStruct", "/Script/KawaiiPhysics.KawaiiPhysics_ExternalForce" },
		{ "Category", "Force|External Force" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe5\xa4\x96\xe5\x8a\x9b\xe3\x81\xae\xe3\x83\x97\xe3\x83\xaa\xe3\x82\xbb\xe3\x83\x83\xe3\x83\x88\xe3\x80\x82""C++\xe3\x81\xa7\xe7\x8b\xac\xe8\x87\xaa\xe3\x81\xae\xe3\x83\x97\xe3\x83\xaa\xe3\x82\xbb\xe3\x83\x83\xe3\x83\x88\xe3\x82\x92\xe8\xbf\xbd\xe5\x8a\xa0\xe5\x8f\xaf\xe8\x83\xbd(Instanced Struct)\n\x09* External force presets. You can add your own presets in C++.\n\x09*/" },
#endif
		{ "ExcludeBaseStruct", "" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xa4\x96\xe5\x8a\x9b\xe3\x81\xae\xe3\x83\x97\xe3\x83\xaa\xe3\x82\xbb\xe3\x83\x83\xe3\x83\x88\xe3\x80\x82""C++\xe3\x81\xa7\xe7\x8b\xac\xe8\x87\xaa\xe3\x81\xae\xe3\x83\x97\xe3\x83\xaa\xe3\x82\xbb\xe3\x83\x83\xe3\x83\x88\xe3\x82\x92\xe8\xbf\xbd\xe5\x8a\xa0\xe5\x8f\xaf\xe8\x83\xbd(Instanced Struct)\nExternal force presets. You can add your own presets in C++." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CustomExternalForces_Inner_MetaData[] = {
		{ "Category", "Force|External Force" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* EXPERIMENTAL: \xe5\xa4\x96\xe5\x8a\x9b\xe3\x81\xae\xe3\x83\x97\xe3\x83\xaa\xe3\x82\xbb\xe3\x83\x83\xe3\x83\x88\xe3\x80\x82""BP\xe3\x83\xbb""C++\xe3\x81\xa7\xe7\x8b\xac\xe8\x87\xaa\xe3\x81\xae\xe3\x83\x97\xe3\x83\xaa\xe3\x82\xbb\xe3\x83\x83\xe3\x83\x88\xe3\x82\x92\xe8\xbf\xbd\xe5\x8a\xa0\xe5\x8f\xaf\xe8\x83\xbd(Instanced Property)\n\x09* \xe6\xb3\xa8\xe6\x84\x8f\xef\xbc\x9a""AnimNode\xe3\x82\x92\xe3\x82\xaf\xe3\x83\xaa\xe3\x83\x83\xe3\x82\xaf or ABP\xe3\x82\x92\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x91\xe3\x82\xa4\xe3\x83\xab\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xe3\x81\xa8\xe6\xad\xa3\xe5\xb8\xb8\xe3\x81\xab\xe5\x8b\x95\xe4\xbd\x9c\xe3\x81\x97\xe3\x81\xbe\xe3\x81\x9b\xe3\x82\x93\n\x09* External force presets (experimental). You can add your own presets in BP or C++.\n\x09* Note: If you do not click on AnimNode or compile ABP, it will not work properly.\n\x09*/" },
#endif
		{ "DisplayName", "CustomExternalForces(EXPERIMENTAL)" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "EXPERIMENTAL: \xe5\xa4\x96\xe5\x8a\x9b\xe3\x81\xae\xe3\x83\x97\xe3\x83\xaa\xe3\x82\xbb\xe3\x83\x83\xe3\x83\x88\xe3\x80\x82""BP\xe3\x83\xbb""C++\xe3\x81\xa7\xe7\x8b\xac\xe8\x87\xaa\xe3\x81\xae\xe3\x83\x97\xe3\x83\xaa\xe3\x82\xbb\xe3\x83\x83\xe3\x83\x88\xe3\x82\x92\xe8\xbf\xbd\xe5\x8a\xa0\xe5\x8f\xaf\xe8\x83\xbd(Instanced Property)\n\xe6\xb3\xa8\xe6\x84\x8f\xef\xbc\x9a""AnimNode\xe3\x82\x92\xe3\x82\xaf\xe3\x83\xaa\xe3\x83\x83\xe3\x82\xaf or ABP\xe3\x82\x92\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x91\xe3\x82\xa4\xe3\x83\xab\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xe3\x81\xa8\xe6\xad\xa3\xe5\xb8\xb8\xe3\x81\xab\xe5\x8b\x95\xe4\xbd\x9c\xe3\x81\x97\xe3\x81\xbe\xe3\x81\x9b\xe3\x82\x93\nExternal force presets (experimental). You can add your own presets in BP or C++.\nNote: If you do not click on AnimNode or compile ABP, it will not work properly." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CustomExternalForces_MetaData[] = {
		{ "Category", "Force|External Force" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* EXPERIMENTAL: \xe5\xa4\x96\xe5\x8a\x9b\xe3\x81\xae\xe3\x83\x97\xe3\x83\xaa\xe3\x82\xbb\xe3\x83\x83\xe3\x83\x88\xe3\x80\x82""BP\xe3\x83\xbb""C++\xe3\x81\xa7\xe7\x8b\xac\xe8\x87\xaa\xe3\x81\xae\xe3\x83\x97\xe3\x83\xaa\xe3\x82\xbb\xe3\x83\x83\xe3\x83\x88\xe3\x82\x92\xe8\xbf\xbd\xe5\x8a\xa0\xe5\x8f\xaf\xe8\x83\xbd(Instanced Property)\n\x09* \xe6\xb3\xa8\xe6\x84\x8f\xef\xbc\x9a""AnimNode\xe3\x82\x92\xe3\x82\xaf\xe3\x83\xaa\xe3\x83\x83\xe3\x82\xaf or ABP\xe3\x82\x92\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x91\xe3\x82\xa4\xe3\x83\xab\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xe3\x81\xa8\xe6\xad\xa3\xe5\xb8\xb8\xe3\x81\xab\xe5\x8b\x95\xe4\xbd\x9c\xe3\x81\x97\xe3\x81\xbe\xe3\x81\x9b\xe3\x82\x93\n\x09* External force presets (experimental). You can add your own presets in BP or C++.\n\x09* Note: If you do not click on AnimNode or compile ABP, it will not work properly.\n\x09*/" },
#endif
		{ "DisplayName", "CustomExternalForces(EXPERIMENTAL)" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "EXPERIMENTAL: \xe5\xa4\x96\xe5\x8a\x9b\xe3\x81\xae\xe3\x83\x97\xe3\x83\xaa\xe3\x82\xbb\xe3\x83\x83\xe3\x83\x88\xe3\x80\x82""BP\xe3\x83\xbb""C++\xe3\x81\xa7\xe7\x8b\xac\xe8\x87\xaa\xe3\x81\xae\xe3\x83\x97\xe3\x83\xaa\xe3\x82\xbb\xe3\x83\x83\xe3\x83\x88\xe3\x82\x92\xe8\xbf\xbd\xe5\x8a\xa0\xe5\x8f\xaf\xe8\x83\xbd(Instanced Property)\n\xe6\xb3\xa8\xe6\x84\x8f\xef\xbc\x9a""AnimNode\xe3\x82\x92\xe3\x82\xaf\xe3\x83\xaa\xe3\x83\x83\xe3\x82\xaf or ABP\xe3\x82\x92\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x91\xe3\x82\xa4\xe3\x83\xab\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84\xe3\x81\xa8\xe6\xad\xa3\xe5\xb8\xb8\xe3\x81\xab\xe5\x8b\x95\xe4\xbd\x9c\xe3\x81\x97\xe3\x81\xbe\xe3\x81\x9b\xe3\x82\x93\nExternal force presets (experimental). You can add your own presets in BP or C++.\nNote: If you do not click on AnimNode or compile ABP, it will not work properly." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAllowWorldCollision_MetaData[] = {
		{ "Category", "Limits|World Collision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe3\x83\xac\xe3\x83\x99\xe3\x83\xab\xe4\xb8\x8a\xe3\x81\xae\xe5\x90\x84\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x81\xa8\xe3\x81\xae\xe5\x88\xa4\xe5\xae\x9a\xe3\x82\x92\xe8\xa1\x8c\xe3\x81\x86\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\xe3\x80\x82\xe6\x9c\x89\xe5\x8a\xb9\xe3\x81\xab\xe3\x81\x99\xe3\x82\x8b\xe3\x81\xa8\xe7\x89\xa9\xe7\x90\x86\xe5\x87\xa6\xe7\x90\x86\xe3\x81\xae\xe8\xb2\xa0\xe8\x8d\xb7\xe3\x81\x8c\xe5\xa4\xa7\xe5\xb9\x85\xe3\x81\xab\xe4\xb8\x8a\xe3\x81\x8c\xe3\x82\x8a\xe3\x81\xbe\xe3\x81\x99\n\x09* Flag for collision detection with each collision on the level. Enabling this will significantly increase the load of physics processing.\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x83\xac\xe3\x83\x99\xe3\x83\xab\xe4\xb8\x8a\xe3\x81\xae\xe5\x90\x84\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x81\xa8\xe3\x81\xae\xe5\x88\xa4\xe5\xae\x9a\xe3\x82\x92\xe8\xa1\x8c\xe3\x81\x86\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\xe3\x80\x82\xe6\x9c\x89\xe5\x8a\xb9\xe3\x81\xab\xe3\x81\x99\xe3\x82\x8b\xe3\x81\xa8\xe7\x89\xa9\xe7\x90\x86\xe5\x87\xa6\xe7\x90\x86\xe3\x81\xae\xe8\xb2\xa0\xe8\x8d\xb7\xe3\x81\x8c\xe5\xa4\xa7\xe5\xb9\x85\xe3\x81\xab\xe4\xb8\x8a\xe3\x81\x8c\xe3\x82\x8a\xe3\x81\xbe\xe3\x81\x99\nFlag for collision detection with each collision on the level. Enabling this will significantly increase the load of physics processing." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bOverrideCollisionParams_MetaData[] = {
		{ "Category", "Limits|World Collision" },
		{ "InlineEditConditionToggle", "" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionChannelSettings_MetaData[] = {
		{ "Category", "Limits|World Collision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* SkeletalMeshComponent\xe3\x81\x8c\xe6\x8c\x81\xe3\x81\xa4\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe8\xa8\xad\xe5\xae\x9a\xe3\x81\xa7\xe3\x81\xaf\xe3\x81\xaa\xe3\x81\x8f\xe3\x80\x81\xe7\x8b\xac\xe8\x87\xaa\xe3\x81\xae\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe8\xa8\xad\xe5\xae\x9a\xe3\x82\x92WorldCollision\xe3\x81\xa7\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\xe9\x9a\x9b\xe3\x81\xab\xe8\xa8\xad\xe5\xae\x9a\n\x09* Use custom collision settings in WorldCollision instead of the collision settings set in SkeletalMeshComponent.\n\x09*/" },
#endif
		{ "DisplayName", "Override SkelComp Collision Params" },
		{ "EditCondition", "bOverrideCollisionParams" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "SkeletalMeshComponent\xe3\x81\x8c\xe6\x8c\x81\xe3\x81\xa4\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe8\xa8\xad\xe5\xae\x9a\xe3\x81\xa7\xe3\x81\xaf\xe3\x81\xaa\xe3\x81\x8f\xe3\x80\x81\xe7\x8b\xac\xe8\x87\xaa\xe3\x81\xae\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe8\xa8\xad\xe5\xae\x9a\xe3\x82\x92WorldCollision\xe3\x81\xa7\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\xe9\x9a\x9b\xe3\x81\xab\xe8\xa8\xad\xe5\xae\x9a\nUse custom collision settings in WorldCollision instead of the collision settings set in SkeletalMeshComponent." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIgnoreSelfComponent_MetaData[] = {
		{ "Category", "Limits|World Collision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* WorldCollision\xe3\x81\xab\xe3\x81\xa6\xe3\x80\x81SkeletalMeshComponent\xe3\x81\x8c\xe6\x8c\x81\xe3\x81\xa4\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3(PhysicsAsset)\xe3\x82\x92\xe7\x84\xa1\xe8\xa6\x96\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\n\x09* In WorldCollision, Flag to ignore collisions for SkeletalMeshComponent(PhysicsAsset) in WorldCollision\n\x09*/" },
#endif
		{ "EditCondition", "bAllowWorldCollision" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
		{ "PinHiddenByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "WorldCollision\xe3\x81\xab\xe3\x81\xa6\xe3\x80\x81SkeletalMeshComponent\xe3\x81\x8c\xe6\x8c\x81\xe3\x81\xa4\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3(PhysicsAsset)\xe3\x82\x92\xe7\x84\xa1\xe8\xa6\x96\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\nIn WorldCollision, Flag to ignore collisions for SkeletalMeshComponent(PhysicsAsset) in WorldCollision" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IgnoreBones_MetaData[] = {
		{ "Category", "Limits|World Collision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* WorldCollision\xe3\x81\xab\xe3\x81\xa6\xe3\x80\x81SkeletalMeshComponent\xe3\x81\x8c\xe6\x8c\x81\xe3\x81\xa4\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3(PhysicsAsset)\xe3\x82\x92\xe7\x84\xa1\xe8\xa6\x96\xe3\x81\x99\xe3\x82\x8b\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xaa\xa8\xef\xbc\x89\n\x09* In WorldCollision, set to ignore collision (PhysicsAsset) of SkeletalMeshComponent using bone\n\x09*/" },
#endif
		{ "EditCondition", "!bIgnoreSelfComponent" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "WorldCollision\xe3\x81\xab\xe3\x81\xa6\xe3\x80\x81SkeletalMeshComponent\xe3\x81\x8c\xe6\x8c\x81\xe3\x81\xa4\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3(PhysicsAsset)\xe3\x82\x92\xe7\x84\xa1\xe8\xa6\x96\xe3\x81\x99\xe3\x82\x8b\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xaa\xa8\xef\xbc\x89\nIn WorldCollision, set to ignore collision (PhysicsAsset) of SkeletalMeshComponent using bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IgnoreBoneNamePrefix_MetaData[] = {
		{ "Category", "Limits|World Collision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* WorldCollision\xe3\x81\xab\xe3\x81\xa6\xe3\x80\x81SkeletalMeshComponent\xe3\x81\x8c\xe6\x8c\x81\xe3\x81\xa4\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3(PhysicsAsset)\xe3\x82\x92\xe7\x84\xa1\xe8\xa6\x96\xe3\x81\x99\xe3\x82\x8b\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xaa\xa8\xe5\x90\x8d\xe3\x81\xae\xe3\x83\x97\xe3\x83\xaa\xe3\x83\x95\xe3\x82\xa3\xe3\x83\x83\xe3\x82\xaf\xe3\x82\xb9\xef\xbc\x89\n\x09* In WorldCollision, set to ignore collision (PhysicsAsset) of SkeletalMeshComponent using bone name prefix\n\x09*/" },
#endif
		{ "EditCondition", "!bIgnoreSelfComponent" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "WorldCollision\xe3\x81\xab\xe3\x81\xa6\xe3\x80\x81SkeletalMeshComponent\xe3\x81\x8c\xe6\x8c\x81\xe3\x81\xa4\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3(PhysicsAsset)\xe3\x82\x92\xe7\x84\xa1\xe8\xa6\x96\xe3\x81\x99\xe3\x82\x8b\xe8\xa8\xad\xe5\xae\x9a\xef\xbc\x88\xe9\xaa\xa8\xe5\x90\x8d\xe3\x81\xae\xe3\x83\x97\xe3\x83\xaa\xe3\x83\x95\xe3\x82\xa3\xe3\x83\x83\xe3\x82\xaf\xe3\x82\xb9\xef\xbc\x89\nIn WorldCollision, set to ignore collision (PhysicsAsset) of SkeletalMeshComponent using bone name prefix" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_KawaiiPhysicsTag_MetaData[] = {
		{ "Category", "Tag" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* ExternalForce\xe3\x81\xaa\xe3\x81\xa9\xe3\x81\xa7\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x95\xe3\x82\xa3\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xaa\xe3\x83\xb3\xe3\x82\xb0\xe7\x94\xa8\xe3\x82\xbf\xe3\x82\xb0\n\x09* Tag for filtering of ExternalForce etc\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "ExternalForce\xe3\x81\xaa\xe3\x81\xa9\xe3\x81\xa7\xe4\xbd\xbf\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\xe3\x83\x95\xe3\x82\xa3\xe3\x83\xab\xe3\x82\xbf\xe3\x83\xaa\xe3\x83\xb3\xe3\x82\xb0\xe7\x94\xa8\xe3\x82\xbf\xe3\x82\xb0\nTag for filtering of ExternalForce etc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ModifyBones_MetaData[] = {
		{ "Category", "Bones" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* \xe7\x89\xa9\xe7\x90\x86\xe5\x88\xb6\xe5\xbe\xa1\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xbf\xe3\x82\xa4\xe3\x83\xa0\xe3\x82\xad\xe3\x83\xa3\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x80\x82Initialize_AnyThread \xe3\x81\xa7\xe6\xaf\x8e\xe5\x9b\x9e\xe5\x86\x8d\xe6\xa7\x8b\xe7\xaf\x89\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b\xe3\x81\x9f\xe3\x82\x81\xe9\x9d\x9e\xe3\x82\xb7\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xa9\xe3\x82\xa4\xe3\x82\xba(Transient)\xe3\x80\x82\n\x09* Runtime cache of bones under physics control. Rebuilt every Initialize_AnyThread, so it is Transient (not serialized).\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x89\xa9\xe7\x90\x86\xe5\x88\xb6\xe5\xbe\xa1\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe3\x83\xa9\xe3\x83\xb3\xe3\x82\xbf\xe3\x82\xa4\xe3\x83\xa0\xe3\x82\xad\xe3\x83\xa3\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x80\x82Initialize_AnyThread \xe3\x81\xa7\xe6\xaf\x8e\xe5\x9b\x9e\xe5\x86\x8d\xe6\xa7\x8b\xe7\xaf\x89\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b\xe3\x81\x9f\xe3\x82\x81\xe9\x9d\x9e\xe3\x82\xb7\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xa9\xe3\x82\xa4\xe3\x82\xba(Transient)\xe3\x80\x82\nRuntime cache of bones under physics control. Rebuilt every Initialize_AnyThread, so it is Transient (not serialized)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeltaTime_MetaData[] = {
		{ "Category", "KawaiiPhysics" },
		{ "ModuleRelativePath", "Public/AnimNode_KawaiiPhysics.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FAnimNode_KawaiiPhysics constinit property declarations ***********
	static const UECodeGen_Private::FStructPropertyParams NewProp_RootBone;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ExcludeBones_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ExcludeBones;
	static const UECodeGen_Private::FStructPropertyParams NewProp_AdditionalRootBones_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_AdditionalRootBones;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DummyBoneLength;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BoneSubdivisionCount;
	static void NewProp_bBoneSubdivisionCollisionOnly_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bBoneSubdivisionCollisionOnly;
	static void NewProp_bBoneSubdivisionDensifyByRadius_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bBoneSubdivisionDensifyByRadius;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BoneConstraintSubdivisionCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BoneConstraintSubdivisionFeedbackScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_BoneForwardAxis_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_BoneForwardAxis;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PhysicsSettings;
	static const UECodeGen_Private::FBytePropertyParams NewProp_SimulationSpace_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_SimulationSpace;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SimulationBaseBone;
	static const UECodeGen_Private::FIntPropertyParams NewProp_TargetFramerate;
	static const UECodeGen_Private::FIntPropertyParams NewProp_WarmUpFrames;
	static void NewProp_bUseWarmUpWhenResetDynamics_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseWarmUpWhenResetDynamics;
	static void NewProp_bNeedWarmUp_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bNeedWarmUp;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TeleportDistanceThreshold;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TeleportRotationThreshold;
	static const UECodeGen_Private::FBytePropertyParams NewProp_PlanarConstraint_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_PlanarConstraint;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SkelCompMoveScale;
	static void NewProp_bUpdatePhysicsSettingsInGame_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUpdatePhysicsSettingsInGame;
	static void NewProp_ResetBoneTransformWhenBoneNotFound_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ResetBoneTransformWhenBoneNotFound;
	static const UECodeGen_Private::FStructPropertyParams NewProp_DampingCurveData;
	static const UECodeGen_Private::FStructPropertyParams NewProp_StiffnessCurveData;
	static const UECodeGen_Private::FStructPropertyParams NewProp_WorldDampingLocationCurveData;
	static const UECodeGen_Private::FStructPropertyParams NewProp_WorldDampingRotationCurveData;
	static const UECodeGen_Private::FStructPropertyParams NewProp_RadiusCurveData;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LimitAngleCurveData;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SphericalLimits_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_SphericalLimits;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CapsuleLimits_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_CapsuleLimits;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BoxLimits_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_BoxLimits;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PlanarLimits_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PlanarLimits;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LimitsDataAsset;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PhysicsAssetForLimits;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SphericalLimitsData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_SphericalLimitsData;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CapsuleLimitsData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_CapsuleLimitsData;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BoxLimitsData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_BoxLimitsData;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PlanarLimitsData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PlanarLimitsData;
	static void NewProp_bSharedCollisionSource_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSharedCollisionSource;
	static void NewProp_bUseSharedCollision_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseSharedCollision;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SharedCollisionGroupTag;
	static const UECodeGen_Private::FBytePropertyParams NewProp_BoneConstraintGlobalComplianceType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_BoneConstraintGlobalComplianceType;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BoneConstraintIterationCountBeforeCollision;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BoneConstraintIterationCountAfterCollision;
	static void NewProp_bAutoAddChildDummyBoneConstraint_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoAddChildDummyBoneConstraint;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BoneConstraints_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_BoneConstraints;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BoneConstraintsDataAsset;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BoneConstraintsData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_BoneConstraintsData;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MergedBoneConstraints_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_MergedBoneConstraints;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SyncBones_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_SyncBones;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Gravity;
	static void NewProp_bUseLegacyGravity_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseLegacyGravity;
	static void NewProp_bUseDefaultGravityZProjectSetting_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseDefaultGravityZProjectSetting;
	static void NewProp_bUseWorldSpaceGravity_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseWorldSpaceGravity;
	static void NewProp_bEnableWind_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableWind;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WindScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WindDirectionNoiseAngle;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SimpleExternalForce;
	static void NewProp_bUseWorldSpaceSimpleExternalForce_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseWorldSpaceSimpleExternalForce;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ExternalForces_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ExternalForces;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CustomExternalForces_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_CustomExternalForces;
	static void NewProp_bAllowWorldCollision_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAllowWorldCollision;
	static void NewProp_bOverrideCollisionParams_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOverrideCollisionParams;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CollisionChannelSettings;
	static void NewProp_bIgnoreSelfComponent_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIgnoreSelfComponent;
	static const UECodeGen_Private::FStructPropertyParams NewProp_IgnoreBones_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_IgnoreBones;
	static const UECodeGen_Private::FNamePropertyParams NewProp_IgnoreBoneNamePrefix_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_IgnoreBoneNamePrefix;
	static const UECodeGen_Private::FStructPropertyParams NewProp_KawaiiPhysicsTag;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ModifyBones_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ModifyBones;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeltaTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FAnimNode_KawaiiPhysics constinit property declarations *************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAnimNode_KawaiiPhysics>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics
static_assert(std::is_polymorphic<FAnimNode_KawaiiPhysics>() == std::is_polymorphic<FAnimNode_SkeletalControlBase>(), "USTRUCT FAnimNode_KawaiiPhysics cannot be polymorphic unless super FAnimNode_SkeletalControlBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FAnimNode_KawaiiPhysics;
class UScriptStruct* FAnimNode_KawaiiPhysics::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FAnimNode_KawaiiPhysics.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FAnimNode_KawaiiPhysics.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("AnimNode_KawaiiPhysics"));
	}
	return Z_Registration_Info_UScriptStruct_FAnimNode_KawaiiPhysics.OuterSingleton;
	}

// ********** Begin ScriptStruct FAnimNode_KawaiiPhysics Property Definitions **********************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_RootBone = { "RootBone", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, RootBone), Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RootBone_MetaData), NewProp_RootBone_MetaData) }; // 1102615820
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_ExcludeBones_Inner = { "ExcludeBones", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(0, nullptr) }; // 1102615820
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_ExcludeBones = { "ExcludeBones", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, ExcludeBones), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExcludeBones_MetaData), NewProp_ExcludeBones_MetaData) }; // 1102615820
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_AdditionalRootBones_Inner = { "AdditionalRootBones", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting, METADATA_PARAMS(0, nullptr) }; // 639501474
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_AdditionalRootBones = { "AdditionalRootBones", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, AdditionalRootBones), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AdditionalRootBones_MetaData), NewProp_AdditionalRootBones_MetaData) }; // 639501474
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_DummyBoneLength = { "DummyBoneLength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, DummyBoneLength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DummyBoneLength_MetaData), NewProp_DummyBoneLength_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneSubdivisionCount = { "BoneSubdivisionCount", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, BoneSubdivisionCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoneSubdivisionCount_MetaData), NewProp_BoneSubdivisionCount_MetaData) };
void Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bBoneSubdivisionCollisionOnly_SetBit(void* Obj)
{
	((FAnimNode_KawaiiPhysics*)Obj)->bBoneSubdivisionCollisionOnly = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bBoneSubdivisionCollisionOnly = { "bBoneSubdivisionCollisionOnly", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAnimNode_KawaiiPhysics), &Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bBoneSubdivisionCollisionOnly_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bBoneSubdivisionCollisionOnly_MetaData), NewProp_bBoneSubdivisionCollisionOnly_MetaData) };
void Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bBoneSubdivisionDensifyByRadius_SetBit(void* Obj)
{
	((FAnimNode_KawaiiPhysics*)Obj)->bBoneSubdivisionDensifyByRadius = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bBoneSubdivisionDensifyByRadius = { "bBoneSubdivisionDensifyByRadius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAnimNode_KawaiiPhysics), &Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bBoneSubdivisionDensifyByRadius_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bBoneSubdivisionDensifyByRadius_MetaData), NewProp_bBoneSubdivisionDensifyByRadius_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintSubdivisionCount = { "BoneConstraintSubdivisionCount", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, BoneConstraintSubdivisionCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoneConstraintSubdivisionCount_MetaData), NewProp_BoneConstraintSubdivisionCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintSubdivisionFeedbackScale = { "BoneConstraintSubdivisionFeedbackScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, BoneConstraintSubdivisionFeedbackScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoneConstraintSubdivisionFeedbackScale_MetaData), NewProp_BoneConstraintSubdivisionFeedbackScale_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneForwardAxis_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneForwardAxis = { "BoneForwardAxis", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, BoneForwardAxis), Z_Construct_UEnum_KawaiiPhysics_EBoneForwardAxis, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoneForwardAxis_MetaData), NewProp_BoneForwardAxis_MetaData) }; // 1723749861
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_PhysicsSettings = { "PhysicsSettings", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, PhysicsSettings), Z_Construct_UScriptStruct_FKawaiiPhysicsSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PhysicsSettings_MetaData), NewProp_PhysicsSettings_MetaData) }; // 2772010112
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SimulationSpace_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SimulationSpace = { "SimulationSpace", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, SimulationSpace), Z_Construct_UEnum_KawaiiPhysics_EKawaiiPhysicsSimulationSpace, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SimulationSpace_MetaData), NewProp_SimulationSpace_MetaData) }; // 3750099244
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SimulationBaseBone = { "SimulationBaseBone", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, SimulationBaseBone), Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SimulationBaseBone_MetaData), NewProp_SimulationBaseBone_MetaData) }; // 1102615820
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_TargetFramerate = { "TargetFramerate", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, TargetFramerate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetFramerate_MetaData), NewProp_TargetFramerate_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_WarmUpFrames = { "WarmUpFrames", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, WarmUpFrames), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarmUpFrames_MetaData), NewProp_WarmUpFrames_MetaData) };
void Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseWarmUpWhenResetDynamics_SetBit(void* Obj)
{
	((FAnimNode_KawaiiPhysics*)Obj)->bUseWarmUpWhenResetDynamics = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseWarmUpWhenResetDynamics = { "bUseWarmUpWhenResetDynamics", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAnimNode_KawaiiPhysics), &Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseWarmUpWhenResetDynamics_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseWarmUpWhenResetDynamics_MetaData), NewProp_bUseWarmUpWhenResetDynamics_MetaData) };
void Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bNeedWarmUp_SetBit(void* Obj)
{
	((FAnimNode_KawaiiPhysics*)Obj)->bNeedWarmUp = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bNeedWarmUp = { "bNeedWarmUp", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAnimNode_KawaiiPhysics), &Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bNeedWarmUp_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bNeedWarmUp_MetaData), NewProp_bNeedWarmUp_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_TeleportDistanceThreshold = { "TeleportDistanceThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, TeleportDistanceThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TeleportDistanceThreshold_MetaData), NewProp_TeleportDistanceThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_TeleportRotationThreshold = { "TeleportRotationThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, TeleportRotationThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TeleportRotationThreshold_MetaData), NewProp_TeleportRotationThreshold_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_PlanarConstraint_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_PlanarConstraint = { "PlanarConstraint", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, PlanarConstraint), Z_Construct_UEnum_KawaiiPhysics_EPlanarConstraint, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlanarConstraint_MetaData), NewProp_PlanarConstraint_MetaData) }; // 462578191
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SkelCompMoveScale = { "SkelCompMoveScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, SkelCompMoveScale), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkelCompMoveScale_MetaData), NewProp_SkelCompMoveScale_MetaData) };
void Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUpdatePhysicsSettingsInGame_SetBit(void* Obj)
{
	((FAnimNode_KawaiiPhysics*)Obj)->bUpdatePhysicsSettingsInGame = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUpdatePhysicsSettingsInGame = { "bUpdatePhysicsSettingsInGame", nullptr, (EPropertyFlags)0x0010040000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAnimNode_KawaiiPhysics), &Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUpdatePhysicsSettingsInGame_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUpdatePhysicsSettingsInGame_MetaData), NewProp_bUpdatePhysicsSettingsInGame_MetaData) };
void Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_ResetBoneTransformWhenBoneNotFound_SetBit(void* Obj)
{
	((FAnimNode_KawaiiPhysics*)Obj)->ResetBoneTransformWhenBoneNotFound = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_ResetBoneTransformWhenBoneNotFound = { "ResetBoneTransformWhenBoneNotFound", nullptr, (EPropertyFlags)0x0010040000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAnimNode_KawaiiPhysics), &Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_ResetBoneTransformWhenBoneNotFound_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResetBoneTransformWhenBoneNotFound_MetaData), NewProp_ResetBoneTransformWhenBoneNotFound_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_DampingCurveData = { "DampingCurveData", nullptr, (EPropertyFlags)0x0010040000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, DampingCurveData), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DampingCurveData_MetaData), NewProp_DampingCurveData_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_StiffnessCurveData = { "StiffnessCurveData", nullptr, (EPropertyFlags)0x0010040000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, StiffnessCurveData), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StiffnessCurveData_MetaData), NewProp_StiffnessCurveData_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_WorldDampingLocationCurveData = { "WorldDampingLocationCurveData", nullptr, (EPropertyFlags)0x0010040000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, WorldDampingLocationCurveData), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldDampingLocationCurveData_MetaData), NewProp_WorldDampingLocationCurveData_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_WorldDampingRotationCurveData = { "WorldDampingRotationCurveData", nullptr, (EPropertyFlags)0x0010040000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, WorldDampingRotationCurveData), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldDampingRotationCurveData_MetaData), NewProp_WorldDampingRotationCurveData_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_RadiusCurveData = { "RadiusCurveData", nullptr, (EPropertyFlags)0x0010040000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, RadiusCurveData), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RadiusCurveData_MetaData), NewProp_RadiusCurveData_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_LimitAngleCurveData = { "LimitAngleCurveData", nullptr, (EPropertyFlags)0x0010040000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, LimitAngleCurveData), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LimitAngleCurveData_MetaData), NewProp_LimitAngleCurveData_MetaData) }; // 2560417949
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SphericalLimits_Inner = { "SphericalLimits", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FSphericalLimit, METADATA_PARAMS(0, nullptr) }; // 2652509308
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SphericalLimits = { "SphericalLimits", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, SphericalLimits), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SphericalLimits_MetaData), NewProp_SphericalLimits_MetaData) }; // 2652509308
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_CapsuleLimits_Inner = { "CapsuleLimits", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FCapsuleLimit, METADATA_PARAMS(0, nullptr) }; // 1186296507
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_CapsuleLimits = { "CapsuleLimits", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, CapsuleLimits), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CapsuleLimits_MetaData), NewProp_CapsuleLimits_MetaData) }; // 1186296507
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoxLimits_Inner = { "BoxLimits", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FBoxLimit, METADATA_PARAMS(0, nullptr) }; // 3222352506
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoxLimits = { "BoxLimits", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, BoxLimits), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoxLimits_MetaData), NewProp_BoxLimits_MetaData) }; // 3222352506
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_PlanarLimits_Inner = { "PlanarLimits", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FPlanarLimit, METADATA_PARAMS(0, nullptr) }; // 4101723162
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_PlanarLimits = { "PlanarLimits", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, PlanarLimits), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlanarLimits_MetaData), NewProp_PlanarLimits_MetaData) }; // 4101723162
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_LimitsDataAsset = { "LimitsDataAsset", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, LimitsDataAsset), Z_Construct_UClass_UKawaiiPhysicsLimitsDataAsset_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LimitsDataAsset_MetaData), NewProp_LimitsDataAsset_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_PhysicsAssetForLimits = { "PhysicsAssetForLimits", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, PhysicsAssetForLimits), Z_Construct_UClass_UPhysicsAsset_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PhysicsAssetForLimits_MetaData), NewProp_PhysicsAssetForLimits_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SphericalLimitsData_Inner = { "SphericalLimitsData", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FSphericalLimit, METADATA_PARAMS(0, nullptr) }; // 2652509308
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SphericalLimitsData = { "SphericalLimitsData", nullptr, (EPropertyFlags)0x0010040000022001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, SphericalLimitsData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SphericalLimitsData_MetaData), NewProp_SphericalLimitsData_MetaData) }; // 2652509308
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_CapsuleLimitsData_Inner = { "CapsuleLimitsData", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FCapsuleLimit, METADATA_PARAMS(0, nullptr) }; // 1186296507
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_CapsuleLimitsData = { "CapsuleLimitsData", nullptr, (EPropertyFlags)0x0010040000022001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, CapsuleLimitsData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CapsuleLimitsData_MetaData), NewProp_CapsuleLimitsData_MetaData) }; // 1186296507
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoxLimitsData_Inner = { "BoxLimitsData", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FBoxLimit, METADATA_PARAMS(0, nullptr) }; // 3222352506
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoxLimitsData = { "BoxLimitsData", nullptr, (EPropertyFlags)0x0010040000022001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, BoxLimitsData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoxLimitsData_MetaData), NewProp_BoxLimitsData_MetaData) }; // 3222352506
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_PlanarLimitsData_Inner = { "PlanarLimitsData", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FPlanarLimit, METADATA_PARAMS(0, nullptr) }; // 4101723162
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_PlanarLimitsData = { "PlanarLimitsData", nullptr, (EPropertyFlags)0x0010040000022001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, PlanarLimitsData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlanarLimitsData_MetaData), NewProp_PlanarLimitsData_MetaData) }; // 4101723162
void Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bSharedCollisionSource_SetBit(void* Obj)
{
	((FAnimNode_KawaiiPhysics*)Obj)->bSharedCollisionSource = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bSharedCollisionSource = { "bSharedCollisionSource", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAnimNode_KawaiiPhysics), &Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bSharedCollisionSource_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSharedCollisionSource_MetaData), NewProp_bSharedCollisionSource_MetaData) };
void Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseSharedCollision_SetBit(void* Obj)
{
	((FAnimNode_KawaiiPhysics*)Obj)->bUseSharedCollision = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseSharedCollision = { "bUseSharedCollision", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAnimNode_KawaiiPhysics), &Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseSharedCollision_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseSharedCollision_MetaData), NewProp_bUseSharedCollision_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SharedCollisionGroupTag = { "SharedCollisionGroupTag", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, SharedCollisionGroupTag), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SharedCollisionGroupTag_MetaData), NewProp_SharedCollisionGroupTag_MetaData) }; // 517357616
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintGlobalComplianceType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintGlobalComplianceType = { "BoneConstraintGlobalComplianceType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, BoneConstraintGlobalComplianceType), Z_Construct_UEnum_KawaiiPhysics_EXPBDComplianceType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoneConstraintGlobalComplianceType_MetaData), NewProp_BoneConstraintGlobalComplianceType_MetaData) }; // 676679353
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintIterationCountBeforeCollision = { "BoneConstraintIterationCountBeforeCollision", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, BoneConstraintIterationCountBeforeCollision), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoneConstraintIterationCountBeforeCollision_MetaData), NewProp_BoneConstraintIterationCountBeforeCollision_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintIterationCountAfterCollision = { "BoneConstraintIterationCountAfterCollision", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, BoneConstraintIterationCountAfterCollision), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoneConstraintIterationCountAfterCollision_MetaData), NewProp_BoneConstraintIterationCountAfterCollision_MetaData) };
void Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bAutoAddChildDummyBoneConstraint_SetBit(void* Obj)
{
	((FAnimNode_KawaiiPhysics*)Obj)->bAutoAddChildDummyBoneConstraint = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bAutoAddChildDummyBoneConstraint = { "bAutoAddChildDummyBoneConstraint", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAnimNode_KawaiiPhysics), &Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bAutoAddChildDummyBoneConstraint_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutoAddChildDummyBoneConstraint_MetaData), NewProp_bAutoAddChildDummyBoneConstraint_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraints_Inner = { "BoneConstraints", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FModifyBoneConstraint, METADATA_PARAMS(0, nullptr) }; // 1109661521
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraints = { "BoneConstraints", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, BoneConstraints), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoneConstraints_MetaData), NewProp_BoneConstraints_MetaData) }; // 1109661521
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintsDataAsset = { "BoneConstraintsDataAsset", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, BoneConstraintsDataAsset), Z_Construct_UClass_UKawaiiPhysicsBoneConstraintsDataAsset_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoneConstraintsDataAsset_MetaData), NewProp_BoneConstraintsDataAsset_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintsData_Inner = { "BoneConstraintsData", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FModifyBoneConstraint, METADATA_PARAMS(0, nullptr) }; // 1109661521
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintsData = { "BoneConstraintsData", nullptr, (EPropertyFlags)0x0010040000022001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, BoneConstraintsData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoneConstraintsData_MetaData), NewProp_BoneConstraintsData_MetaData) }; // 1109661521
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_MergedBoneConstraints_Inner = { "MergedBoneConstraints", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FModifyBoneConstraint, METADATA_PARAMS(0, nullptr) }; // 1109661521
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_MergedBoneConstraints = { "MergedBoneConstraints", nullptr, (EPropertyFlags)0x0010000000002000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, MergedBoneConstraints), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MergedBoneConstraints_MetaData), NewProp_MergedBoneConstraints_MetaData) }; // 1109661521
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SyncBones_Inner = { "SyncBones", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone, METADATA_PARAMS(0, nullptr) }; // 1044275891
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SyncBones = { "SyncBones", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, SyncBones), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SyncBones_MetaData), NewProp_SyncBones_MetaData) }; // 1044275891
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_Gravity = { "Gravity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, Gravity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Gravity_MetaData), NewProp_Gravity_MetaData) };
void Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseLegacyGravity_SetBit(void* Obj)
{
	((FAnimNode_KawaiiPhysics*)Obj)->bUseLegacyGravity = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseLegacyGravity = { "bUseLegacyGravity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAnimNode_KawaiiPhysics), &Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseLegacyGravity_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseLegacyGravity_MetaData), NewProp_bUseLegacyGravity_MetaData) };
void Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseDefaultGravityZProjectSetting_SetBit(void* Obj)
{
	((FAnimNode_KawaiiPhysics*)Obj)->bUseDefaultGravityZProjectSetting = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseDefaultGravityZProjectSetting = { "bUseDefaultGravityZProjectSetting", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAnimNode_KawaiiPhysics), &Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseDefaultGravityZProjectSetting_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseDefaultGravityZProjectSetting_MetaData), NewProp_bUseDefaultGravityZProjectSetting_MetaData) };
void Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseWorldSpaceGravity_SetBit(void* Obj)
{
	((FAnimNode_KawaiiPhysics*)Obj)->bUseWorldSpaceGravity = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseWorldSpaceGravity = { "bUseWorldSpaceGravity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAnimNode_KawaiiPhysics), &Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseWorldSpaceGravity_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseWorldSpaceGravity_MetaData), NewProp_bUseWorldSpaceGravity_MetaData) };
void Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bEnableWind_SetBit(void* Obj)
{
	((FAnimNode_KawaiiPhysics*)Obj)->bEnableWind = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bEnableWind = { "bEnableWind", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAnimNode_KawaiiPhysics), &Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bEnableWind_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableWind_MetaData), NewProp_bEnableWind_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_WindScale = { "WindScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, WindScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WindScale_MetaData), NewProp_WindScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_WindDirectionNoiseAngle = { "WindDirectionNoiseAngle", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, WindDirectionNoiseAngle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WindDirectionNoiseAngle_MetaData), NewProp_WindDirectionNoiseAngle_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SimpleExternalForce = { "SimpleExternalForce", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, SimpleExternalForce), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SimpleExternalForce_MetaData), NewProp_SimpleExternalForce_MetaData) };
void Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseWorldSpaceSimpleExternalForce_SetBit(void* Obj)
{
	((FAnimNode_KawaiiPhysics*)Obj)->bUseWorldSpaceSimpleExternalForce = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseWorldSpaceSimpleExternalForce = { "bUseWorldSpaceSimpleExternalForce", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAnimNode_KawaiiPhysics), &Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseWorldSpaceSimpleExternalForce_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseWorldSpaceSimpleExternalForce_MetaData), NewProp_bUseWorldSpaceSimpleExternalForce_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_ExternalForces_Inner = { "ExternalForces", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FInstancedStruct, METADATA_PARAMS(0, nullptr) }; // 3949785911
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_ExternalForces = { "ExternalForces", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, ExternalForces), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExternalForces_MetaData), NewProp_ExternalForces_MetaData) }; // 3949785911
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_CustomExternalForces_Inner = { "CustomExternalForces", nullptr, (EPropertyFlags)0x0106000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CustomExternalForces_Inner_MetaData), NewProp_CustomExternalForces_Inner_MetaData) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_CustomExternalForces = { "CustomExternalForces", nullptr, (EPropertyFlags)0x011400800000000d, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, CustomExternalForces), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CustomExternalForces_MetaData), NewProp_CustomExternalForces_MetaData) };
void Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bAllowWorldCollision_SetBit(void* Obj)
{
	((FAnimNode_KawaiiPhysics*)Obj)->bAllowWorldCollision = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bAllowWorldCollision = { "bAllowWorldCollision", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAnimNode_KawaiiPhysics), &Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bAllowWorldCollision_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAllowWorldCollision_MetaData), NewProp_bAllowWorldCollision_MetaData) };
void Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bOverrideCollisionParams_SetBit(void* Obj)
{
	((FAnimNode_KawaiiPhysics*)Obj)->bOverrideCollisionParams = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bOverrideCollisionParams = { "bOverrideCollisionParams", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAnimNode_KawaiiPhysics), &Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bOverrideCollisionParams_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bOverrideCollisionParams_MetaData), NewProp_bOverrideCollisionParams_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_CollisionChannelSettings = { "CollisionChannelSettings", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, CollisionChannelSettings), Z_Construct_UScriptStruct_FBodyInstance, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionChannelSettings_MetaData), NewProp_CollisionChannelSettings_MetaData) }; // 1979150459
void Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bIgnoreSelfComponent_SetBit(void* Obj)
{
	((FAnimNode_KawaiiPhysics*)Obj)->bIgnoreSelfComponent = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bIgnoreSelfComponent = { "bIgnoreSelfComponent", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAnimNode_KawaiiPhysics), &Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bIgnoreSelfComponent_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIgnoreSelfComponent_MetaData), NewProp_bIgnoreSelfComponent_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_IgnoreBones_Inner = { "IgnoreBones", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(0, nullptr) }; // 1102615820
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_IgnoreBones = { "IgnoreBones", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, IgnoreBones), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IgnoreBones_MetaData), NewProp_IgnoreBones_MetaData) }; // 1102615820
const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_IgnoreBoneNamePrefix_Inner = { "IgnoreBoneNamePrefix", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_IgnoreBoneNamePrefix = { "IgnoreBoneNamePrefix", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, IgnoreBoneNamePrefix), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IgnoreBoneNamePrefix_MetaData), NewProp_IgnoreBoneNamePrefix_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_KawaiiPhysicsTag = { "KawaiiPhysicsTag", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, KawaiiPhysicsTag), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_KawaiiPhysicsTag_MetaData), NewProp_KawaiiPhysicsTag_MetaData) }; // 517357616
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_ModifyBones_Inner = { "ModifyBones", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone, METADATA_PARAMS(0, nullptr) }; // 1078151775
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_ModifyBones = { "ModifyBones", nullptr, (EPropertyFlags)0x0010000000002004, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, ModifyBones), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ModifyBones_MetaData), NewProp_ModifyBones_MetaData) }; // 1078151775
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_DeltaTime = { "DeltaTime", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_KawaiiPhysics, DeltaTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeltaTime_MetaData), NewProp_DeltaTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_RootBone,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_ExcludeBones_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_ExcludeBones,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_AdditionalRootBones_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_AdditionalRootBones,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_DummyBoneLength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneSubdivisionCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bBoneSubdivisionCollisionOnly,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bBoneSubdivisionDensifyByRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintSubdivisionCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintSubdivisionFeedbackScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneForwardAxis_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneForwardAxis,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_PhysicsSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SimulationSpace_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SimulationSpace,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SimulationBaseBone,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_TargetFramerate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_WarmUpFrames,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseWarmUpWhenResetDynamics,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bNeedWarmUp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_TeleportDistanceThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_TeleportRotationThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_PlanarConstraint_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_PlanarConstraint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SkelCompMoveScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUpdatePhysicsSettingsInGame,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_ResetBoneTransformWhenBoneNotFound,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_DampingCurveData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_StiffnessCurveData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_WorldDampingLocationCurveData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_WorldDampingRotationCurveData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_RadiusCurveData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_LimitAngleCurveData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SphericalLimits_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SphericalLimits,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_CapsuleLimits_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_CapsuleLimits,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoxLimits_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoxLimits,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_PlanarLimits_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_PlanarLimits,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_LimitsDataAsset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_PhysicsAssetForLimits,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SphericalLimitsData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SphericalLimitsData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_CapsuleLimitsData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_CapsuleLimitsData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoxLimitsData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoxLimitsData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_PlanarLimitsData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_PlanarLimitsData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bSharedCollisionSource,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseSharedCollision,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SharedCollisionGroupTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintGlobalComplianceType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintGlobalComplianceType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintIterationCountBeforeCollision,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintIterationCountAfterCollision,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bAutoAddChildDummyBoneConstraint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraints_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraints,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintsDataAsset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintsData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_BoneConstraintsData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_MergedBoneConstraints_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_MergedBoneConstraints,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SyncBones_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SyncBones,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_Gravity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseLegacyGravity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseDefaultGravityZProjectSetting,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseWorldSpaceGravity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bEnableWind,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_WindScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_WindDirectionNoiseAngle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_SimpleExternalForce,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bUseWorldSpaceSimpleExternalForce,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_ExternalForces_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_ExternalForces,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_CustomExternalForces_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_CustomExternalForces,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bAllowWorldCollision,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bOverrideCollisionParams,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_CollisionChannelSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_bIgnoreSelfComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_IgnoreBones_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_IgnoreBones,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_IgnoreBoneNamePrefix_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_IgnoreBoneNamePrefix,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_KawaiiPhysicsTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_ModifyBones_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_ModifyBones,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewProp_DeltaTime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FAnimNode_KawaiiPhysics Property Definitions ************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	Z_Construct_UScriptStruct_FAnimNode_SkeletalControlBase,
	&NewStructOps,
	"AnimNode_KawaiiPhysics",
	Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::PropPointers),
	sizeof(FAnimNode_KawaiiPhysics),
	alignof(FAnimNode_KawaiiPhysics),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000205),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics()
{
	if (!Z_Registration_Info_UScriptStruct_FAnimNode_KawaiiPhysics.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FAnimNode_KawaiiPhysics.InnerSingleton, Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FAnimNode_KawaiiPhysics.InnerSingleton);
}
// ********** End ScriptStruct FAnimNode_KawaiiPhysics *********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_AnimNode_KawaiiPhysics_h__Script_KawaiiPhysics_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FAnimNode_KawaiiPhysics::StaticStruct, Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics_Statics::NewStructOps, TEXT("AnimNode_KawaiiPhysics"),&Z_Registration_Info_UScriptStruct_FAnimNode_KawaiiPhysics, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FAnimNode_KawaiiPhysics), 3752603673U) },
	};
}; // Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_AnimNode_KawaiiPhysics_h__Script_KawaiiPhysics_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_AnimNode_KawaiiPhysics_h__Script_KawaiiPhysics_1734792888{
	TEXT("/Script/KawaiiPhysics"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_AnimNode_KawaiiPhysics_h__Script_KawaiiPhysics_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_AnimNode_KawaiiPhysics_h__Script_KawaiiPhysics_Statics::ScriptStructInfo),
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
