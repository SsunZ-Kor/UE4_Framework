// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_Intro.h"

#include "Client/Framework/Managers/Managers.h"
#include "Client/GameContents/UI/Window_System_Intro/Window_System_Intro.h"

AGameMode_Intro::AGameMode_Intro()
{
}

void AGameMode_Intro::OnInit()
{

	// 로고 UI 출력
	auto uclass_Logo = Managers::Asset->LoadBP<UUserWidget>("WidgetBlueprint'/Game/GameContents/System/UIBP_LOGO/UIBP_Logo.UIBP_Logo_C'");
	if (uclass_Logo)
	{
		auto pUIBP_Logo = Cast<UUserWidget>(CreateWidget(Managers::GameInst, uclass_Logo, TEXT("UIBP_Logo")));
		pUIBP_Logo->AddToViewport(500);
	}

	// 인트로창 미리 띄워놓기
	Managers::UI->OpenWindow<UWindow_System_Intro>();

	Super::OnInit();
}