// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "KawaiiPhysicsBoneConstraintsDataAsset.h"

#ifdef KAWAIIPHYSICS_KawaiiPhysicsBoneConstraintsDataAsset_generated_h
#error "KawaiiPhysicsBoneConstraintsDataAsset.generated.h already included, missing '#pragma once' in KawaiiPhysicsBoneConstraintsDataAsset.h"
#endif
#define KAWAIIPHYSICS_KawaiiPhysicsBoneConstraintsDataAsset_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FModifyBoneConstraintData *****************************************
struct Z_Construct_UScriptStruct_FModifyBoneConstraintData_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintsDataAsset_h_16_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FModifyBoneConstraintData_Statics; \
	static class UScriptStruct* StaticStruct();


struct FModifyBoneConstraintData;
// ********** End ScriptStruct FModifyBoneConstraintData *******************************************

// ********** Begin ScriptStruct FRegexPatternBoneSet **********************************************
struct Z_Construct_UScriptStruct_FRegexPatternBoneSet_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintsDataAsset_h_62_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FRegexPatternBoneSet_Statics; \
	KAWAIIPHYSICS_API static class UScriptStruct* StaticStruct();


struct FRegexPatternBoneSet;
// ********** End ScriptStruct FRegexPatternBoneSet ************************************************

// ********** Begin Class UKawaiiPhysicsBoneConstraintsDataAsset ***********************************
#if WITH_EDITOR
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintsDataAsset_h_81_RPC_WRAPPERS_NO_PURE_DECLS_EOD \
	DECLARE_FUNCTION(execApplyRegex);
#else // WITH_EDITOR
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintsDataAsset_h_81_RPC_WRAPPERS_NO_PURE_DECLS_EOD
#endif // WITH_EDITOR


#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintsDataAsset_h_81_ARCHIVESERIALIZER \
	DECLARE_FARCHIVE_SERIALIZER(UKawaiiPhysicsBoneConstraintsDataAsset, NO_API)


struct Z_Construct_UClass_UKawaiiPhysicsBoneConstraintsDataAsset_Statics;
KAWAIIPHYSICS_API UClass* Z_Construct_UClass_UKawaiiPhysicsBoneConstraintsDataAsset_NoRegister();

#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintsDataAsset_h_81_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUKawaiiPhysicsBoneConstraintsDataAsset(); \
	friend struct ::Z_Construct_UClass_UKawaiiPhysicsBoneConstraintsDataAsset_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend KAWAIIPHYSICS_API UClass* ::Z_Construct_UClass_UKawaiiPhysicsBoneConstraintsDataAsset_NoRegister(); \
public: \
	DECLARE_CLASS2(UKawaiiPhysicsBoneConstraintsDataAsset, UDataAsset, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/KawaiiPhysics"), Z_Construct_UClass_UKawaiiPhysicsBoneConstraintsDataAsset_NoRegister) \
	DECLARE_SERIALIZER(UKawaiiPhysicsBoneConstraintsDataAsset) \
	FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintsDataAsset_h_81_ARCHIVESERIALIZER \
	virtual UObject* _getUObject() const override { return const_cast<UKawaiiPhysicsBoneConstraintsDataAsset*>(this); }


#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintsDataAsset_h_81_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UKawaiiPhysicsBoneConstraintsDataAsset(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UKawaiiPhysicsBoneConstraintsDataAsset(UKawaiiPhysicsBoneConstraintsDataAsset&&) = delete; \
	UKawaiiPhysicsBoneConstraintsDataAsset(const UKawaiiPhysicsBoneConstraintsDataAsset&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UKawaiiPhysicsBoneConstraintsDataAsset); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UKawaiiPhysicsBoneConstraintsDataAsset); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UKawaiiPhysicsBoneConstraintsDataAsset) \
	NO_API virtual ~UKawaiiPhysicsBoneConstraintsDataAsset();


#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintsDataAsset_h_77_PROLOG
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintsDataAsset_h_81_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintsDataAsset_h_81_RPC_WRAPPERS_NO_PURE_DECLS_EOD \
	FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintsDataAsset_h_81_INCLASS_NO_PURE_DECLS \
	FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintsDataAsset_h_81_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UKawaiiPhysicsBoneConstraintsDataAsset;

// ********** End Class UKawaiiPhysicsBoneConstraintsDataAsset *************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintsDataAsset_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
