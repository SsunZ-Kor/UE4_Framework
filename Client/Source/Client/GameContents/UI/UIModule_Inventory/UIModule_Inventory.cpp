// Fill out your copyright notice in the Description page of Project Settings.


#include "UIModule_Inventory.h"

#include "UIListViewItem_Inventory.h"
#include "Client/Framework/Managers/Managers.h"
#include "Client/Framework/Managers/UserDataManager/UserCharacterData.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/ListView.h"
#include "Components/TileView.h"

void UViewData_Inventory::SetData(UserItemInfo* const pUserItemInfo)
{
	m_pUserItemInfo = pUserItemInfo;
}

const UserItemInfo* UViewData_Inventory::GetData()
{
	return m_pUserItemInfo;
}

void UUIModule_Inventory::OnUIModuleOpened(UWindowBase* pWndParent)
{
	Super::OnUIModuleOpened(pWndParent);

	// 리스트 뷰 초기화
	m_pPanel_ListView = Cast<UCanvasPanel>(GetWidgetFromName((TEXT("CanvasPanel_ListView"))));
	m_pListView = Cast<UListView>(GetWidgetFromName((TEXT("ListView_Inventory"))));
	m_pListView->OnItemClicked().AddUObject(this, &UUIModule_Inventory::OnClick_ListItem);
	m_pBtn_ListView = Cast<UButton>(GetWidgetFromName((TEXT("btn_ListView"))));
	m_pBtn_ListView->OnClicked.AddDynamic(this, &UUIModule_Inventory::OnClick_ChangeListView);

	// 타일 뷰 초기화
	m_pPanel_TileView = Cast<UCanvasPanel>(GetWidgetFromName((TEXT("CanvasPanel_TileView"))));
	m_pTileView = Cast<UTileView>(GetWidgetFromName((TEXT("TileView_Inventory"))));
	m_pTileView->OnItemClicked().AddUObject(this, &UUIModule_Inventory::OnClick_ListItem);
	m_pBtn_TileView = Cast<UButton>(GetWidgetFromName((TEXT("btn_TileView"))));
	m_pBtn_TileView->OnClicked.AddDynamic(this, &UUIModule_Inventory::OnClick_ChangeTileView);

	// 데이터 세팅
	auto allItemInfo = Managers::User->CharacterData->GetAllItemInfo();
	for (auto& pair : allItemInfo)
	{
		auto* pUScrollListData = NewObject<UViewData_Inventory>(this);
		pUScrollListData->SetData(pair.Value);
		
		m_pListView->AddItem(pUScrollListData);
		m_pTileView->AddItem(pUScrollListData);
	}

	// 기본은 Tile로 보여준다.
	ChangeViewType(EInvenViewTypes::Tile);
}

void UUIModule_Inventory::OnClick_ListItem(UObject* pUScrollItemData)
{
	LOG_WARNING(TEXT("Test"));
}

void UUIModule_Inventory::OnClick_ChangeListView()
{
	ChangeViewType(EInvenViewTypes::List);
}

void UUIModule_Inventory::OnClick_ChangeTileView()
{
	ChangeViewType(EInvenViewTypes::Tile);
}

void UUIModule_Inventory::ChangeViewType(const EInvenViewTypes& invenViewTypes)
{
	switch (invenViewTypes)
	{
		case EInvenViewTypes::List:
			m_pPanel_ListView->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			m_pPanel_TileView->SetVisibility(ESlateVisibility::Collapsed);
			break;
		case EInvenViewTypes::Tile:
			m_pPanel_ListView->SetVisibility(ESlateVisibility::Collapsed);
			m_pPanel_TileView->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			break;
	}
}
