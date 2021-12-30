#include "UIManager.h"
#include "UIBase/LoadingBase.h"
#include "Client/Framework/Managers/Managers.h"

ULoadingBase* UIManager::OpenLoading(const FString& loadingName)
{
	if (loadingName.IsEmpty())
		return nullptr;
	
	// LoadingPage Instance 생성
	FString refPath = FString::Printf(TEXT("WidgetBlueprint'/Game/GameContents/UI/LoadingPages/%s/%s.%s_C'"), *loadingName, *loadingName, *loadingName);
	auto BPClass = Managers::Asset->LoadBP<ULoadingBase>(*(refPath));
	if (!BPClass)
		return nullptr;
	
	auto pNewLoadingPage = Cast<ULoadingBase>(CreateWidget(Managers::GameInst, BPClass, *loadingName));
	if (!pNewLoadingPage)
		return nullptr;

	// 한번 쓰고 버리도록 구현되어 있다. 게임 상황에 맞춰서 변경하자
	// 로딩 페이지 띄우기
	pNewLoadingPage->AddToViewport(1000);
	Managers::GameInst->AddWidget(pNewLoadingPage);

	return pNewLoadingPage;
}

void UIManager::CloseLoading(ULoadingBase* pLoadingPage)
{
	if (pLoadingPage)
	{
		// 한번 쓰고 버리도록 구현되어 있다. 게임 상황에 맞춰서 변경하자
		// 로딩 페이지 지우기
		pLoadingPage->RemoveFromViewport();
		Managers::GameInst->RemoveWidget(pLoadingPage);
	}
}