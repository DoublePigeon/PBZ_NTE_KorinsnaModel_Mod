// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ExternalForces/KawaiiPhysicsExternalForce.h"

#ifdef KAWAIIPHYSICS_KawaiiPhysicsExternalForce_generated_h
#error "KawaiiPhysicsExternalForce.generated.h already included, missing '#pragma once' in KawaiiPhysicsExternalForce.h"
#endif
#define KAWAIIPHYSICS_KawaiiPhysicsExternalForce_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FKawaiiPhysics_ExternalForce **************************************
struct Z_Construct_UScriptStruct_FKawaiiPhysics_ExternalForce_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_ExternalForces_KawaiiPhysicsExternalForce_h_52_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FKawaiiPhysics_ExternalForce_Statics; \
	static class UScriptStruct* StaticStruct();


struct FKawaiiPhysics_ExternalForce;
// ********** End ScriptStruct FKawaiiPhysics_ExternalForce ****************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_ExternalForces_KawaiiPhysicsExternalForce_h

// ********** Begin Enum EExternalForceSpace *******************************************************
#define FOREACH_ENUM_EEXTERNALFORCESPACE(op) \
	op(EExternalForceSpace::ComponentSpace) \
	op(EExternalForceSpace::WorldSpace) \
	op(EExternalForceSpace::BoneSpace) 

enum class EExternalForceSpace : uint8;
template<> struct TIsUEnumClass<EExternalForceSpace> { enum { Value = true }; };
template<> KAWAIIPHYSICS_NON_ATTRIBUTED_API UEnum* StaticEnum<EExternalForceSpace>();
// ********** End Enum EExternalForceSpace *********************************************************

// ********** Begin Enum EExternalForceCurveEvaluateType *******************************************
#define FOREACH_ENUM_EEXTERNALFORCECURVEEVALUATETYPE(op) \
	op(EExternalForceCurveEvaluateType::Single) \
	op(EExternalForceCurveEvaluateType::Average) \
	op(EExternalForceCurveEvaluateType::Max) \
	op(EExternalForceCurveEvaluateType::Min) 

enum class EExternalForceCurveEvaluateType : uint8;
template<> struct TIsUEnumClass<EExternalForceCurveEvaluateType> { enum { Value = true }; };
template<> KAWAIIPHYSICS_NON_ATTRIBUTED_API UEnum* StaticEnum<EExternalForceCurveEvaluateType>();
// ********** End Enum EExternalForceCurveEvaluateType *********************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
