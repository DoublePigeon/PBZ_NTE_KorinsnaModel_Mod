// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "KawaiiPhysicsCollisionLimits.h"
#include "Animation/BoneReference.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeKawaiiPhysicsCollisionLimits() {}

// ********** Begin Cross Module References ********************************************************
ANIMGRAPHRUNTIME_API UEnum* Z_Construct_UEnum_AnimGraphRuntime_ESphericalLimitType();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FPlane();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FQuat();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FBoneReference();
KAWAIIPHYSICS_API UEnum* Z_Construct_UEnum_KawaiiPhysics_ECollisionLimitType();
KAWAIIPHYSICS_API UEnum* Z_Construct_UEnum_KawaiiPhysics_ECollisionSourceType();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FBoxLimit();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FCapsuleLimit();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FCollisionLimitBase();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FPlanarLimit();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FSphericalLimit();
UPackage* Z_Construct_UPackage__Script_KawaiiPhysics();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum ECollisionLimitType *******************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ECollisionLimitType;
static UEnum* ECollisionLimitType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ECollisionLimitType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ECollisionLimitType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_KawaiiPhysics_ECollisionLimitType, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("ECollisionLimitType"));
	}
	return Z_Registration_Info_UEnum_ECollisionLimitType.OuterSingleton;
}
template<> KAWAIIPHYSICS_NON_ATTRIBUTED_API UEnum* StaticEnum<ECollisionLimitType>()
{
	return ECollisionLimitType_StaticEnum();
}
struct Z_Construct_UEnum_KawaiiPhysics_ECollisionLimitType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Box.Name", "ECollisionLimitType::Box" },
		{ "Capsule.Name", "ECollisionLimitType::Capsule" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Enum representing the type of collision limit in KawaiiPhysics.\n */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
		{ "None.Name", "ECollisionLimitType::None" },
		{ "Planar.Name", "ECollisionLimitType::Planar" },
		{ "Spherical.Name", "ECollisionLimitType::Spherical" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Enum representing the type of collision limit in KawaiiPhysics." },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ECollisionLimitType::None", (int64)ECollisionLimitType::None },
		{ "ECollisionLimitType::Spherical", (int64)ECollisionLimitType::Spherical },
		{ "ECollisionLimitType::Capsule", (int64)ECollisionLimitType::Capsule },
		{ "ECollisionLimitType::Box", (int64)ECollisionLimitType::Box },
		{ "ECollisionLimitType::Planar", (int64)ECollisionLimitType::Planar },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_KawaiiPhysics_ECollisionLimitType_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_KawaiiPhysics_ECollisionLimitType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	nullptr,
	"ECollisionLimitType",
	"ECollisionLimitType",
	Z_Construct_UEnum_KawaiiPhysics_ECollisionLimitType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_KawaiiPhysics_ECollisionLimitType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_KawaiiPhysics_ECollisionLimitType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_KawaiiPhysics_ECollisionLimitType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_KawaiiPhysics_ECollisionLimitType()
{
	if (!Z_Registration_Info_UEnum_ECollisionLimitType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ECollisionLimitType.InnerSingleton, Z_Construct_UEnum_KawaiiPhysics_ECollisionLimitType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ECollisionLimitType.InnerSingleton;
}
// ********** End Enum ECollisionLimitType *********************************************************

// ********** Begin Enum ECollisionSourceType ******************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ECollisionSourceType;
static UEnum* ECollisionSourceType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ECollisionSourceType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ECollisionSourceType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_KawaiiPhysics_ECollisionSourceType, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("ECollisionSourceType"));
	}
	return Z_Registration_Info_UEnum_ECollisionSourceType.OuterSingleton;
}
template<> KAWAIIPHYSICS_NON_ATTRIBUTED_API UEnum* StaticEnum<ECollisionSourceType>()
{
	return ECollisionSourceType_StaticEnum();
}
struct Z_Construct_UEnum_KawaiiPhysics_ECollisionSourceType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "AnimNode.Comment", "/** Use the value set in the AnimNode */" },
		{ "AnimNode.Name", "ECollisionSourceType::AnimNode" },
		{ "AnimNode.ToolTip", "Use the value set in the AnimNode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Enum representing the source type of the collision limit in KawaiiPhysics.\n */" },
