// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Client/Framework/Managers/UIManager/UIBase/WindowBase.h"
#include "Window_System_Intro.generated.h"

class UButton;

UCLASS()
class CLIENT_API UWindow_System_Intro : public UWindowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Window System Intro", meta=(BindWidget, AllowPrivateAccess="true", DisplayName="Btn Start"))
	UButton* m_pBtn_Start;

	UFUNCTION()
	void OnClick_StartGame();

public:
	UWindow_System_Intro(const FObjectInitializer& ObjectInitializer);
	virtual bool IsLocked() override;

public:
	virtual void OnWindowCreate() override;
};