// Copyright 2020 - Trifolium Digital Limited

#include "SDDCInfoPanel.h"


#define LOCTEXT_NAMESPACE "FDDCSettingsToolModule"


///////////////////////////////////////////////////////////////////////
// SDDCInfoPanel


void SDDCInfoPanel::Construct(const FArguments& InArgs, const FName& InCacheName, TWeakObjectPtr<UDDCInfo> InCacheInformation)
{
	CacheInformation = InCacheInformation;

	TSharedPtr<SWidget> InfoView = nullptr;
	if (CacheInformation.IsValid())
	{
		// Build the property view layout.
		FDetailsViewArgs DetailsViewArgs;
		{
			DetailsViewArgs.bAllowSearch = true;
			DetailsViewArgs.bHideSelectionTip = true;
			DetailsViewArgs.bLockable = false;
			DetailsViewArgs.bSearchInitialKeyFocus = true;
			DetailsViewArgs.bUpdatesFromSelection = false;
			DetailsViewArgs.NotifyHook = nullptr;
			DetailsViewArgs.bShowOptions = true;
			DetailsViewArgs.bShowModifiedPropertiesOption = false;
			DetailsViewArgs.bAllowMultipleTopLevelObjects = true;
			DetailsViewArgs.bShowActorLabel = false;
			DetailsViewArgs.bCustomNameAreaLocation = true;
			DetailsViewArgs.bCustomFilterAreaLocation = true;
			DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::ObjectsUseNameArea;
			DetailsViewArgs.bShowPropertyMatrixButton = false;
		}
		FPropertyEditorModule& EditModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		MainPropertyView = EditModule.CreateDetailView(DetailsViewArgs);
		MainPropertyView->SetObject(CacheInformation.Get());
		InfoView = MainPropertyView.ToSharedRef();
	}
	else
	{
		InfoView = SNew(SBox)
			.HAlign(EHorizontalAlignment::HAlign_Center)
			.VAlign(EVerticalAlignment::VAlign_Fill)
			.Padding(16.0f)
			[
				SNew(STextBlock)
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
				.Text(LOCTEXT("CacheNotInUse_Tooltip", "Not in use."))
			];
	}

	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("MessageLog.ListBorder"))
			.BorderBackgroundColor(FLinearColor(0.1f, 0.1f, 0.4f, 0.5f))
			.Padding(FMargin(2.0f, 2.0f, 2.0f, 2.0f))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.HAlign(EHorizontalAlignment::HAlign_Center)
				.AutoHeight()
				[
					SNew(STextBlock)
					.Font(FDDCSettingsToolStyle::Get().GetFontStyle("DDCEditor.LabelFont"))
					.Text(FText::FromName(InCacheName))
				]
				+ SVerticalBox::Slot()
				.Padding(2.0f, 0.0f, 2.0f, 0.0f)
				[
					InfoView.ToSharedRef()
				]
			]
		]
	];
}


#undef LOCTEXT_NAMESPACE