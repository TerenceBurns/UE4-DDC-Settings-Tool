// Copyright 2020 - Trifolium Digital Limited

#include "SDDCSettingsTool.h"
#include "DerivedDataCacheInterface.h"

#define LOCTEXT_NAMESPACE "FDDCSettingsToolModule"

/**
 * Constants for this tool.
 */
namespace DDCSettingsToolViewConstants
{
	const FName LocalKeyName("Local", FNAME_Find);
	const FName SharedKeyName("Shared", FNAME_Find);
}


///////////////////////////////////////////////////////////////////////
// SDDCSettingsTool


#pragma optimize("", off)

void SDDCSettingsTool::Construct(const FArguments& InArgs)
{
	FDerivedDataCacheInterface* DDC = GetDerivedDataCache();
	
	UDDCInfo* LocalDDCInfo = NewObject<UDDCInfo>(GetTransientPackage(), UDDCInfo::StaticClass(), DDCSettingsToolViewConstants::LocalKeyName);
	UDDCInfo* SharedDDCInfo = nullptr;

	if (FConfigSection* DdcSection = GConfig->GetSectionPrivate(DDC->GetGraphName(), false, true, GEngineIni))
	{
		if (const FConfigValue* LocalValue = DdcSection->Find(DDCSettingsToolViewConstants::LocalKeyName))
		{
			LocalDDCInfo->LoadFromIniString(LocalValue->GetSavedValue());
		}

		if (const FConfigValue* SharedValue = DdcSection->Find(DDCSettingsToolViewConstants::SharedKeyName))
		{
			SharedDDCInfo = NewObject<UDDCInfo>(GetTransientPackage(), UDDCInfo::StaticClass(), DDCSettingsToolViewConstants::SharedKeyName);
			SharedDDCInfo->LoadFromIniString(SharedValue->GetSavedValue());
		}
	}

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.Padding(0.0f, 0.0f, 1.0f, 0.0f)
			[
				SAssignNew(LocalDDCInfoWidget, SDDCInfoPanel, DDCSettingsToolViewConstants::LocalKeyName, LocalDDCInfo)
			]
			+ SHorizontalBox::Slot()
			.Padding(1.0f, 0.0f, 0.0f, 0.0f)
			[
				SAssignNew(SharedDDCInfoWidget, SDDCInfoPanel, DDCSettingsToolViewConstants::SharedKeyName, SharedDDCInfo)
			]
		]
		+ SVerticalBox::Slot()
		.Padding(FMargin(0.0f, 2.0f, 0.0f, 0.0f))
		.AutoHeight()
		[
			SAssignNew(SaveToIniWidget, SDDCSaveToIniPanel, LocalDDCInfo, SharedDDCInfo)
		]
	];
}

#pragma optimize("", on)

SDDCSettingsTool::~SDDCSettingsTool()
{

}


#undef LOCTEXT_NAMESPACE