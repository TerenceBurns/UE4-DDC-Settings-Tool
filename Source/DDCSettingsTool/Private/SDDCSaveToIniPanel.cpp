// Copyright 2020 - Trifolium Digital Limited

#include "SDDCSaveToIniPanel.h"
#include "DDCInfo.h"
#include "DerivedDataCacheInterface.h"
#include "Widgets/Input/SComboBox.h"


#define LOCTEXT_NAMESPACE "FDDCSettingsToolModule"

/**
 * Constants for this tool.
 */
namespace DDCSaveToIniPanelViewConstants
{

}


///////////////////////////////////////////////////////////////////////
// SDDCInfoPanel


#pragma optimize("", off)

void SDDCSaveToIniPanel::Construct(const FArguments& InArgs, TWeakObjectPtr<UDDCInfo> InLocalDdcObj, TWeakObjectPtr<UDDCInfo> InSharedDdcObj)
{
	LocalDdcObj = InLocalDdcObj;
	SharedDdcObj = InSharedDdcObj;

	GatherIniFilePaths();

	FDerivedDataCacheInterface* DDC = GetDerivedDataCache();
	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		.Padding(2.0f)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("MessageLog.ListBorder"))
			.BorderBackgroundColor(FLinearColor(0.1f, 0.1f, 0.4f, 0.5f))
			.Padding(4.0f)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.0f, 8.0f, 0.0f, 0.0f)
				.HAlign(EHorizontalAlignment::HAlign_Center)
				[
					// category description
					SNew(STextBlock)
					.ColorAndOpacity(FSlateColor::UseSubduedForeground())
					.Text(LOCTEXT("CurrentBackendLabel", "Current DDC Backend in use:"))
				]
				+ SVerticalBox::Slot()
				.HAlign(EHorizontalAlignment::HAlign_Center)
				.Padding(0.0f, 0.0f, 0.0f, 8.0f)
				.AutoHeight()
				[
					SNew(STextBlock)
					.Font(FDDCSettingsToolStyle::Get().GetFontStyle("DDCEditor.LabelFont"))
					.Text(FText::FromString(DDC->GetGraphName()))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(EHorizontalAlignment::HAlign_Fill)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.FillWidth(1.0f)
					[
						SNew(SBorder)
						.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
						.Padding(2.0f)
						[
							SNew(SBorder)
							.BorderImage(FEditorStyle::GetBrush("MessageLog.ListBorder"))
							.BorderBackgroundColor(FLinearColor(0.1f, 0.1f, 0.4f, 0.7f))
							[
								SNew(SVerticalBox)
								+ SVerticalBox::Slot()
								.Padding(2.0f, 2.0f, 0.0f, 0.0f)
								.AutoHeight()
								[
										SNew(STextBlock)
										.Text(LOCTEXT("SaveChangesLabel", "Save changes:"))
										.Font(FEditorStyle::GetFontStyle("PropertyWindow.NormalFont"))
								]
								+ SVerticalBox::Slot()
								.AutoHeight()
//								.Padding(4.0f, 0.0f, 4.0f, 4.0f)
								.Padding(8.0f)
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
									.FillWidth(1.0f)
									.Padding(0.0f, 0.0f, 8.0f, 0.0f)
									[
										SAssignNew(ChosenIniComboBox, SComboBox<TSharedPtr<FString>>)
										.OptionsSource(&AvailableIniPaths)
										.OnGenerateWidget(this, &SDDCSaveToIniPanel::GenerateIniFileComboBoxWidget)
										.OnSelectionChanged(this, &SDDCSaveToIniPanel::HandleIniFileSelectionChanged)
										.ToolTipText(LOCTEXT("IniSelection_Tooltip", "Choose which config file to use when saving the DDC changes"))
										[
											SNew(STextBlock)
											.Text(this, &SDDCSaveToIniPanel::GetSelectedIniFileNameText)
										]
									]
									+ SHorizontalBox::Slot()
									.AutoWidth()
									[
										SNew(SButton)
										.Text(LOCTEXT("SaveButtonLabel", "Save"))
										.ToolTipText(LOCTEXT("SaveButton_Tooltip", "Save changes to the specified config file."))
										.OnClicked_Lambda([this]()
										{
											return(FReply::Handled());
										})
									]
								]
							]
						]
					]
				]
			]
		]
	];
}



void SDDCSaveToIniPanel::GatherIniFilePaths()
{
	FString ProjectDirUserIniFile = FPaths::ConvertRelativePathToFull(FPaths::ProjectConfigDir() / TEXT("UserEngine.ini"));
	AvailableIniPaths.Add(MakeShared<FString>(ProjectDirUserIniFile));

	FString UserDirUserIniFile = FPaths::ConvertRelativePathToFull(FString(FPlatformProcess::UserDir()) / TEXT("Unreal Engine") / TEXT("Engine") / TEXT("Config") / TEXT("UserEngine.ini"));
	AvailableIniPaths.Add(MakeShared<FString>(UserDirUserIniFile));
	
	FString UserSettingsDirUserIniFile = FPaths::ConvertRelativePathToFull(FString(FPlatformProcess::UserSettingsDir()) / TEXT("Unreal Engine") / TEXT("Engine") / TEXT("Config") / TEXT("UserEngine.ini"));
	AvailableIniPaths.Add(MakeShared<FString>(UserSettingsDirUserIniFile));
	
	FString DefaultIniFile = FPaths::ConvertRelativePathToFull(FPaths::ProjectConfigDir() / TEXT("DefaultEngine.ini"));
	AvailableIniPaths.Add(MakeShared<FString>(DefaultIniFile));

	// Default to the engine saved xml
	SelectedIniPath = AvailableIniPaths[0];
}


TSharedRef<SWidget> SDDCSaveToIniPanel::GenerateIniFileComboBoxWidget(TSharedPtr<FString> InItem)
{
	return
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.Padding(2.0f)
		.HAlign(EHorizontalAlignment::HAlign_Left)
		[
			SNew(STextBlock)
			.Text(FText::FromString(*InItem))
		];
}

void SDDCSaveToIniPanel::HandleIniFileSelectionChanged(TSharedPtr<FString> InSelection, ESelectInfo::Type SelectInfo)
{
	if (InSelection.IsValid())
	{
		SelectedIniPath = InSelection;
	}
}

FText SDDCSaveToIniPanel::GetSelectedIniFileNameText() const
{
	return FText::FromString(*this->SelectedIniPath);
}

#pragma optimize("", on)

#undef LOCTEXT_NAMESPACE