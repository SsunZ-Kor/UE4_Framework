// Fill out your copyright notice in the Description page of Project Settings.


#include "Window_System_Popup.h"

#include "Client/Framework/Managers/Managers.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/MultiLineEditableText.h"
#include "Components/TextBlock.h"

void UWindow_System_Popup::OnWindowCreate()
{
	Super::OnWindowCreate();

	m_pCanvas_LastAttached = nullptr;

	m_pCanvasRoot = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Canvas_Root")));
	
	m_pTxt_Title = Cast<UTextBlock>(GetWidgetFromName(TEXT("CTxt_Title")));
	m_pTxt_Contents = Cast<UMultiLineEditableText>(GetWidgetFromName(TEXT("CTxt_Contents")));;

	// Button Roots
	m_pCanvas_BtnSetRoot_01 = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Canvas_Btn1Set")));
	m_pCanvas_BtnSetRoot_02 = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Canvas_Btn2Set")));
	m_pCanvas_BtnSetRoot_03 = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Canvas_Btn3Set")));

	// Buttons
	m_pBtn_Ok_01 = Cast<UButton>(GetWidgetFromName(TEXT("Btn_1_Ok")));
	m_pBtn_Ok_02 = Cast<UButton>(GetWidgetFromName(TEXT("Btn_2_Ok")));
	m_pBtn_Ok_03 = Cast<UButton>(GetWidgetFromName(TEXT("Btn_3_Ok")));
	m_pBtn_Ok_01->OnClicked.AddDynamic(this, &UWindow_System_Popup::OnClick_Ok);
	m_pBtn_Ok_02->OnClicked.AddDynamic(this, &UWindow_System_Popup::OnClick_Ok);
	m_pBtn_Ok_03->OnClicked.AddDynamic(this, &UWindow_System_Popup::OnClick_Ok);
	
	m_pBtn_Cancel_02 = Cast<UButton>(GetWidgetFromName(TEXT("Btn_2_Cancel")));
	m_pBtn_Cancel_03 = Cast<UButton>(GetWidgetFromName(TEXT("Btn_3_Cancel")));
	m_pBtn_Cancel_02->OnClicked.AddDynamic(this, &UWindow_System_Popup::OnClick_Cancel);
	m_pBtn_Cancel_03->OnClicked.AddDynamic(this, &UWindow_System_Popup::OnClick_Cancel);

	m_pBtn_No_02 = Cast<UButton>(GetWidgetFromName(TEXT("Btn_3_No")));
	m_pBtn_No_02->OnClicked.AddDynamic(this, &UWindow_System_Popup::OnClick_No);

	// Button Texts
	m_pTxt_Ok_01 = Cast<UTextBlock>(GetWidgetFromName(TEXT("CTxt_1_Ok")));
	m_pTxt_Ok_02 = Cast<UTextBlock>(GetWidgetFromName(TEXT("CTxt_2_Ok")));
	m_pTxt_Ok_03 = Cast<UTextBlock>(GetWidgetFromName(TEXT("CTxt_3_Ok")));
	
	m_pTxt_Cancel_02 = Cast<UTextBlock>(GetWidgetFromName(TEXT("CTxt_2_Cancel")));
	m_pTxt_Cancel_03 = Cast<UTextBlock>(GetWidgetFromName(TEXT("CTxt_3_Cancel")));

	m_pTxt_No_03 = Cast<UTextBlock>(GetWidgetFromName(TEXT("CTxt_3_No")));

	// 모든 BtnSet을 화면에서 지운다.
	m_pCanvas_BtnSetRoot_01->SetVisibility(ESlateVisibility::Hidden);
	m_pCanvas_BtnSetRoot_02->SetVisibility(ESlateVisibility::Hidden);
	m_pCanvas_BtnSetRoot_03->SetVisibility(ESlateVisibility::Hidden);
}

void UWindow_System_Popup::BeginDestroy()
{
	Super::BeginDestroy();
}

void UWindow_System_Popup::Init(const FString& txt_Title, const FString& txt_Contents, const FString& txt_Ok, std::function<void()> okCallback)
{
	InitCommon(txt_Title, txt_Contents, 2, okCallback, nullptr, nullptr);
	ChangeRoot(m_pCanvas_BtnSetRoot_01);

	m_pTxt_Ok_01->SetText(FText::FromString(txt_Ok));
}

void UWindow_System_Popup::Init(const FString& txt_Title, const FString& txt_Contents, const FString& txt_Ok, std::function<void()> okCallback, const FString& txt_Cancel, std::function<void()> cancelCallback)
{
	InitCommon(txt_Title, txt_Contents, 2, okCallback, nullptr, cancelCallback);
	ChangeRoot(m_pCanvas_BtnSetRoot_01);

	m_pTxt_Ok_02->SetText(FText::FromString(txt_Ok));
	m_pTxt_Cancel_02->SetText(FText::FromString(txt_Cancel));
}

void UWindow_System_Popup::Init(const FString& txt_Title, const FString& txt_Contents, const FString& txt_Ok, std::function<void()> okCallback, const FString& txt_No, std::function<void()> noCallback, const FString& txt_Cancel,	std::function<void()> cancelCallback)
{
	InitCommon(txt_Title, txt_Contents, 3, okCallback, noCallback, cancelCallback);
	ChangeRoot(m_pCanvas_BtnSetRoot_01);

	m_pTxt_Ok_03->SetText(FText::FromString(txt_Ok));
	m_pTxt_No_03->SetText(FText::FromString(txt_No));
	m_pTxt_Cancel_03->SetText(FText::FromString(txt_Cancel));
}


void UWindow_System_Popup::OnClick_Ok()
{
	CallAndClear(m_okCallback);
}

void UWindow_System_Popup::OnClick_No()
{
	CallAndClear(m_noCallback);
}

void UWindow_System_Popup::OnClick_Cancel()
{
	CallAndClear(m_cancelCallback);
}

void UWindow_System_Popup::OnClick_Escape()
{
	switch(m_nBtnType)
	{
		case 1:
			OnClick_Ok();
			break;
		default:
			OnClick_Cancel();
			break;
	}
}

bool UWindow_System_Popup::Close()
{
	RemoveFromViewport();
	OnWindowClosed(false);
	Managers::UI->RefreshModalBlock();
	return true;
}

void UWindow_System_Popup::CallAndClear(std::function<void()> call)
{
	Close();

	m_okCallback = nullptr;
	m_noCallback = nullptr;
	m_cancelCallback = nullptr;

	if (call)
		call();
}

void UWindow_System_Popup::InitCommon(const FString& txt_Title, const FString& txt_Contents, const int& nBtnType, std::function<void()> okCallback, std::function<void()> noCallback, std::function<void()> cancelCallback)
{
	m_okCallback = okCallback;
	m_noCallback = noCallback;
	m_cancelCallback = cancelCallback;
	
	m_nBtnType = nBtnType;
	m_pTxt_Title->SetText(FText::FromString(txt_Title));
	m_pTxt_Contents->SetText(FText::FromString(txt_Contents));
}

void UWindow_System_Popup::ChangeRoot(UCanvasPanel*& pCanvas_BtnSetRoot)
{
	if (m_pCanvas_LastAttached)
	{
		if (m_pCanvas_LastAttached == pCanvas_BtnSetRoot)
			return;

		m_pCanvas_LastAttached->SetVisibility(ESlateVisibility::Hidden);
	}
	
	m_pCanvas_LastAttached = pCanvas_BtnSetRoot;
	m_pCanvas_LastAttached->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}