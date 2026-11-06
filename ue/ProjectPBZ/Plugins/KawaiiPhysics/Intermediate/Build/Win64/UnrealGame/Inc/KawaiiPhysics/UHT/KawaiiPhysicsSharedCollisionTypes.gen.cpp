// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "KawaiiPhysicsSharedCollisionTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeKawaiiPhysicsSharedCollisionTypes() {}

// ********** Begin Cross Module References ********************************************************
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FKawaiiPhysicsSharedCollisionData();
UPackage* Z_Construct_UPackage__Script_KawaiiPhysics();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FKawaiiPhysicsSharedCollisionData *********************************
struct Z_Construct_UScriptStruct_FKawaiiPhysicsSharedCollisionData_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FKawaiiPhysicsSharedCollisionData); }
	static inline consteval int16 GetStructAlignment() { return alignof(FKawaiiPhysicsSharedCollisionData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \xe5\x85\xb1\xe6\x9c\x89\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x83\x87\xe3\x83\xbc\xe3\x82\xbf\xef\xbc\x88\xe3\x83\xaf\xe3\x83\xbc\xe3\x83\xab\xe3\x83\x89\xe7\xa9\xba\xe9\x96\x93\xe3\x80\x81\xe8\xa8\x88\xe7\xae\x97\xe6\xb8\x88\xe3\x81\xbf\xef\xbc\x89\n * Pre-computed collision data in world space for sharing between KawaiiPhysics AnimNodes\n */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSharedCollisionTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x85\xb1\xe6\x9c\x89\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x83\x87\xe3\x83\xbc\xe3\x82\xbf\xef\xbc\x88\xe3\x83\xaf\xe3\x83\xbc\xe3\x83\xab\xe3\x83\x89\xe7\xa9\xba\xe9\x96\x93\xe3\x80\x81\xe8\xa8\x88\xe7\xae\x97\xe6\xb8\x88\xe3\x81\xbf\xef\xbc\x89\nPre-computed collision data in world space for sharing between KawaiiPhysics AnimNodes" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FKawaiiPhysicsSharedCollisionData constinit property declarations *
// ********** End ScriptStruct FKawaiiPhysicsSharedCollisionData constinit property declarations ***
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FKawaiiPhysicsSharedCollisionData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FKawaiiPhysicsSharedCollisionData_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FKawaiiPhysicsSharedCollisionData;
class UScriptStruct* FKawaiiPhysicsSharedCollisionData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FKawaiiPhysicsSharedCollisionData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FKawaiiPhysicsSharedCollisionData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FKawaiiPhysicsSharedCollisionData, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("KawaiiPhysicsSharedCollisionData"));
	}
	return Z_Registration_Info_UScriptStruct_FKawaiiPhysicsSharedCollisionData.OuterSingleton;
	}
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FKawaiiPhysicsSharedCollisionData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	nullptr,
	&NewStructOps,
	"KawaiiPhysicsSharedCollisionData",
	nullptr,
	0,
	sizeof(FKawaiiPhysicsSharedCollisionData),
	alignof(FKawaiiPhysicsSharedCollisionData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FKawaiiPhysicsSharedCollisionData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FKawaiiPhysicsSharedCollisionData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FKawaiiPhysicsSharedCollisionData()
{
	if (!Z_Registration_Info_UScriptStruct_FKawaiiPhysicsSharedCollisionData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FKawaiiPhysicsSharedCollisionData.InnerSingleton, Z_Construct_UScriptStruct_FKawaiiPhysicsSharedCollisionData_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FKawaiiPhysicsSharedCollisionData.InnerSingleton);
}
// ********** End ScriptStruct FKawaiiPhysicsSharedCollisionData ***********************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSharedCollisionTypes_h__Script_KawaiiPhysics_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FKawaiiPhysicsSharedCollisionData::StaticStruct, Z_Construct_UScriptStruct_FKawaiiPhysicsSharedCollisionData_Statics::NewStructOps, TEXT("KawaiiPhysicsSharedCollisionData"),&Z_Registration_Info_UScriptStruct_FKawaiiPhysicsSharedCollisionData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FKawaiiPhysicsSharedCollisionData), 3639512401U) },
	};
}; // Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSharedCollisionTypes_h__Script_KawaiiPhysics_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSharedCollisionTypes_h__Script_KawaiiPhysics_2222994571{
	TEXT("/Script/KawaiiPhysics"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSharedCollisionTypes_h__Script_KawaiiPhysics_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSharedCollisionTypes_h__Script_KawaiiPhysics_Statics::ScriptStructInfo),
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
