// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "KawaiiPhysicsCustomExternalForce.h"
#include "AnimNode_KawaiiPhysics.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeKawaiiPhysicsCustomExternalForce() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FTransform();
ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
KAWAIIPHYSICS_API UClass* Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce();
KAWAIIPHYSICS_API UClass* Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_NoRegister();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics();
UPackage* Z_Construct_UPackage__Script_KawaiiPhysics();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UKawaiiPhysics_CustomExternalForce Function Apply ************************
struct KawaiiPhysics_CustomExternalForce_eventApply_Parms
{
	FAnimNode_KawaiiPhysics Node;
	int32 ModifyBoneIndex;
	const USkeletalMeshComponent* SkelComp;
	FTransform BoneTransform;
};
static FName NAME_UKawaiiPhysics_CustomExternalForce_Apply = FName(TEXT("Apply"));
void UKawaiiPhysics_CustomExternalForce::Apply(FAnimNode_KawaiiPhysics& Node, int32 ModifyBoneIndex, const USkeletalMeshComponent* SkelComp, FTransform const& BoneTransform)
{
	UFunction* Func = FindFunctionChecked(NAME_UKawaiiPhysics_CustomExternalForce_Apply);
	if (!Func->GetOwnerClass()->HasAnyClassFlags(CLASS_Native))
	{
		KawaiiPhysics_CustomExternalForce_eventApply_Parms Parms;
		Parms.Node=Node;
		Parms.ModifyBoneIndex=ModifyBoneIndex;
		Parms.SkelComp=SkelComp;
		Parms.BoneTransform=BoneTransform;
	ProcessEvent(Func,&Parms);
		Node=Parms.Node;
	}
	else
	{
		Apply_Implementation(Node, ModifyBoneIndex, SkelComp, BoneTransform);
	}
}
struct Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCustomExternalForce.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkelComp_MetaData[] = {
		{ "EditInline", "true" },
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoneTransform_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function Apply constinit property declarations *********************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Node;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ModifyBoneIndex;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SkelComp;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BoneTransform;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function Apply constinit property declarations ***********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function Apply Property Definitions ********************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply_Statics::NewProp_Node = { "Node", nullptr, (EPropertyFlags)0x0010008008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(KawaiiPhysics_CustomExternalForce_eventApply_Parms, Node), Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics, METADATA_PARAMS(0, nullptr) }; // 3752603673
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply_Statics::NewProp_ModifyBoneIndex = { "ModifyBoneIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(KawaiiPhysics_CustomExternalForce_eventApply_Parms, ModifyBoneIndex), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply_Statics::NewProp_SkelComp = { "SkelComp", nullptr, (EPropertyFlags)0x0010000000080082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(KawaiiPhysics_CustomExternalForce_eventApply_Parms, SkelComp), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkelComp_MetaData), NewProp_SkelComp_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply_Statics::NewProp_BoneTransform = { "BoneTransform", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(KawaiiPhysics_CustomExternalForce_eventApply_Parms, BoneTransform), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoneTransform_MetaData), NewProp_BoneTransform_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply_Statics::NewProp_Node,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply_Statics::NewProp_ModifyBoneIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply_Statics::NewProp_SkelComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply_Statics::NewProp_BoneTransform,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply_Statics::PropPointers) < 2048);
// ********** End Function Apply Property Definitions **********************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce, nullptr, "Apply", 	Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply_Statics::PropPointers), 
sizeof(KawaiiPhysics_CustomExternalForce_eventApply_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08C20C00, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply_Statics::Function_MetaDataParams), Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(KawaiiPhysics_CustomExternalForce_eventApply_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UKawaiiPhysics_CustomExternalForce::execApply)
{
	P_GET_STRUCT_REF(FAnimNode_KawaiiPhysics,Z_Param_Out_Node);
	P_GET_PROPERTY(FIntProperty,Z_Param_ModifyBoneIndex);
	P_GET_OBJECT(USkeletalMeshComponent,Z_Param_SkelComp);
	P_GET_STRUCT_REF(FTransform,Z_Param_Out_BoneTransform);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Apply_Implementation(Z_Param_Out_Node,Z_Param_ModifyBoneIndex,Z_Param_SkelComp,Z_Param_Out_BoneTransform);
	P_NATIVE_END;
}
// ********** End Class UKawaiiPhysics_CustomExternalForce Function Apply **************************

// ********** Begin Class UKawaiiPhysics_CustomExternalForce Function IsDebugEnabled ***************
struct Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_IsDebugEnabled_Statics
{
	struct KawaiiPhysics_CustomExternalForce_eventIsDebugEnabled_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "KawaiiPhysics|CustomExternalForce" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCustomExternalForce.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsDebugEnabled constinit property declarations ************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsDebugEnabled constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsDebugEnabled Property Definitions ***********************************
void Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_IsDebugEnabled_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((KawaiiPhysics_CustomExternalForce_eventIsDebugEnabled_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_IsDebugEnabled_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(KawaiiPhysics_CustomExternalForce_eventIsDebugEnabled_Parms), &Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_IsDebugEnabled_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_IsDebugEnabled_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_IsDebugEnabled_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_IsDebugEnabled_Statics::PropPointers) < 2048);
// ********** End Function IsDebugEnabled Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_IsDebugEnabled_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce, nullptr, "IsDebugEnabled", 	Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_IsDebugEnabled_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_IsDebugEnabled_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_IsDebugEnabled_Statics::KawaiiPhysics_CustomExternalForce_eventIsDebugEnabled_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_IsDebugEnabled_Statics::Function_MetaDataParams), Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_IsDebugEnabled_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_IsDebugEnabled_Statics::KawaiiPhysics_CustomExternalForce_eventIsDebugEnabled_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_IsDebugEnabled()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_IsDebugEnabled_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UKawaiiPhysics_CustomExternalForce::execIsDebugEnabled)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsDebugEnabled();
	P_NATIVE_END;
}
// ********** End Class UKawaiiPhysics_CustomExternalForce Function IsDebugEnabled *****************

// ********** Begin Class UKawaiiPhysics_CustomExternalForce Function PreApply *********************
struct KawaiiPhysics_CustomExternalForce_eventPreApply_Parms
{
	FAnimNode_KawaiiPhysics Node;
	const USkeletalMeshComponent* SkelComp;
};
static FName NAME_UKawaiiPhysics_CustomExternalForce_PreApply = FName(TEXT("PreApply"));
void UKawaiiPhysics_CustomExternalForce::PreApply(FAnimNode_KawaiiPhysics& Node, const USkeletalMeshComponent* SkelComp)
{
	UFunction* Func = FindFunctionChecked(NAME_UKawaiiPhysics_CustomExternalForce_PreApply);
	if (!Func->GetOwnerClass()->HasAnyClassFlags(CLASS_Native))
	{
		KawaiiPhysics_CustomExternalForce_eventPreApply_Parms Parms;
		Parms.Node=Node;
		Parms.SkelComp=SkelComp;
	ProcessEvent(Func,&Parms);
		Node=Parms.Node;
	}
	else
	{
		PreApply_Implementation(Node, SkelComp);
	}
}
struct Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_PreApply_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe9\x87\x8d\xe8\xa6\x81 / IMPORTANT (Thread-safety):\n// PreApply / Apply \xe3\x81\xaf EvaluateSkeletalControl_AnyThread \xe3\x81\x8b\xe3\x82\x89\xe5\x91\xbc\xe3\x81\xb0\xe3\x82\x8c\xe3\x80\x81\xe3\x82\xa2\xe3\x83\x8b\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xb7\xe3\x83\xa7\xe3\x83\xb3\xe3\x83\xbb\xe3\x83\xaf\xe3\x83\xbc\xe3\x82\xab\xe3\x83\xbc\xe3\x82\xb9\xe3\x83\xac\xe3\x83\x83\xe3\x83\x89\xe3\x81\xa7\xe5\x8b\x95\xe3\x81\x8d\xe3\x81\x86\xe3\x82\x8b\xe3\x80\x82\n// \xe5\xae\x9f\xe8\xa3\x85\xef\xbc\x88\xe7\x89\xb9\xe3\x81\xab BP\xef\xbc\x89\xe3\x81\xaf GameThread \xe5\xb0\x82\xe7\x94\xa8 API\xef\xbc\x88\xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc/\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xae\xe7\xa0\xb4\xe5\xa3\x8a\xe3\x83\xbb\xe3\x82\xb9\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\xb3\xe3\x80\x81\xe3\x83\xac\xe3\x82\xa4\xe3\x82\xad\xe3\x83\xa3\xe3\x82\xb9\xe3\x83\x88\xe3\x80\x81UObject \xe3\x83\xa9\xe3\x82\xa4\xe3\x83\x95\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xaf\xe3\x83\xab\xe7\xad\x89\xef\xbc\x89\xe3\x81\xab\xe8\xa7\xa6\xe3\x82\x8c\xe3\x81\xaa\xe3\x81\x84\xe3\x81\x93\xe3\x81\xa8\xe3\x80\x82\xe5\xbf\x85\xe8\xa6\x81\xe3\x81\xaa\xe5\x80\xa4\xe3\x81\xaf\xe4\xba\x8b\xe5\x89\x8d\xe3\x81\xab\xe3\x82\xad\xe3\x83\xa3\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\x97\xe3\x80\x81\xe3\x81\x93\xe3\x81\x93\xe3\x81\xa7\xe3\x81\xaf\xe8\xaa\xad\xe3\x81\xbf\xe5\x8f\x96\xe3\x82\x8a\xe3\x81\xae\xe3\x81\xbf\xe3\x80\x82\n// PreApply / Apply may run on the animation worker thread (called from EvaluateSkeletalControl_AnyThread).\n// Implementations (especially Blueprint) must NOT touch game-thread-only APIs (spawn/destroy actors/components, raycasts, UObject lifecycle); cache needed values beforehand and only read them here.\n" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCustomExternalForce.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x87\x8d\xe8\xa6\x81 / IMPORTANT (Thread-safety):\nPreApply / Apply \xe3\x81\xaf EvaluateSkeletalControl_AnyThread \xe3\x81\x8b\xe3\x82\x89\xe5\x91\xbc\xe3\x81\xb0\xe3\x82\x8c\xe3\x80\x81\xe3\x82\xa2\xe3\x83\x8b\xe3\x83\xa1\xe3\x83\xbc\xe3\x82\xb7\xe3\x83\xa7\xe3\x83\xb3\xe3\x83\xbb\xe3\x83\xaf\xe3\x83\xbc\xe3\x82\xab\xe3\x83\xbc\xe3\x82\xb9\xe3\x83\xac\xe3\x83\x83\xe3\x83\x89\xe3\x81\xa7\xe5\x8b\x95\xe3\x81\x8d\xe3\x81\x86\xe3\x82\x8b\xe3\x80\x82\n\xe5\xae\x9f\xe8\xa3\x85\xef\xbc\x88\xe7\x89\xb9\xe3\x81\xab BP\xef\xbc\x89\xe3\x81\xaf GameThread \xe5\xb0\x82\xe7\x94\xa8 API\xef\xbc\x88\xe3\x82\xa2\xe3\x82\xaf\xe3\x82\xbf\xe3\x83\xbc/\xe3\x82\xb3\xe3\x83\xb3\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\x8d\xe3\x83\xb3\xe3\x83\x88\xe3\x81\xae\xe7\xa0\xb4\xe5\xa3\x8a\xe3\x83\xbb\xe3\x82\xb9\xe3\x83\x9d\xe3\x83\xbc\xe3\x83\xb3\xe3\x80\x81\xe3\x83\xac\xe3\x82\xa4\xe3\x82\xad\xe3\x83\xa3\xe3\x82\xb9\xe3\x83\x88\xe3\x80\x81UObject \xe3\x83\xa9\xe3\x82\xa4\xe3\x83\x95\xe3\x82\xb5\xe3\x82\xa4\xe3\x82\xaf\xe3\x83\xab\xe7\xad\x89\xef\xbc\x89\xe3\x81\xab\xe8\xa7\xa6\xe3\x82\x8c\xe3\x81\xaa\xe3\x81\x84\xe3\x81\x93\xe3\x81\xa8\xe3\x80\x82\xe5\xbf\x85\xe8\xa6\x81\xe3\x81\xaa\xe5\x80\xa4\xe3\x81\xaf\xe4\xba\x8b\xe5\x89\x8d\xe3\x81\xab\xe3\x82\xad\xe3\x83\xa3\xe3\x83\x83\xe3\x82\xb7\xe3\x83\xa5\xe3\x81\x97\xe3\x80\x81\xe3\x81\x93\xe3\x81\x93\xe3\x81\xa7\xe3\x81\xaf\xe8\xaa\xad\xe3\x81\xbf\xe5\x8f\x96\xe3\x82\x8a\xe3\x81\xae\xe3\x81\xbf\xe3\x80\x82\nPreApply / Apply may run on the animation worker thread (called from EvaluateSkeletalControl_AnyThread).\nImplementations (especially Blueprint) must NOT touch game-thread-only APIs (spawn/destroy actors/components, raycasts, UObject lifecycle); cache needed values beforehand and only read them here." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkelComp_MetaData[] = {
		{ "EditInline", "true" },
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function PreApply constinit property declarations ******************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Node;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SkelComp;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function PreApply constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function PreApply Property Definitions *****************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_PreApply_Statics::NewProp_Node = { "Node", nullptr, (EPropertyFlags)0x0010008008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(KawaiiPhysics_CustomExternalForce_eventPreApply_Parms, Node), Z_Construct_UScriptStruct_FAnimNode_KawaiiPhysics, METADATA_PARAMS(0, nullptr) }; // 3752603673
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_PreApply_Statics::NewProp_SkelComp = { "SkelComp", nullptr, (EPropertyFlags)0x0010000000080082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(KawaiiPhysics_CustomExternalForce_eventPreApply_Parms, SkelComp), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkelComp_MetaData), NewProp_SkelComp_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_PreApply_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_PreApply_Statics::NewProp_Node,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_PreApply_Statics::NewProp_SkelComp,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_PreApply_Statics::PropPointers) < 2048);
// ********** End Function PreApply Property Definitions *******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_PreApply_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce, nullptr, "PreApply", 	Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_PreApply_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_PreApply_Statics::PropPointers), 
sizeof(KawaiiPhysics_CustomExternalForce_eventPreApply_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08420C00, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_PreApply_Statics::Function_MetaDataParams), Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_PreApply_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(KawaiiPhysics_CustomExternalForce_eventPreApply_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_PreApply()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_PreApply_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UKawaiiPhysics_CustomExternalForce::execPreApply)
{
	P_GET_STRUCT_REF(FAnimNode_KawaiiPhysics,Z_Param_Out_Node);
	P_GET_OBJECT(USkeletalMeshComponent,Z_Param_SkelComp);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PreApply_Implementation(Z_Param_Out_Node,Z_Param_SkelComp);
	P_NATIVE_END;
}
// ********** End Class UKawaiiPhysics_CustomExternalForce Function PreApply ***********************

