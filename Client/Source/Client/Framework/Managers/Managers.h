// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Client/Framework/ClientGameInstance.h"
#include "Client/Framework/GameModes/ClientGameModeBase.h"

// #include "GameDataManager/GameDataManager.h"
#include "SFXManager/SFXManager.h"
#include "FXManager/FXManager.h"
#include "UIManager/UIManager.h"
#include "UserDataManager/UserDataManager.h"
#include "WorldManager/WorldManager.h"
#include "AssetManager/ClientAssetManager.h"
#include "NetworkManager/NetworkManager.h"
#include "LocalDataManager/LocalDataManager.h"
#include "BGMManager/BGMManager.h"
#include "DataFileManager/DataFileManager.h"
#include "LocalizationManager/LocalizationManager.h"

class CLIENT_API Managers
{
private:
	static bool m_bIsInit;

	static UClientGameInstance* m_pGameInst;

	// static GameDataManager* m_pGameDataMgr;
	static DataFileManager* m_pGameDataMgr;
	static LocalizationManager* m_pLZMgr;
	static UBGMManager* m_pBGMMgr;
	static SFXManager* m_pSFXMgr;
	static FXManager* m_pFXMgr;
	static UIManager* m_pUIMgr;
	static WorldManager* m_pWorldMgr;
	static NetworkManager* m_pNetworkMgr;
	static UserDataManager* m_pUserMgr;
	static ClientAssetManager* m_pAssetMgr;
	static LocalDataManager* m_pLocalDataMgr;

public:
	// static GameDataManager* const& GameData;
	static DataFileManager* const& GameData;
	static LocalizationManager* const& LZ;
	static UBGMManager* const& BGM;
	static SFXManager* const& SFX;
	static FXManager* const& FX;
	static UIManager* const& UI;
	static WorldManager* const& World;
	static NetworkManager* const& Net;
	static UClientGameInstance* const& GameInst;
	static ClientAssetManager* const& Asset;
	static UserDataManager* const& User;
	static LocalDataManager* const& LocalData;

public:
	static bool IsInit();
	
	static void Init(UWorld* pWorld);
	static void OnGameModeTick(const float& fDeltaTime);
	static void Release();
	static void Quit();

	static void OnPrevChangeWorld();
	static void OnPostChangeWorld();

private :
	Managers();
	~Managers();
};