#endif
		{ "DataAsset.Comment", "/** Use the value set in the DataAsset */" },
		{ "DataAsset.Name", "ECollisionSourceType::DataAsset" },
		{ "DataAsset.ToolTip", "Use the value set in the DataAsset" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
		{ "PhysicsAsset.Comment", "/** Use the value set in the PhysicsAsset */" },
		{ "PhysicsAsset.Name", "ECollisionSourceType::PhysicsAsset" },
		{ "PhysicsAsset.ToolTip", "Use the value set in the PhysicsAsset" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Enum representing the source type of the collision limit in KawaiiPhysics." },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ECollisionSourceType::AnimNode", (int64)ECollisionSourceType::AnimNode },
		{ "ECollisionSourceType::DataAsset", (int64)ECollisionSourceType::DataAsset },
		{ "ECollisionSourceType::PhysicsAsset", (int64)ECollisionSourceType::PhysicsAsset },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_KawaiiPhysics_ECollisionSourceType_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_KawaiiPhysics_ECollisionSourceType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	nullptr,
	"ECollisionSourceType",
	"ECollisionSourceType",
	Z_Construct_UEnum_KawaiiPhysics_ECollisionSourceType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_KawaiiPhysics_ECollisionSourceType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_KawaiiPhysics_ECollisionSourceType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_KawaiiPhysics_ECollisionSourceType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_KawaiiPhysics_ECollisionSourceType()
{
	if (!Z_Registration_Info_UEnum_ECollisionSourceType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ECollisionSourceType.InnerSingleton, Z_Construct_UEnum_KawaiiPhysics_ECollisionSourceType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ECollisionSourceType.InnerSingleton;
}
// ********** End Enum ECollisionSourceType ********************************************************

// ********** Begin ScriptStruct FCollisionLimitBase ***********************************************
struct Z_Construct_UScriptStruct_FCollisionLimitBase_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FCollisionLimitBase); }
	static inline consteval int16 GetStructAlignment() { return alignof(FCollisionLimitBase); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Base structure for defining collision limits in KawaiiPhysics.\n */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Base structure for defining collision limits in KawaiiPhysics." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DrivingBone_MetaData[] = {
		{ "Category", "CollisionLimitBase" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Bone to attach the sphere to */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Bone to attach the sphere to" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OffsetLocation_MetaData[] = {
		{ "Category", "CollisionLimitBase" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Offset location from the driving bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Offset location from the driving bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OffsetRotation_MetaData[] = {
		{ "Category", "CollisionLimitBase" },
		{ "ClampMax", "360" },
		{ "ClampMin", "-360" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Offset rotation from the driving bone */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Offset rotation from the driving bone" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Location of the collision limit */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Location of the collision limit" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Rotation_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Rotation of the collision limit */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Rotation of the collision limit" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnable_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether the collision limit is enabled */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether the collision limit is enabled" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceType_MetaData[] = {
		{ "Category", "CollisionLimitBase" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Source type of the collision limit */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Source type of the collision limit" },
#endif
	};
#if WITH_EDITORONLY_DATA
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Guid_MetaData[] = {
		{ "Category", "Debug" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Unique identifier for the collision limit (editor only) */" },
#endif
		{ "IgnoreForMemberInitializationTest", "" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Unique identifier for the collision limit (editor only)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Type of the collision limit (editor only) */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Type of the collision limit (editor only)" },
#endif
	};
#endif // WITH_EDITORONLY_DATA
#endif // WITH_METADATA

// ********** Begin ScriptStruct FCollisionLimitBase constinit property declarations ***************
	static const UECodeGen_Private::FStructPropertyParams NewProp_DrivingBone;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OffsetLocation;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OffsetRotation;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Location;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Rotation;
	static void NewProp_bEnable_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnable;
	static const UECodeGen_Private::FBytePropertyParams NewProp_SourceType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_SourceType;
#if WITH_EDITORONLY_DATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Guid;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Type;
#endif // WITH_EDITORONLY_DATA
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FCollisionLimitBase constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FCollisionLimitBase>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FCollisionLimitBase_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FCollisionLimitBase;
class UScriptStruct* FCollisionLimitBase::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FCollisionLimitBase.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FCollisionLimitBase.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FCollisionLimitBase, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("CollisionLimitBase"));
	}
	return Z_Registration_Info_UScriptStruct_FCollisionLimitBase.OuterSingleton;
	}

// ********** Begin ScriptStruct FCollisionLimitBase Property Definitions **************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_DrivingBone = { "DrivingBone", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCollisionLimitBase, DrivingBone), Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DrivingBone_MetaData), NewProp_DrivingBone_MetaData) }; // 1102615820
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_OffsetLocation = { "OffsetLocation", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCollisionLimitBase, OffsetLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OffsetLocation_MetaData), NewProp_OffsetLocation_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_OffsetRotation = { "OffsetRotation", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCollisionLimitBase, OffsetRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OffsetRotation_MetaData), NewProp_OffsetRotation_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCollisionLimitBase, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Location_MetaData), NewProp_Location_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_Rotation = { "Rotation", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCollisionLimitBase, Rotation), Z_Construct_UScriptStruct_FQuat, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rotation_MetaData), NewProp_Rotation_MetaData) };
void Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_bEnable_SetBit(void* Obj)
{
	((FCollisionLimitBase*)Obj)->bEnable = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_bEnable = { "bEnable", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FCollisionLimitBase), &Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_bEnable_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnable_MetaData), NewProp_bEnable_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_SourceType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_SourceType = { "SourceType", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCollisionLimitBase, SourceType), Z_Construct_UEnum_KawaiiPhysics_ECollisionSourceType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceType_MetaData), NewProp_SourceType_MetaData) }; // 1161007709