// ********** Begin Class UKawaiiPhysics_CustomExternalForce ***************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UKawaiiPhysics_CustomExternalForce;
UClass* UKawaiiPhysics_CustomExternalForce::GetPrivateStaticClass()
{
	using TClass = UKawaiiPhysics_CustomExternalForce;
	if (!Z_Registration_Info_UClass_UKawaiiPhysics_CustomExternalForce.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("KawaiiPhysics_CustomExternalForce"),
			Z_Registration_Info_UClass_UKawaiiPhysics_CustomExternalForce.InnerSingleton,
			StaticRegisterNativesUKawaiiPhysics_CustomExternalForce,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UKawaiiPhysics_CustomExternalForce.InnerSingleton;
}
UClass* Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_NoRegister()
{
	return UKawaiiPhysics_CustomExternalForce::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "KawaiiPhysicsCustomExternalForce.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCustomExternalForce.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsEnabled_MetaData[] = {
		{ "Category", "KawaiiPhysics|CustomExternalForce" },
		{ "DisplayPriority", "1" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCustomExternalForce.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDrawDebug_MetaData[] = {
		{ "Category", "KawaiiPhysics|CustomExternalForce" },
		{ "DisplayPriority", "1" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsCustomExternalForce.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UKawaiiPhysics_CustomExternalForce constinit property declarations *******
	static void NewProp_bIsEnabled_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsEnabled;
	static void NewProp_bDrawDebug_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDrawDebug;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UKawaiiPhysics_CustomExternalForce constinit property declarations *********
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("Apply"), .Pointer = &UKawaiiPhysics_CustomExternalForce::execApply },
		{ .NameUTF8 = UTF8TEXT("IsDebugEnabled"), .Pointer = &UKawaiiPhysics_CustomExternalForce::execIsDebugEnabled },
		{ .NameUTF8 = UTF8TEXT("PreApply"), .Pointer = &UKawaiiPhysics_CustomExternalForce::execPreApply },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_Apply, "Apply" }, // 1589887215
		{ &Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_IsDebugEnabled, "IsDebugEnabled" }, // 3603803808
		{ &Z_Construct_UFunction_UKawaiiPhysics_CustomExternalForce_PreApply, "PreApply" }, // 2647743791
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UKawaiiPhysics_CustomExternalForce>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics

// ********** Begin Class UKawaiiPhysics_CustomExternalForce Property Definitions ******************
void Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::NewProp_bIsEnabled_SetBit(void* Obj)
{
	((UKawaiiPhysics_CustomExternalForce*)Obj)->bIsEnabled = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::NewProp_bIsEnabled = { "bIsEnabled", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UKawaiiPhysics_CustomExternalForce), &Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::NewProp_bIsEnabled_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsEnabled_MetaData), NewProp_bIsEnabled_MetaData) };
void Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::NewProp_bDrawDebug_SetBit(void* Obj)
{
	((UKawaiiPhysics_CustomExternalForce*)Obj)->bDrawDebug = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::NewProp_bDrawDebug = { "bDrawDebug", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UKawaiiPhysics_CustomExternalForce), &Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::NewProp_bDrawDebug_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDrawDebug_MetaData), NewProp_bDrawDebug_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::NewProp_bIsEnabled,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::NewProp_bDrawDebug,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::PropPointers) < 2048);
