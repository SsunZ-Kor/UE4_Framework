#include "GameCharacterEditor.h"

#include "Client/Framework/GameCharacter/ActionControl/ActionDataDetail.h"
#include "MenuTool/MenuTool_GameCharacter.h"
#include "TabTool/ActionEditor/TabToolAction_GameCharacter.h"

IMPLEMENT_GAME_MODULE(FGameCharacterEditor, GameCharacterEditor)

TSharedRef<FWorkspaceItem> FGameCharacterEditor::MenuRoot = FWorkspaceItem::NewGroup(FText::FromString("Menu Root"));

void FGameCharacterEditor::AddModuleListeners()
{
	// 메뉴 모듈, 탭 모듈 추가
	ModuleListeners.Add(MakeShareable(new MenuTool_GameCharacter));
	ModuleListeners.Add(MakeShareable(new TabToolAction_GameCharacter));
}

void FGameCharacterEditor::StartupModule()
{
	if (!IsRunningCommandlet())
	{
		// 메뉴
		MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuBarExtension("Window", EExtensionHook::After, NULL, FMenuBarExtensionDelegate::CreateRaw(this, &FGameCharacterEditor::MakePulldownMenu));

		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		LevelEditorMenuExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();
		LevelEditorMenuExtensibilityManager->AddExtender(MenuExtender);

		// 디테일
		FPropertyEditorModule& PropertyModule = 
			FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

		PropertyModule.RegisterCustomClassLayout(
			"ActionData", FOnGetDetailCustomizationInstance::CreateStatic(&ActionDataDetail::MakeInstance));
	}
	
	IGameCharacterModuleInterface::StartupModule();
}

void FGameCharacterEditor::ShutdownModule()
{
	IGameCharacterModuleInterface::ShutdownModule();
}

void FGameCharacterEditor::AddMenuExtension(const FMenuExtensionDelegate &extensionDelegate, FName extensionHook, const TSharedPtr<FUICommandList> &CommandList, EExtensionHook::Position position)
{
	MenuExtender->AddMenuExtension(extensionHook, position, CommandList, extensionDelegate);
}

void FGameCharacterEditor::MakePulldownMenu(FMenuBarBuilder &menuBuilder)
{
	// 상단 메뉴 추가
	menuBuilder.AddPullDownMenu(
		FText::FromString("Game Character"),
		FText::FromString("Open the Game Character menu"),
		FNewMenuDelegate::CreateRaw(this, &FGameCharacterEditor::FillPulldownMenu),
		"Game Character",
		FName(TEXT("Game Character Menu"))
	);
}

void FGameCharacterEditor::FillPulldownMenu(FMenuBuilder &menuBuilder)
{
	// 상단 메뉴 섹션 구성
	menuBuilder.BeginSection("Game Character Action", FText::FromString("Game Character Action"));
	menuBuilder.AddMenuSeparator(FName("Action"));
	menuBuilder.EndSection();

	//menuBuilder.BeginSection("ExampleSection", FText::FromString("Section 2"));
	//menuBuilder.AddMenuSeparator(FName("Section_2"));
	//menuBuilder.EndSection();
}