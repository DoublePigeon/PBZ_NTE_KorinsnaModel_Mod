// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "KawaiiPhysicsBoneConstraintTypes.h"
#include "Animation/BoneReference.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeKawaiiPhysicsBoneConstraintTypes() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FBoneReference();
KAWAIIPHYSICS_API UEnum* Z_Construct_UEnum_KawaiiPhysics_EXPBDComplianceType();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FModifyBoneConstraint();
UPackage* Z_Construct_UPackage__Script_KawaiiPhysics();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EXPBDComplianceType *******************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EXPBDComplianceType;
static UEnum* EXPBDComplianceType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EXPBDComplianceType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EXPBDComplianceType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_KawaiiPhysics_EXPBDComplianceType, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("EXPBDComplianceType"));
	}
	return Z_Registration_Info_UEnum_EXPBDComplianceType.OuterSingleton;
}
template<> KAWAIIPHYSICS_NON_ATTRIBUTED_API UEnum* StaticEnum<EXPBDComplianceType>()
{
	return EXPBDComplianceType_StaticEnum();
}
struct Z_Construct_UEnum_KawaiiPhysics_EXPBDComplianceType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Concrete.DisplayName", "Concrete" },
		{ "Concrete.Name", "EXPBDComplianceType::Concrete" },
		{ "Fat.DisplayName", "Fat" },
		{ "Fat.Name", "EXPBDComplianceType::Fat" },
		{ "Leather.DisplayName", "Leather" },
		{ "Leather.Name", "EXPBDComplianceType::Leather" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsBoneConstraintTypes.h" },
		{ "Muscle.DisplayName", "Muscle" },
		{ "Muscle.Name", "EXPBDComplianceType::Muscle" },
		{ "Rubber.DisplayName", "Rubber" },
		{ "Rubber.Name", "EXPBDComplianceType::Rubber" },
		{ "Tendon.DisplayName", "Tendon" },
		{ "Tendon.Name", "EXPBDComplianceType::Tendon" },
		{ "Wood.DisplayName", "Wood" },
		{ "Wood.Name", "EXPBDComplianceType::Wood" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EXPBDComplianceType::Concrete", (int64)EXPBDComplianceType::Concrete },
		{ "EXPBDComplianceType::Wood", (int64)EXPBDComplianceType::Wood },
		{ "EXPBDComplianceType::Leather", (int64)EXPBDComplianceType::Leather },
		{ "EXPBDComplianceType::Tendon", (int64)EXPBDComplianceType::Tendon },
		{ "EXPBDComplianceType::Rubber", (int64)EXPBDComplianceType::Rubber },
		{ "EXPBDComplianceType::Muscle", (int64)EXPBDComplianceType::Muscle },
		{ "EXPBDComplianceType::Fat", (int64)EXPBDComplianceType::Fat },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_KawaiiPhysics_EXPBDComplianceType_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_KawaiiPhysics_EXPBDComplianceType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	nullptr,
	"EXPBDComplianceType",
	"EXPBDComplianceType",
	Z_Construct_UEnum_KawaiiPhysics_EXPBDComplianceType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_KawaiiPhysics_EXPBDComplianceType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_KawaiiPhysics_EXPBDComplianceType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_KawaiiPhysics_EXPBDComplianceType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_KawaiiPhysics_EXPBDComplianceType()
{
	if (!Z_Registration_Info_UEnum_EXPBDComplianceType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EXPBDComplianceType.InnerSingleton, Z_Construct_UEnum_KawaiiPhysics_EXPBDComplianceType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EXPBDComplianceType.InnerSingleton;
}
// ********** End Enum EXPBDComplianceType *********************************************************

// ********** Begin ScriptStruct FModifyBoneConstraint *********************************************
struct Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FModifyBoneConstraint); }
	static inline consteval int16 GetStructAlignment() { return alignof(FModifyBoneConstraint); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Structure representing a constraint between two bones for the KawaiiPhysics system.\n */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsBoneConstraintTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Structure representing a constraint between two bones for the KawaiiPhysics system." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Bone1_MetaData[] = {
		{ "Category", "KawaiiPhysics" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The first bone reference in the constraint */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsBoneConstraintTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The first bone reference in the constraint" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Bone2_MetaData[] = {
		{ "Category", "KawaiiPhysics" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The second bone reference in the constraint */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsBoneConstraintTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The second bone reference in the constraint" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bOverrideCompliance_MetaData[] = {
		{ "Category", "KawaiiPhysics" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Flag to override the compliance type */" },
#endif
		{ "InlineEditConditionToggle", "" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsBoneConstraintTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Flag to override the compliance type" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComplianceType_MetaData[] = {
		{ "Category", "KawaiiPhysics" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The compliance type to use if overridden */" },
#endif
		{ "EditCondition", "bOverrideCompliance" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsBoneConstraintTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The compliance type to use if overridden" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bExcludeFromSubdivision_MetaData[] = {
		{ "Category", "KawaiiPhysics" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * \xe3\x81\x93\xe3\x81\xae""Constraint\xe3\x82\x92""BoneConstraintSubdivision\xe3\x81\xae\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\x8b\xe3\x82\x89\xe9\x99\xa4\xe5\xa4\x96\xe3\x81\x99\xe3\x82\x8b\xef\xbc\x88\xe6\xa7\x8b\xe9\x80\xa0/\xe5\xaf\xbe\xe8\xa7\x92""Constraint\xe7\x94\xa8\xe3\x81\xae\xe3\x82\xaa\xe3\x83\x97\xe3\x83\x88\xe3\x82\xa2\xe3\x82\xa6\xe3\x83\x88\xef\xbc\x89\n\x09 * Exclude this constraint from BoneConstraintSubdivision (opt-out for structural/diagonal constraints).\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsBoneConstraintTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x81\x93\xe3\x81\xae""Constraint\xe3\x82\x92""BoneConstraintSubdivision\xe3\x81\xae\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\x8b\xe3\x82\x89\xe9\x99\xa4\xe5\xa4\x96\xe3\x81\x99\xe3\x82\x8b\xef\xbc\x88\xe6\xa7\x8b\xe9\x80\xa0/\xe5\xaf\xbe\xe8\xa7\x92""Constraint\xe7\x94\xa8\xe3\x81\xae\xe3\x82\xaa\xe3\x83\x97\xe3\x83\x88\xe3\x82\xa2\xe3\x82\xa6\xe3\x83\x88\xef\xbc\x89\nExclude this constraint from BoneConstraintSubdivision (opt-out for structural/diagonal constraints)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ModifyBoneIndex1_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Index of the first modify bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsBoneConstraintTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Index of the first modify bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ModifyBoneIndex2_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Index of the second modify bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsBoneConstraintTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Index of the second modify bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Length_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Length of the constraint */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsBoneConstraintTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Length of the constraint" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsDummy_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Flag indicating if this is a dummy constraint */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsBoneConstraintTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Flag indicating if this is a dummy constraint" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Lambda_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Lambda value for the constraint */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsBoneConstraintTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Lambda value for the constraint" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FModifyBoneConstraint constinit property declarations *************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Bone1;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Bone2;
	static void NewProp_bOverrideCompliance_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOverrideCompliance;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ComplianceType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ComplianceType;
	static void NewProp_bExcludeFromSubdivision_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bExcludeFromSubdivision;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ModifyBoneIndex1;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ModifyBoneIndex2;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Length;
	static void NewProp_bIsDummy_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsDummy;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Lambda;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FModifyBoneConstraint constinit property declarations ***************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FModifyBoneConstraint>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FModifyBoneConstraint;
class UScriptStruct* FModifyBoneConstraint::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FModifyBoneConstraint.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FModifyBoneConstraint.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FModifyBoneConstraint, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("ModifyBoneConstraint"));
	}
	return Z_Registration_Info_UScriptStruct_FModifyBoneConstraint.OuterSingleton;
	}

// ********** Begin ScriptStruct FModifyBoneConstraint Property Definitions ************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_Bone1 = { "Bone1", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FModifyBoneConstraint, Bone1), Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Bone1_MetaData), NewProp_Bone1_MetaData) }; // 1102615820
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_Bone2 = { "Bone2", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FModifyBoneConstraint, Bone2), Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Bone2_MetaData), NewProp_Bone2_MetaData) }; // 1102615820
void Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_bOverrideCompliance_SetBit(void* Obj)
{
	((FModifyBoneConstraint*)Obj)->bOverrideCompliance = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_bOverrideCompliance = { "bOverrideCompliance", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FModifyBoneConstraint), &Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_bOverrideCompliance_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bOverrideCompliance_MetaData), NewProp_bOverrideCompliance_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_ComplianceType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_ComplianceType = { "ComplianceType", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FModifyBoneConstraint, ComplianceType), Z_Construct_UEnum_KawaiiPhysics_EXPBDComplianceType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComplianceType_MetaData), NewProp_ComplianceType_MetaData) }; // 676679353
void Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_bExcludeFromSubdivision_SetBit(void* Obj)
{
	((FModifyBoneConstraint*)Obj)->bExcludeFromSubdivision = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_bExcludeFromSubdivision = { "bExcludeFromSubdivision", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FModifyBoneConstraint), &Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_bExcludeFromSubdivision_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bExcludeFromSubdivision_MetaData), NewProp_bExcludeFromSubdivision_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_ModifyBoneIndex1 = { "ModifyBoneIndex1", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FModifyBoneConstraint, ModifyBoneIndex1), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ModifyBoneIndex1_MetaData), NewProp_ModifyBoneIndex1_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_ModifyBoneIndex2 = { "ModifyBoneIndex2", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FModifyBoneConstraint, ModifyBoneIndex2), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ModifyBoneIndex2_MetaData), NewProp_ModifyBoneIndex2_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_Length = { "Length", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FModifyBoneConstraint, Length), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Length_MetaData), NewProp_Length_MetaData) };
void Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_bIsDummy_SetBit(void* Obj)
{
	((FModifyBoneConstraint*)Obj)->bIsDummy = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_bIsDummy = { "bIsDummy", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FModifyBoneConstraint), &Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_bIsDummy_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsDummy_MetaData), NewProp_bIsDummy_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_Lambda = { "Lambda", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FModifyBoneConstraint, Lambda), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Lambda_MetaData), NewProp_Lambda_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_Bone1,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_Bone2,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_bOverrideCompliance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_ComplianceType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_ComplianceType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_bExcludeFromSubdivision,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_ModifyBoneIndex1,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_ModifyBoneIndex2,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_Length,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_bIsDummy,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewProp_Lambda,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FModifyBoneConstraint Property Definitions **************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	nullptr,
	&NewStructOps,
	"ModifyBoneConstraint",
	Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::PropPointers),
	sizeof(FModifyBoneConstraint),
	alignof(FModifyBoneConstraint),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FModifyBoneConstraint()
{
	if (!Z_Registration_Info_UScriptStruct_FModifyBoneConstraint.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FModifyBoneConstraint.InnerSingleton, Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FModifyBoneConstraint.InnerSingleton);
}
// ********** End ScriptStruct FModifyBoneConstraint ***********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintTypes_h__Script_KawaiiPhysics_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EXPBDComplianceType_StaticEnum, TEXT("EXPBDComplianceType"), &Z_Registration_Info_UEnum_EXPBDComplianceType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 676679353U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FModifyBoneConstraint::StaticStruct, Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics::NewStructOps, TEXT("ModifyBoneConstraint"),&Z_Registration_Info_UScriptStruct_FModifyBoneConstraint, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FModifyBoneConstraint), 1109661521U) },
	};
}; // Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintTypes_h__Script_KawaiiPhysics_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintTypes_h__Script_KawaiiPhysics_3407688038{
	TEXT("/Script/KawaiiPhysics"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintTypes_h__Script_KawaiiPhysics_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintTypes_h__Script_KawaiiPhysics_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintTypes_h__Script_KawaiiPhysics_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintTypes_h__Script_KawaiiPhysics_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
