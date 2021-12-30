// Fill out your copyright notice in the Description page of Project Settings.


#include "WindowBase.h"

#include "UIModuleBase.h"
#include "Client/Framework/Managers/Managers.h"

UWindowBase::UWindowBase(const FObjectInitializer& ObjectInitializer) : UImmortalWidget(ObjectInitializer)
{
	m_bIsPopup = false;
	m_bUseModalBlock = false;
	m_bUseMouse = true;
}

UWindowBase::~UWindowBase()
{
	if (m_pNode)
	{
		m_pNode->RemoveSelf();
		
		delete m_pNode;
		m_pNode = nullptr;
	}
}

void UWindowBase::BeginDestroy()
{
	Super::BeginDestroy();

	ClearUIModule();
}

TDoubleLinkedListEx<UWindowBase*>::TDoubleLinkedListExNode* UWindowBase::GetNode()
{
	if (!m_pNode)
		m_pNode = new TDoubleLinkedListEx<UWindowBase*>::TDoubleLinkedListExNode(this);
	
	return m_pNode;
}

bool UWindowBase::IsInStack() const
{
	return m_pNode && m_pNode->GetList();
}

const bool& UWindowBase::IsShowing() const
{
	return m_IsShowing;
}

const bool& UWindowBase::IsPopup() const
{
	return m_bIsPopup;
}

const bool& UWindowBase::UseModalBlock() const
{
	return m_bUseModalBlock;
}

const int32& UWindowBase::GetZOrder() const
{
	return m_zOrder;
}

bool UWindowBase::IsInLastStack()
{
	return Managers::UI->IsLastStackWindow(this);
}

void UWindowBase::OnWindowCreate()
{
}

void UWindowBase::OnWindowOpened(const bool& bOpen, const int32& zOrder)
{
	m_zOrder = zOrder;
	m_IsShowing = true;

	// 복구 된 것이면
	if (!bOpen && m_map_ModuleStackNode.Num() > 0)
	{
		for (auto pair : m_map_ModuleStackNode)
		{
			const auto& moduleInfo = pair.Value;
			auto pModule = moduleInfo.Node->GetValue();
			pModule->OnUIModuleOpened(this);
			pModule->SetRoot(moduleInfo.Parent);
			pModule->SetPosition(moduleInfo.Location);
		}
		
		// zOrder_Module 정리
		int zOrder_Module = 0;
		auto node_Module = m_llist_ModuleStack.GetHead();
		while (node_Module)
		{
			node_Module->GetValue()->SetZOrder(++zOrder_Module);
			node_Module = node_Module->GetNextNode();
		}
	}
}

void UWindowBase::OnWindowClosed(const bool& bClosed)
{
	m_IsShowing = false;
}

void UWindowBase::OnWindowLastStack()
{
	auto pInputCtrl = Managers::UI->GetInputCtrl();
	if (pInputCtrl)
	{
		pInputCtrl->ClearKey(false);
		InitHotkey();
		pInputCtrl->SaveKey();
	}

	// 마우스 커서 세팅
	Managers::UI->GetInputCtrl()->SetMouseEnable(m_bUseMouse);
}

bool UWindowBase::IsLocked()
{
	return false;
}

void UWindowBase::Refresh()
{
}

bool UWindowBase::Close()
{
	return Managers::UI->CloseWindow(this);
}

void UWindowBase::InitHotkey()
{
	
}