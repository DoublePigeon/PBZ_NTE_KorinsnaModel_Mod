// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "KawaiiPhysicsCustomExternalForce.h"

#ifdef KAWAIIPHYSICS_KawaiiPhysicsCustomExternalForce_generated_h
#error "KawaiiPhysicsCustomExternalForce.generated.h already included, missing '#pragma once' in KawaiiPhysicsCustomExternalForce.h"
#endif
#define KAWAIIPHYSICS_KawaiiPhysicsCustomExternalForce_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class USkeletalMeshComponent;
struct FAnimNode_KawaiiPhysics;

// ********** Begin Class UKawaiiPhysics_CustomExternalForce ***************************************
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCustomExternalForce_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execIsDebugEnabled); \
	DECLARE_FUNCTION(execApply); \
	DECLARE_FUNCTION(execPreApply);


#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCustomExternalForce_h_11_CALLBACK_WRAPPERS
struct Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics;
KAWAIIPHYSICS_API UClass* Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_NoRegister();

#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCustomExternalForce_h_11_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUKawaiiPhysics_CustomExternalForce(); \
	friend struct ::Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend KAWAIIPHYSICS_API UClass* ::Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_NoRegister(); \
public: \
	DECLARE_CLASS2(UKawaiiPhysics_CustomExternalForce, UObject, COMPILED_IN_FLAGS(CLASS_Abstract), CASTCLASS_None, TEXT("/Script/KawaiiPhysics"), Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_NoRegister) \
	DECLARE_SERIALIZER(UKawaiiPhysics_CustomExternalForce)


#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCustomExternalForce_h_11_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UKawaiiPhysics_CustomExternalForce(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UKawaiiPhysics_CustomExternalForce(UKawaiiPhysics_CustomExternalForce&&) = delete; \
	UKawaiiPhysics_CustomExternalForce(const UKawaiiPhysics_CustomExternalForce&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UKawaiiPhysics_CustomExternalForce); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UKawaiiPhysics_CustomExternalForce); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UKawaiiPhysics_CustomExternalForce) \
	NO_API virtual ~UKawaiiPhysics_CustomExternalForce();


#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCustomExternalForce_h_8_PROLOG
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCustomExternalForce_h_11_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCustomExternalForce_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCustomExternalForce_h_11_CALLBACK_WRAPPERS \
	FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCustomExternalForce_h_11_INCLASS_NO_PURE_DECLS \
	FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCustomExternalForce_h_11_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UKawaiiPhysics_CustomExternalForce;

// ********** End Class UKawaiiPhysics_CustomExternalForce *****************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCustomExternalForce_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
