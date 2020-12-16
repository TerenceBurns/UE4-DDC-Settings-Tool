// Copyright 2020 - Trifolium Digital Limited

#include "SDDCInfoPanel.h"


#define LOCTEXT_NAMESPACE "FDDCSettingsToolModule"

/**
 * Constants for this tool.
 */
namespace DDCInfoPanelViewConstants
{
	static FName ListHeader_Property("Property");
	const float ListHeader_Property_Ratio = 1.0f;

	static FName ListHeader_Value("Value");
	const float ListHeader_Value_Ratio = 1.0f;
}


///////////////////////////////////////////////////////////////////////
// SDDCInfoPanel


#pragma optimize("", off)

void SDDCInfoPanel::Construct(const FArguments& InArgs, FDDCData&& InCacheInformation)
{
	CacheInformation = MoveTemp(InCacheInformation);
	
	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		.Padding(4.0f)
		[
			//SAssignNew(DataDetailsView, SListView<FDDCData>)
			//.ItemHeight(24)						
			//.ScrollbarVisibility(EVisibility::Visible)
			//.ListItemsSource(&FilteredPlugins)
			//.OnGenerateRow(this, &SQuickPluginListView::OnGenerateWidgetForList)
			//.HeaderRow
			//(
			//	SNew(SHeaderRow)
			//	+ SHeaderRow::Column(DDCInfoPanelViewConstants::ListHeader_Property)
			//	.DefaultLabel(LOCTEXT("DDCDataPropertyHeader", "Property"))
			//	.FillWidth(DDCInfoPanelViewConstants::ListHeader_Property_Ratio)
			//	.SortMode(EColumnSortMode::None)
			//	+ SHeaderRow::Column(PluginListViewHelpers::ListHeader_Value)
			//	.DefaultLabel(LOCTEXT("DDCDataValueHeader", "Value"))
			//	.FillWidth(DDCInfoPanelViewConstants::ListHeader_Value_Ratio)
			//	.SortMode(EColumnSortMode::None)
			//)
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.HAlign(EHorizontalAlignment::HAlign_Left)
			.AutoHeight()
			[
				SNew(STextBlock)
				.Font(FEditorStyle::GetFontStyle("SettingsEditor.CatgoryAndSectionFont"))
				.Text(FText::FromString(CacheInformation.CacheName))
			]
			+ SVerticalBox::Slot()
			.HAlign(EHorizontalAlignment::HAlign_Left)
			.AutoHeight()
			[
				SNew(STextBlock)
				.Font(FEditorStyle::GetFontStyle("PropertyWindow.NormalFont"))
				.Text(FText::FromString(CacheInformation.Path))
			]
		]
	];
}

#pragma optimize("", on)

#undef LOCTEXT_NAMESPACE