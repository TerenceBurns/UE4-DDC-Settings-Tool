// Copyright 2020 - Trifolium Digital Limited

#include "DDCSettingsToolCommands.h"

#define LOCTEXT_NAMESPACE "FDDCSettingsToolModule"


void FDDCSettingsToolCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "DDC Settings", "Update your user settings for the DDC.", EUserInterfaceActionType::Button, FInputGesture());
}


#undef LOCTEXT_NAMESPACE
