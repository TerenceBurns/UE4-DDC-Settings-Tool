// Copyright 2020 - Trifolium Digital Limited

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"

#include "DDCInfo.h"
#include "Widgets/Input/SComboBox.h"

/**
 * Slate widget to allow users to edit which Plugins are enabled for this project.
 */
class SDDCSaveToIniPanel
	: public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDDCSaveToIniPanel) {}
	SLATE_END_ARGS();

	void Construct(const FArguments& InArgs, TWeakObjectPtr<UDDCInfo> InLocalDdcObj, TWeakObjectPtr<UDDCInfo> InSharedDdcObj);
	virtual ~SDDCSaveToIniPanel() {}

public:

	// Begin selected config file functionality (Drop down)
	TSharedRef<SWidget> GenerateIniFileComboBoxWidget(TSharedPtr<FString> InItem);
	void HandleIniFileSelectionChanged(TSharedPtr<FString> InSelection, ESelectInfo::Type SelectInfo);
	
	FText GetSelectedIniFileNameText() const;
	// End selected config file functionality (Drop down)
	void GatherIniFilePaths();
	
private:
	//
	TWeakObjectPtr<UDDCInfo> LocalDdcObj;

	//
	TWeakObjectPtr<UDDCInfo> SharedDdcObj;

	//
	TSharedPtr<SComboBox<TSharedPtr<FString>>> ChosenIniComboBox;

	//
	TSharedPtr<FString> SelectedIniPath;

	//
	TArray<TSharedPtr<FString>> AvailableIniPaths;
};