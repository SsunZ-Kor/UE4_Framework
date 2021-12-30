#pragma once

#include "Blueprint/IUserObjectListEntry.h"
#include "Client/Framework/Managers/UIManager/UIBase/ImmortalWidget.h"
#include "UIListViewItem_Inventory.generated.h"

class UImage;
class UTextBlock;
class UserItemInfo;


UCLASS()
class CLIENT_API UUIListViewItem_Inventory : public UImmortalWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIScrollItem Inventory", meta=(AllowPrivateAccess="true", DisplayName="Img Icon"))
	UImage* m_pImg_Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIScrollItem Inventory", meta=(AllowPrivateAccess="true", DisplayName="Txt Name"))
	UTextBlock* m_pTxt_Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIScrollItem Inventory", meta=(AllowPrivateAccess="true", DisplayName="Txt Count"))
	UTextBlock* m_pTxt_Count;

public:
	virtual void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject* pUObj) override;
};