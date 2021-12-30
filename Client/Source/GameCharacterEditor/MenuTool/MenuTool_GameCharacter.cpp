#include "MenuTool_GameCharacter.h"
#include "../GameCharacterEditor.h"

#define LOCTEXT_NAMESPACE "MenuTool"

class MenuToolCommands_GameCharacter : public TCommands<MenuToolCommands_GameCharacter>
{
public:
	TSharedPtr<FUICommandInfo> CommandInfo_OpenWindow;
	TSharedPtr<FUICommandInfo> CommandInfo_CheckAction;

public:
	MenuToolCommands_GameCharacter()
		: TCommands<MenuToolCommands_GameCharacter>(
		TEXT("GameCharacterMenuTool"), // Context name for fast lookup
		FText::FromString("Game Character Menu Tool"), // Context name for displaying
		NAME_None,   // No parent context
		FEditorStyle::GetStyleSetName() // Icon Style Set
		)
	{
	}

	virtual void RegisterCommands() override
	{
		UI_COMMAND(CommandInfo_OpenWindow, "Open Action Editor", "Open Game Character Action Editor Window", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(CommandInfo_CheckAction, "Check Invalid Action", "정보가 비어있는 액션을 검색합니다.", EUserInterfaceActionType::Button, FInputChord());
	}
};

void MenuTool_GameCharacter::OnStartupModule()
{
	// 
	CommandList = MakeShareable(new FUICommandList);

	// Map Commands
	{
		MenuToolCommands_GameCharacter::Register();
		
		CommandList->MapAction(
			MenuToolCommands_GameCharacter::Get().CommandInfo_OpenWindow,
			FExecuteAction::CreateSP(this, &MenuTool_GameCharacter::OnClick_Menu_OpenWindow),
			FCanExecuteAction());

		CommandList->MapAction(
			MenuToolCommands_GameCharacter::Get().CommandInfo_CheckAction,
			FExecuteAction::CreateSP(this, &MenuTool_GameCharacter::OnClick_Menu_OpenWindow),
			FCanExecuteAction());
	}

	// Section에 할당
	FGameCharacterEditor::Get().AddMenuExtension(
		FMenuExtensionDelegate::CreateRaw(this, &MenuTool_GameCharacter::MakeMenuEntry),
		FName("Action"),
		CommandList);
}

void MenuTool_GameCharacter::OnShutdownModule()
{
	MenuToolCommands_GameCharacter::Unregister();
}

void MenuTool_GameCharacter::MakeMenuEntry(FMenuBuilder &menuBuilder)
{
	menuBuilder.AddMenuEntry(MenuToolCommands_GameCharacter::Get().CommandInfo_OpenWindow);
	menuBuilder.AddMenuEntry(MenuToolCommands_GameCharacter::Get().CommandInfo_CheckAction);

	//menuBuilder.AddSubMenu(
	//	FText::FromString("Sub Menu"),
	//	FText::FromString("This is example sub menu"),
	//	FNewMenuDelegate::CreateSP(this, &MenuTool::MakeSubMenu)
	//);}
}

// 2단 메뉴
//void MenuTool::MakeSubMenu(FMenuBuilder& menuBuilder)
//{
//	menuBuilder.AddMenuEntry(MenuToolCommands::Get().CommandInfo_CheckAction);
//	menuBuilder.AddMenuEntry(MenuToolCommands::Get().MenuCommand3);
//}


void MenuTool_GameCharacter::OnClick_Menu_OpenWindow()
{
	UE_LOG(LogClass, Log, TEXT("Clicked OnClick_Menu_OpenWindow"));
}

#undef LOCTEXT_NAMESPACE
