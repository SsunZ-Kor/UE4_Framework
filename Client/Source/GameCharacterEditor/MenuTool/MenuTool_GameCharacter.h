#pragma once

#include "../IGameCharacterModuleInterface.h"

class MenuTool_GameCharacter : public IGameCharacterModuleListenerInterface, public TSharedFromThis<MenuTool_GameCharacter>
{
	
protected:
	TSharedPtr<FUICommandList> CommandList;

public:
	virtual ~MenuTool_GameCharacter() {}

	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;

	void MakeMenuEntry(FMenuBuilder &menuBuilder);
	//void MakeSubMenu(FMenuBuilder &menuBuilder);
	
	// UI Command functions
	void OnClick_Menu_OpenWindow();

};
