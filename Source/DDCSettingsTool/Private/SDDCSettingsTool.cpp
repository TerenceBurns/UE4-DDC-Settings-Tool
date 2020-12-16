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
	
	FDDCData LocalDDCData(DDCSettingsToolViewConstants::LocalKeyName.ToString());
	FDDCData SharedDDCData(DDCSettingsToolViewConstants::SharedKeyName.ToString());

	if (FConfigSection* DdcSection = GConfig->GetSectionPrivate(DDC->GetGraphName(), false, true, GEngineIni))
	{
		if (const FConfigValue* LocalValue = DdcSection->Find(DDCSettingsToolViewConstants::LocalKeyName))
		{
			LocalDDCData.LoadFromIniString(LocalValue->GetValue());
		}

		if (const FConfigValue* SharedValue = DdcSection->Find(DDCSettingsToolViewConstants::SharedKeyName))
		{
			SharedDDCData.LoadFromIniString(SharedValue->GetValue());
		}
	}

	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("NoBorder"))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.HAlign(EHorizontalAlignment::HAlign_Left)
			.AutoHeight()
			[
				SNew(STextBlock)
				.Font(FEditorStyle::GetFontStyle("SettingsEditor.CatgoryAndSectionFont"))
				.Text(FText::FromString(FString::Printf(TEXT("DDC: %s"), DDC->GetGraphName())))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(16.0f, 8.0f, 0.0f, 0.0f)
			[
				// category description
				SNew(STextBlock)
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
				.Text(FText::FromString(DDC->GetGraphName()))
			]
			+ SVerticalBox::Slot()
			.Padding(2.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(2.0f)
				[
					SAssignNew(LocalDDCInfoWidget, SDDCInfoPanel, MoveTemp(LocalDDCData))
				]
				+ SHorizontalBox::Slot()
				.Padding(2.0f)
				[
					SAssignNew(SharedDDCInfoWidget, SDDCInfoPanel, MoveTemp(SharedDDCData))
				]
			]
		]
	];
}

#pragma optimize("", on)

SDDCSettingsTool::~SDDCSettingsTool()
{

}


void SDDCSettingsTool::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	
}

#undef LOCTEXT_NAMESPACE