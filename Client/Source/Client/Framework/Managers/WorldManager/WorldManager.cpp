// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManager.h"

#include "ULandData.h"
#include "Client/Framework/Managers/Managers.h"
#include "Client/Framework/Managers/UIManager/UIBase/LoadingBase.h"
#include "Client/GameContents/SpawnSystem/SpawnSystem.h"

WorldManager::SLevelExecuteInfo::SLevelExecuteInfo()
{
	ExecuteType = ELevelExecuteTypes::None;
}

WorldManager::SLevelExecuteInfo::SLevelExecuteInfo(const ELevelExecuteTypes& excuteType, const FString& levelName)
{
	ExecuteType = excuteType;
	LevelName = levelName;
}

WorldManager::WorldManager()
{
	m_WorldId = EWorldId::Intro;
	m_pCrrWorld = nullptr;
	m_pCrrGameMode = nullptr;

	m_bIsLoading = false;
	m_pLoadingPage = nullptr;

	m_bIsLoadingLevel = false;

	m_pCrrLandActor = nullptr;
	UUID_LevelLoad = 0;
}

WorldManager::~WorldManager()
{
}

void WorldManager::RegistWorld(UWorld* const pWorld)
{
	m_pCrrWorld = pWorld;
	m_pCrrGameMode = Cast<AClientGameModeBase>(m_pCrrWorld->GetAuthGameMode());
}

UWorld* WorldManager::GetWorld() const
{
	return m_pCrrWorld;
}

AClientGameModeBase* WorldManager::GetGameMode() const
{
	return m_pCrrGameMode;
}

const bool& WorldManager::IsLoading() const
{
	return m_bIsLoading;
}

void WorldManager::LoadWorld(const EWorldId& worldId, const FString& loadingName)
{
	if (m_pLoadingPage || m_WorldId == worldId)
		return;

	m_bIsLoading = true;
	m_WorldId = worldId;

	// 레벨 로드 목록 및 대기열 목록 클리어
	m_set_LoadedLand.Empty();
	m_set_LoadedSpawn.Empty();
	
	m_queue_LevelExecuteInfo.Empty();

	m_bIsLoadingLevel = false;

	// 로딩 페이지 오픈
	m_pLoadingPage = Managers::UI->OpenLoading(loadingName);
	if (m_pLoadingPage)
		m_pLoadingPage->Open();
	else
		OnEnd_LoadingAnim_Open();
}

const bool& WorldManager::IsLevelLoading() const
{
	return m_bIsLoadingLevel;
}

void WorldManager::LoadLandAsync(const FString& name_LandLevel)
{
	if (name_LandLevel.IsEmpty())
		return;
	
	// 주변 레벨 데이터 가져오기
	FString level_LandDataName = name_LandLevel + TEXT("_Data");
	auto levelLandData = Managers::Asset->LoadObj<UULandData>(FString::Printf(TEXT("ULandData'/Game/GameContents/Levels/Level_Land/%s.%s'"), *level_LandDataName, *level_LandDataName));
	if (levelLandData)
	{
		// 필요한 랜드 레벨 수집
		TSet<FString> set_NewLands;
		set_NewLands.Add(name_LandLevel);
		for (auto& landName : levelLandData->NeighboringLandNames)
			set_NewLands.Add(landName);

		// 현재 로드 되어있는 랜드 중 삭제해야한다면 큐에 추가
		for (auto& landName_Loaded : m_set_LoadedLand)
		{
			if (set_NewLands.Contains(landName_Loaded))
				continue;

			m_queue_LevelExecuteInfo.Enqueue(SLevelExecuteInfo(ELevelExecuteTypes::UnloadLand, landName_Loaded));
		}

		// 로드 큐에 추가
		for (auto& landName_Load : set_NewLands)
		{
			if (m_set_LoadedLand.Contains(landName_Load))
				continue;
			
			m_queue_LevelExecuteInfo.Enqueue(SLevelExecuteInfo(ELevelExecuteTypes::LoadLand, landName_Load));
		}
	}

	// 로딩 중이 아니면 로딩 시작
	if (!m_bIsLoadingLevel)
	{
		m_bIsLoadingLevel = true;
		LoadCompleteLevel();
	}
}

void WorldManager::LoadSpawnAsync(const FString& name_SpawnLevel)
{
	if (name_SpawnLevel.IsEmpty())
		return;

	m_queue_LevelExecuteInfo.Enqueue(SLevelExecuteInfo(ELevelExecuteTypes::LoadSpawn, name_SpawnLevel));

	// 로딩 중이 아니면 로딩 시작
	if (!m_bIsLoadingLevel)
	{
		m_bIsLoadingLevel = true;
		LoadCompleteLevel();
	}
}

void WorldManager::UnloadSpawnAsync(const FString& name_SpawnLevel)
{
	if (name_SpawnLevel.IsEmpty())
		return;

	m_queue_LevelExecuteInfo.Enqueue(SLevelExecuteInfo(ELevelExecuteTypes::UnloadSpawn, name_SpawnLevel));

	// 로딩 중이 아니면 로딩 시작
	if (!m_bIsLoadingLevel)
	{
		m_bIsLoadingLevel = true;
		LoadCompleteLevel();
	}
}

