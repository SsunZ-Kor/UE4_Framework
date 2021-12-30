
#pragma once

#include "Blueprint/IUserObjectListEntry.h"
#include "Client/Framework/Managers/UIManager/UIBase/ImmortalWidget.h"
#include "UITreeViewItem_Help.generated.h"

class UTextBlock;
class UCanvasPanel;
class UImage;

UCLASS()
class CLIENT_API UUITreeViewItem_Help : public UImmortalWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UITileViewItem Help", meta=(AllowPrivateAccess="true"))
	UCanvasPanel* m_pCanvas_HelpCategory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UITileViewItem Help", meta=(AllowPrivateAccess="true"))
	UCanvasPanel* m_pCanvas_Help;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UITileViewItem Help", meta=(AllowPrivateAccess="true"))
	UTextBlock* m_pTxt_HelpCategoryName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UITileViewItem Help", meta=(AllowPrivateAccess="true"))
	UTextBlock* m_pTxt_HelpName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UITileViewItem Help", meta=(AllowPrivateAccess="true"))
	UImage* m_pImg_HelpBg_Selected;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UITileViewItem Help", meta=(AllowPrivateAccess="true"))
	UImage* m_pImg_HelpBg_Unselected;

	UPROPERTY()
	UObject* m_Data;

public:
	virtual void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject* pUObj) override;
	void SetSelected(const bool& bSelected);
	bool IsSameData(UObject* pUObj);
};