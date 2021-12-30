#pragma once

#include "GameCharacterEditor/GameCharacterEditor.h"
#include "GameCharacterEditor/IGameCharacterModuleInterface.h"

class TabToolBase_GameCharacter : public IGameCharacterModuleListenerInterface, public TSharedFromThis<TabToolBase_GameCharacter>
{
protected:
	FName m_TabName;
	FText m_TabDisplayName;
    FText m_ToolTipText;

public:

	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;

	virtual void Init();
	virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& TabSpawnArgs);

	virtual void MakeMenuEntry(FMenuBuilder &menuBuilder);
};
