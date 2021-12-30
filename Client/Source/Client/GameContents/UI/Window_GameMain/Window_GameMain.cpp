// Fill out your copyright notice in the Description page of Project Settings.


#include "Window_GameMain.h"
#include "Client/Framework/Managers/Managers.h"
#include "Client/GameContents/GameModes/GameMode_Game.h"
#include "Client/GameContents/UI/UIModule_CharacterInfo/UIModule_CharacterInfo.h"
#include "Client/GameContents/UI/UIModule_Help/UIModule_Help.h"
#include "Client/GameContents/UI/UIModule_Inventory/UIModule_Inventory.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"

class UButton;

bool UWindow_GameMain::IsLocked()
{
	OnClick_UIModule_MainMenu();
	return true;
}

UWindow_GameMain::UWindow_GameMain(const FObjectInitializer& ObjectInitializer)
	: UWindowBase(ObjectInitializer)
{
	bIsFocusable = true;
	m_bUseMouse = false;
}

void UWindow_GameMain::OnWindowCreate()
{
	Super::OnWindowCreate();

	// 오브젝트 찾기
	m_pCanvasPanel_CharacterInfoRoot = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Canvas_CharacterInfoRoot")));
	m_pCanvasPanel_InventoryRoot = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Canvas_InventoryRoot")));
	m_pCanvasPanel_CenterRoot = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Canvas_CenterRoot")));

	m_pBtn_CharacterInfo = Cast<UButton>(GetWidgetFromName(TEXT("btn_CharacterInfo")));
	m_pBtn_Inventory =  Cast<UButton>(GetWidgetFromName(TEXT("btn_Inventory")));
	m_pBtn_MainMenu =  Cast<UButton>(GetWidgetFromName(TEXT("btn_MainMenu")));
	
	m_pBorder_Background = Cast<UBorder>(GetWidgetFromName(TEXT("border_Background")));

	// 버튼 이벤트 세팅
	m_pBtn_CharacterInfo->OnClicked.AddDynamic(this, &UWindow_GameMain::OnClick_UIModule_CharacterInfo);
	m_pBtn_Inventory->OnClicked.AddDynamic(this, &UWindow_GameMain::UWindow_GameMain::OnClick_UIModule_Inventory);
	m_pBtn_MainMenu->OnClicked.AddDynamic(this, &UWindow_GameMain::OnClick_UIModule_MainMenu);

	m_pBorder_Background->OnMouseButtonDownEvent.BindDynamic(this, &UWindow_GameMain::OnMouseBtnDown_BackgroundBorder);
	m_pBorder_Background->OnMouseButtonUpEvent.BindDynamic(this, &UWindow_GameMain::OnMouseBtnUp_BackgroundBorder);
}

void UWindow_GameMain::InitHotkey()
{
	AddKey_PlayerCtrl();
	AddKey(EKeys::C, this, &UWindow_GameMain::OnClick_UIModule_CharacterInfo);
	AddKey(EKeys::F1, this, &UWindow_GameMain::OnClick_UIModule_Help);
	AddKey(EKeys::I, this, &UWindow_GameMain::OnClick_UIModule_Inventory);
	AddKey(EKeys::LeftControl, this, &UWindow_GameMain::OnKeyDown_ShowMouse);
}

void UWindow_GameMain::OnKeyDown_ShowMouse()
{
	Managers::UI->GetInputCtrl()->SetMouseEnable(true);
}

void UWindow_GameMain::OnClick_UIModule_CharacterInfo()
{
	if (IsOpenedUIModule<UUIModule_CharacterInfo>())
	{
		CloseUIModule<UUIModule_CharacterInfo>();
	}
	else if (const auto pGameMode = Cast<AGameMode_Game>(Managers::World->GetGameMode()))
	{
		auto pUIModule = OpenUIModule<UUIModule_CharacterInfo>(m_pCanvasPanel_CharacterInfoRoot);
		if (pUIModule)
			pUIModule->Init(pGameMode->GetPlayerCharacter());
	}
}

void UWindow_GameMain::OnClick_UIModule_Inventory()
{
	if (IsOpenedUIModule<UUIModule_Inventory>())
		CloseUIModule<UUIModule_Inventory>();
	else
		auto pUIModule = OpenUIModule<UUIModule_Inventory>(m_pCanvasPanel_InventoryRoot);
}

void UWindow_GameMain::OnClick_UIModule_Help()
{
	if (IsOpenedUIModule<UUIModule_Help>())
		CloseUIModule<UUIModule_Help>();
	else
		auto pUIModule = OpenUIModule<UUIModule_Help>(m_pCanvasPanel_CenterRoot);
}

void UWindow_GameMain::OnClick_UIModule_MainMenu()
{
}

FEventReply  UWindow_GameMain::OnMouseBtnDown_BackgroundBorder(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	// 왼쪽 클릭이라면 마우스를 다시 숨긴다.
	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		Managers::UI->GetInputCtrl()->SetMouseEnable(false);
	
	// 가장 마지막 백그라운드일 것, 그냥 처리해버리자
	return FEventReply(true);
}

FEventReply  UWindow_GameMain::OnMouseBtnUp_BackgroundBorder(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	// 오른쪽 클릭이라면 오브젝트 픽킹 시작
	if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		// Todo :: 픽킹
	}
	// 가장 마지막 백그라운드일 것, 그냥 처리해버리자
	return FEventReply(true);
}