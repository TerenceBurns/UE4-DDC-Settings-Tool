// Copyright 2020 - Trifolium Digital Limited

#include "DDCSettingsTool.h"
#include "DDCSettingsToolStyle.h"
#include "DDCSettingsToolCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "SDDCSettingsTool.h"

static const FName DDCSettingsToolTabName("DDCSettingsTool");


#define LOCTEXT_NAMESPACE "FDDCSettingsToolModule"


void FDDCSettingsToolModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FDDCSettingsToolStyle::Initialize();
	FDDCSettingsToolStyle::ReloadTextures();

	FDDCSettingsToolCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FDDCSettingsToolCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FDDCSettingsToolModule::PluginButtonClicked),
		FCanExecuteAction());

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FDDCSettingsToolModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}

	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FDDCSettingsToolModule::AddToolbarExtension));

		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(DDCSettingsToolTabName, FOnSpawnTab::CreateRaw(this, &FDDCSettingsToolModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FDDCSettingsToolTabTitle", "DDC Settings"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}


void FDDCSettingsToolModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FDDCSettingsToolStyle::Shutdown();

	FDDCSettingsToolCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DDCSettingsToolTabName);
}


TSharedRef<SDockTab> FDDCSettingsToolModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SDDCSettingsTool)
		];
}


void FDDCSettingsToolModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(DDCSettingsToolTabName);
}


void FDDCSettingsToolModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FDDCSettingsToolCommands::Get().OpenPluginWindow);
}


void FDDCSettingsToolModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FDDCSettingsToolCommands::Get().OpenPluginWindow);
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDDCSettingsToolModule, DDCSettingsTool)