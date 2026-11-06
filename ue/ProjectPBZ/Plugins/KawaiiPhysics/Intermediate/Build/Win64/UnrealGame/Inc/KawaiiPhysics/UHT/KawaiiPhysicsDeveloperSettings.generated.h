// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "KawaiiPhysicsDeveloperSettings.h"

#ifdef KAWAIIPHYSICS_KawaiiPhysicsDeveloperSettings_generated_h
#error "KawaiiPhysicsDeveloperSettings.generated.h already included, missing '#pragma once' in KawaiiPhysicsDeveloperSettings.h"
#endif
#define KAWAIIPHYSICS_KawaiiPhysicsDeveloperSettings_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UKawaiiPhysicsDeveloperSettings ******************************************
struct Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics;
KAWAIIPHYSICS_API UClass* Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_NoRegister();

#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsDeveloperSettings_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUKawaiiPhysicsDeveloperSettings(); \
	friend struct ::Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend KAWAIIPHYSICS_API UClass* ::Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_NoRegister(); \
public: \
	DECLARE_CLASS2(UKawaiiPhysicsDeveloperSettings, UDeveloperSettings, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), CASTCLASS_None, TEXT("/Script/KawaiiPhysics"), Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_NoRegister) \
	DECLARE_SERIALIZER(UKawaiiPhysicsDeveloperSettings) \
	static constexpr const TCHAR* StaticConfigName() {return TEXT("Engine");} \



#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsDeveloperSettings_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UKawaiiPhysicsDeveloperSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UKawaiiPhysicsDeveloperSettings(UKawaiiPhysicsDeveloperSettings&&) = delete; \
	UKawaiiPhysicsDeveloperSettings(const UKawaiiPhysicsDeveloperSettings&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UKawaiiPhysicsDeveloperSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UKawaiiPhysicsDeveloperSettings); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UKawaiiPhysicsDeveloperSettings) \
	NO_API virtual ~UKawaiiPhysicsDeveloperSettings();


#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsDeveloperSettings_h_13_PROLOG
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsDeveloperSettings_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsDeveloperSettings_h_16_INCLASS_NO_PURE_DECLS \
	FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsDeveloperSettings_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UKawaiiPhysicsDeveloperSettings;

// ********** End Class UKawaiiPhysicsDeveloperSettings ********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsDeveloperSettings_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
