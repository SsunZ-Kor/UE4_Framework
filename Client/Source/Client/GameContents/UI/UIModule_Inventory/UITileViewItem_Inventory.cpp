#include "UITileViewItem_Inventory.h"

#include "UIModule_Inventory.h"
#include "Client/Framework/Managers/Managers.h"
#include "Client/Framework/Managers/UserDataManager/UserCharacterData_Define.h"
#include "Client/GameContents/GameDatas/ItemData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


void UUITileViewItem_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	m_pImg_Icon = Cast<UImage>(GetWidgetFromName(TEXT("Cimg_Icon")));
	m_pTxt_Count = Cast<UTextBlock>(GetWidgetFromName(TEXT("Ctxt_Count")));
}

void UUITileViewItem_Inventory::NativeOnListItemObjectSet(UObject* pUObj)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(pUObj);

	const auto pUViewData = Cast<UViewData_Inventory>(pUObj);
	const auto pUserItemInfo = pUViewData->GetData();
	const auto* const pItemData = pUserItemInfo->GetData();

	// 스프라이트 세팅
	const auto refPath = FString::Printf(TEXT("Texture2D'/Game/GameContents/UITexture/Icon_Item/%s.%s'"), *pItemData->ImgNameIcon, *pItemData->ImgNameIcon);
	m_pImg_Icon->SetBrushFromTexture(Managers::Asset->LoadObj<UTexture2D>(*refPath));
	
	// 갯수 세팅
	const auto& nCount =  pUserItemInfo->GetCount();
	if (nCount >= 0)
	{
		m_pTxt_Count->SetVisibility(ESlateVisibility::Visible);
		m_pTxt_Count->SetText(FText::FromString(FString::Printf(TEXT("x %d"), nCount)));
	}
	else
	{
		m_pTxt_Count->SetVisibility(ESlateVisibility::Hidden);
	}
}