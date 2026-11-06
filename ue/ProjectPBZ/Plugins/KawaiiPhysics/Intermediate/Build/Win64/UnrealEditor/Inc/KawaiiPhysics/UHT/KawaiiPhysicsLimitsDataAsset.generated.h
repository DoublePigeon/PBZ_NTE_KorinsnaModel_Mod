// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "KawaiiPhysicsLimitsDataAsset.h"

#ifdef KAWAIIPHYSICS_KawaiiPhysicsLimitsDataAsset_generated_h
#error "KawaiiPhysicsLimitsDataAsset.generated.h already included, missing '#pragma once' in KawaiiPhysicsLimitsDataAsset.h"
#endif
#define KAWAIIPHYSICS_KawaiiPhysicsLimitsDataAsset_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FCollisionLimitDataBase *******************************************
struct Z_Construct_UScriptStruct_FCollisionLimitDataBase_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsLimitsDataAsset_h_16_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FCollisionLimitDataBase_Statics; \
	KAWAIIPHYSICS_API static class UScriptStruct* StaticStruct();


struct FCollisionLimitDataBase;
// ********** End ScriptStruct FCollisionLimitDataBase *********************************************

// ********** Begin ScriptStruct FSphericalLimitData ***********************************************
struct Z_Construct_UScriptStruct_FSphericalLimitData_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsLimitsDataAsset_h_59_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FSphericalLimitData_Statics; \
	KAWAIIPHYSICS_API static class UScriptStruct* StaticStruct(); \
	typedef FCollisionLimitDataBase Super;


struct FSphericalLimitData;
// ********** End ScriptStruct FSphericalLimitData *************************************************

// ********** Begin ScriptStruct FCapsuleLimitData *************************************************
struct Z_Construct_UScriptStruct_FCapsuleLimitData_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsLimitsDataAsset_h_84_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FCapsuleLimitData_Statics; \
	KAWAIIPHYSICS_API static class UScriptStruct* StaticStruct(); \
	typedef FCollisionLimitDataBase Super;


struct FCapsuleLimitData;
// ********** End ScriptStruct FCapsuleLimitData ***************************************************

// ********** Begin ScriptStruct FBoxLimitData *****************************************************
struct Z_Construct_UScriptStruct_FBoxLimitData_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsLimitsDataAsset_h_107_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FBoxLimitData_Statics; \
	KAWAIIPHYSICS_API static class UScriptStruct* StaticStruct(); \
	typedef FCollisionLimitDataBase Super;


struct FBoxLimitData;
// ********** End ScriptStruct FBoxLimitData *******************************************************

// ********** Begin ScriptStruct FPlanarLimitData **************************************************
struct Z_Construct_UScriptStruct_FPlanarLimitData_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsLimitsDataAsset_h_126_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FPlanarLimitData_Statics; \
	KAWAIIPHYSICS_API static class UScriptStruct* StaticStruct(); \
	typedef FCollisionLimitDataBase Super;


struct FPlanarLimitData;
// ********** End ScriptStruct FPlanarLimitData ****************************************************

// ********** Begin Class UKawaiiPhysicsLimitsDataAsset ********************************************
#if WITH_EDITORONLY_DATA
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsLimitsDataAsset_h_149_ARCHIVESERIALIZER \
	DECLARE_FARCHIVE_SERIALIZER(UKawaiiPhysicsLimitsDataAsset, NO_API)
#else // WITH_EDITORONLY_DATA
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsLimitsDataAsset_h_149_ARCHIVESERIALIZER
#endif // WITH_EDITORONLY_DATA


struct Z_Construct_UClass_UKawaiiPhysicsLimitsDataAsset_Statics;
KAWAIIPHYSICS_API UClass* Z_Construct_UClass_UKawaiiPhysicsLimitsDataAsset_NoRegister();

#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsLimitsDataAsset_h_149_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUKawaiiPhysicsLimitsDataAsset(); \
	friend struct ::Z_Construct_UClass_UKawaiiPhysicsLimitsDataAsset_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend KAWAIIPHYSICS_API UClass* ::Z_Construct_UClass_UKawaiiPhysicsLimitsDataAsset_NoRegister(); \
public: \
	DECLARE_CLASS2(UKawaiiPhysicsLimitsDataAsset, UDataAsset, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/KawaiiPhysics"), Z_Construct_UClass_UKawaiiPhysicsLimitsDataAsset_NoRegister) \
	DECLARE_SERIALIZER(UKawaiiPhysicsLimitsDataAsset) \
	FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsLimitsDataAsset_h_149_ARCHIVESERIALIZER \
	virtual UObject* _getUObject() const override { return const_cast<UKawaiiPhysicsLimitsDataAsset*>(this); }


#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsLimitsDataAsset_h_149_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UKawaiiPhysicsLimitsDataAsset(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UKawaiiPhysicsLimitsDataAsset(UKawaiiPhysicsLimitsDataAsset&&) = delete; \
	UKawaiiPhysicsLimitsDataAsset(const UKawaiiPhysicsLimitsDataAsset&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UKawaiiPhysicsLimitsDataAsset); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UKawaiiPhysicsLimitsDataAsset); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UKawaiiPhysicsLimitsDataAsset) \
	NO_API virtual ~UKawaiiPhysicsLimitsDataAsset();


#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsLimitsDataAsset_h_145_PROLOG
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsLimitsDataAsset_h_149_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsLimitsDataAsset_h_149_INCLASS_NO_PURE_DECLS \
	FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsLimitsDataAsset_h_149_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UKawaiiPhysicsLimitsDataAsset;

// ********** End Class UKawaiiPhysicsLimitsDataAsset **********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsLimitsDataAsset_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
