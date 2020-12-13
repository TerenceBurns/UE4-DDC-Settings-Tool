// Copyright 2020 - Trifolium Digital Limited

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "DDCSettingsToolStyle.h"

class FDDCSettingsToolCommands : public TCommands<FDDCSettingsToolCommands>
{
public:

	FDDCSettingsToolCommands()
		: TCommands<FDDCSettingsToolCommands>(TEXT("DDCSettingsTool"), NSLOCTEXT("Contexts", "DDCSettingsTool", "DDCSettingsTool Plugin"), NAME_None, FDDCSettingsToolStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};