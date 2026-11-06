// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "KawaiiPhysicsBoneConstraintTypes.h"

#ifdef KAWAIIPHYSICS_KawaiiPhysicsBoneConstraintTypes_generated_h
#error "KawaiiPhysicsBoneConstraintTypes.generated.h already included, missing '#pragma once' in KawaiiPhysicsBoneConstraintTypes.h"
#endif
#define KAWAIIPHYSICS_KawaiiPhysicsBoneConstraintTypes_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FModifyBoneConstraint *********************************************
struct Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics;
#define FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintTypes_h_27_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FModifyBoneConstraint_Statics; \
	KAWAIIPHYSICS_API static class UScriptStruct* StaticStruct();


struct FModifyBoneConstraint;
// ********** End ScriptStruct FModifyBoneConstraint ***********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsBoneConstraintTypes_h

// ********** Begin Enum EXPBDComplianceType *******************************************************
#define FOREACH_ENUM_EXPBDCOMPLIANCETYPE(op) \
	op(EXPBDComplianceType::Concrete) \
	op(EXPBDComplianceType::Wood) \
	op(EXPBDComplianceType::Leather) \
	op(EXPBDComplianceType::Tendon) \
	op(EXPBDComplianceType::Rubber) \
	op(EXPBDComplianceType::Muscle) \
	op(EXPBDComplianceType::Fat) 

enum class EXPBDComplianceType : uint8;
template<> struct TIsUEnumClass<EXPBDComplianceType> { enum { Value = true }; };
template<> KAWAIIPHYSICS_NON_ATTRIBUTED_API UEnum* StaticEnum<EXPBDComplianceType>();
// ********** End Enum EXPBDComplianceType *********************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
