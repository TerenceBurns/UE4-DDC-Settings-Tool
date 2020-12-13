// Copyright 2020 - Trifolium Digital Limited

#include "SDDCSettingsTool.h"

#define LOCTEXT_NAMESPACE "FDDCSettingsToolModule"

/**
 * Constants for this tool.
 */
namespace DDCSettingsToolViewConstants
{
	
}


///////////////////////////////////////////////////////////////////////
// SDDCSettingsTool


void SDDCSettingsTool::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		.Padding(4.0f)
		[
			SNew(SVerticalBox)
		]
	];
}


SDDCSettingsTool::~SDDCSettingsTool()
{

}


void SDDCSettingsTool::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	
}

#undef LOCTEXT_NAMESPACE