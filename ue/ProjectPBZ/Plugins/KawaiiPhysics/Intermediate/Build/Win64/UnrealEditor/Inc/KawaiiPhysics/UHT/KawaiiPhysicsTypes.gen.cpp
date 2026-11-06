// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "KawaiiPhysicsTypes.h"
#include "Animation/BoneReference.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeKawaiiPhysicsTypes() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FQuat();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FBoneReference();
KAWAIIPHYSICS_API UEnum* Z_Construct_UEnum_KawaiiPhysics_EBoneForwardAxis();
KAWAIIPHYSICS_API UEnum* Z_Construct_UEnum_KawaiiPhysics_EKawaiiPhysicsSimulationSpace();
KAWAIIPHYSICS_API UEnum* Z_Construct_UEnum_KawaiiPhysics_EPlanarConstraint();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FKawaiiPhysicsSettings();
UPackage* Z_Construct_UPackage__Script_KawaiiPhysics();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EKawaiiPhysicsSimulationSpace *********************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EKawaiiPhysicsSimulationSpace;
static UEnum* EKawaiiPhysicsSimulationSpace_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EKawaiiPhysicsSimulationSpace.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EKawaiiPhysicsSimulationSpace.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_KawaiiPhysics_EKawaiiPhysicsSimulationSpace, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("EKawaiiPhysicsSimulationSpace"));
	}
	return Z_Registration_Info_UEnum_EKawaiiPhysicsSimulationSpace.OuterSingleton;
}
template<> KAWAIIPHYSICS_NON_ATTRIBUTED_API UEnum* StaticEnum<EKawaiiPhysicsSimulationSpace>()
{
	return EKawaiiPhysicsSimulationSpace_StaticEnum();
}
struct Z_Construct_UEnum_KawaiiPhysics_EKawaiiPhysicsSimulationSpace_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BaseBoneSpace.Comment", "/** Simulate in another bone space */" },
		{ "BaseBoneSpace.Name", "EKawaiiPhysicsSimulationSpace::BaseBoneSpace" },
		{ "BaseBoneSpace.ToolTip", "Simulate in another bone space" },
		{ "BlueprintType", "true" },
		{ "ComponentSpace.Comment", "/** Simulate in component space */" },
		{ "ComponentSpace.Name", "EKawaiiPhysicsSimulationSpace::ComponentSpace" },
		{ "ComponentSpace.ToolTip", "Simulate in component space" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
		{ "WorldSpace.Comment", "/** Simulate in world space. This fixes the issues of root bones moving suddenly */" },
		{ "WorldSpace.Name", "EKawaiiPhysicsSimulationSpace::WorldSpace" },
		{ "WorldSpace.ToolTip", "Simulate in world space. This fixes the issues of root bones moving suddenly" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EKawaiiPhysicsSimulationSpace::ComponentSpace", (int64)EKawaiiPhysicsSimulationSpace::ComponentSpace },
		{ "EKawaiiPhysicsSimulationSpace::WorldSpace", (int64)EKawaiiPhysicsSimulationSpace::WorldSpace },
		{ "EKawaiiPhysicsSimulationSpace::BaseBoneSpace", (int64)EKawaiiPhysicsSimulationSpace::BaseBoneSpace },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_KawaiiPhysics_EKawaiiPhysicsSimulationSpace_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_KawaiiPhysics_EKawaiiPhysicsSimulationSpace_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	nullptr,
	"EKawaiiPhysicsSimulationSpace",
	"EKawaiiPhysicsSimulationSpace",
	Z_Construct_UEnum_KawaiiPhysics_EKawaiiPhysicsSimulationSpace_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_KawaiiPhysics_EKawaiiPhysicsSimulationSpace_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_KawaiiPhysics_EKawaiiPhysicsSimulationSpace_Statics::Enum_MetaDataParams), Z_Construct_UEnum_KawaiiPhysics_EKawaiiPhysicsSimulationSpace_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_KawaiiPhysics_EKawaiiPhysicsSimulationSpace()
{
	if (!Z_Registration_Info_UEnum_EKawaiiPhysicsSimulationSpace.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EKawaiiPhysicsSimulationSpace.InnerSingleton, Z_Construct_UEnum_KawaiiPhysics_EKawaiiPhysicsSimulationSpace_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EKawaiiPhysicsSimulationSpace.InnerSingleton;
}
// ********** End Enum EKawaiiPhysicsSimulationSpace ***********************************************

// ********** Begin Enum EPlanarConstraint *********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EPlanarConstraint;
static UEnum* EPlanarConstraint_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EPlanarConstraint.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EPlanarConstraint.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_KawaiiPhysics_EPlanarConstraint, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("EPlanarConstraint"));
	}
	return Z_Registration_Info_UEnum_EPlanarConstraint.OuterSingleton;
}
template<> KAWAIIPHYSICS_NON_ATTRIBUTED_API UEnum* StaticEnum<EPlanarConstraint>()
{
	return EPlanarConstraint_StaticEnum();
}
struct Z_Construct_UEnum_KawaiiPhysics_EPlanarConstraint_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Enum representing the planar constraint axis in KawaiiPhysics.\n */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
		{ "None.Comment", "/** No planar constraint */" },
		{ "None.Name", "EPlanarConstraint::None" },
		{ "None.ToolTip", "No planar constraint" },
		{ "ScriptName", "KP_PlanarConstraint" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Enum representing the planar constraint axis in KawaiiPhysics." },
#endif
		{ "X.Comment", "/** Constrain to the X axis */" },
		{ "X.Name", "EPlanarConstraint::X" },
		{ "X.ToolTip", "Constrain to the X axis" },
		{ "Y.Comment", "/** Constrain to the Y axis */" },
		{ "Y.Name", "EPlanarConstraint::Y" },
		{ "Y.ToolTip", "Constrain to the Y axis" },
		{ "Z.Comment", "/** Constrain to the Z axis */" },
		{ "Z.Name", "EPlanarConstraint::Z" },
		{ "Z.ToolTip", "Constrain to the Z axis" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EPlanarConstraint::None", (int64)EPlanarConstraint::None },
		{ "EPlanarConstraint::X", (int64)EPlanarConstraint::X },
		{ "EPlanarConstraint::Y", (int64)EPlanarConstraint::Y },
		{ "EPlanarConstraint::Z", (int64)EPlanarConstraint::Z },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_KawaiiPhysics_EPlanarConstraint_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_KawaiiPhysics_EPlanarConstraint_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	nullptr,
	"EPlanarConstraint",
	"EPlanarConstraint",
	Z_Construct_UEnum_KawaiiPhysics_EPlanarConstraint_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_KawaiiPhysics_EPlanarConstraint_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_KawaiiPhysics_EPlanarConstraint_Statics::Enum_MetaDataParams), Z_Construct_UEnum_KawaiiPhysics_EPlanarConstraint_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_KawaiiPhysics_EPlanarConstraint()
{
	if (!Z_Registration_Info_UEnum_EPlanarConstraint.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EPlanarConstraint.InnerSingleton, Z_Construct_UEnum_KawaiiPhysics_EPlanarConstraint_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EPlanarConstraint.InnerSingleton;
}
// ********** End Enum EPlanarConstraint ***********************************************************

// ********** Begin Enum EBoneForwardAxis **********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EBoneForwardAxis;
static UEnum* EBoneForwardAxis_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EBoneForwardAxis.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EBoneForwardAxis.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_KawaiiPhysics_EBoneForwardAxis, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("EBoneForwardAxis"));
	}
	return Z_Registration_Info_UEnum_EBoneForwardAxis.OuterSingleton;
}
template<> KAWAIIPHYSICS_NON_ATTRIBUTED_API UEnum* StaticEnum<EBoneForwardAxis>()
{
	return EBoneForwardAxis_StaticEnum();
}
struct Z_Construct_UEnum_KawaiiPhysics_EBoneForwardAxis_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Enum representing the forward axis of a bone in KawaiiPhysics.\n */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Enum representing the forward axis of a bone in KawaiiPhysics." },
#endif
		{ "X_Negative.Name", "EBoneForwardAxis::X_Negative" },
		{ "X_Positive.Name", "EBoneForwardAxis::X_Positive" },
		{ "Y_Negative.Name", "EBoneForwardAxis::Y_Negative" },
		{ "Y_Positive.Name", "EBoneForwardAxis::Y_Positive" },
		{ "Z_Negative.Name", "EBoneForwardAxis::Z_Negative" },
		{ "Z_Positive.Name", "EBoneForwardAxis::Z_Positive" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EBoneForwardAxis::X_Positive", (int64)EBoneForwardAxis::X_Positive },
		{ "EBoneForwardAxis::X_Negative", (int64)EBoneForwardAxis::X_Negative },
		{ "EBoneForwardAxis::Y_Positive", (int64)EBoneForwardAxis::Y_Positive },
		{ "EBoneForwardAxis::Y_Negative", (int64)EBoneForwardAxis::Y_Negative },
		{ "EBoneForwardAxis::Z_Positive", (int64)EBoneForwardAxis::Z_Positive },
		{ "EBoneForwardAxis::Z_Negative", (int64)EBoneForwardAxis::Z_Negative },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_KawaiiPhysics_EBoneForwardAxis_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_KawaiiPhysics_EBoneForwardAxis_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	nullptr,
	"EBoneForwardAxis",
	"EBoneForwardAxis",
	Z_Construct_UEnum_KawaiiPhysics_EBoneForwardAxis_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_KawaiiPhysics_EBoneForwardAxis_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_KawaiiPhysics_EBoneForwardAxis_Statics::Enum_MetaDataParams), Z_Construct_UEnum_KawaiiPhysics_EBoneForwardAxis_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_KawaiiPhysics_EBoneForwardAxis()
{
	if (!Z_Registration_Info_UEnum_EBoneForwardAxis.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EBoneForwardAxis.InnerSingleton, Z_Construct_UEnum_KawaiiPhysics_EBoneForwardAxis_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EBoneForwardAxis.InnerSingleton;
}
// ********** End Enum EBoneForwardAxis ************************************************************

// ********** Begin ScriptStruct FKawaiiPhysicsRootBoneSetting *************************************
struct Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FKawaiiPhysicsRootBoneSetting); }
	static inline consteval int16 GetStructAlignment() { return alignof(FKawaiiPhysicsRootBoneSetting); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Structure representing the root bone settings for KawaiiPhysics.\n */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Structure representing the root bone settings for KawaiiPhysics." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RootBone_MetaData[] = {
		{ "Category", "Bones" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe6\x8c\x87\xe5\xae\x9a\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xa8\xe3\x81\x9d\xe3\x82\x8c\xe4\xbb\xa5\xe4\xb8\x8b\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe5\x88\xb6\xe5\xbe\xa1\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xab\n\x09* Control the specified bone and the bones below it\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x8c\x87\xe5\xae\x9a\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xa8\xe3\x81\x9d\xe3\x82\x8c\xe4\xbb\xa5\xe4\xb8\x8b\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe5\x88\xb6\xe5\xbe\xa1\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xab\nControl the specified bone and the bones below it" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OverrideExcludeBones_MetaData[] = {
		{ "Category", "Bones" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe6\x8c\x87\xe5\xae\x9a\xe3\x81\x97\xe3\x81\x9f\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xa8\xe3\x81\x9d\xe3\x82\x8c\xe4\xbb\xa5\xe4\xb8\x8b\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe5\x88\xb6\xe5\xbe\xa1\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\x8b\xe3\x82\x89\xe9\x99\xa4\xe5\x8e\xbb\n\x09* Do NOT control the specified bone and the bones below it\n\x09*/" },
#endif
		{ "EditCondition", "bUseOverrideExcludeBones" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x8c\x87\xe5\xae\x9a\xe3\x81\x97\xe3\x81\x9f\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xa8\xe3\x81\x9d\xe3\x82\x8c\xe4\xbb\xa5\xe4\xb8\x8b\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x92\xe5\x88\xb6\xe5\xbe\xa1\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\x8b\xe3\x82\x89\xe9\x99\xa4\xe5\x8e\xbb\nDo NOT control the specified bone and the bones below it" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseOverrideExcludeBones_MetaData[] = {
		{ "Category", "Bones" },
		{ "InlineEditConditionToggle", "" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FKawaiiPhysicsRootBoneSetting constinit property declarations *****
	static const UECodeGen_Private::FStructPropertyParams NewProp_RootBone;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OverrideExcludeBones_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OverrideExcludeBones;
	static void NewProp_bUseOverrideExcludeBones_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseOverrideExcludeBones;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FKawaiiPhysicsRootBoneSetting constinit property declarations *******
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FKawaiiPhysicsRootBoneSetting>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FKawaiiPhysicsRootBoneSetting;
class UScriptStruct* FKawaiiPhysicsRootBoneSetting::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FKawaiiPhysicsRootBoneSetting.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FKawaiiPhysicsRootBoneSetting.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("KawaiiPhysicsRootBoneSetting"));
	}
	return Z_Registration_Info_UScriptStruct_FKawaiiPhysicsRootBoneSetting.OuterSingleton;
	}

// ********** Begin ScriptStruct FKawaiiPhysicsRootBoneSetting Property Definitions ****************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::NewProp_RootBone = { "RootBone", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsRootBoneSetting, RootBone), Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RootBone_MetaData), NewProp_RootBone_MetaData) }; // 1102615820
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::NewProp_OverrideExcludeBones_Inner = { "OverrideExcludeBones", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(0, nullptr) }; // 1102615820
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::NewProp_OverrideExcludeBones = { "OverrideExcludeBones", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsRootBoneSetting, OverrideExcludeBones), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OverrideExcludeBones_MetaData), NewProp_OverrideExcludeBones_MetaData) }; // 1102615820
void Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::NewProp_bUseOverrideExcludeBones_SetBit(void* Obj)
{
	((FKawaiiPhysicsRootBoneSetting*)Obj)->bUseOverrideExcludeBones = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::NewProp_bUseOverrideExcludeBones = { "bUseOverrideExcludeBones", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FKawaiiPhysicsRootBoneSetting), &Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::NewProp_bUseOverrideExcludeBones_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseOverrideExcludeBones_MetaData), NewProp_bUseOverrideExcludeBones_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::NewProp_RootBone,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::NewProp_OverrideExcludeBones_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::NewProp_OverrideExcludeBones,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::NewProp_bUseOverrideExcludeBones,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FKawaiiPhysicsRootBoneSetting Property Definitions ******************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	nullptr,
	&NewStructOps,
	"KawaiiPhysicsRootBoneSetting",
	Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::PropPointers),
	sizeof(FKawaiiPhysicsRootBoneSetting),
	alignof(FKawaiiPhysicsRootBoneSetting),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting()
{
	if (!Z_Registration_Info_UScriptStruct_FKawaiiPhysicsRootBoneSetting.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FKawaiiPhysicsRootBoneSetting.InnerSingleton, Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FKawaiiPhysicsRootBoneSetting.InnerSingleton);
}
// ********** End ScriptStruct FKawaiiPhysicsRootBoneSetting ***************************************

