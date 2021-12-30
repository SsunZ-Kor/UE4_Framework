// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Client/Framework/Managers/UIManager/UIBase/WindowBase.h"
#include "Window_GameMain.generated.h"

class UButton;
class UBorder;

UCLASS()
class CLIENT_API UWindow_GameMain : public UWindowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Window GameMain", meta=(AllowPrivateAccess="true", DisplayName="Root Character"))
	UCanvasPanel* m_pCanvasPanel_CharacterInfoRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Window GameMain", meta=(AllowPrivateAccess="true", DisplayName="Root Inventory"))
	UCanvasPanel* m_pCanvasPanel_InventoryRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Window GameMain", meta=(AllowPrivateAccess="true", DisplayName="Root Center"))
   	UCanvasPanel* m_pCanvasPanel_CenterRoot;

	// 우하단 버튼들
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Window GameMain", meta=(AllowPrivateAccess="true", DisplayName="Btn Char"))
	UButton* m_pBtn_CharacterInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Window GameMain", meta=(AllowPrivateAccess="true", DisplayName="Btn Inventory"))
	UButton* m_pBtn_Inventory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Window GameMain", meta=(AllowPrivateAccess="true", DisplayName="Btn MainMenu"))
	UButton* m_pBtn_MainMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Window GameMain", meta=(AllowPrivateAccess="true", DisplayName="Backboard"))
	UBorder* m_pBorder_Background;

public:
	virtual bool IsLocked() override;

public:
	UWindow_GameMain(const FObjectInitializer& ObjectInitializer);
	virtual void OnWindowCreate() override;

protected:
	virtual void InitHotkey() override;
	
public:
	
	UFUNCTION(BlueprintCallable)
	void OnClick_UIModule_CharacterInfo();
	UFUNCTION(BlueprintCallable)
	void OnClick_UIModule_Inventory();
	UFUNCTION(BlueprintCallable)
	void OnClick_UIModule_Help();
	UFUNCTION(BlueprintCallable)
	void OnClick_UIModule_MainMenu();

	void OnKeyDown_ShowMouse();
	UFUNCTION(BlueprintCallable)
	FEventReply  OnMouseBtnDown_BackgroundBorder(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
	UFUNCTION(BlueprintCallable)
	FEventReply  OnMouseBtnUp_BackgroundBorder(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
};