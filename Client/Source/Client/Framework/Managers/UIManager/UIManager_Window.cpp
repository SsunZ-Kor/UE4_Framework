// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "UIBase/WindowBase.h"
#include "UIBase/LoadingBase.h"
#include "Client/Framework/Managers/Managers.h"
#include "UserInputController.h"
#include "Window_System_Popup/Window_System_Popup.h"

constexpr int32 UIManager::ZORDER_WINDOW_START = 0;
constexpr int32 UIManager::ZORDER_WINDOW_INTERVAL = 100;
constexpr int32 UIManager::ZORDER_POPUP = 100000;

UIManager::UIManager()
{
	m_pWnd_Popup = nullptr;
	m_pModalBlock = nullptr;
	m_pUserInputCtrl = nullptr;
}

UIManager::~UIManager()
{
	if (m_pWnd_Popup)
	{
		Managers::GameInst->RemoveWidget(m_pWnd_Popup);
		m_pWnd_Popup = nullptr;
	}
	
	if (m_pModalBlock)
	{
		Managers::GameInst->RemoveWidget(m_pModalBlock);
		m_pModalBlock = nullptr;
	}

	
	m_llist_WndStack.Empty(false);
}

void UIManager::Init()
{
	txt_Default_Ok = TEXT("예");
	txt_Default_No = TEXT("아니오");
	txt_Default_Cancel = TEXT("취소");

	// ModalBlock 세팅
	const auto refPath_Modalblock = TEXT("WidgetBlueprint'/Game/GameContents/UI/Windows/UIModalBlock.UIModalBlock_C'");
	auto BPClass_ModalBlack = Managers::Asset->LoadBP<UUserWidget>(refPath_Modalblock);
	if (BPClass_ModalBlack)
	{
		m_pModalBlock = Cast<UUserWidget>(CreateWidget(Managers::GameInst, BPClass_ModalBlack, TEXT("UIModalBlock")));
		Managers::GameInst->AddWidget(m_pModalBlock);
	}
	else
	{
		LOG_ERROR(TEXT("Failed :: Not Found BP :: %s"), refPath_Modalblock);
	}

	// UserInput 갱신
	m_pUserInputCtrl = Cast<AUserInputController>(Managers::World->GetWorld()->GetFirstPlayerController());
}

void UIManager::OnPostChangeLevel()
{
	// UserInput 갱신
	m_pUserInputCtrl = Cast<AUserInputController>(Managers::World->GetWorld()->GetFirstPlayerController());

	// 로드가 끝날때까지 Input을 잠금,
	// 추후 AGameModeBase::OnStartGame에서 열어준다.
	m_pUserInputCtrl->SetActorTickEnabled(false);
}

AUserInputController* const& UIManager::GetInputCtrl() const
{
	return m_pUserInputCtrl;
}

template <typename T>
T* UIManager::GetWindow(const bool& bCreate)
{
	const auto& uclass = T::StaticClass();
	// Window Instance 체크
	if (m_map_WndInst.Contains(uclass))
		return Cast<T>(m_map_WndInst[uclass]);

	// 생성 여부 체크
	if (!bCreate)
		return nullptr;

	FString wndName = T::StaticClass()->GetName();

	// Window Instance 생성
	FString refPath = FString::Printf(TEXT("WidgetBlueprint'/Game/GameContents/UI/Windows/%s/%s.%s_C'"), *wndName, *wndName, *wndName);
	auto BPClass = Managers::Asset->LoadBP<T>(*refPath);
	if (!BPClass)
	{
		LOG_ERROR(TEXT("Failed :: Not Found BP :: %s"), *refPath);
		return nullptr;
	}

	auto pWnd_New = Cast<T>(CreateWidget(Managers::GameInst, BPClass, *wndName));
	if (!pWnd_New)
		return nullptr;

	m_map_WndInst.Add(uclass, pWnd_New);
	Managers::GameInst->AddWidget(pWnd_New);

	pWnd_New->OnWindowCreate();
	
	return pWnd_New;
}

template <typename T>
T* UIManager::OpenWindow()
{
	auto pWnd =  GetWindow<T>(true);
	OpenWindow(pWnd);

	return pWnd;
}

void UIManager::OpenWindow(UWindowBase* pWnd)
{
	if (!pWnd)
		return;

	// 마지막 Window가 현재 Window인지 체크
	auto node_LastWindow = m_llist_WndStack.GetTail();
	if (node_LastWindow && node_LastWindow->GetValue() == pWnd)
		return;

	// 팝업이 아닐 경우 기존 보여지던 Window 정리
	if (!pWnd->IsPopup())
	{
		// zOrder 초기화
		zOrder = ZORDER_WINDOW_START;
	
		// 이전 Window Hide
		auto node_Wnd = m_llist_WndStack.GetTail();
		while (node_Wnd)
		{
			auto node_PrvWnd = node_Wnd;
			auto pWnd_Prv = node_PrvWnd->GetValue();

			node_Wnd = node_Wnd->GetPrevNode();

			// 이미 꺼져있다면
			if (!pWnd_Prv->IsShowing())
				break;

			// 뷰포트에서 제거
			pWnd_Prv->RemoveFromViewport();
			pWnd_Prv->OnWindowClosed(false);
		}
	}

	// 목표 Window Open
	m_llist_WndStack.AddTail(pWnd->GetNode());

	auto crrZOrder = zOrder;
	zOrder += ZORDER_WINDOW_INTERVAL;

	pWnd->AddToViewport(crrZOrder);
	pWnd->OnWindowOpened(true, crrZOrder);
	pWnd->OnWindowLastStack();

	RefreshModalBlock();
}