#if WITH_EDITORONLY_DATA
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_Guid = { "Guid", nullptr, (EPropertyFlags)0x0010000800020001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCollisionLimitBase, Guid), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Guid_MetaData), NewProp_Guid_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000800000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCollisionLimitBase, Type), Z_Construct_UEnum_KawaiiPhysics_ECollisionLimitType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Type_MetaData), NewProp_Type_MetaData) }; // 289547355
#endif // WITH_EDITORONLY_DATA
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_DrivingBone,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_OffsetLocation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_OffsetRotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_Location,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_Rotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_bEnable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_SourceType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_SourceType,
#if WITH_EDITORONLY_DATA
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_Guid,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_Type_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewProp_Type,
#endif // WITH_EDITORONLY_DATA
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FCollisionLimitBase Property Definitions ****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	nullptr,
	&NewStructOps,
	"CollisionLimitBase",
	Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::PropPointers),
	sizeof(FCollisionLimitBase),
	alignof(FCollisionLimitBase),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FCollisionLimitBase()
{
	if (!Z_Registration_Info_UScriptStruct_FCollisionLimitBase.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FCollisionLimitBase.InnerSingleton, Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FCollisionLimitBase.InnerSingleton);
}
// ********** End ScriptStruct FCollisionLimitBase *************************************************

