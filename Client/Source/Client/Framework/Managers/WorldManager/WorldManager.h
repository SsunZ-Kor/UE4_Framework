// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>

#include "Client/Framework/GameModes/ClientGameModeBase.h"

UENUM()
enum class EWorldId : uint8
{
	Intro,
	Lobby,
	Game,
};

class ULoadingBase;

class CLIENT_API WorldManager
{
private:
	enum class ELevelExecuteTypes : uint8
	{
		None,
		LoadLand,
		UnloadLand,
		LoadSpawn,
		UnloadSpawn,
	};
	
	struct SLevelExecuteInfo
	{
		ELevelExecuteTypes ExecuteType;
		FString LevelName;

		SLevelExecuteInfo();
		SLevelExecuteInfo(const ELevelExecuteTypes& excuteType, const FString& levelName);
	};

	// For World
	EWorldId m_WorldId;
	UWorld* m_pCrrWorld;
	AClientGameModeBase* m_pCrrGameMode;

	bool m_bIsLoading;
	ULoadingBase* m_pLoadingPage;

	// For Level
	bool m_bIsLoadingLevel;					// 레벨 로드 중인가?
	TSet<FString> m_set_LoadedLand;		// 로드 완료된 랜드
	TSet<FString> m_set_LoadedSpawn;		// 로드 완료된 스폰

	AActor* m_pCrrLandActor;

	TQueue<SLevelExecuteInfo> m_queue_LevelExecuteInfo;	// 로드 대기 큐

	int32 UUID_LevelLoad;
	std::function<void()> m_callback_LoadComplete;

	
public:
	WorldManager();
	~WorldManager();

	void RegistWorld(UWorld* const pWorld);

	UWorld* GetWorld() const;
	AClientGameModeBase* GetGameMode() const;
	const bool& IsLoading() const;

	void LoadWorld(const EWorldId& worldId, const FString& loadingName);

public:	// 레벨 스트리밍용
	const bool& IsLevelLoading() const;

	void LoadLandAsync(const FString&  name_LandLevel);
	void LoadSpawnAsync(const FString&  name_SpawnLevel);
   	void UnloadSpawnAsync(const FString&  name_SpawnLevel);
	void SetLevelAsyncEndCallback(std::function<void()> callback);
	void LoadCompleteLevel();

	void CheckAndLoadLand(const AActor* const& target);

public: // GameMode 및 LoadinUI 통신
	void OnEnd_LoadingAnim_Open();
	void OnEnd_LoadingAnim_Close();

	void OnStart_GameModeInit(AClientGameModeBase* pGameMode);
	void OnEnd_GameModeInit();
};