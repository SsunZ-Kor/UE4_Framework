// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers.h"

#include "Client/Framework/GameCharacter/GameCharacter.h"

bool Managers::m_bIsInit = false;

UClientGameInstance* Managers::m_pGameInst = nullptr;
UClientGameInstance* const& Managers::GameInst = m_pGameInst;

WorldManager* Managers::m_pWorldMgr = nullptr;
WorldManager* const& Managers::World = m_pWorldMgr;

// GameDataManager* Managers::m_pGameDataMgr = nullptr;
// GameDataManager* const& Managers::GameData = m_pGameDataMgr;

DataFileManager* Managers::m_pGameDataMgr = nullptr;
DataFileManager* const& Managers::GameData = m_pGameDataMgr;

LocalizationManager* Managers::m_pLZMgr = nullptr;
LocalizationManager* const& Managers::LZ = m_pLZMgr;

UBGMManager* Managers::m_pBGMMgr = nullptr;
UBGMManager* const& Managers::BGM = m_pBGMMgr;

SFXManager* Managers::m_pSFXMgr = nullptr;
SFXManager* const& Managers::SFX = m_pSFXMgr;

FXManager* Managers::m_pFXMgr = nullptr;
FXManager* const& Managers::FX = m_pFXMgr;

UIManager* Managers::m_pUIMgr = nullptr;
UIManager* const& Managers::UI = m_pUIMgr;

NetworkManager* Managers::m_pNetworkMgr = nullptr;
NetworkManager* const& Managers::Net = m_pNetworkMgr;

ClientAssetManager* Managers::m_pAssetMgr = nullptr;
ClientAssetManager* const& Managers::Asset = m_pAssetMgr;

UserDataManager* Managers::m_pUserMgr = nullptr;
UserDataManager* const& Managers::User = m_pUserMgr;

LocalDataManager* Managers::m_pLocalDataMgr = nullptr;
LocalDataManager* const& Managers::LocalData = m_pLocalDataMgr;


/* private */
Managers::Managers() {}
/* private */

Managers::~Managers() {}

bool Managers::IsInit()
{
	return m_bIsInit;
}

void Managers::Init(UWorld* pWorld)
{
	if (m_bIsInit || pWorld == nullptr)
		return;

	m_bIsInit = true;

	m_pGameInst = Cast<UClientGameInstance>(pWorld->GetGameInstance());

	// 가장 먼저 Init 한다.
	m_pWorldMgr = new WorldManager;
	m_pWorldMgr->RegistWorld(pWorld);

	m_pLocalDataMgr = new LocalDataManager();
	m_pLocalDataMgr->Init();

	m_pAssetMgr = new ClientAssetManager();
	m_pAssetMgr->Init();
	
	m_pGameDataMgr = new DataFileManager();
	m_pGameDataMgr->Init();

	m_pLZMgr = new LocalizationManager();
	m_pLZMgr->Init();

	m_pBGMMgr = NewObject<UBGMManager>();
	m_pGameInst->AddUObject(m_pBGMMgr);
	m_pBGMMgr->Init();
	
	m_pSFXMgr = new SFXManager();
	m_pSFXMgr->Init();
	
	m_pFXMgr = new FXManager();
	m_pFXMgr->Init();

	m_pUIMgr = new UIManager();
	m_pUIMgr->Init();

	m_pNetworkMgr = new NetworkManager();
	m_pNetworkMgr->Init();

	// Todo :: Run AssetMgr PMS

	m_pUserMgr = new UserDataManager();
	m_pUserMgr->Init();
}

void Managers::OnGameModeTick(const float& fDeltaTime)
{
	if (m_pNetworkMgr)
		m_pNetworkMgr->OnGameModeTick();
	if (m_pBGMMgr)
		m_pBGMMgr->OnGameModeTick(fDeltaTime);
}

void Managers::Release()
{
	if (!m_bIsInit)
		return;

	m_bIsInit = false;

	/* Release */
	if (m_pNetworkMgr)	{ delete m_pNetworkMgr;						m_pNetworkMgr = nullptr;	}
	if (m_pGameDataMgr)		{ delete m_pGameDataMgr;						m_pGameDataMgr = nullptr;		}
	if (m_pLZMgr)		{ delete m_pLZMgr;							m_pLZMgr = nullptr;	}
	if (m_pUIMgr)		{ delete m_pUIMgr;							m_pUIMgr = nullptr;			}
	if (m_pSFXMgr)		{ delete m_pSFXMgr;							m_pSFXMgr = nullptr;		}
	if (m_pBGMMgr)		{ m_pGameInst->RemoveUObject(m_pBGMMgr);	m_pBGMMgr = nullptr;		}
	if (m_pFXMgr)		{ delete m_pFXMgr;							m_pFXMgr = nullptr;			}
	if (m_pAssetMgr)	{ delete m_pAssetMgr;						m_pAssetMgr = nullptr;		}
	if (m_pUserMgr)		{ delete m_pUserMgr;						m_pUserMgr = nullptr;		}
	if (m_pLocalDataMgr){ delete m_pLocalDataMgr;					m_pLocalDataMgr = nullptr;	}
	if (m_pWorldMgr)	{ delete m_pWorldMgr;						m_pWorldMgr = nullptr;		}

	m_pGameInst = nullptr;

	if (AGameCharacter::AllyInfo)
	{
		delete AGameCharacter::AllyInfo;
		AGameCharacter::AllyInfo = nullptr;
	}
}

void Managers::Quit()
{
	// Todo :: 
}

void Managers::OnPrevChangeWorld()
{
	if (m_pSFXMgr)
		m_pSFXMgr->OnPrevChangeLevel();
	
	if (m_pFXMgr)
		m_pFXMgr->OnPrevChangeLevel();
}

void Managers::OnPostChangeWorld()
{
	if (m_pSFXMgr)
		m_pSFXMgr->OnPostChangeLevel();

	if (m_pUIMgr)
		m_pUIMgr->OnPostChangeLevel();
}