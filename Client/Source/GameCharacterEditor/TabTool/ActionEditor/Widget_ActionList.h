#pragma once
#include "TabToolAction_GameCharacter.h"

class Widget_ActionList : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(Widget_ActionList){}
	SLATE_ARGUMENT(TWeakPtr<class TabToolAction_GameCharacter>, Tool)
	SLATE_END_ARGS()

	TWeakPtr<TabToolAction_GameCharacter> tool;

	TSharedPtr<SListView<TSharedPtr<ActionDataInfo>>> m_ListView;

public:
	void Construct(const FArguments& InArgs);
	TSharedRef<ITableRow> OnGenerateRowForActionDataList(TSharedPtr<ActionDataInfo> InInfo,const TSharedRef<STableViewBase>& OwnerTable);
	void OnSelectionChangedForActionDataList(TSharedPtr<ActionDataInfo> selectedValue, ESelectInfo::Type type);
};