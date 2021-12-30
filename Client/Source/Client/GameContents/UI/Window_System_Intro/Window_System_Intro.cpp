// Fill out your copyright notice in the Description page of Project Settings.


#include "Window_System_Intro.h"

#include "Client/Framework/Managers/Managers.h"
#include "Components/Button.h"

UWindow_System_Intro::UWindow_System_Intro(const FObjectInitializer& ObjectInitializer)
	: UWindowBase(ObjectInitializer)
{
	bIsFocusable = true;
	m_bUseMouse = true;
}

void UWindow_System_Intro::OnWindowCreate()
{
	Super::OnWindowCreate();

	m_pBtn_Start->OnClicked.AddDynamic(this, &UWindow_System_Intro::OnClick_StartGame);
}

void UWindow_System_Intro::OnClick_StartGame()
{
	Managers::World->LoadWorld(EWorldId::Game, TEXT("LoadingPage_AnimInOut"));
}

bool UWindow_System_Intro::IsLocked()
{
	return false;
}
