// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Client/Framework/Managers/UIManager/UIBase/UIModuleBase.h"
#include "UIModule_Inventory.generated.h"

class UListView;
class UTileView;
class UserItemInfo;
class UCanvasPanel;
class UButton;

UENUM()
enum class EInvenViewTypes : uint8
{
	List,
	Tile,
};

UCLASS()
class UViewData_Inventory : public UObject
{
	GENERATED_BODY()

	UserItemInfo* m_pUserItemInfo;
public:
	void SetData(UserItemInfo* const m_pUserItemInfo);
	const UserItemInfo* GetData();
};

UCLASS()
class CLIENT_API UUIModule_Inventory : public UUIModuleBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIModule Inventory", meta=(AllowPrivateAccess="true", DisplayName="List Panel"))
	UCanvasPanel* m_pPanel_ListView;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIModule Inventory", meta=(AllowPrivateAccess="true", DisplayName="Tile Panel"))
	UCanvasPanel* m_pPanel_TileView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIModule Inventory", meta=(AllowPrivateAccess="true", DisplayName="List"))
	UListView* m_pListView;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIModule Inventory", meta=(AllowPrivateAccess="true", DisplayName="Tile"))
	UTileView* m_pTileView;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIModule Inventory", meta=(AllowPrivateAccess="true", DisplayName="Btn List"))
	UButton* m_pBtn_ListView;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIModule Inventory", meta=(AllowPrivateAccess="true", DisplayName="Btn Tile"))
	UButton* m_pBtn_TileView;

public:
	virtual void OnUIModuleOpened(UWindowBase* pWndParent) override;

	void OnClick_ListItem(UObject* pUScrollItemData);

	UFUNCTION()
	void OnClick_ChangeListView();
	UFUNCTION()
	void OnClick_ChangeTileView();

private:	
	void ChangeViewType(const EInvenViewTypes& invenViewTypes);
};