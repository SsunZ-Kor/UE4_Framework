// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>
#include "Client/Framework/Managers/UIManager/UIBase/WindowBase.h"
#include "Window_System_Popup.generated.h"

class UCanvasPanel;
class UButton;
class UTextBlock;
class UMultiLineEditableText;

UCLASS()
class CLIENT_API UWindow_System_Popup : public UWindowBase
{
	GENERATED_BODY()
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCanvasPanel* m_pCanvasRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_pTxt_Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UMultiLineEditableText* m_pTxt_Contents;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCanvasPanel* m_pCanvas_BtnSetRoot_01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCanvasPanel* m_pCanvas_BtnSetRoot_02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCanvasPanel* m_pCanvas_BtnSetRoot_03;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_pBtn_Ok_01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_pBtn_Ok_02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_pBtn_Ok_03;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_pBtn_Cancel_02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_pBtn_Cancel_03;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_pBtn_No_02;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_pTxt_Ok_01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_pTxt_Ok_02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_pTxt_Ok_03;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_pTxt_Cancel_02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_pTxt_Cancel_03;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_pTxt_No_03;

	UPROPERTY()
	UCanvasPanel* m_pCanvas_LastAttached;

	std::function<void()> m_okCallback;
	std::function<void()> m_noCallback;
	std::function<void()> m_cancelCallback;
	int m_nBtnType;

public:
	virtual void OnWindowCreate() override;
	virtual void BeginDestroy() override;
	
	void Init(const FString& txt_Title, const FString& txt_Contents, const FString& txt_Ok,	std::function<void()> okCallback);
	void Init(const FString& txt_Title, const FString& txt_Contents, const FString& txt_Ok,	std::function<void()> okCallback, const FString& txt_Cancel, std::function<void()> cancelCallback);
	void Init(const FString& txt_Title, const FString& txt_Contents, const FString& txt_Ok,	std::function<void()> okCallback, const FString& txt_No, std::function<void()> noCallback, const FString& txt_Cancel, std::function<void()> cancelCallback);

	UFUNCTION(BlueprintCallable)
	void OnClick_Ok();
	UFUNCTION(BlueprintCallable)
	void OnClick_No();
	UFUNCTION(BlueprintCallable)
	void OnClick_Cancel();

	void OnClick_Escape();

	virtual bool Close() override;

private:
	void CallAndClear(std::function<void()> call);
	void ChangeRoot(UCanvasPanel*& pCanvas_BtnSetRoot);
	void InitCommon(const FString& txt_Title, const FString& txt_Contents, const int& nBtnType, std::function<void()> okCallback, std::function<void()> noCallback, std::function<void()> cancelCallback);
};