template <typename T>
bool UIManager::CloseWindow()
{
	auto pWnd_Close = UIManager::GetWindow<T>(false);
	return CloseWindow(pWnd_Close);
}

bool UIManager::CloseWindow(UWindowBase* pWnd)
{
	if (!pWnd)
		return true;

	if (!pWnd->IsInStack())
		return true;
	
	// 거부 체크
	if (pWnd->IsLocked())
		return false;

	// List에서 제거, Viewport에서 제거, Close Event
	pWnd->GetNode()->RemoveSelf();
	pWnd->RemoveFromViewport();
	pWnd->OnWindowClosed(true);

	// 꺼져있던 Window거나 Popup형이면 호출스택 탈출
	// 남은 UI가 없어도 호출스택 탈출
	if (pWnd->IsPopup() || m_llist_WndStack.Num() == 0)
		return true;

	/* 스택에 남은 Window를 켜주기 */
	
	// zOrder 초기화
	zOrder = 0;
	
	// 이전 Window 중 PopupType이 아닌 것을 찾는다.
	auto node_Wnd = m_llist_WndStack.GetTail();
	while (node_Wnd && !node_Wnd->GetValue()->IsPopup() && node_Wnd->GetPrevNode())
		node_Wnd = node_Wnd->GetPrevNode();

	// 해당 노드부터 차례대로 켜준다.
	while (node_Wnd)
	{
		auto pWnd_Prev = node_Wnd->GetValue();
		node_Wnd = node_Wnd->GetNextNode();

		pWnd_Prev->AddToViewport(++zOrder);
		pWnd_Prev->OnWindowOpened(false, zOrder);
	}

	node_Wnd = m_llist_WndStack.GetTail();
	if (node_Wnd)
		node_Wnd->GetValue()->OnWindowLastStack();

	RefreshModalBlock();
	return true;
}

bool UIManager::CloseWindow(UWindowBase* pWnd, const bool& bDestroy)
{
	auto bResult = CloseWindow(pWnd);
	if (bDestroy && bResult)
		Managers::GameInst->RemoveWidget(pWnd);

	return bResult;
}

bool UIManager::CloseLastWindow()
{
	if (m_pWnd_Popup && m_pWnd_Popup->IsShowing())
	{
		m_pWnd_Popup->OnClick_Escape();
		return true;
	}
	
	if (m_llist_WndStack.Num() == 0)
		return true;
	
	auto node_Last = m_llist_WndStack.GetTail();
	auto pWnd = node_Last->GetValue();
	if (pWnd->HasModule())
		return pWnd->CloseLastModule();
	
	return CloseWindow(pWnd);
}

void UIManager::ClearWindow(bool bDestroy)
{
	// 이전 Window 중 PopupType이 아닌 것을 찾는다.
	auto node_Wnd = m_llist_WndStack.GetTail();
	while (node_Wnd)
	{
		auto node_Close = node_Wnd;
		auto pWnd_Close = node_Close->GetValue();

		node_Wnd = node_Wnd->GetPrevNode();

		// 스택과 뷰포트에서 제거
		node_Close->RemoveSelf();
		if (pWnd_Close->IsInViewport())
			pWnd_Close->RemoveFromViewport();
	}

	// 바인딩된 키 모두 제거
	if (m_pUserInputCtrl)
		m_pUserInputCtrl->ClearKey(true);

	// 삭제
	if (bDestroy)
	{
		for (auto& pair : m_map_WndInst)
			Managers::GameInst->RemoveWidget(pair.Value);

		m_map_WndInst.Empty();
	}

	if (m_pModalBlock->IsInViewport())
		m_pModalBlock->RemoveFromViewport();
}

bool UIManager::IsLastStackWindow(UWindowBase* pWnd) const
{
	const auto& node_Wnd = pWnd->GetNode();
	return node_Wnd->GetList() && !node_Wnd->GetNextNode();
}

void UIManager::RefreshModalBlock() const
{
	// 일단 제거
	if (m_pModalBlock->IsInViewport())
		m_pModalBlock->RemoveFromViewport();
	
	// 팝업이 활성화 중이면
	if (m_pWnd_Popup && m_pWnd_Popup->IsShowing())
	{
		m_pModalBlock->AddToViewport(m_pWnd_Popup->GetZOrder() - 1);
		return;
	}

	auto node_Wnd = m_llist_WndStack.GetTail();
	while (node_Wnd)
	{
		const auto& pWnd = node_Wnd->GetValue();
		if (!pWnd->IsShowing())
			break;
		
		if (pWnd->UseModalBlock())
		{
			m_pModalBlock->AddToViewport(m_pWnd_Popup->GetZOrder() - 1);
			break;
		}
		
		node_Wnd = node_Wnd->GetPrevNode();
	}
}
