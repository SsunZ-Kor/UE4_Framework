#include "UITreeViewItem_Help.h"

#include "UIModule_Help.h"
#include "Client/GameContents/GameDatas/HelpCategoryData.h"
#include "Client/GameContents/GameDatas/HelpData.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


void UUITreeViewItem_Help::NativeConstruct()
{
	Super::NativeConstruct();

	m_pCanvas_HelpCategory = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("CanvasPanel_HelpCategory")));;
	m_pCanvas_Help = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("CanvasPanel_Help")));;
	m_pTxt_HelpCategoryName = Cast<UTextBlock>(GetWidgetFromName(TEXT("Ctxt_HelpCategoryName")));;
	m_pTxt_HelpName = Cast<UTextBlock>(GetWidgetFromName(TEXT("Ctxt_HelpName")));;
	m_pImg_HelpBg_Selected = Cast<UImage>(GetWidgetFromName(TEXT("img_HelpBg_Selected")));;
	m_pImg_HelpBg_Unselected = Cast<UImage>(GetWidgetFromName(TEXT("img_HelpBg")));;
}

void UUITreeViewItem_Help::NativeOnListItemObjectSet(UObject* pUObj)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(pUObj);

	m_Data = pUObj;

	const auto pViewData_HelpCategory = Cast<UViewData_HelpCategory>(pUObj);
	if (pViewData_HelpCategory)
	{
		m_pCanvas_HelpCategory->SetVisibility(ESlateVisibility::Visible);
		m_pCanvas_Help->SetVisibility(ESlateVisibility::Hidden);
		
		const auto pHelpCategoryData = pViewData_HelpCategory->GetData();
		m_pTxt_HelpCategoryName->SetText(FText::FromString(pHelpCategoryData->Name));
		return;
	}

	const auto pViewData_Help = Cast<UViewData_Help>(pUObj);
	if (pViewData_Help)
	{
		pViewData_Help->SetItem(this);
		m_pCanvas_HelpCategory->SetVisibility(ESlateVisibility::Hidden);
		m_pCanvas_Help->SetVisibility(ESlateVisibility::Visible);
		
		const auto pHelpData = pViewData_Help->GetData();
		m_pTxt_HelpName->SetText(FText::FromString(pHelpData->Name));

		SetSelected(pViewData_Help->GetSelected());
		return;
	}
}

void UUITreeViewItem_Help::SetSelected(const bool& bSelected)
{
	if (bSelected)
	{
		m_pImg_HelpBg_Selected->SetVisibility(ESlateVisibility::Visible);
		m_pImg_HelpBg_Unselected->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		m_pImg_HelpBg_Selected->SetVisibility(ESlateVisibility::Hidden);
		m_pImg_HelpBg_Unselected->SetVisibility(ESlateVisibility::Visible);
	}
}

bool UUITreeViewItem_Help::IsSameData(UObject* pUObj)
{
	return m_Data == pUObj;
}
