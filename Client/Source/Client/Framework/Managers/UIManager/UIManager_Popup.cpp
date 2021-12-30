#include "UIManager.h"
#include "Window_System_Popup/Window_System_Popup.h"

void UIManager::Popup(const FString& txt_Title, const FString& txt_Contents, const FString& txt_Ok,	std::function<void()> okCallback)
{
	if (!m_pWnd_Popup)
		m_pWnd_Popup = GetWindow<UWindow_System_Popup>(true);
	
	m_pWnd_Popup->Init(txt_Title, txt_Contents, txt_Ok, okCallback);
	
	if (!m_pWnd_Popup->IsInViewport())
		m_pWnd_Popup->AddToViewport(ZORDER_POPUP);
	
	m_pWnd_Popup->OnWindowOpened(true, ZORDER_POPUP);
	RefreshModalBlock();
}

void UIManager::Popup(const FString& txt_Title, const FString& txt_Contents, const FString& txt_Ok,	std::function<void()> okCallback, const FString& txt_Cancel, std::function<void()> cancelCallback)
{
	if (!m_pWnd_Popup)
		m_pWnd_Popup = GetWindow<UWindow_System_Popup>(true);
	
	m_pWnd_Popup->Init(txt_Title, txt_Contents, txt_Ok, okCallback, txt_Cancel, cancelCallback);
	
	if (!m_pWnd_Popup->IsInViewport())
		m_pWnd_Popup->AddToViewport(ZORDER_POPUP);
	
	m_pWnd_Popup->OnWindowOpened(true, ZORDER_POPUP);
	RefreshModalBlock();
}

void UIManager::Popup(const FString& txt_Title, const FString& txt_Contents, const FString& txt_Ok,	std::function<void()> okCallback, const FString& txt_No, std::function<void()> noCallback, const FString& txt_Cancel, std::function<void()> cancelCallback)
{
	if (!m_pWnd_Popup)
		m_pWnd_Popup = GetWindow<UWindow_System_Popup>(true);
	
	m_pWnd_Popup->Init(txt_Title, txt_Contents, txt_Ok, okCallback, txt_No, noCallback, txt_Cancel, cancelCallback);

	if (!m_pWnd_Popup->IsInViewport())
		m_pWnd_Popup->AddToViewport(ZORDER_POPUP);

	m_pWnd_Popup->OnWindowOpened(true, ZORDER_POPUP);
	RefreshModalBlock();
}

void UIManager::Popup(const FString& txt_Title, const FString& txt_Contents, std::function<void()> okCallback)
{
	Popup(txt_Title, txt_Contents, txt_Default_Ok, okCallback);
}

void UIManager::Popup(const FString& txt_Title, const FString& txt_Contents, std::function<void()> okCallback,	std::function<void()> cancelCallback)
{
	Popup(txt_Title, txt_Contents, txt_Default_Ok, okCallback, txt_Default_Cancel, cancelCallback);
}

void UIManager::Popup(const FString& txt_Title, const FString& txt_Contents, std::function<void()> okCallback,	std::function<void()> noCallback, std::function<void()> cancelCallback)
{
	Popup(txt_Title, txt_Contents, txt_Default_Ok, okCallback, txt_Default_No, noCallback, txt_Default_Cancel, cancelCallback);
}