// ********** Begin ScriptStruct FKawaiiPhysicsSettings ********************************************
struct Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FKawaiiPhysicsSettings); }
	static inline consteval int16 GetStructAlignment() { return alignof(FKawaiiPhysicsSettings); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Structure representing the settings for KawaiiPhysics.\n */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Structure representing the settings for KawaiiPhysics." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Damping_MetaData[] = {
		{ "Category", "KawaiiPhysics" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe6\xb8\x9b\xe8\xa1\xb0\xe5\xba\xa6\xef\xbc\x9a\xe6\x8f\xba\xe3\x82\x8c\xe3\x81\xae\xe5\xbc\xb7\xe3\x81\x95\xe3\x82\x92\xe5\x88\xb6\xe5\xbe\xa1\xe3\x80\x82\xe5\x80\xa4\xe3\x81\x8c\xe5\xb0\x8f\xe3\x81\x95\xe3\x81\x84\xe3\x81\xbb\xe3\x81\xa9\xe3\x80\x81\xe5\x8a\xa0\xe9\x80\x9f\xe5\xba\xa6\xe3\x82\x92\xe7\x89\xa9\xe7\x90\x86\xe6\x8c\x99\xe5\x8b\x95\xe3\x81\xab\xe5\x8f\x8d\xe6\x98\xa0\n\x09* Damping physical behavior. As the value is smaller, the acceleration is more reflected to the physical behavior\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xb8\x9b\xe8\xa1\xb0\xe5\xba\xa6\xef\xbc\x9a\xe6\x8f\xba\xe3\x82\x8c\xe3\x81\xae\xe5\xbc\xb7\xe3\x81\x95\xe3\x82\x92\xe5\x88\xb6\xe5\xbe\xa1\xe3\x80\x82\xe5\x80\xa4\xe3\x81\x8c\xe5\xb0\x8f\xe3\x81\x95\xe3\x81\x84\xe3\x81\xbb\xe3\x81\xa9\xe3\x80\x81\xe5\x8a\xa0\xe9\x80\x9f\xe5\xba\xa6\xe3\x82\x92\xe7\x89\xa9\xe7\x90\x86\xe6\x8c\x99\xe5\x8b\x95\xe3\x81\xab\xe5\x8f\x8d\xe6\x98\xa0\nDamping physical behavior. As the value is smaller, the acceleration is more reflected to the physical behavior" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Stiffness_MetaData[] = {
		{ "Category", "KawaiiPhysics" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe5\x89\x9b\xe6\x80\xa7\xe5\xba\xa6\xef\xbc\x9a\xe5\x80\xa4\xe3\x81\x8c\xe5\xa4\xa7\xe3\x81\x8d\xe3\x81\x84\xe3\x81\xbb\xe3\x81\xa9\xe3\x80\x81\xe5\x85\x83\xe3\x81\xae\xe5\xbd\xa2\xe7\x8a\xb6\xe3\x82\x92\xe7\xb6\xad\xe6\x8c\x81\n\x09* Stiffness of physical behavior. As the value is larger, pre-physics shape is more respected\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x89\x9b\xe6\x80\xa7\xe5\xba\xa6\xef\xbc\x9a\xe5\x80\xa4\xe3\x81\x8c\xe5\xa4\xa7\xe3\x81\x8d\xe3\x81\x84\xe3\x81\xbb\xe3\x81\xa9\xe3\x80\x81\xe5\x85\x83\xe3\x81\xae\xe5\xbd\xa2\xe7\x8a\xb6\xe3\x82\x92\xe7\xb6\xad\xe6\x8c\x81\nStiffness of physical behavior. As the value is larger, pre-physics shape is more respected" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldDampingLocation_MetaData[] = {
		{ "Category", "KawaiiPhysics" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* \xe3\x83\xaf\xe3\x83\xbc\xe3\x83\xab\xe3\x83\x89\xe5\xba\xa7\xe6\xa8\x99\xe7\xb3\xbb\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b Skeletal Mesh Component \xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe9\x87\x8f\xe3\x81\xae\xe3\x83\x80\xe3\x83\xb3\xe3\x83\x94\xe3\x83\xb3\xe3\x82\xb0(\xe6\x8a\x91\xe5\x88\xb6)\xe9\x87\x8f\xe3\x80\x82\n\x09* 0 = \xe7\xa7\xbb\xe5\x8b\x95\xe9\x87\x8f\xe3\x82\x92\xe3\x83\x95\xe3\x83\xab\xe5\x8f\x8d\xe6\x98\xa0(\xe6\x8f\xba\xe3\x82\x8c\xe6\x9c\x80\xe5\xa4\xa7) / 1 = \xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xab\xe8\xbf\xbd\xe5\xbe\x93(\xe5\x8f\x8d\xe6\x98\xa0\xe3\x81\xaa\xe3\x81\x97)\xe3\x80\x82\xe5\xae\x9f\xe9\x9a\x9b\xe3\x81\xae\xe5\x8f\x8d\xe6\x98\xa0\xe7\x8e\x87 = (1 - WorldDampingLocation)\n\x09* Damping (suppression) of the Skeletal Mesh Component's world-space movement.\n\x09* 0 = movement fully reflected (max sway) / 1 = follows component (no reflection). Actual reflection factor = (1 - WorldDampingLocation).\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x83\xaf\xe3\x83\xbc\xe3\x83\xab\xe3\x83\x89\xe5\xba\xa7\xe6\xa8\x99\xe7\xb3\xbb\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b Skeletal Mesh Component \xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe9\x87\x8f\xe3\x81\xae\xe3\x83\x80\xe3\x83\xb3\xe3\x83\x94\xe3\x83\xb3\xe3\x82\xb0(\xe6\x8a\x91\xe5\x88\xb6)\xe9\x87\x8f\xe3\x80\x82\n0 = \xe7\xa7\xbb\xe5\x8b\x95\xe9\x87\x8f\xe3\x82\x92\xe3\x83\x95\xe3\x83\xab\xe5\x8f\x8d\xe6\x98\xa0(\xe6\x8f\xba\xe3\x82\x8c\xe6\x9c\x80\xe5\xa4\xa7) / 1 = \xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xab\xe8\xbf\xbd\xe5\xbe\x93(\xe5\x8f\x8d\xe6\x98\xa0\xe3\x81\xaa\xe3\x81\x97)\xe3\x80\x82\xe5\xae\x9f\xe9\x9a\x9b\xe3\x81\xae\xe5\x8f\x8d\xe6\x98\xa0\xe7\x8e\x87 = (1 - WorldDampingLocation)\nDamping (suppression) of the Skeletal Mesh Component's world-space movement.\n0 = movement fully reflected (max sway) / 1 = follows component (no reflection). Actual reflection factor = (1 - WorldDampingLocation)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldDampingRotation_MetaData[] = {
		{ "Category", "KawaiiPhysics" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* \xe3\x83\xaf\xe3\x83\xbc\xe3\x83\xab\xe3\x83\x89\xe5\xba\xa7\xe6\xa8\x99\xe7\xb3\xbb\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b Skeletal Mesh Component \xe3\x81\xae\xe5\x9b\x9e\xe8\xbb\xa2\xe9\x87\x8f\xe3\x81\xae\xe3\x83\x80\xe3\x83\xb3\xe3\x83\x94\xe3\x83\xb3\xe3\x82\xb0(\xe6\x8a\x91\xe5\x88\xb6)\xe9\x87\x8f\xe3\x80\x82\n\x09* 0 = \xe5\x9b\x9e\xe8\xbb\xa2\xe9\x87\x8f\xe3\x82\x92\xe3\x83\x95\xe3\x83\xab\xe5\x8f\x8d\xe6\x98\xa0(\xe6\x8f\xba\xe3\x82\x8c\xe6\x9c\x80\xe5\xa4\xa7) / 1 = \xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xab\xe8\xbf\xbd\xe5\xbe\x93(\xe5\x8f\x8d\xe6\x98\xa0\xe3\x81\xaa\xe3\x81\x97)\xe3\x80\x82\xe5\xae\x9f\xe9\x9a\x9b\xe3\x81\xae\xe5\x8f\x8d\xe6\x98\xa0\xe7\x8e\x87 = (1 - WorldDampingRotation)\n\x09* Damping (suppression) of the Skeletal Mesh Component's world-space rotation.\n\x09* 0 = rotation fully reflected (max sway) / 1 = follows component (no reflection). Actual reflection factor = (1 - WorldDampingRotation).\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x83\xaf\xe3\x83\xbc\xe3\x83\xab\xe3\x83\x89\xe5\xba\xa7\xe6\xa8\x99\xe7\xb3\xbb\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8b Skeletal Mesh Component \xe3\x81\xae\xe5\x9b\x9e\xe8\xbb\xa2\xe9\x87\x8f\xe3\x81\xae\xe3\x83\x80\xe3\x83\xb3\xe3\x83\x94\xe3\x83\xb3\xe3\x82\xb0(\xe6\x8a\x91\xe5\x88\xb6)\xe9\x87\x8f\xe3\x80\x82\n0 = \xe5\x9b\x9e\xe8\xbb\xa2\xe9\x87\x8f\xe3\x82\x92\xe3\x83\x95\xe3\x83\xab\xe5\x8f\x8d\xe6\x98\xa0(\xe6\x8f\xba\xe3\x82\x8c\xe6\x9c\x80\xe5\xa4\xa7) / 1 = \xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xab\xe8\xbf\xbd\xe5\xbe\x93(\xe5\x8f\x8d\xe6\x98\xa0\xe3\x81\xaa\xe3\x81\x97)\xe3\x80\x82\xe5\xae\x9f\xe9\x9a\x9b\xe3\x81\xae\xe5\x8f\x8d\xe6\x98\xa0\xe7\x8e\x87 = (1 - WorldDampingRotation)\nDamping (suppression) of the Skeletal Mesh Component's world-space rotation.\n0 = rotation fully reflected (max sway) / 1 = follows component (no reflection). Actual reflection factor = (1 - WorldDampingRotation)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Radius_MetaData[] = {
		{ "Category", "KawaiiPhysics" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe5\x8d\x8a\xe5\xbe\x84\n\x09* Radius of bone's collision\n\x09*/" },
#endif
		{ "DisplayName", "Collision Radius" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x90\x84\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe5\x8d\x8a\xe5\xbe\x84\nRadius of bone's collision" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LimitAngle_MetaData[] = {
		{ "Category", "KawaiiPhysics" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \n\x09* \xe7\x89\xa9\xe7\x90\x86\xe6\x8c\x99\xe5\x8b\x95\xe3\x81\xab\xe3\x82\x88\xe3\x82\x8b\xe5\x9b\x9e\xe8\xbb\xa2\xe5\x88\xb6\xe9\x99\x90\xe3\x80\x82\xe9\x81\xa9\xe5\x88\x87\xe3\x81\xab\xe8\xa8\xad\xe5\xae\x9a\xe3\x81\x99\xe3\x82\x8b\xe3\x81\x93\xe3\x81\xa8\xe3\x81\xa7\xe8\x8d\x92\xe3\x81\xb6\xe3\x82\x8a\xe3\x82\x92\xe6\x8a\x91\xe5\x88\xb6\n\x09* Rotational limitations in physical behavior. Setting the value properly can suppress excessive shaking\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x89\xa9\xe7\x90\x86\xe6\x8c\x99\xe5\x8b\x95\xe3\x81\xab\xe3\x82\x88\xe3\x82\x8b\xe5\x9b\x9e\xe8\xbb\xa2\xe5\x88\xb6\xe9\x99\x90\xe3\x80\x82\xe9\x81\xa9\xe5\x88\x87\xe3\x81\xab\xe8\xa8\xad\xe5\xae\x9a\xe3\x81\x99\xe3\x82\x8b\xe3\x81\x93\xe3\x81\xa8\xe3\x81\xa7\xe8\x8d\x92\xe3\x81\xb6\xe3\x82\x8a\xe3\x82\x92\xe6\x8a\x91\xe5\x88\xb6\nRotational limitations in physical behavior. Setting the value properly can suppress excessive shaking" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FKawaiiPhysicsSettings constinit property declarations ************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Damping;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Stiffness;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WorldDampingLocation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WorldDampingRotation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Radius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LimitAngle;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FKawaiiPhysicsSettings constinit property declarations **************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FKawaiiPhysicsSettings>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FKawaiiPhysicsSettings;
class UScriptStruct* FKawaiiPhysicsSettings::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FKawaiiPhysicsSettings.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FKawaiiPhysicsSettings.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FKawaiiPhysicsSettings, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("KawaiiPhysicsSettings"));
	}
	return Z_Registration_Info_UScriptStruct_FKawaiiPhysicsSettings.OuterSingleton;
	}

// ********** Begin ScriptStruct FKawaiiPhysicsSettings Property Definitions ***********************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::NewProp_Damping = { "Damping", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSettings, Damping), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Damping_MetaData), NewProp_Damping_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::NewProp_Stiffness = { "Stiffness", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSettings, Stiffness), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Stiffness_MetaData), NewProp_Stiffness_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::NewProp_WorldDampingLocation = { "WorldDampingLocation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSettings, WorldDampingLocation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldDampingLocation_MetaData), NewProp_WorldDampingLocation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::NewProp_WorldDampingRotation = { "WorldDampingRotation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSettings, WorldDampingRotation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldDampingRotation_MetaData), NewProp_WorldDampingRotation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::NewProp_Radius = { "Radius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSettings, Radius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Radius_MetaData), NewProp_Radius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::NewProp_LimitAngle = { "LimitAngle", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSettings, LimitAngle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LimitAngle_MetaData), NewProp_LimitAngle_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::NewProp_Damping,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::NewProp_Stiffness,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::NewProp_WorldDampingLocation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::NewProp_WorldDampingRotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::NewProp_Radius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::NewProp_LimitAngle,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FKawaiiPhysicsSettings Property Definitions *************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	nullptr,
	&NewStructOps,
	"KawaiiPhysicsSettings",
	Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::PropPointers),
	sizeof(FKawaiiPhysicsSettings),
	alignof(FKawaiiPhysicsSettings),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FKawaiiPhysicsSettings()
{
	if (!Z_Registration_Info_UScriptStruct_FKawaiiPhysicsSettings.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FKawaiiPhysicsSettings.InnerSingleton, Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FKawaiiPhysicsSettings.InnerSingleton);
}
// ********** End ScriptStruct FKawaiiPhysicsSettings **********************************************

// ********** Begin ScriptStruct FKawaiiPhysicsModifyBone ******************************************
struct Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FKawaiiPhysicsModifyBone); }
	static inline consteval int16 GetStructAlignment() { return alignof(FKawaiiPhysicsModifyBone); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Structure representing a bone that can be modified by the KawaiiPhysics system.\n */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Structure representing a bone that can be modified by the KawaiiPhysics system." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoneRef_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Reference to the bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Reference to the bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Index_MetaData[] = {
		{ "Category", "KawaiiPhysics|ModifyBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Index of the bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Index of the bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParentIndex_MetaData[] = {
		{ "Category", "KawaiiPhysics|ModifyBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Index of the parent bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Index of the parent bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChildIndices_MetaData[] = {
		{ "Category", "KawaiiPhysics|ModifyBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Indices of the child bones */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Indices of the child bones" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PhysicsSettings_MetaData[] = {
		{ "Category", "KawaiiPhysics|ModifyBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Physics settings for the bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Physics settings for the bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[] = {
		{ "Category", "KawaiiPhysics|ModifyBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Current location of the bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Current location of the bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PrevLocation_MetaData[] = {
		{ "Category", "KawaiiPhysics|ModifyBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Previous location of the bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Previous location of the bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PrevRotation_MetaData[] = {
		{ "Category", "KawaiiPhysics|ModifyBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Previous rotation of the bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Previous rotation of the bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PoseLocation_MetaData[] = {
		{ "Category", "KawaiiPhysics|ModifyBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Pose location of the bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pose location of the bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PoseRotation_MetaData[] = {
		{ "Category", "KawaiiPhysics|ModifyBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Pose rotation of the bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pose rotation of the bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PoseScale_MetaData[] = {
		{ "Category", "KawaiiPhysics|ModifyBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Pose scale of the bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pose scale of the bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoneLength_MetaData[] = {
		{ "Category", "KawaiiPhysics|ModifyBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Length of the bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Length of the bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LengthFromRoot_MetaData[] = {
		{ "Category", "KawaiiPhysics|ModifyBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Length from the root bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Length from the root bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LengthRateFromRoot_MetaData[] = {
		{ "Category", "KawaiiPhysics|ModifyBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Length rate from the root bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Length rate from the root bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDummy_MetaData[] = {
		{ "Category", "KawaiiPhysics|ModifyBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Flag indicating if this is a dummy bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Flag indicating if this is a dummy bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bInterBoneDummy_MetaData[] = {
		{ "Category", "KawaiiPhysics|ModifyBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* \xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\xef\xbc\x88""2\xe3\x81\xa4\xe3\x81\xae\xe5\xae\x9f\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x81\xab\xe6\x8c\xbf\xe5\x85\xa5\xe3\x81\x95\xe3\x82\x8c\xe3\x81\x9f\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xef\xbc\x89\n\x09* Flag: this is an inter-bone dummy (inserted between two real bones)\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x83\x95\xe3\x83\xa9\xe3\x82\xb0\xef\xbc\x88""2\xe3\x81\xa4\xe3\x81\xae\xe5\xae\x9f\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x81\xab\xe6\x8c\xbf\xe5\x85\xa5\xe3\x81\x95\xe3\x82\x8c\xe3\x81\x9f\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xef\xbc\x89\nFlag: this is an inter-bone dummy (inserted between two real bones)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InterBoneRealChildIndex_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* \xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x81\xae\xe8\xa3\x9c\xe9\x96\x93\xe5\x85\x88\xef\xbc\x88\xe5\xae\x9f\xe5\xad\x90\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xef\xbc\x89\xe3\x81\xae\xe3\x82\xa4\xe3\x83\xb3\xe3\x83\x87\xe3\x83\x83\xe3\x82\xaf\xe3\x82\xb9 / Real child bone index for PoseLocation interpolation\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x81\xae\xe8\xa3\x9c\xe9\x96\x93\xe5\x85\x88\xef\xbc\x88\xe5\xae\x9f\xe5\xad\x90\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xef\xbc\x89\xe3\x81\xae\xe3\x82\xa4\xe3\x83\xb3\xe3\x83\x87\xe3\x83\x83\xe3\x82\xaf\xe3\x82\xb9 / Real child bone index for PoseLocation interpolation" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InterBoneRealParentIndex_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* \xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x81\xae\xe8\xa3\x9c\xe9\x96\x93\xe5\x85\x83\xef\xbc\x88\xe5\xae\x9f\xe8\xa6\xaa\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xef\xbc\x89\xe3\x81\xae\xe3\x82\xa4\xe3\x83\xb3\xe3\x83\x87\xe3\x83\x83\xe3\x82\xaf\xe3\x82\xb9 / Real parent bone index for PoseLocation interpolation\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x81\xae\xe8\xa3\x9c\xe9\x96\x93\xe5\x85\x83\xef\xbc\x88\xe5\xae\x9f\xe8\xa6\xaa\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xef\xbc\x89\xe3\x81\xae\xe3\x82\xa4\xe3\x83\xb3\xe3\x83\x87\xe3\x83\x83\xe3\x82\xaf\xe3\x82\xb9 / Real parent bone index for PoseLocation interpolation" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InterBoneAlpha_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* \xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x81\xae\xe8\xa3\x9c\xe9\x96\x93\xe3\x82\xa2\xe3\x83\xab\xe3\x83\x95\xe3\x82\xa1\xef\xbc\x88""0.0=\xe5\xae\x9f\xe8\xa6\xaa, 1.0=\xe5\xae\x9f\xe5\xad\x90\xef\xbc\x89/ Interpolation alpha between real parent and child\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe9\x96\x93\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xe3\x81\xae\xe8\xa3\x9c\xe9\x96\x93\xe3\x82\xa2\xe3\x83\xab\xe3\x83\x95\xe3\x82\xa1\xef\xbc\x88""0.0=\xe5\xae\x9f\xe8\xa6\xaa, 1.0=\xe5\xae\x9f\xe5\xad\x90\xef\xbc\x89/ Interpolation alpha between real parent and child" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bBridgeDummy_MetaData[] = {
		{ "Category", "KawaiiPhysics|ModifyBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* \xe6\xa8\xaa\xe6\x96\xb9\xe5\x90\x91""BoneConstraint\xe4\xb8\x8a\xe3\x81\xab\xe6\x8c\xbf\xe5\x85\xa5\xe3\x81\x95\xe3\x82\x8c\xe3\x81\x9f\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe4\xbb\xa3\xe7\x90\x86\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xef\xbc\x88\xe7\xb8\xa6\xe9\x9a\x8e\xe5\xb1\xa4\xe3\x81\xab\xe5\xb1\x9e\xe3\x81\x95\xe3\x81\x9a\xe3\x80\x81\xe5\xb8\xb8\xe3\x81\xab\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe5\xb0\x82\xe7\x94\xa8\xef\xbc\x89\n\x09* Collision-proxy dummy inserted along a horizontal BoneConstraint (not in the vertical hierarchy; always collision-only).\n\x09* \xe9\x85\x8d\xe7\xbd\xae\xe7\x94\xa8\xe3\x81\xab InterBoneRealParentIndex/InterBoneRealChildIndex/InterBoneAlpha \xe3\x82\x92\xe7\xab\xaf\xe7\x82\xb9""1/\xe7\xab\xaf\xe7\x82\xb9""2/\xe8\xa3\x9c\xe9\x96\x93\xe7\x8e\x87\xe3\x81\xa8\xe3\x81\x97\xe3\x81\xa6\xe6\xb5\x81\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82\n\x09* Reuses InterBoneRealParentIndex/InterBoneRealChildIndex/InterBoneAlpha as endpoint1/endpoint2/lerp-alpha for placement.\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xa8\xaa\xe6\x96\xb9\xe5\x90\x91""BoneConstraint\xe4\xb8\x8a\xe3\x81\xab\xe6\x8c\xbf\xe5\x85\xa5\xe3\x81\x95\xe3\x82\x8c\xe3\x81\x9f\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe4\xbb\xa3\xe7\x90\x86\xe3\x83\x80\xe3\x83\x9f\xe3\x83\xbc\xef\xbc\x88\xe7\xb8\xa6\xe9\x9a\x8e\xe5\xb1\xa4\xe3\x81\xab\xe5\xb1\x9e\xe3\x81\x95\xe3\x81\x9a\xe3\x80\x81\xe5\xb8\xb8\xe3\x81\xab\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe5\xb0\x82\xe7\x94\xa8\xef\xbc\x89\nCollision-proxy dummy inserted along a horizontal BoneConstraint (not in the vertical hierarchy; always collision-only).\n\xe9\x85\x8d\xe7\xbd\xae\xe7\x94\xa8\xe3\x81\xab InterBoneRealParentIndex/InterBoneRealChildIndex/InterBoneAlpha \xe3\x82\x92\xe7\xab\xaf\xe7\x82\xb9""1/\xe7\xab\xaf\xe7\x82\xb9""2/\xe8\xa3\x9c\xe9\x96\x93\xe7\x8e\x87\xe3\x81\xa8\xe3\x81\x97\xe3\x81\xa6\xe6\xb5\x81\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82\nReuses InterBoneRealParentIndex/InterBoneRealChildIndex/InterBoneAlpha as endpoint1/endpoint2/lerp-alpha for placement." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSkipSimulate_MetaData[] = {
		{ "Category", "KawaiiPhysics|ModifyBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Flag indicating if simulation should be skipped for this bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Flag indicating if simulation should be skipped for this bone" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FKawaiiPhysicsModifyBone constinit property declarations **********
	static const UECodeGen_Private::FStructPropertyParams NewProp_BoneRef;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Index;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ParentIndex;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ChildIndices_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ChildIndices;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PhysicsSettings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Location;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PrevLocation;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PrevRotation;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PoseLocation;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PoseRotation;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PoseScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BoneLength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LengthFromRoot;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LengthRateFromRoot;
	static void NewProp_bDummy_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDummy;
	static void NewProp_bInterBoneDummy_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bInterBoneDummy;
	static const UECodeGen_Private::FIntPropertyParams NewProp_InterBoneRealChildIndex;
	static const UECodeGen_Private::FIntPropertyParams NewProp_InterBoneRealParentIndex;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InterBoneAlpha;
	static void NewProp_bBridgeDummy_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bBridgeDummy;
	static void NewProp_bSkipSimulate_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSkipSimulate;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FKawaiiPhysicsModifyBone constinit property declarations ************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FKawaiiPhysicsModifyBone>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FKawaiiPhysicsModifyBone;
class UScriptStruct* FKawaiiPhysicsModifyBone::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FKawaiiPhysicsModifyBone.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FKawaiiPhysicsModifyBone.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("KawaiiPhysicsModifyBone"));
	}
	return Z_Registration_Info_UScriptStruct_FKawaiiPhysicsModifyBone.OuterSingleton;
	}

// ********** Begin ScriptStruct FKawaiiPhysicsModifyBone Property Definitions *********************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_BoneRef = { "BoneRef", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsModifyBone, BoneRef), Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoneRef_MetaData), NewProp_BoneRef_MetaData) }; // 1102615820
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsModifyBone, Index), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Index_MetaData), NewProp_Index_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_ParentIndex = { "ParentIndex", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsModifyBone, ParentIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParentIndex_MetaData), NewProp_ParentIndex_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_ChildIndices_Inner = { "ChildIndices", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_ChildIndices = { "ChildIndices", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsModifyBone, ChildIndices), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChildIndices_MetaData), NewProp_ChildIndices_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_PhysicsSettings = { "PhysicsSettings", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsModifyBone, PhysicsSettings), Z_Construct_UScriptStruct_FKawaiiPhysicsSettings, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PhysicsSettings_MetaData), NewProp_PhysicsSettings_MetaData) }; // 2772010112
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsModifyBone, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Location_MetaData), NewProp_Location_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_PrevLocation = { "PrevLocation", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsModifyBone, PrevLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PrevLocation_MetaData), NewProp_PrevLocation_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_PrevRotation = { "PrevRotation", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsModifyBone, PrevRotation), Z_Construct_UScriptStruct_FQuat, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PrevRotation_MetaData), NewProp_PrevRotation_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_PoseLocation = { "PoseLocation", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsModifyBone, PoseLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PoseLocation_MetaData), NewProp_PoseLocation_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_PoseRotation = { "PoseRotation", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsModifyBone, PoseRotation), Z_Construct_UScriptStruct_FQuat, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PoseRotation_MetaData), NewProp_PoseRotation_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_PoseScale = { "PoseScale", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsModifyBone, PoseScale), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PoseScale_MetaData), NewProp_PoseScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_BoneLength = { "BoneLength", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsModifyBone, BoneLength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoneLength_MetaData), NewProp_BoneLength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_LengthFromRoot = { "LengthFromRoot", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsModifyBone, LengthFromRoot), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LengthFromRoot_MetaData), NewProp_LengthFromRoot_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_LengthRateFromRoot = { "LengthRateFromRoot", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsModifyBone, LengthRateFromRoot), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LengthRateFromRoot_MetaData), NewProp_LengthRateFromRoot_MetaData) };
void Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_bDummy_SetBit(void* Obj)
{
	((FKawaiiPhysicsModifyBone*)Obj)->bDummy = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_bDummy = { "bDummy", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FKawaiiPhysicsModifyBone), &Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_bDummy_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDummy_MetaData), NewProp_bDummy_MetaData) };
void Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_bInterBoneDummy_SetBit(void* Obj)
{
	((FKawaiiPhysicsModifyBone*)Obj)->bInterBoneDummy = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_bInterBoneDummy = { "bInterBoneDummy", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FKawaiiPhysicsModifyBone), &Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_bInterBoneDummy_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bInterBoneDummy_MetaData), NewProp_bInterBoneDummy_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_InterBoneRealChildIndex = { "InterBoneRealChildIndex", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsModifyBone, InterBoneRealChildIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InterBoneRealChildIndex_MetaData), NewProp_InterBoneRealChildIndex_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_InterBoneRealParentIndex = { "InterBoneRealParentIndex", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsModifyBone, InterBoneRealParentIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InterBoneRealParentIndex_MetaData), NewProp_InterBoneRealParentIndex_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_InterBoneAlpha = { "InterBoneAlpha", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsModifyBone, InterBoneAlpha), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InterBoneAlpha_MetaData), NewProp_InterBoneAlpha_MetaData) };
void Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_bBridgeDummy_SetBit(void* Obj)
{
	((FKawaiiPhysicsModifyBone*)Obj)->bBridgeDummy = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_bBridgeDummy = { "bBridgeDummy", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FKawaiiPhysicsModifyBone), &Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_bBridgeDummy_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bBridgeDummy_MetaData), NewProp_bBridgeDummy_MetaData) };
void Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_bSkipSimulate_SetBit(void* Obj)
{
	((FKawaiiPhysicsModifyBone*)Obj)->bSkipSimulate = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_bSkipSimulate = { "bSkipSimulate", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FKawaiiPhysicsModifyBone), &Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_bSkipSimulate_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSkipSimulate_MetaData), NewProp_bSkipSimulate_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_BoneRef,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_Index,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_ParentIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_ChildIndices_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_ChildIndices,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_PhysicsSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_Location,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_PrevLocation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_PrevRotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_PoseLocation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_PoseRotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_PoseScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_BoneLength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_LengthFromRoot,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_LengthRateFromRoot,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_bDummy,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_bInterBoneDummy,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_InterBoneRealChildIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_InterBoneRealParentIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_InterBoneAlpha,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_bBridgeDummy,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewProp_bSkipSimulate,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FKawaiiPhysicsModifyBone Property Definitions ***********************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	nullptr,
	&NewStructOps,
	"KawaiiPhysicsModifyBone",
	Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::PropPointers),
	sizeof(FKawaiiPhysicsModifyBone),
	alignof(FKawaiiPhysicsModifyBone),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone()
{
	if (!Z_Registration_Info_UScriptStruct_FKawaiiPhysicsModifyBone.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FKawaiiPhysicsModifyBone.InnerSingleton, Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FKawaiiPhysicsModifyBone.InnerSingleton);
}
// ********** End ScriptStruct FKawaiiPhysicsModifyBone ********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsTypes_h__Script_KawaiiPhysics_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EKawaiiPhysicsSimulationSpace_StaticEnum, TEXT("EKawaiiPhysicsSimulationSpace"), &Z_Registration_Info_UEnum_EKawaiiPhysicsSimulationSpace, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3750099244U) },
		{ EPlanarConstraint_StaticEnum, TEXT("EPlanarConstraint"), &Z_Registration_Info_UEnum_EPlanarConstraint, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 462578191U) },
		{ EBoneForwardAxis_StaticEnum, TEXT("EBoneForwardAxis"), &Z_Registration_Info_UEnum_EBoneForwardAxis, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1723749861U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FKawaiiPhysicsRootBoneSetting::StaticStruct, Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics::NewStructOps, TEXT("KawaiiPhysicsRootBoneSetting"),&Z_Registration_Info_UScriptStruct_FKawaiiPhysicsRootBoneSetting, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FKawaiiPhysicsRootBoneSetting), 639501474U) },
		{ FKawaiiPhysicsSettings::StaticStruct, Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics::NewStructOps, TEXT("KawaiiPhysicsSettings"),&Z_Registration_Info_UScriptStruct_FKawaiiPhysicsSettings, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FKawaiiPhysicsSettings), 2772010112U) },
		{ FKawaiiPhysicsModifyBone::StaticStruct, Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics::NewStructOps, TEXT("KawaiiPhysicsModifyBone"),&Z_Registration_Info_UScriptStruct_FKawaiiPhysicsModifyBone, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FKawaiiPhysicsModifyBone), 1078151775U) },
	};
}; // Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsTypes_h__Script_KawaiiPhysics_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsTypes_h__Script_KawaiiPhysics_3403789644{
	TEXT("/Script/KawaiiPhysics"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsTypes_h__Script_KawaiiPhysics_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsTypes_h__Script_KawaiiPhysics_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsTypes_h__Script_KawaiiPhysics_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsTypes_h__Script_KawaiiPhysics_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
