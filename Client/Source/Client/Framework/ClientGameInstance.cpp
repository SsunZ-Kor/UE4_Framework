// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientGameInstance.h"

#include "Blueprint/UserWidget.h"
#include "Managers/Managers.h"

void UClientGameInstance::Init()
{
	Super::Init();
}

void UClientGameInstance::BeginDestroy()
{
	Managers::Release();

	Super::BeginDestroy();
}

void UClientGameInstance::AddWidget(UUserWidget* pUserWidget)
{
	if (m_set_WidgetInst.Contains(pUserWidget))
		return;

	m_set_WidgetInst.Add(pUserWidget);
}

void UClientGameInstance::RemoveWidget(UUserWidget* pUserWidget)
{
	if (m_set_WidgetInst.Contains(pUserWidget))
	{
		m_set_WidgetInst.Remove(pUserWidget);
		pUserWidget->ConditionalBeginDestroy();
	}
}

void UClientGameInstance::ClearWidgets()
{
	TArray<UUserWidget*> delWidgets;
	{
		for(auto& pWidget : m_set_WidgetInst)
			delWidgets.Add(pWidget);
	}
	
	m_set_WidgetInst.Empty();
	
	{
		for (auto& pWidget : delWidgets)
			pWidget->ConditionalBeginDestroy();
	}
}

void UClientGameInstance::AddMat(UMaterialInterface* pMat)
{
	if (m_set_Mat.Contains(pMat))
		return;

	m_set_Mat.Add(pMat);
}

void UClientGameInstance::RemoveMat(UMaterialInterface* pMat)
{
	if (m_set_Mat.Contains(pMat))
	{
		m_set_Mat.Remove(pMat);
		pMat->ConditionalBeginDestroy();
	}
}

void UClientGameInstance::RemoveMat(const TArray<UMaterialInterface*>& mats)
{
	for (int i = 0 ; i < mats.Num(); ++i)
		RemoveMat(mats[i]);
}

void UClientGameInstance::RemoveMat(const TArray<UMaterialInstanceDynamic*>& mats)
{
	for (int i = 0 ; i < mats.Num(); ++i)
		RemoveMat(mats[i]);
}

void UClientGameInstance::ClearMat()
{
	TArray<UMaterialInterface*> delMats;
	{
		for(auto& pMat : m_set_Mat)
			delMats.Add(pMat);
	}
	
	m_set_Mat.Empty();
	
	{
		for (auto& pMat : delMats)
			pMat->ConditionalBeginDestroy();
	}
}

void UClientGameInstance::AddUObject(UObject* pMgr)
{
	if (m_set_uObj.Contains(pMgr))
		return;
	
	m_set_uObj.Add(pMgr);
}

void UClientGameInstance::RemoveUObject(UObject* pMgr)
{
	if (m_set_uObj.Contains(pMgr))
	{
		m_set_uObj.Remove(pMgr);
		pMgr->ConditionalBeginDestroy();
	}
}

void UClientGameInstance::OnComplete_LoadLevel()
{
	if (Managers::World)
		Managers::World->LoadCompleteLevel();
}
