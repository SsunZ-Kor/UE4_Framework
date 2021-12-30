#include "GenericEx.h"
#include "Engine.h"
#include "Client/Framework/ClientGameBase.h"

template<class T>
void LoadAllObject(FString directory, TArray<T*>& result)
{
	result.Empty();
	// ObjLibrary로 해당 경로의 모든 파일 찾기
	auto objLibrary = UObjectLibrary::CreateLibrary(T::StaticClass(), true, true);
	objLibrary->LoadAssetDataFromPath(directory);

	TArray<FAssetData> assetDatas;
	objLibrary->GetAssetDataList(assetDatas);

	for (int i =0 ; i < assetDatas.Num(); ++i)
	{
		auto assetData = assetDatas[i];
		auto refPath = FString::Printf(TEXT("%s'%s'"), *T::StaticClass()->GetName(), *assetData.ObjectPath.GetPlainNameString());
		T* uasset = LoadObject<T> (nullptr, *refPath);
		if (!uasset)
			continue;

		result.Add(uasset);
	}
}

template <typename UENUMTYPE>
FString UEnumToString(UENUMTYPE enumValue)
{
	FString text = typeid(UENUMTYPE).name();
	text.ReplaceInline(TEXT("enum "), TEXT(""));
	
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *text, true);
	if (!enumPtr)
		return FString("Invalid");

	return enumPtr->GetNameStringByValue(static_cast<int64>(enumValue));
}