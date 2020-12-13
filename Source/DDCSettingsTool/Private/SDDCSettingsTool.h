// Copyright 2020 - Trifolium Digital Limited

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"


/**
 * Slate widget to allow users to edit which Plugins are enabled for this project.
 */
class SDDCSettingsTool
	: public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SDDCSettingsTool) {}
		SLATE_DEFAULT_SLOT(FArguments, Content)
	SLATE_END_ARGS()


	/** The body of the slate window for our plugin settings widget. */
	void Construct(const FArguments& InArgs);

	/** Destructor */
	virtual ~SDDCSettingsTool();

// Begin SWidget interface
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
// End SWidget interface
};