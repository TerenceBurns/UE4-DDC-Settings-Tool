// Copyright 2020 - Trifolium Digital Limited

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"

#include "Widgets/Views/SHeaderRow.h"

#include "DDCData.h"


/**
 * Slate widget to allow users to edit which Plugins are enabled for this project.
 */
class SDDCInfoPanel
	: public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDDCInfoPanel) {}
	SLATE_END_ARGS();

	void Construct(const FArguments& InArgs, FDDCData&& InCacheInformation);
	virtual ~SDDCInfoPanel() {}

private:
	FDDCData CacheInformation;
};