void WorldManager::SetLevelAsyncEndCallback(std::function<void()> callback)
{
	m_callback_LoadComplete = callback;
}

void WorldManager::LoadCompleteLevel()
{
	while (!m_queue_LevelExecuteInfo.IsEmpty())
	{
		SLevelExecuteInfo levelInfo;
		m_queue_LevelExecuteInfo.Dequeue(levelInfo);

		FLatentActionInfo actionInfo;
		actionInfo.UUID = ++UUID_LevelLoad;
		actionInfo.Linkage = 1;
		actionInfo.CallbackTarget = Managers::GameInst;
		actionInfo.ExecutionFunction = "OnComplete_LoadLevel";

		// Load 일 경우
		switch (levelInfo.ExecuteType)
		{
			case ELevelExecuteTypes::LoadLand:
				{
					if (m_set_LoadedLand.Contains(levelInfo.LevelName))
						continue;

					m_set_LoadedLand.Add(levelInfo.LevelName);
					UGameplayStatics::LoadStreamLevel(m_pCrrWorld, *levelInfo.LevelName, true, false, actionInfo);
				}
				break;
			case ELevelExecuteTypes::LoadSpawn:
				{
					if (m_set_LoadedSpawn.Contains(levelInfo.LevelName))
						continue;

					m_set_LoadedSpawn.Add(levelInfo.LevelName);
					UGameplayStatics::LoadStreamLevel(m_pCrrWorld, *levelInfo.LevelName, true, false, actionInfo);
				}
				break;
			case ELevelExecuteTypes::UnloadLand:
				{
					if (!m_set_LoadedLand.Contains(levelInfo.LevelName))
						continue;

					m_set_LoadedLand.Remove(levelInfo.LevelName);
					UGameplayStatics::UnloadStreamLevel(m_pCrrWorld, *(levelInfo.LevelName), actionInfo, false);
				}
				break;
			case ELevelExecuteTypes::UnloadSpawn:
				{
					if (!m_set_LoadedSpawn.Contains(levelInfo.LevelName))
						continue;

					m_set_LoadedSpawn.Remove(levelInfo.LevelName);
					UGameplayStatics::UnloadStreamLevel(m_pCrrWorld, *(levelInfo.LevelName), actionInfo, false);
				}
				break;
			default:
				continue;
		}

		return;
	}
	
	m_bIsLoadingLevel = false;

	// 완료 콜백
	if (m_callback_LoadComplete)
	{
		auto callback = m_callback_LoadComplete;
		m_callback_LoadComplete = nullptr;
		callback();
	}
}

void WorldManager::CheckAndLoadLand(const AActor* const& target)
{
	/* 지역 체크 */
	// 타겟 유효성 체크 및 레벨 로드 진행중 체크
	if (!target || m_bIsLoadingLevel)
		return;
	
	FVector vStart = target->GetActorLocation();
	FVector vEnd = vStart - target->GetActorUpVector() * 1000000;
	
	FCollisionQueryParams	params(NAME_None, false, target);
	// params.bReturnPhysicalMaterial = true;

	FHitResult hitResult;
	if (GetWorld()->LineTraceSingleByObjectType(hitResult, vStart, vEnd, ECC_TO_BITFIELD(ECollisionChannel::ECC_GameTraceChannel6), params))
	{
		auto pLandActor = hitResult.GetActor();
		if (!m_pCrrLandActor)
		{
			m_pCrrLandActor = pLandActor;
#if WITH_EDITOR
			LOG_WARNING(TEXT("Current Land : %s"), *pLandActor->GetName())
#endif
		}
		else if (m_pCrrLandActor != pLandActor)
		{
			// 현재 랜드랑 다르면 레벨 로드
			m_pCrrLandActor = pLandActor;
			Managers::World->LoadLandAsync(pLandActor->GetName());
#if WITH_EDITOR
			LOG_WARNING(TEXT("Current Land : %s"), *pLandActor->GetName())
#endif
		}
	}
}

// ULoadingBase->OnEndAnim_Open에서 호출됨
void WorldManager::OnEnd_LoadingAnim_Open()
{
	if (m_pCrrGameMode)
		m_pCrrGameMode->OnEndGame();

	// 매니저들에게 레벨이 바뀌기 직전임을 알림
	Managers::OnPrevChangeWorld();
	
	// 레벨을 연다
	UGameplayStatics::OpenLevel(GetWorld(), *FString::Printf(TEXT("Level_%s"), *UEnumToString(m_WorldId)));
}

void WorldManager::OnStart_GameModeInit(AClientGameModeBase* pGameMode)
{
	m_pCrrGameMode = pGameMode;
	m_pCrrWorld = pGameMode->GetWorld();

	Managers::OnPostChangeWorld();
}

// ULoadingBase->OnEndAnim_Close에서 호출됨
void WorldManager::OnEnd_GameModeInit()
{
	if (m_pLoadingPage)
		m_pLoadingPage->Close();
	else
		OnEnd_LoadingAnim_Close();
}

void WorldManager::OnEnd_LoadingAnim_Close()
{
	Managers::UI->CloseLoading(m_pLoadingPage);
	m_pLoadingPage = nullptr;
	m_bIsLoading = false;

	if (m_pCrrGameMode)
		m_pCrrGameMode->OnStartGame();
}