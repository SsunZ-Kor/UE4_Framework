// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientAssetManager.h"

#include "Engine/AssetManager.h"

template <typename T>
void LoadAsyncInfo<T>::Init(const FSoftObjectPath& softPath, TSharedPtr<FStreamableHandle> handle)
{
	m_Handle = handle;
	m_SoftPath = softPath;
	m_IsComplete = false;
}

template <typename T>
void LoadAsyncInfo<T>::Complete()
{
	m_IsComplete = true;
	if (m_Handle)
	{
		m_Handle->ReleaseHandle();
		m_Handle = nullptr;
	}
}

template <typename T>
const bool& LoadAsyncInfo<T>::IsComplete() const
{
	return m_IsComplete;
}

template <typename T>
T* LoadAsyncInfo<T>::GetAsset() const
{
	if (m_IsComplete && m_SoftPath.IsValid())
	{
		TAssetPtr<T> assetPtr(m_SoftPath);
		if (assetPtr)
			return assetPtr.Get();
	}

	return nullptr;
}


ClientAssetManager::ClientAssetManager()
{
}

ClientAssetManager::~ClientAssetManager()
{
}

void ClientAssetManager::Init()
{
}


template <typename T>
T* ClientAssetManager::LoadObj(const FString& refPath)
{
	return Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *refPath));
}

template <typename T>
UClass* ClientAssetManager::LoadBP(const FString& refPath)
{
	return StaticLoadClass(T::StaticClass(), nullptr, *refPath);
}

// 사용 후 꼭 LoadAsyncInfo<T>*을 delete 할것
template <typename T>
LoadAsyncInfo<T>* ClientAssetManager::LoadAsyncObj(const FString& refPath)
{
	auto path = refPath;

	// FSoftObjectPath 생성
	int idx;
	path.FindChar('\'', idx);
	path.RemoveAt(0, ++idx);
	path.RemoveAt(path.Len() - 1, 1);
	FSoftObjectPath softPath(path);

	LOG_WARNING(TEXT("%s"), *path);

	// 로딩
	LoadAsyncInfo<T>* pLoadInfo = new LoadAsyncInfo<T>();
	auto callback = FStreamableDelegate::CreateLambda([pLoadInfo](){pLoadInfo->Complete();});
	
	auto handle =
		UAssetManager::GetStreamableManager().RequestAsyncLoad(softPath, callback);

	pLoadInfo->Init(softPath, handle);
	return pLoadInfo;
}

template <typename T>
void ClientAssetManager::LoadAsyncObj(const FString& refPath, std::function<void(T*)> completeCallback)
{
	auto path = refPath;

	// FSoftObjectPath 생성
	int idx;
	path.FindChar('\'', idx);
	path.RemoveAt(0, ++idx);
	path.RemoveAt(path.Len() - 1, 1);
	FSoftObjectPath softPath(path);

	TSharedPtr<FStreamableHandle> handle;
	auto callback = FStreamableDelegate::CreateLambda([&handle, softPath, completeCallback]()
	{
		handle->ReleaseHandle();
		if (completeCallback)
		{
			TAssetPtr<T> assetPtr(softPath);
			if (assetPtr)
				completeCallback(assetPtr.Get());
		}
	});
	
	handle = UAssetManager::GetStreamableManager().RequestAsyncLoad(softPath, callback);
}