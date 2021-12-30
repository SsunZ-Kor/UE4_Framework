// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>

#include "../../ClientGameBase.h"

/**
 * 
 */

template<typename T = UClass>
class CLIENT_API LoadAsyncInfo
{
public:
	TSharedPtr<FStreamableHandle> m_Handle;
	FSoftObjectPath m_SoftPath;
	bool m_IsComplete;

	void Init(const FSoftObjectPath& softPath, TSharedPtr<FStreamableHandle> handle);
	void Complete();
	
	const bool& IsComplete() const;
	T* GetAsset() const;
};

class CLIENT_API ClientAssetManager
{
public:
	ClientAssetManager();
	~ClientAssetManager();

	void Init();

	template<typename T = UClass>
	T* LoadObj(const FString& refPath);
	template<typename T = UClass>
	UClass* LoadBP(const FString& refPath);
	template<typename T = UClass>
	LoadAsyncInfo<T>* LoadAsyncObj(const FString& refPath);

	template<typename T = UClass>
	void LoadAsyncObj(const FString& refPath, std::function<void(T*)> completeCallback);
};