// ********** Begin ScriptStruct FSphericalLimit ***************************************************
struct Z_Construct_UScriptStruct_FSphericalLimit_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FSphericalLimit); }
	static inline consteval int16 GetStructAlignment() { return alignof(FSphericalLimit); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Structure representing a spherical limit for collision in KawaiiPhysics.\n */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Structure representing a spherical limit for collision in KawaiiPhysics." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Radius_MetaData[] = {
		{ "Category", "SphericalLimit" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Radius of the sphere */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Radius of the sphere" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LimitType_MetaData[] = {
		{ "Category", "SphericalLimit" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether to lock bodies inside or outside of the sphere */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether to lock bodies inside or outside of the sphere" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FSphericalLimit constinit property declarations *******************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Radius;
	static const UECodeGen_Private::FBytePropertyParams NewProp_LimitType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_LimitType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FSphericalLimit constinit property declarations *********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSphericalLimit>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FSphericalLimit_Statics
static_assert(std::is_polymorphic<FSphericalLimit>() == std::is_polymorphic<FCollisionLimitBase>(), "USTRUCT FSphericalLimit cannot be polymorphic unless super FCollisionLimitBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FSphericalLimit;
class UScriptStruct* FSphericalLimit::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FSphericalLimit.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FSphericalLimit.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FSphericalLimit, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("SphericalLimit"));
	}
	return Z_Registration_Info_UScriptStruct_FSphericalLimit.OuterSingleton;
	}

// ********** Begin ScriptStruct FSphericalLimit Property Definitions ******************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FSphericalLimit_Statics::NewProp_Radius = { "Radius", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSphericalLimit, Radius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Radius_MetaData), NewProp_Radius_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FSphericalLimit_Statics::NewProp_LimitType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FSphericalLimit_Statics::NewProp_LimitType = { "LimitType", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSphericalLimit, LimitType), Z_Construct_UEnum_AnimGraphRuntime_ESphericalLimitType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LimitType_MetaData), NewProp_LimitType_MetaData) }; // 2108738164
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSphericalLimit_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSphericalLimit_Statics::NewProp_Radius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSphericalLimit_Statics::NewProp_LimitType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSphericalLimit_Statics::NewProp_LimitType,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSphericalLimit_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FSphericalLimit Property Definitions ********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSphericalLimit_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	Z_Construct_UScriptStruct_FCollisionLimitBase,
	&NewStructOps,
	"SphericalLimit",
	Z_Construct_UScriptStruct_FSphericalLimit_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSphericalLimit_Statics::PropPointers),
	sizeof(FSphericalLimit),
	alignof(FSphericalLimit),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSphericalLimit_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FSphericalLimit_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FSphericalLimit()
{
	if (!Z_Registration_Info_UScriptStruct_FSphericalLimit.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FSphericalLimit.InnerSingleton, Z_Construct_UScriptStruct_FSphericalLimit_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FSphericalLimit.InnerSingleton);
}
// ********** End ScriptStruct FSphericalLimit *****************************************************

// ********** Begin ScriptStruct FCapsuleLimit *****************************************************
struct Z_Construct_UScriptStruct_FCapsuleLimit_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FCapsuleLimit); }
	static inline consteval int16 GetStructAlignment() { return alignof(FCapsuleLimit); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Structure representing a capsule limit for collision in KawaiiPhysics.\n */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Structure representing a capsule limit for collision in KawaiiPhysics." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Radius_MetaData[] = {
		{ "Category", "CapsuleLimit" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Radius of the capsule */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Radius of the capsule" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Length_MetaData[] = {
		{ "Category", "CapsuleLimit" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Length of the capsule */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Length of the capsule" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FCapsuleLimit constinit property declarations *********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Radius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Length;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FCapsuleLimit constinit property declarations ***********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FCapsuleLimit>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FCapsuleLimit_Statics
static_assert(std::is_polymorphic<FCapsuleLimit>() == std::is_polymorphic<FCollisionLimitBase>(), "USTRUCT FCapsuleLimit cannot be polymorphic unless super FCollisionLimitBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FCapsuleLimit;
class UScriptStruct* FCapsuleLimit::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FCapsuleLimit.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FCapsuleLimit.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FCapsuleLimit, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("CapsuleLimit"));
	}
	return Z_Registration_Info_UScriptStruct_FCapsuleLimit.OuterSingleton;
	}

// ********** Begin ScriptStruct FCapsuleLimit Property Definitions ********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCapsuleLimit_Statics::NewProp_Radius = { "Radius", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCapsuleLimit, Radius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Radius_MetaData), NewProp_Radius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCapsuleLimit_Statics::NewProp_Length = { "Length", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCapsuleLimit, Length), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Length_MetaData), NewProp_Length_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FCapsuleLimit_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCapsuleLimit_Statics::NewProp_Radius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCapsuleLimit_Statics::NewProp_Length,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCapsuleLimit_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FCapsuleLimit Property Definitions **********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FCapsuleLimit_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	Z_Construct_UScriptStruct_FCollisionLimitBase,
	&NewStructOps,
	"CapsuleLimit",
	Z_Construct_UScriptStruct_FCapsuleLimit_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCapsuleLimit_Statics::PropPointers),
	sizeof(FCapsuleLimit),
	alignof(FCapsuleLimit),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCapsuleLimit_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FCapsuleLimit_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FCapsuleLimit()
{
	if (!Z_Registration_Info_UScriptStruct_FCapsuleLimit.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FCapsuleLimit.InnerSingleton, Z_Construct_UScriptStruct_FCapsuleLimit_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FCapsuleLimit.InnerSingleton);
}
// ********** End ScriptStruct FCapsuleLimit *******************************************************

