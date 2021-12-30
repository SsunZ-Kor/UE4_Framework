#pragma once
#include "Client/Framework/GameCharacter/ActionControl/ActionEvent/ActionEventDataBase.h"
#include "Client/Framework/GameCharacter/ActionControl/ActionTrigger/ActionTriggerData.h"
#include "GameCharacterEditor/TabTool/BaseClasses/TabToolBase_GameCharacter.h"

class Widget_ActionList;
class Widget_ActionData;

class ActionDataInfo
{
public:
	FString Name;
	FString Name_GameCha;
	FString Path;

	ActionDataInfo(){};
};

class TabToolAction_GameCharacter : public TabToolBase_GameCharacter
{
	// Static Data
	TArray<TSharedRef<EActionEventTypes>> m_AllEventTypes;

	// Action Data
	TArray<TSharedPtr<ActionDataInfo>> m_AllActionDataInfos;
	TArray<TSharedPtr<ActionDataInfo>> m_AllActionDataInfos_Filtered;

	// Selected Data Infos
	TSharedPtr<ActionDataInfo> m_SelectedActionDataInfo;
	UActionData* m_SelectedActionData = nullptr;
	TArray<TSharedPtr<FActionEventDataBase>> m_SelectedActionEventData;
	TArray<TSharedPtr<FActionTriggerData>> m_SelectedActionTriggerData;

	// For Search
	FString m_StrFileter;

	// Widget
	TSharedPtr<Widget_ActionList> m_pWidget_ActionList;
	TSharedPtr<Widget_ActionData> m_pWidget_ActionData;

public:
	virtual ~TabToolAction_GameCharacter () override;
	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;
	
	virtual void Init() override;
	virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& TabSpawnArgs) override;

private:
	void GetAllFilesInDirectory(TArray<FString>& results, const FString& directory, const bool& fullPath, const FString& onlyFilesStartingWith, const FString& onlyFilesWithExtension);

public:
	const TArray<TSharedRef<EActionEventTypes>>& GetAllActionEventTypes();
	
	void RefreshAllActionDataInfo();
	TArray<TSharedPtr<ActionDataInfo>>& GetAllActionDataInfos();
	TArray<TSharedPtr<ActionDataInfo>>& GetFilteredActionDataInfos();

	FText GetFilterText();
	void SetFilterText(const FText& txt);
	void RefreshFilteredActionDataInfos();

	void LoadSelectedActionData(TSharedPtr<ActionDataInfo> pActionDataInfo);
	void SaveSelectedActionData();
	
	TSharedPtr<ActionDataInfo> GetSelectedActionDataInfo();
	UActionData*& GetSelectedActionData();
	TArray<TSharedPtr<FActionEventDataBase>>& GetSelectedActionEventData();
	TArray<TSharedPtr<FActionTriggerData>>& GetSelectedActionTriggerData();
};