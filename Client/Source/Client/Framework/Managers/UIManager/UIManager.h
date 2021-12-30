// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>

#include "../../ClientGameBase.h"
#include "UserInputController.h"


class UWindowBase;
class UUIModuleBase;
class ULoadingBase;
class UWindow_System_Popup;

class CLIENT_API UIManager
{
private: // For Window
	int32 zOrder = 0;
	static const int32 ZORDER_WINDOW_START;
	static const int32 ZORDER_WINDOW_INTERVAL;
	static const int32 ZORDER_POPUP;

	TDoubleLinkedListEx<UWindowBase*> m_llist_WndStack;
	TMap<UClass*, UWindowBase*> m_map_WndInst;

	UUserWidget* m_pModalBlock;

private : // For Popup
	UWindow_System_Popup* m_pWnd_Popup;
	
	// Todo :: Localization
	FString txt_Default_Ok;
	FString txt_Default_No;
	FString txt_Default_Cancel;

private :
	TMap<UClass*, int> /*<UIModuleBase::StaticClass, refCount>*/ map_ModuleRefCount;
	TMap<UClass*, UUIModuleBase*> map_ModulelInst;
	AUserInputController* m_pUserInputCtrl;

public:
	UIManager();
	~UIManager();
public:
	void Init();
	void OnPostChangeLevel();
	AUserInputController* const& GetInputCtrl() const;

public: // For Window	
	template<typename T = UWindowBase>
   	T* GetWindow(const bool& bCreate);
	template<typename T = UWindowBase>
	T* OpenWindow();
	void OpenWindow(UWindowBase* pWnd);
	template<typename T = UWindowBase>
	bool CloseWindow();
	bool CloseWindow(UWindowBase* pWnd);
	bool CloseWindow(UWindowBase* pWnd, const bool& bDestroy);
	bool CloseLastWindow();
	void ClearWindow(bool bDestroy);
	bool IsLastStackWindow(UWindowBase* pWnd) const;

	void RefreshModalBlock() const;

public : // For Loading
	ULoadingBase* OpenLoading(const FString& loadingName);
	void CloseLoading(ULoadingBase* pLoadingPage);

public : // For Popup
	void Popup(const FString& txt_Title, const FString& txt_Contents, const FString& txt_Ok, std::function<void()> okCallback);
	void Popup(const FString& txt_Title, const FString& txt_Contents, const FString& txt_Ok, std::function<void()> okCallback, const FString& txt_Cancel, std::function<void()> cancelCallback);
	void Popup(const FString& txt_Title, const FString& txt_Contents, const FString& txt_Ok, std::function<void()> okCallback, const FString& txt_No, std::function<void()> noCallback, const FString& txt_Cancel, std::function<void()> cancelCallback);
	void Popup(const FString& txt_Title, const FString& txt_Contents, std::function<void()> okCallback);
	void Popup(const FString& txt_Title, const FString& txt_Contents, std::function<void()> okCallback, std::function<void()> cancelCallback);
	void Popup(const FString& txt_Title, const FString& txt_Contents, std::function<void()> okCallback, std::function<void()> noCallback, std::function<void()> cancelCallback);

public: // For Module
	template<typename T = UUIModuleBase>
	T* GetUIModule(const bool& bCreate);
	void AddUIModuleRefCount(UClass* pModuleUClass);
	void SubUIModuleRefCount(UClass* pModuleUClass);
};