// ********** Begin ScriptStruct FBoxLimit *********************************************************
struct Z_Construct_UScriptStruct_FBoxLimit_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FBoxLimit); }
	static inline consteval int16 GetStructAlignment() { return alignof(FBoxLimit); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Structure representing a box limit for collision in KawaiiPhysics.\n */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Structure representing a box limit for collision in KawaiiPhysics." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Extent_MetaData[] = {
		{ "Category", "BoxLimit" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The extent of the box defining the box limit */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The extent of the box defining the box limit" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FBoxLimit constinit property declarations *************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Extent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FBoxLimit constinit property declarations ***************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBoxLimit>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FBoxLimit_Statics
static_assert(std::is_polymorphic<FBoxLimit>() == std::is_polymorphic<FCollisionLimitBase>(), "USTRUCT FBoxLimit cannot be polymorphic unless super FCollisionLimitBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBoxLimit;
class UScriptStruct* FBoxLimit::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBoxLimit.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBoxLimit.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBoxLimit, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("BoxLimit"));
	}
	return Z_Registration_Info_UScriptStruct_FBoxLimit.OuterSingleton;
	}

// ********** Begin ScriptStruct FBoxLimit Property Definitions ************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FBoxLimit_Statics::NewProp_Extent = { "Extent", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBoxLimit, Extent), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Extent_MetaData), NewProp_Extent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBoxLimit_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBoxLimit_Statics::NewProp_Extent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBoxLimit_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FBoxLimit Property Definitions **************************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBoxLimit_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	Z_Construct_UScriptStruct_FCollisionLimitBase,
	&NewStructOps,
	"BoxLimit",
	Z_Construct_UScriptStruct_FBoxLimit_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBoxLimit_Statics::PropPointers),
	sizeof(FBoxLimit),
	alignof(FBoxLimit),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBoxLimit_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBoxLimit_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBoxLimit()
{
	if (!Z_Registration_Info_UScriptStruct_FBoxLimit.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBoxLimit.InnerSingleton, Z_Construct_UScriptStruct_FBoxLimit_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FBoxLimit.InnerSingleton);
}
// ********** End ScriptStruct FBoxLimit ***********************************************************

// ********** Begin ScriptStruct FPlanarLimit ******************************************************
struct Z_Construct_UScriptStruct_FPlanarLimit_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FPlanarLimit); }
	static inline consteval int16 GetStructAlignment() { return alignof(FPlanarLimit); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Structure representing a planar limit for collision in KawaiiPhysics.\n */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Structure representing a planar limit for collision in KawaiiPhysics." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Plane_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The plane defining the planar limit */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCollisionLimits.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The plane defining the planar limit" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FPlanarLimit constinit property declarations **********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Plane;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FPlanarLimit constinit property declarations ************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FPlanarLimit>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FPlanarLimit_Statics
static_assert(std::is_polymorphic<FPlanarLimit>() == std::is_polymorphic<FCollisionLimitBase>(), "USTRUCT FPlanarLimit cannot be polymorphic unless super FCollisionLimitBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FPlanarLimit;
class UScriptStruct* FPlanarLimit::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FPlanarLimit.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FPlanarLimit.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FPlanarLimit, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("PlanarLimit"));
	}
	return Z_Registration_Info_UScriptStruct_FPlanarLimit.OuterSingleton;
	}

