// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "KawaiiPhysicsSharedCollisionSubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeKawaiiPhysicsSharedCollisionSubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UTickableWorldSubsystem();
KAWAIIPHYSICS_API UClass* Z_Construct_UClass_UKawaiiPhysicsSharedCollisionSubsystem();
KAWAIIPHYSICS_API UClass* Z_Construct_UClass_UKawaiiPhysicsSharedCollisionSubsystem_NoRegister();
UPackage* Z_Construct_UPackage__Script_KawaiiPhysics();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UKawaiiPhysicsSharedCollisionSubsystem ***********************************
FClassRegistrationInfo Z_Registration_Info_UClass_UKawaiiPhysicsSharedCollisionSubsystem;
UClass* UKawaiiPhysicsSharedCollisionSubsystem::GetPrivateStaticClass()
{
	using TClass = UKawaiiPhysicsSharedCollisionSubsystem;
	if (!Z_Registration_Info_UClass_UKawaiiPhysicsSharedCollisionSubsystem.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("KawaiiPhysicsSharedCollisionSubsystem"),
			Z_Registration_Info_UClass_UKawaiiPhysicsSharedCollisionSubsystem.InnerSingleton,
			StaticRegisterNativesUKawaiiPhysicsSharedCollisionSubsystem,
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
	return Z_Registration_Info_UClass_UKawaiiPhysicsSharedCollisionSubsystem.InnerSingleton;
}
UClass* Z_Construct_UClass_UKawaiiPhysicsSharedCollisionSubsystem_NoRegister()
{
	return UKawaiiPhysicsSharedCollisionSubsystem::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UKawaiiPhysicsSharedCollisionSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * KawaiiPhysics AnimNode\xe9\x96\x93\xe3\x81\xa7\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x83\x87\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe5\x85\xb1\xe6\x9c\x89\xe3\x81\x99\xe3\x82\x8b\xe3\x81\x9f\xe3\x82\x81\xe3\x81\xaeWorldSubsystem\n * WorldSubsystem for sharing collision data between KawaiiPhysics AnimNodes in an attached actor family\n */" },
#endif
		{ "IncludePath", "KawaiiPhysicsSharedCollisionSubsystem.h" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSharedCollisionSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "KawaiiPhysics AnimNode\xe9\x96\x93\xe3\x81\xa7\xe3\x82\xb3\xe3\x83\xaa\xe3\x82\xb8\xe3\x83\xa7\xe3\x83\xb3\xe3\x83\x87\xe3\x83\xbc\xe3\x82\xbf\xe3\x82\x92\xe5\x85\xb1\xe6\x9c\x89\xe3\x81\x99\xe3\x82\x8b\xe3\x81\x9f\xe3\x82\x81\xe3\x81\xaeWorldSubsystem\nWorldSubsystem for sharing collision data between KawaiiPhysics AnimNodes in an attached actor family" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UKawaiiPhysicsSharedCollisionSubsystem constinit property declarations ***
// ********** End Class UKawaiiPhysicsSharedCollisionSubsystem constinit property declarations *****
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UKawaiiPhysicsSharedCollisionSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UKawaiiPhysicsSharedCollisionSubsystem_Statics
UObject* (*const Z_Construct_UClass_UKawaiiPhysicsSharedCollisionSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UTickableWorldSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_KawaiiPhysics,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UKawaiiPhysicsSharedCollisionSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UKawaiiPhysicsSharedCollisionSubsystem_Statics::ClassParams = {
	&UKawaiiPhysicsSharedCollisionSubsystem::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UKawaiiPhysicsSharedCollisionSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UKawaiiPhysicsSharedCollisionSubsystem_Statics::Class_MetaDataParams)
};
void UKawaiiPhysicsSharedCollisionSubsystem::StaticRegisterNativesUKawaiiPhysicsSharedCollisionSubsystem()
{
}
UClass* Z_Construct_UClass_UKawaiiPhysicsSharedCollisionSubsystem()
{
	if (!Z_Registration_Info_UClass_UKawaiiPhysicsSharedCollisionSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UKawaiiPhysicsSharedCollisionSubsystem.OuterSingleton, Z_Construct_UClass_UKawaiiPhysicsSharedCollisionSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UKawaiiPhysicsSharedCollisionSubsystem.OuterSingleton;
}
UKawaiiPhysicsSharedCollisionSubsystem::UKawaiiPhysicsSharedCollisionSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UKawaiiPhysicsSharedCollisionSubsystem);
UKawaiiPhysicsSharedCollisionSubsystem::~UKawaiiPhysicsSharedCollisionSubsystem() {}
// ********** End Class UKawaiiPhysicsSharedCollisionSubsystem *************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSharedCollisionSubsystem_h__Script_KawaiiPhysics_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UKawaiiPhysicsSharedCollisionSubsystem, UKawaiiPhysicsSharedCollisionSubsystem::StaticClass, TEXT("UKawaiiPhysicsSharedCollisionSubsystem"), &Z_Registration_Info_UClass_UKawaiiPhysicsSharedCollisionSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UKawaiiPhysicsSharedCollisionSubsystem), 209960771U) },
	};
}; // Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSharedCollisionSubsystem_h__Script_KawaiiPhysics_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSharedCollisionSubsystem_h__Script_KawaiiPhysics_1459032786{
	TEXT("/Script/KawaiiPhysics"),
	Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSharedCollisionSubsystem_h__Script_KawaiiPhysics_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ProjectPBZ_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSharedCollisionSubsystem_h__Script_KawaiiPhysics_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
