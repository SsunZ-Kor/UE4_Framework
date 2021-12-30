#pragma once
#include "TabToolAction_GameCharacter.h"
#include "Client/Framework/GameCharacter/ActionControl/ActionEvent/ActionEventDataBase.h"
#include "Client/Framework/GameCharacter/ActionControl/ActionTrigger/ActionTriggerData.h"

class UActionData;
struct FActionEventDataBase;

	
	UENUM()
	enum class EWidgetActionDataMode : uint8
	{
		Event,
		Trigger,
	};

class Widget_ActionData : public SCompoundWidget
{
private:
	
	SLATE_BEGIN_ARGS(Widget_ActionData){}
	SLATE_ARGUMENT(TWeakPtr<class TabToolAction_GameCharacter>, Tool)
	SLATE_END_ARGS()

	TWeakPtr<TabToolAction_GameCharacter> tool;
	EWidgetActionDataMode m_Mode;

public:
	void Construct(const FArguments& InArgs);

	TSharedRef<SWidget> GetWidget_ActionBasicData();
	TSharedRef<ITableRow> OnGenerateRowForActionEventDataList(TSharedPtr<FActionEventDataBase> InInfo,const TSharedRef<STableViewBase>& OwnerTable);
	void OnSelectionChangedForActionEventDataList(TSharedPtr<FActionEventDataBase> selectedValue, ESelectInfo::Type type);

	TSharedRef<ITableRow> OnGenerateRowForActionTriggerDataList(TSharedPtr<FActionTriggerData> InInfo,const TSharedRef<STableViewBase>& OwnerTable);
	void OnSelectionChangedForActionTriggerDataList(TSharedPtr<FActionTriggerData> selectedValue, ESelectInfo::Type type);
};