// ********** Begin ScriptStruct FPlanarLimit Property Definitions *********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FPlanarLimit_Statics::NewProp_Plane = { "Plane", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPlanarLimit, Plane), Z_Construct_UScriptStruct_FPlane, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Plane_MetaData), NewProp_Plane_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FPlanarLimit_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPlanarLimit_Statics::NewProp_Plane,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPlanarLimit_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FPlanarLimit Property Definitions ***********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FPlanarLimit_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	Z_Construct_UScriptStruct_FCollisionLimitBase,
	&NewStructOps,
	"PlanarLimit",
	Z_Construct_UScriptStruct_FPlanarLimit_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPlanarLimit_Statics::PropPointers),
	sizeof(FPlanarLimit),
	alignof(FPlanarLimit),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPlanarLimit_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FPlanarLimit_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FPlanarLimit()
{
	if (!Z_Registration_Info_UScriptStruct_FPlanarLimit.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FPlanarLimit.InnerSingleton, Z_Construct_UScriptStruct_FPlanarLimit_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FPlanarLimit.InnerSingleton);
}
// ********** End ScriptStruct FPlanarLimit ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCollisionLimits_h__Script_KawaiiPhysics_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ ECollisionLimitType_StaticEnum, TEXT("ECollisionLimitType"), &Z_Registration_Info_UEnum_ECollisionLimitType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 289547355U) },
		{ ECollisionSourceType_StaticEnum, TEXT("ECollisionSourceType"), &Z_Registration_Info_UEnum_ECollisionSourceType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1161007709U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FCollisionLimitBase::StaticStruct, Z_Construct_UScriptStruct_FCollisionLimitBase_Statics::NewStructOps, TEXT("CollisionLimitBase"),&Z_Registration_Info_UScriptStruct_FCollisionLimitBase, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FCollisionLimitBase), 151384694U) },
		{ FSphericalLimit::StaticStruct, Z_Construct_UScriptStruct_FSphericalLimit_Statics::NewStructOps, TEXT("SphericalLimit"),&Z_Registration_Info_UScriptStruct_FSphericalLimit, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FSphericalLimit), 2652509308U) },
		{ FCapsuleLimit::StaticStruct, Z_Construct_UScriptStruct_FCapsuleLimit_Statics::NewStructOps, TEXT("CapsuleLimit"),&Z_Registration_Info_UScriptStruct_FCapsuleLimit, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FCapsuleLimit), 1186296507U) },
		{ FBoxLimit::StaticStruct, Z_Construct_UScriptStruct_FBoxLimit_Statics::NewStructOps, TEXT("BoxLimit"),&Z_Registration_Info_UScriptStruct_FBoxLimit, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBoxLimit), 3222352506U) },
		{ FPlanarLimit::StaticStruct, Z_Construct_UScriptStruct_FPlanarLimit_Statics::NewStructOps, TEXT("PlanarLimit"),&Z_Registration_Info_UScriptStruct_FPlanarLimit, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FPlanarLimit), 4101723162U) },
	};
}; // Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCollisionLimits_h__Script_KawaiiPhysics_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCollisionLimits_h__Script_KawaiiPhysics_596244209{
	TEXT("/Script/KawaiiPhysics"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCollisionLimits_h__Script_KawaiiPhysics_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCollisionLimits_h__Script_KawaiiPhysics_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCollisionLimits_h__Script_KawaiiPhysics_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCollisionLimits_h__Script_KawaiiPhysics_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