// ********** End Class UKawaiiPhysics_CustomExternalForce Property Definitions ********************
UObject* (*const Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_KawaiiPhysics,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::ClassParams = {
	&UKawaiiPhysics_CustomExternalForce::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::PropPointers),
	0,
	0x001030A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::Class_MetaDataParams), Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::Class_MetaDataParams)
};
void UKawaiiPhysics_CustomExternalForce::StaticRegisterNativesUKawaiiPhysics_CustomExternalForce()
{
	UClass* Class = UKawaiiPhysics_CustomExternalForce::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::Funcs));
}
UClass* Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce()
{
	if (!Z_Registration_Info_UClass_UKawaiiPhysics_CustomExternalForce.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UKawaiiPhysics_CustomExternalForce.OuterSingleton, Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UKawaiiPhysics_CustomExternalForce.OuterSingleton;
}
UKawaiiPhysics_CustomExternalForce::UKawaiiPhysics_CustomExternalForce(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UKawaiiPhysics_CustomExternalForce);
UKawaiiPhysics_CustomExternalForce::~UKawaiiPhysics_CustomExternalForce() {}
// ********** End Class UKawaiiPhysics_CustomExternalForce *****************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCustomExternalForce_h__Script_KawaiiPhysics_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UKawaiiPhysics_CustomExternalForce, UKawaiiPhysics_CustomExternalForce::StaticClass, TEXT("UKawaiiPhysics_CustomExternalForce"), &Z_Registration_Info_UClass_UKawaiiPhysics_CustomExternalForce, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UKawaiiPhysics_CustomExternalForce), 2257212040U) },
	};
}; // Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCustomExternalForce_h__Script_KawaiiPhysics_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCustomExternalForce_h__Script_KawaiiPhysics_3029740341{
	TEXT("/Script/KawaiiPhysics"),
	Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCustomExternalForce_h__Script_KawaiiPhysics_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsCustomExternalForce_h__Script_KawaiiPhysics_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
