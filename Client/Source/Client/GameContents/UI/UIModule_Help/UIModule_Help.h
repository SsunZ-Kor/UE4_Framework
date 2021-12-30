// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Client/Framework/Managers/UIManager/UIBase/UIModuleBase.h"
#include "UIModule_Help.generated.h"

class UTreeView;
class UMultiLineEditableText;
class UUITreeViewItem_Help;
class CHelpCategoryData;
class CHelpData;

UCLASS()
class UViewData_Help : public UObject
{
	GENERATED_BODY()

	const CHelpData* m_pHelpData;
	bool m_IsSelected;

	UUITreeViewItem_Help* m_pUITreeViewItem_Help;

public:
	void SetData(const CHelpData* const pHelpData);
	const CHelpData* const& GetData() const;

	void SetItem(UUITreeViewItem_Help* pUITreeViewItem_Help);
	void SetSelected(const bool& bSelected);
	const bool&  GetSelected();
};

UCLASS()
class UViewData_HelpCategory : public UObject
{
	GENERATED_BODY()

	const CHelpCategoryData* m_pHelpCategoryData;
	UPROPERTY()
	TArray<UObject*> m_HelpDatas;

public:
	void SetData(const CHelpCategoryData* const pHelpCategoryData, const TArray<const CHelpData*>& HelpDatas);
	const CHelpCategoryData* const& GetData() const;
	TArray<UObject*>& GetChildrenData();
};

UCLASS()
class CLIENT_API UUIModule_Help : public UUIModuleBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIModule Help", meta=(AllowPrivateAccess="true", DisplayName="Tile"))
	UTreeView* m_pTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIModule Help", meta=(AllowPrivateAccess="true", DisplayName="Contents"))
	UMultiLineEditableText* CTxt_HelpContents;


	UPROPERTY()
	UViewData_Help* m_pUViewData_Help_Selected;
	
public:
	virtual void OnUIModuleCreate(UClass* pBaseUClass) override;

	UFUNCTION()
	void OnClick_Item(UObject* pUObj);
	
	UFUNCTION()
	void GetItemChildren(UObject* pUObj, TArray<UObject*>& pUObj_Children);
};