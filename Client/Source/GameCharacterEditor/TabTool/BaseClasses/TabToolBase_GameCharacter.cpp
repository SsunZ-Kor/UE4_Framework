#include "TabToolBase_GameCharacter.h"

void TabToolBase_GameCharacter::OnStartupModule()
{
	Init();
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(m_TabName, FOnSpawnTab::CreateRaw(this, &TabToolBase_GameCharacter::SpawnTab))
		.SetGroup(FGameCharacterEditor::Get().GetMenuRoot())
		.SetDisplayName(m_TabDisplayName)
		.SetTooltipText(m_ToolTipText);
	
	IGameCharacterModuleListenerInterface::OnStartupModule();
}

void TabToolBase_GameCharacter::OnShutdownModule()
{
    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(m_TabName);

	IGameCharacterModuleListenerInterface::OnShutdownModule();
}

void TabToolBase_GameCharacter::Init()
{
}

TSharedRef<SDockTab> TabToolBase_GameCharacter::SpawnTab(const FSpawnTabArgs& TabSpawnArgs)
{
	return SNew(SDockTab);
}

void TabToolBase_GameCharacter::MakeMenuEntry(FMenuBuilder& menuBuilder)
{
	FGlobalTabmanager::Get()->PopulateTabSpawnerMenu(menuBuilder, m_TabName);
}