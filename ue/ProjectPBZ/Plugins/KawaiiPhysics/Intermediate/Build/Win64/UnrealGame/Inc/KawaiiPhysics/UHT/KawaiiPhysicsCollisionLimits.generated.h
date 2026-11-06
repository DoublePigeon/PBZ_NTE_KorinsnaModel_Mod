// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "KawaiiPhysicsCollisionLimits.h"

#ifdef KAWAIIPHYSICS_KawaiiPhysicsCollisionLimits_generated_h
#error "KawaiiPhysicsCollisionLimits.generated.h already included, missing '#pragma once' in KawaiiPhysicsCollisionLimits.h"
#endif
#define KAWAIIPHYSICS_KawaiiPhysicsCollisionLimits_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FCollisionLimitBase ***********************************************
struct Z_Construct_UScriptStruct_FCollisionLimitBase_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCollisionLimits_h_44_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FCollisionLimitBase_Statics; \
	KAWAIIPHYSICS_API static class UScriptStruct* StaticStruct();


struct FCollisionLimitBase;
// ********** End ScriptStruct FCollisionLimitBase *************************************************

// ********** Begin ScriptStruct FSphericalLimit ***************************************************
struct Z_Construct_UScriptStruct_FSphericalLimit_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCollisionLimits_h_110_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FSphericalLimit_Statics; \
	KAWAIIPHYSICS_API static class UScriptStruct* StaticStruct(); \
	typedef FCollisionLimitBase Super;


struct FSphericalLimit;
// ********** End ScriptStruct FSphericalLimit *****************************************************

// ********** Begin ScriptStruct FCapsuleLimit *****************************************************
struct Z_Construct_UScriptStruct_FCapsuleLimit_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCollisionLimits_h_145_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FCapsuleLimit_Statics; \
	KAWAIIPHYSICS_API static class UScriptStruct* StaticStruct(); \
	typedef FCollisionLimitBase Super;


struct FCapsuleLimit;
// ********** End ScriptStruct FCapsuleLimit *******************************************************

// ********** Begin ScriptStruct FBoxLimit *********************************************************
struct Z_Construct_UScriptStruct_FBoxLimit_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCollisionLimits_h_180_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FBoxLimit_Statics; \
	KAWAIIPHYSICS_API static class UScriptStruct* StaticStruct(); \
	typedef FCollisionLimitBase Super;


struct FBoxLimit;
// ********** End ScriptStruct FBoxLimit ***********************************************************

// ********** Begin ScriptStruct FPlanarLimit ******************************************************
struct Z_Construct_UScriptStruct_FPlanarLimit_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCollisionLimits_h_210_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FPlanarLimit_Statics; \
	KAWAIIPHYSICS_API static class UScriptStruct* StaticStruct(); \
	typedef FCollisionLimitBase Super;


struct FPlanarLimit;
// ********** End ScriptStruct FPlanarLimit ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCollisionLimits_h

// ********** Begin Enum ECollisionLimitType *******************************************************
#define FOREACH_ENUM_ECOLLISIONLIMITTYPE(op) \
	op(ECollisionLimitType::None) \
	op(ECollisionLimitType::Spherical) \
	op(ECollisionLimitType::Capsule) \
	op(ECollisionLimitType::Box) \
	op(ECollisionLimitType::Planar) 

enum class ECollisionLimitType : uint8;
template<> struct TIsUEnumClass<ECollisionLimitType> { enum { Value = true }; };
template<> KAWAIIPHYSICS_NON_ATTRIBUTED_API UEnum* StaticEnum<ECollisionLimitType>();
// ********** End Enum ECollisionLimitType *********************************************************

// ********** Begin Enum ECollisionSourceType ******************************************************
#define FOREACH_ENUM_ECOLLISIONSOURCETYPE(op) \
	op(ECollisionSourceType::AnimNode) \
	op(ECollisionSourceType::DataAsset) \
	op(ECollisionSourceType::PhysicsAsset) 

enum class ECollisionSourceType : uint8;
template<> struct TIsUEnumClass<ECollisionSourceType> { enum { Value = true }; };
template<> KAWAIIPHYSICS_NON_ATTRIBUTED_API UEnum* StaticEnum<ECollisionSourceType>();
// ********** End Enum ECollisionSourceType ********************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
