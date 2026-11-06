// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "KawaiiPhysicsSyncBone.h"

#ifdef KAWAIIPHYSICS_KawaiiPhysicsSyncBone_generated_h
#error "KawaiiPhysicsSyncBone.generated.h already included, missing '#pragma once' in KawaiiPhysicsSyncBone.h"
#endif
#define KAWAIIPHYSICS_KawaiiPhysicsSyncBone_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FKawaiiPhysicsSyncTarget ******************************************
struct Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSyncBone_h_31_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics; \
	static class UScriptStruct* StaticStruct();


struct FKawaiiPhysicsSyncTarget;
// ********** End ScriptStruct FKawaiiPhysicsSyncTarget ********************************************

// ********** Begin ScriptStruct FKawaiiPhysicsSyncTargetRoot **************************************
struct Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTargetRoot_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSyncBone_h_101_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTargetRoot_Statics; \
	static class UScriptStruct* StaticStruct(); \
	typedef FKawaiiPhysicsSyncTarget Super;


struct FKawaiiPhysicsSyncTargetRoot;
// ********** End ScriptStruct FKawaiiPhysicsSyncTargetRoot ****************************************

// ********** Begin ScriptStruct FKawaiiPhysicsSyncBone ********************************************
struct Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSyncBone_h_144_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics; \
	static class UScriptStruct* StaticStruct();


struct FKawaiiPhysicsSyncBone;
// ********** End ScriptStruct FKawaiiPhysicsSyncBone **********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSyncBone_h

// ********** Begin Enum ESyncBoneDirection ********************************************************
#define FOREACH_ENUM_ESYNCBONEDIRECTION(op) \
	op(ESyncBoneDirection::Both) \
	op(ESyncBoneDirection::Positive) \
	op(ESyncBoneDirection::Negative) \
	op(ESyncBoneDirection::None) 

enum class ESyncBoneDirection : uint8;
template<> struct TIsUEnumClass<ESyncBoneDirection> { enum { Value = true }; };
template<> KAWAIIPHYSICS_NON_ATTRIBUTED_API UEnum* StaticEnum<ESyncBoneDirection>();
// ********** End Enum ESyncBoneDirection **********************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
