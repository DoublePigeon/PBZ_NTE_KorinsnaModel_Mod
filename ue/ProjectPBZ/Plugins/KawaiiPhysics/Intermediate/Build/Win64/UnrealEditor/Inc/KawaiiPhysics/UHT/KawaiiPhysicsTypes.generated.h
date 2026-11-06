// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "KawaiiPhysicsTypes.h"

#ifdef KAWAIIPHYSICS_KawaiiPhysicsTypes_generated_h
#error "KawaiiPhysicsTypes.generated.h already included, missing '#pragma once' in KawaiiPhysicsTypes.h"
#endif
#define KAWAIIPHYSICS_KawaiiPhysicsTypes_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FKawaiiPhysicsRootBoneSetting *************************************
struct Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsTypes_h_56_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FKawaiiPhysicsRootBoneSetting_Statics; \
	static class UScriptStruct* StaticStruct();


struct FKawaiiPhysicsRootBoneSetting;
// ********** End ScriptStruct FKawaiiPhysicsRootBoneSetting ***************************************

// ********** Begin ScriptStruct FKawaiiPhysicsSettings ********************************************
struct Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsTypes_h_82_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FKawaiiPhysicsSettings_Statics; \
	static class UScriptStruct* StaticStruct();


struct FKawaiiPhysicsSettings;
// ********** End ScriptStruct FKawaiiPhysicsSettings **********************************************

// ********** Begin ScriptStruct FKawaiiPhysicsModifyBone ******************************************
struct Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsTypes_h_138_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FKawaiiPhysicsModifyBone_Statics; \
	static class UScriptStruct* StaticStruct();


struct FKawaiiPhysicsModifyBone;
// ********** End ScriptStruct FKawaiiPhysicsModifyBone ********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsTypes_h

// ********** Begin Enum EKawaiiPhysicsSimulationSpace *********************************************
#define FOREACH_ENUM_EKAWAIIPHYSICSSIMULATIONSPACE(op) \
	op(EKawaiiPhysicsSimulationSpace::ComponentSpace) \
	op(EKawaiiPhysicsSimulationSpace::WorldSpace) \
	op(EKawaiiPhysicsSimulationSpace::BaseBoneSpace) 

enum class EKawaiiPhysicsSimulationSpace : uint8;
template<> struct TIsUEnumClass<EKawaiiPhysicsSimulationSpace> { enum { Value = true }; };
template<> KAWAIIPHYSICS_NON_ATTRIBUTED_API UEnum* StaticEnum<EKawaiiPhysicsSimulationSpace>();
// ********** End Enum EKawaiiPhysicsSimulationSpace ***********************************************

// ********** Begin Enum EPlanarConstraint *********************************************************
#define FOREACH_ENUM_EPLANARCONSTRAINT(op) \
	op(EPlanarConstraint::None) \
	op(EPlanarConstraint::X) \
	op(EPlanarConstraint::Y) \
	op(EPlanarConstraint::Z) 

enum class EPlanarConstraint : uint8;
template<> struct TIsUEnumClass<EPlanarConstraint> { enum { Value = true }; };
template<> KAWAIIPHYSICS_NON_ATTRIBUTED_API UEnum* StaticEnum<EPlanarConstraint>();
// ********** End Enum EPlanarConstraint ***********************************************************

// ********** Begin Enum EBoneForwardAxis **********************************************************
#define FOREACH_ENUM_EBONEFORWARDAXIS(op) \
	op(EBoneForwardAxis::X_Positive) \
	op(EBoneForwardAxis::X_Negative) \
	op(EBoneForwardAxis::Y_Positive) \
	op(EBoneForwardAxis::Y_Negative) \
	op(EBoneForwardAxis::Z_Positive) \
	op(EBoneForwardAxis::Z_Negative) 

enum class EBoneForwardAxis : uint8;
template<> struct TIsUEnumClass<EBoneForwardAxis> { enum { Value = true }; };
template<> KAWAIIPHYSICS_NON_ATTRIBUTED_API UEnum* StaticEnum<EBoneForwardAxis>();
// ********** End Enum EBoneForwardAxis ************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
