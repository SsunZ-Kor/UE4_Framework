#include "UIModule_Help.h"

#include "Client/Framework/Managers/Managers.h"
#include "Components/TreeView.h"
#include "Components/MultiLineEditableText.h"
#include "UITreeViewItem_Help.h"

void UViewData_HelpCategory::SetData(const CHelpCategoryData* const pHelpCategoryData, const TArray<const CHelpData*>& HelpDatas)
{
	m_pHelpCategoryData = pHelpCategoryData;

	for (auto pHelpData : HelpDatas)
	{
		auto pUViewData_Help = NewObject<UViewData_Help>(this);
		pUViewData_Help->SetData(pHelpData);
		m_HelpDatas.Add(pUViewData_Help);
	}
}

const CHelpCategoryData* const& UViewData_HelpCategory::GetData() const
{
	return m_pHelpCategoryData;
}

TArray<UObject*>& UViewData_HelpCategory::GetChildrenData()
{
	return m_HelpDatas;
}

void UViewData_Help::SetData(const CHelpData* const pHelpData)
{
	m_pHelpData = pHelpData;
	m_IsSelected = false;
}

void UViewData_Help::SetItem(UUITreeViewItem_Help* pUITreeViewItem_Help)
{
	m_pUITreeViewItem_Help = pUITreeViewItem_Help;
}

void UViewData_Help::SetSelected(const bool& bSelected)
{
	m_IsSelected = bSelected;

	// 리스트와 데이터가 일치한다면 꺼준다.
	if (m_pUITreeViewItem_Help && m_pUITreeViewItem_Help->IsSameData(this))
		m_pUITreeViewItem_Help->SetSelected(bSelected);
}

const bool& UViewData_Help::GetSelected()
{
	return m_IsSelected;
}

const CHelpData* const& UViewData_Help::GetData() const
{
	return m_pHelpData;
}

void UUIModule_Help::OnUIModuleCreate(UClass* pBaseUClass)
{
	Super::OnUIModuleCreate(pBaseUClass);

	m_pUViewData_Help_Selected = false;

	CTxt_HelpContents = Cast<UMultiLineEditableText>(GetWidgetFromName((TEXT("CTxt_HelpContents"))));
	m_pTreeView = Cast<UTreeView>(GetWidgetFromName((TEXT("TreeView_Help"))));

	CTxt_HelpContents->SetText(FText::FromString(FString(TEXT("항목을 선택해 주세요"))));
	m_pTreeView->OnItemClicked().AddUObject(this, &UUIModule_Help::OnClick_Item);
	m_pTreeView->SetOnGetItemChildren(this,  &UUIModule_Help::GetItemChildren);

	// 도움말 데이터 준비
	TMap<int, TArray<const CHelpData*>> map_HelpDatas;

	auto* HelpDatas = Managers::GameData->GetMapData<CHelpData>();
	for (auto& pHelpData : *HelpDatas)
	{
		auto& categoryDataId = pHelpData.Value->CategoryDataId;
		
		if (!map_HelpDatas.Contains(categoryDataId))
			map_HelpDatas.Add(categoryDataId, TArray<const CHelpData*>());

		map_HelpDatas[categoryDataId].Add(pHelpData.Value);
	}

	// 도움말 카테고리 데이터 세팅
	auto* HelpCategoryDatas = Managers::GameData->GetMapData<CHelpCategoryData>();
	for (auto& pHelpCategoryData : *HelpCategoryDatas)
	{
		// 정작 도움말이 없다면 넘긴다.
		if (!map_HelpDatas.Contains(pHelpCategoryData.Value->ID))
			continue;
		
		auto* pUViewData_HelpCategory = NewObject<UViewData_HelpCategory>(this);
		pUViewData_HelpCategory->SetData(pHelpCategoryData.Value, map_HelpDatas[pHelpCategoryData.Value->ID]);
		
		m_pTreeView->AddItem(pUViewData_HelpCategory);
	}
}

void UUIModule_Help::OnClick_Item(UObject* pUObj)
{
	// 열림 닫힘은 알아서 된다.

	// 내용 세팅
	const auto pViewData_Help = Cast<UViewData_Help>(pUObj);
	if (pViewData_Help)
	{
		const auto pHelpData = pViewData_Help->GetData();
		CTxt_HelpContents->SetText(FText::FromString(pHelpData->TxtContents));

		if (m_pUViewData_Help_Selected)
			m_pUViewData_Help_Selected->SetSelected(false);

		m_pUViewData_Help_Selected = pViewData_Help;
		m_pUViewData_Help_Selected->SetSelected(true);
	}
}

void UUIModule_Help::GetItemChildren(UObject* pUObj, TArray<UObject*>& pUObj_Children)
{
	auto* pUViewData_HelpCategory = Cast<UViewData_HelpCategory>(pUObj);
	if (pUViewData_HelpCategory)
		pUObj_Children = pUViewData_HelpCategory->GetChildrenData();
}