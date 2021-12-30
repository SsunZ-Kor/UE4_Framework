#include "WindowBase.h"
#include "UIModuleBase.h"
#include "Client/Framework/Managers/Managers.h"
#include "Components/CanvasPanel.h"

SModuleInfo::SModuleInfo(TDoubleLinkedListEx<UUIModuleBase*>::TDoubleLinkedListExNode* node, UCanvasPanel* parent, FVector2D location)
	: Node(node), Parent(parent), Location(location){}

template<typename T>
T* UWindowBase::GetUIModule(const bool& bCreate)
{
	return Managers::UI->GetUIModule<T>(bCreate);
}

template <typename T>
bool UWindowBase::IsOpenedUIModule()
{
	return m_map_ModuleStackNode.Contains(T::StaticClass());
}

template <typename T>
T* UWindowBase::OpenUIModule(UCanvasPanel* pCanvasPanel)
{
	if (!pCanvasPanel)
	{
		LOG_ERROR(TEXT("Failed :: %s :: Canvas Panel is NULL"), *(T::StaticClass()->GetName()));
		return nullptr;
	}

	// Instance 가져오기
	auto pModule = GetUIModule<T>(true);
	if (!pModule)
		return nullptr;

	const auto& uclass = T::StaticClass();

	// 스텍에 추가
	if (m_map_ModuleStackNode.Contains(uclass))
	{
		auto& moduleInfo = m_map_ModuleStackNode[uclass];
		// 이미 추가되어 있다면 스택 순서만 바꿔준다.
		m_llist_ModuleStack.AddTail(moduleInfo.Node);
		if (moduleInfo.Parent != pCanvasPanel)
		{
			moduleInfo.Parent = pCanvasPanel;
			moduleInfo.Location = FVector2D::ZeroVector;
			pModule->SetRoot(pCanvasPanel);
			pModule->SetPosition(FVector2D::ZeroVector);
		}
	}
	else
	{
		// 추가 되어있지 않다면 새로 노드를 만들어 스택에 넣어준다.
		auto node_Module = new TDoubleLinkedListEx<UUIModuleBase*>::TDoubleLinkedListExNode(pModule);
		m_llist_ModuleStack.AddTail(node_Module);
		m_map_ModuleStackNode.Add(uclass, SModuleInfo(node_Module, pCanvasPanel, FVector2D::ZeroVector));

		// 레퍼런스 카운트 증가 및 OpenEvent
		Managers::UI->AddUIModuleRefCount(uclass);
		pModule->SetRoot(pCanvasPanel);
		pModule->SetPosition(FVector2D::ZeroVector);
		pModule->OnUIModuleOpened(this);
	}

	// zOrder 재정렬
	int zOrder = 0;
	auto node_Module = m_llist_ModuleStack.GetHead();
	while (node_Module)
	{
		node_Module->GetValue()->SetZOrder(++zOrder);
		node_Module = node_Module->GetNextNode();
	}

	// 마우스를 사용하지 않는 UI에서 모듈을 키면 커서를 켜준다.
	if (!m_bUseMouse && m_llist_ModuleStack.Num() > 0)
		Managers::UI->GetInputCtrl()->SetMouseEnable(true);

	return pModule;
}

template <typename T>
bool UWindowBase::CloseUIModule()
{
	return CloseUIModule(GetUIModule<T>(false));
}

bool UWindowBase::CloseUIModule(UUIModuleBase* pModule)
{
	if (!pModule)
		return true;

	const auto& uclass = pModule->GetStaticClass();

	// 열려 있는 Module 인지 체크
	if (!m_map_ModuleStackNode.Contains(uclass))
		return true;

	// 잠김 체크
	if (pModule->IsLocked())
		return false;

	auto node_Module = m_map_ModuleStackNode[uclass].Node;

	// 스택에서 제거, 노드 제거
	node_Module->RemoveSelf();
	m_map_ModuleStackNode.Remove(uclass);
	delete node_Module;

	pModule->OnUIModuleClosed();

	// 레퍼런스 카운트 감소
	Managers::UI->SubUIModuleRefCount(uclass);

	// 마우스를 사용하지 않는 UI에서 모듈을 껏을때 0개면 마우스도 꺼준다.
	if (!m_bUseMouse && m_llist_ModuleStack.Num() == 0)
		Managers::UI->GetInputCtrl()->SetMouseEnable(false);

	
	return true;
}

void UWindowBase::ClearUIModule()
{
	auto node_Module = m_llist_ModuleStack.GetHead();
	while (node_Module)
	{
		auto pModule = node_Module->GetValue();
		if (Managers::IsInit())
			Managers::UI->SubUIModuleRefCount(pModule->GetStaticClass());

		node_Module = node_Module->GetNextNode();
	}

	m_map_ModuleStackNode.Empty();
	m_llist_ModuleStack.Empty(true);
}

bool UWindowBase::HasModule()
{
	return m_llist_ModuleStack.Num() > 0;
}

bool UWindowBase::CloseLastModule()
{
	auto node_Module = m_llist_ModuleStack.GetTail();
	if (node_Module)
		return CloseUIModule(node_Module->GetValue());

	return true;
}


