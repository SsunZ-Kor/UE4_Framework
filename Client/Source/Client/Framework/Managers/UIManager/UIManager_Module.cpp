#include "UIManager.h"
#include "Client/Framework/Managers/Managers.h"
#include "UIBase/UIModuleBase.h"

template <typename T>
T* UIManager::GetUIModule(const bool& bCreate)
{
	const auto& uclass = T::StaticClass();
	// Module Instance 체크
	if (map_ModulelInst.Contains(uclass))
		return Cast<T>(map_ModulelInst[uclass]);

	// 생성 여부 체크
	if (!bCreate)
		return nullptr;

	FString moduleName = T::StaticClass()->GetName();

	// Module Instance 생성
	FString refPath = FString::Printf(TEXT("WidgetBlueprint'/Game/GameContents/UI/UIModules/%s/%s.%s_C'"), *moduleName, *moduleName, *moduleName);
	auto BPClass = Managers::Asset->LoadBP<T>(*refPath);
	if (!BPClass)
	{
		LOG_ERROR(TEXT("Failed :: Not Found BP :: %s"), *refPath);
		return nullptr;
	}

	auto pModule = Cast<T>(CreateWidget(Managers::GameInst, BPClass, *moduleName));
	if (!pModule)
		return nullptr;

	map_ModulelInst.Add(uclass, pModule);
	map_ModuleRefCount.Add(uclass, 0);
	Managers::GameInst->AddWidget(pModule);

	pModule->OnUIModuleCreate(uclass);
	
	return pModule;
}

void UIManager::AddUIModuleRefCount(UClass* pModuleUClass)
{
	++map_ModuleRefCount[pModuleUClass];
}

void UIManager::SubUIModuleRefCount(UClass* pModuleUClass)
{
	auto refCount = --map_ModuleRefCount[pModuleUClass];

	// 레퍼런스 카운트가 0이면 삭제한다.
	if (refCount == 0)
	{
		Managers::GameInst->RemoveWidget(map_ModulelInst[pModuleUClass]);
		map_ModuleRefCount.Remove(pModuleUClass);
		map_ModulelInst.Remove(pModuleUClass);
	}
}