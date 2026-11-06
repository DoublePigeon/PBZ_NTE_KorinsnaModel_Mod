// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "KawaiiPhysicsDeveloperSettings.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeKawaiiPhysicsDeveloperSettings() {}

// ********** Begin Cross Module References ********************************************************
DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings();
KAWAIIPHYSICS_API UClass* Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings();
KAWAIIPHYSICS_API UClass* Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_NoRegister();
UPackage* Z_Construct_UPackage__Script_KawaiiPhysics();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UKawaiiPhysicsDeveloperSettings ******************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UKawaiiPhysicsDeveloperSettings;
UClass* UKawaiiPhysicsDeveloperSettings::GetPrivateStaticClass()
{
	using TClass = UKawaiiPhysicsDeveloperSettings;
	if (!Z_Registration_Info_UClass_UKawaiiPhysicsDeveloperSettings.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("KawaiiPhysicsDeveloperSettings"),
			Z_Registration_Info_UClass_UKawaiiPhysicsDeveloperSettings.InnerSingleton,
			StaticRegisterNativesUKawaiiPhysicsDeveloperSettings,
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
	return Z_Registration_Info_UClass_UKawaiiPhysicsDeveloperSettings.InnerSingleton;
}
UClass* Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_NoRegister()
{
	return UKawaiiPhysicsDeveloperSettings::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * KawaiiPhysics \xe3\x81\xae\xe3\x83\x97\xe3\x83\xad\xe3\x82\xb8\xe3\x82\xa7\xe3\x82\xaf\xe3\x83\x88\xe5\x85\xa8\xe4\xbd\x93\xe8\xa8\xad\xe5\xae\x9a / Project-wide settings for KawaiiPhysics.\n * Project Settings > Plugins > Kawaii Physics \xe3\x81\xab\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b\xe3\x80\x82\n */" },
#endif
		{ "DisplayName", "Kawaii Physics" },
		{ "IncludePath", "KawaiiPhysicsDeveloperSettings.h" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsDeveloperSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "KawaiiPhysics \xe3\x81\xae\xe3\x83\x97\xe3\x83\xad\xe3\x82\xb8\xe3\x82\xa7\xe3\x82\xaf\xe3\x83\x88\xe5\x85\xa8\xe4\xbd\x93\xe8\xa8\xad\xe5\xae\x9a / Project-wide settings for KawaiiPhysics.\nProject Settings > Plugins > Kawaii Physics \xe3\x81\xab\xe8\xa1\xa8\xe7\xa4\xba\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b\xe3\x80\x82" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseFixedSubstepping_MetaData[] = {
		{ "Category", "Simulation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* \xe3\x82\xb7\xe3\x83\x9f\xe3\x83\xa5\xe3\x83\xac\xe3\x83\xbc\xe3\x82\xb7\xe3\x83\xa7\xe3\x83\xb3\xe5\x85\xa8\xe4\xbd\x93\xe3\x82\x92\xe5\x9b\xba\xe5\xae\x9a\xe3\x82\xbf\xe3\x82\xa4\xe3\x83\xa0\xe3\x82\xb9\xe3\x83\x86\xe3\x83\x83\xe3\x83\x97\xef\xbc\x88""FixedDt = 1/TargetFramerate\xef\xbc\x89\xe3\x81\xa7\xe3\x82\xb5\xe3\x83\x96\xe3\x82\xb9\xe3\x83\x86\xe3\x83\x83\xe3\x83\x97\xe5\xae\x9f\xe8\xa1\x8c\xe3\x81\x97\xe3\x80\x81\n\x09* \xe3\x83\x95\xe3\x83\xac\xe3\x83\xbc\xe3\x83\xa0\xe3\x83\xac\xe3\x83\xbc\xe3\x83\x88\xe4\xbe\x9d\xe5\xad\x98\xe3\x81\xae\xe6\x8c\x99\xe5\x8b\x95\xe3\x82\x92\xe8\xa7\xa3\xe6\xb6\x88\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82\xef\xbc\x88\xe4\xbd\x8e""fps\xe6\x99\x82\xe3\x81\xaf\xe3\x82\xb5\xe3\x83\x96\xe3\x82\xb9\xe3\x83\x86\xe3\x83\x83\xe3\x83\x97\xe6\x95\xb0\xe3\x81\x8c\xe5\xa2\x97\xe3\x81\x88\xe8\xb2\xa0\xe8\x8d\xb7\xe3\x81\x8c\xe4\xb8\x8a\xe3\x81\x8c\xe3\x82\x8b\xef\xbc\x89\xe3\x80\x82\n\x09* Run the whole simulation with fixed-timestep substepping (FixedDt = 1/TargetFramerate) for true\n\x09* frame-rate independence (CPU cost rises at low fps as substep count grows).\n\x09*/" },
#endif
		{ "DisplayName", "Use Fixed Substepping" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsDeveloperSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x82\xb7\xe3\x83\x9f\xe3\x83\xa5\xe3\x83\xac\xe3\x83\xbc\xe3\x82\xb7\xe3\x83\xa7\xe3\x83\xb3\xe5\x85\xa8\xe4\xbd\x93\xe3\x82\x92\xe5\x9b\xba\xe5\xae\x9a\xe3\x82\xbf\xe3\x82\xa4\xe3\x83\xa0\xe3\x82\xb9\xe3\x83\x86\xe3\x83\x83\xe3\x83\x97\xef\xbc\x88""FixedDt = 1/TargetFramerate\xef\xbc\x89\xe3\x81\xa7\xe3\x82\xb5\xe3\x83\x96\xe3\x82\xb9\xe3\x83\x86\xe3\x83\x83\xe3\x83\x97\xe5\xae\x9f\xe8\xa1\x8c\xe3\x81\x97\xe3\x80\x81\n\xe3\x83\x95\xe3\x83\xac\xe3\x83\xbc\xe3\x83\xa0\xe3\x83\xac\xe3\x83\xbc\xe3\x83\x88\xe4\xbe\x9d\xe5\xad\x98\xe3\x81\xae\xe6\x8c\x99\xe5\x8b\x95\xe3\x82\x92\xe8\xa7\xa3\xe6\xb6\x88\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82\xef\xbc\x88\xe4\xbd\x8e""fps\xe6\x99\x82\xe3\x81\xaf\xe3\x82\xb5\xe3\x83\x96\xe3\x82\xb9\xe3\x83\x86\xe3\x83\x83\xe3\x83\x97\xe6\x95\xb0\xe3\x81\x8c\xe5\xa2\x97\xe3\x81\x88\xe8\xb2\xa0\xe8\x8d\xb7\xe3\x81\x8c\xe4\xb8\x8a\xe3\x81\x8c\xe3\x82\x8b\xef\xbc\x89\xe3\x80\x82\nRun the whole simulation with fixed-timestep substepping (FixedDt = 1/TargetFramerate) for true\nframe-rate independence (CPU cost rises at low fps as substep count grows)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxSubsteps_MetaData[] = {
		{ "Category", "Simulation" },
		{ "ClampMax", "16" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* 1\xe3\x83\x95\xe3\x83\xac\xe3\x83\xbc\xe3\x83\xa0\xe3\x81\x82\xe3\x81\x9f\xe3\x82\x8a\xe3\x81\xae\xe6\x9c\x80\xe5\xa4\xa7\xe3\x82\xb5\xe3\x83\x96\xe3\x82\xb9\xe3\x83\x86\xe3\x83\x83\xe3\x83\x97\xe6\x95\xb0\xe3\x80\x82\xe4\xbd\x8e""fps/\xe3\x83\x92\xe3\x83\x83\xe3\x83\x81\xe6\x99\x82\xe3\x81\xae\xe6\x9a\xb4\xe8\xb5\xb0\xef\xbc\x88spiral of death\xef\xbc\x89\xe3\x82\x92\xe9\x98\xb2\xe3\x81\x90\xe4\xb8\x8a\xe9\x99\x90\xe3\x80\x82\n\x09* \xe3\x81\x93\xe3\x82\x8c\xe3\x82\x92\xe8\xb6\x85\xe3\x81\x88\xe3\x82\x8b\xe5\x88\x86\xe3\x81\xae\xe6\x99\x82\xe9\x96\x93\xe3\x81\xaf\xe7\xa0\xb4\xe6\xa3\x84\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b\xe3\x80\x82\n\x09* Maximum substeps per frame. Caps catch-up at low fps / hitches (prevents spiral of death);\n\x09* time beyond this is dropped.\n\x09*/" },
#endif
		{ "DisplayName", "Max Substeps" },
		{ "EditCondition", "bUseFixedSubstepping" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsDeveloperSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "1\xe3\x83\x95\xe3\x83\xac\xe3\x83\xbc\xe3\x83\xa0\xe3\x81\x82\xe3\x81\x9f\xe3\x82\x8a\xe3\x81\xae\xe6\x9c\x80\xe5\xa4\xa7\xe3\x82\xb5\xe3\x83\x96\xe3\x82\xb9\xe3\x83\x86\xe3\x83\x83\xe3\x83\x97\xe6\x95\xb0\xe3\x80\x82\xe4\xbd\x8e""fps/\xe3\x83\x92\xe3\x83\x83\xe3\x83\x81\xe6\x99\x82\xe3\x81\xae\xe6\x9a\xb4\xe8\xb5\xb0\xef\xbc\x88spiral of death\xef\xbc\x89\xe3\x82\x92\xe9\x98\xb2\xe3\x81\x90\xe4\xb8\x8a\xe9\x99\x90\xe3\x80\x82\n\xe3\x81\x93\xe3\x82\x8c\xe3\x82\x92\xe8\xb6\x85\xe3\x81\x88\xe3\x82\x8b\xe5\x88\x86\xe3\x81\xae\xe6\x99\x82\xe9\x96\x93\xe3\x81\xaf\xe7\xa0\xb4\xe6\xa3\x84\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b\xe3\x80\x82\nMaximum substeps per frame. Caps catch-up at low fps / hitches (prevents spiral of death);\ntime beyond this is dropped." },
#endif
		{ "UIMin", "1" },
	};
#if WITH_EDITORONLY_DATA
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InterBoneDummyWarningThreshold_MetaData[] = {
		{ "Category", "Performance Warnings" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* BoneSubdivisionCount \xe3\x81\xa7\xe7\x94\x9f\xe6\x88\x90\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b inter-bone dummy bone \xe6\x95\xb0\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4\xe3\x80\x82""0\xe3\x81\xa7\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe7\x84\xa1\xe5\x8a\xb9\xe5\x8c\x96\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82\n\x09* Warning threshold for inter-bone dummy bones generated by BoneSubdivisionCount. Set to 0 to disable.\n\x09*/" },
#endif
		{ "DisplayName", "Inter-Bone Dummy Warning Threshold" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsDeveloperSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "BoneSubdivisionCount \xe3\x81\xa7\xe7\x94\x9f\xe6\x88\x90\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b inter-bone dummy bone \xe6\x95\xb0\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4\xe3\x80\x82""0\xe3\x81\xa7\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe7\x84\xa1\xe5\x8a\xb9\xe5\x8c\x96\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82\nWarning threshold for inter-bone dummy bones generated by BoneSubdivisionCount. Set to 0 to disable." },
#endif
		{ "UIMax", "1000" },
		{ "UIMin", "0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BridgeDummyWarningThreshold_MetaData[] = {
		{ "Category", "Performance Warnings" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* BoneConstraintSubdivisionCount \xe3\x81\xa7\xe7\x94\x9f\xe6\x88\x90\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b bridge collision-proxy dummy bone \xe6\x95\xb0\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4\xe3\x80\x82""0\xe3\x81\xa7\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe7\x84\xa1\xe5\x8a\xb9\xe5\x8c\x96\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82\n\x09* Warning threshold for bridge collision-proxy dummy bones generated by BoneConstraintSubdivisionCount. Set to 0 to disable.\n\x09*/" },
#endif
		{ "DisplayName", "Bridge Dummy Warning Threshold" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsDeveloperSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "BoneConstraintSubdivisionCount \xe3\x81\xa7\xe7\x94\x9f\xe6\x88\x90\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b bridge collision-proxy dummy bone \xe6\x95\xb0\xe3\x81\xae\xe8\xad\xa6\xe5\x91\x8a\xe3\x81\x97\xe3\x81\x8d\xe3\x81\x84\xe5\x80\xa4\xe3\x80\x82""0\xe3\x81\xa7\xe8\xad\xa6\xe5\x91\x8a\xe3\x82\x92\xe7\x84\xa1\xe5\x8a\xb9\xe5\x8c\x96\xe3\x81\x99\xe3\x82\x8b\xe3\x80\x82\nWarning threshold for bridge collision-proxy dummy bones generated by BoneConstraintSubdivisionCount. Set to 0 to disable." },
#endif
		{ "UIMax", "1000" },
		{ "UIMin", "0" },
	};
#endif // WITH_EDITORONLY_DATA
#endif // WITH_METADATA

// ********** Begin Class UKawaiiPhysicsDeveloperSettings constinit property declarations **********
	static void NewProp_bUseFixedSubstepping_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseFixedSubstepping;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxSubsteps;
#if WITH_EDITORONLY_DATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_InterBoneDummyWarningThreshold;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BridgeDummyWarningThreshold;
#endif // WITH_EDITORONLY_DATA
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UKawaiiPhysicsDeveloperSettings constinit property declarations ************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UKawaiiPhysicsDeveloperSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics

// ********** Begin Class UKawaiiPhysicsDeveloperSettings Property Definitions *********************
void Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::NewProp_bUseFixedSubstepping_SetBit(void* Obj)
{
	((UKawaiiPhysicsDeveloperSettings*)Obj)->bUseFixedSubstepping = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::NewProp_bUseFixedSubstepping = { "bUseFixedSubstepping", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UKawaiiPhysicsDeveloperSettings), &Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::NewProp_bUseFixedSubstepping_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseFixedSubstepping_MetaData), NewProp_bUseFixedSubstepping_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::NewProp_MaxSubsteps = { "MaxSubsteps", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UKawaiiPhysicsDeveloperSettings, MaxSubsteps), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxSubsteps_MetaData), NewProp_MaxSubsteps_MetaData) };
#if WITH_EDITORONLY_DATA
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::NewProp_InterBoneDummyWarningThreshold = { "InterBoneDummyWarningThreshold", nullptr, (EPropertyFlags)0x0010000800004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UKawaiiPhysicsDeveloperSettings, InterBoneDummyWarningThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InterBoneDummyWarningThreshold_MetaData), NewProp_InterBoneDummyWarningThreshold_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::NewProp_BridgeDummyWarningThreshold = { "BridgeDummyWarningThreshold", nullptr, (EPropertyFlags)0x0010000800004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UKawaiiPhysicsDeveloperSettings, BridgeDummyWarningThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BridgeDummyWarningThreshold_MetaData), NewProp_BridgeDummyWarningThreshold_MetaData) };
#endif // WITH_EDITORONLY_DATA
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::NewProp_bUseFixedSubstepping,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::NewProp_MaxSubsteps,
#if WITH_EDITORONLY_DATA
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::NewProp_InterBoneDummyWarningThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::NewProp_BridgeDummyWarningThreshold,
#endif // WITH_EDITORONLY_DATA
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::PropPointers) < 2048);
// ********** End Class UKawaiiPhysicsDeveloperSettings Property Definitions ***********************
UObject* (*const Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDeveloperSettings,
	(UObject* (*)())Z_Construct_UPackage__Script_KawaiiPhysics,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::ClassParams = {
	&UKawaiiPhysicsDeveloperSettings::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::PropPointers),
	0,
	0x001000A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::Class_MetaDataParams)
};
void UKawaiiPhysicsDeveloperSettings::StaticRegisterNativesUKawaiiPhysicsDeveloperSettings()
{
}
UClass* Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings()
{
	if (!Z_Registration_Info_UClass_UKawaiiPhysicsDeveloperSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UKawaiiPhysicsDeveloperSettings.OuterSingleton, Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UKawaiiPhysicsDeveloperSettings.OuterSingleton;
}
UKawaiiPhysicsDeveloperSettings::UKawaiiPhysicsDeveloperSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UKawaiiPhysicsDeveloperSettings);
UKawaiiPhysicsDeveloperSettings::~UKawaiiPhysicsDeveloperSettings() {}
// ********** End Class UKawaiiPhysicsDeveloperSettings ********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsDeveloperSettings_h__Script_KawaiiPhysics_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UKawaiiPhysicsDeveloperSettings, UKawaiiPhysicsDeveloperSettings::StaticClass, TEXT("UKawaiiPhysicsDeveloperSettings"), &Z_Registration_Info_UClass_UKawaiiPhysicsDeveloperSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UKawaiiPhysicsDeveloperSettings), 511452459U) },
	};
}; // Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsDeveloperSettings_h__Script_KawaiiPhysics_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsDeveloperSettings_h__Script_KawaiiPhysics_1867780577{
	TEXT("/Script/KawaiiPhysics"),
	Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsDeveloperSettings_h__Script_KawaiiPhysics_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsDeveloperSettings_h__Script_KawaiiPhysics_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
