// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnSystem.h"

#include "SpawnPoint.h"
#include "SpawnTrigger.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "SpawnCharacter.h"
#include "Client/Framework/GameCharacter/ActionControl/ActionController.h"
#include "Client/Framework/GameCharacter/AnimControl/AnimController.h"
#include "Client/Framework/GameCharacter/BrainControl/BrainController.h"
#include "Client/Framework/Managers/Managers.h"
#include "Client/GameContents/GameDatas/GameCharacterData.h"

CSpawnCharacterContainer::~CSpawnCharacterContainer()
{
	// 스폰 캐릭터 전부 삭제
	auto node_Cha = Llist_Inactivate.GetHead();
	while (node_Cha)
	{
		auto pSpawnCha = node_Cha->GetValue();

		node_Cha->RemoveSelf();
		node_Cha = Llist_Inactivate.GetHead();
		
		if (IsValid(pSpawnCha))
			pSpawnCha->Destroy();
	}
	
	Llist_Inactivate.Empty(false);
}

ASpawnCharacter* CSpawnCharacterContainer::PopGameCharacter()
{
	auto node_Cha = Llist_Inactivate.GetHead();
	node_Cha->RemoveSelf();
	return node_Cha->GetValue();
}

void CSpawnCharacterContainer::PushGameCharacter(ASpawnCharacter* const& pSpawnCha)
{
	auto node_Cha = pSpawnCha->GetSpawnNode();
	Llist_Inactivate.AddHead(pSpawnCha);
}

// Sets default values
ASpawnSystem::ASpawnSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Idx_CrrSpawnInfo = -1;
}

void ASpawnSystem::BeginPlay()
{
	Super::BeginPlay();
}

void ASpawnSystem::BeginDestroy()
{
	Super::BeginDestroy();
	
	// 컨테이너 모두 해제
	for (auto& pair : m_map_SpawnCharacterContainer)
		delete pair.Value;

	m_map_SpawnCharacterContainer.Empty();
}

void ASpawnSystem::Tick(float DeltaSeconds)
{
	// 틱은 m_State == ESpawnSystemState::Spawn 일때만 들어온다.

	Super::Tick(DeltaSeconds);

	OnTickSpawn(DeltaSeconds);
}

void ASpawnSystem::Init()
{
	TMap<int, int> map_MaxGameCharCount;
	
	for(int i = 0 ; i < m_SpawnInfos.Num(); ++i)
	{
		auto& spawnInfo = m_SpawnInfos[0];

		// Trigger 초기화 (Collider Off)
		if (spawnInfo.Trigger)
			spawnInfo.Trigger->Init(this);

		// LvSequence 초기화
		if (spawnInfo.LvSuquence_Start)
		{
			auto pPlayer = spawnInfo.LvSuquence_Start->GetSequencePlayer();
			pPlayer->Stop();
			pPlayer->OnStop.AddDynamic(this, &ASpawnSystem::OnEndCutscene);
			pPlayer->OnFinished.AddDynamic(this, &ASpawnSystem::OnEndCutscene);
		}

		// 현재 스폰포인트의 등장 캐릭터 갯수 수집
		TMap<int, int> map_GameChaCount;

		// SpawnPoint 초기화
		for (auto& spawnPointInfo : spawnInfo.SpawnPointInfos)
		{
			if (map_GameChaCount.Contains(spawnPointInfo.GameCharacterDataId))
				++(map_GameChaCount[spawnPointInfo.GameCharacterDataId]);
			else
				// Todo :: 만약 이전 SpawnInfo가 전부 처치 조건이 아니면 남는 갯수 + 1로 시작
				map_GameChaCount.Add(spawnPointInfo.GameCharacterDataId, 1);
		}

		// Spawn할 GameCha MaxCount만 수집
		for (auto& pair : map_GameChaCount)
		{
			if (map_MaxGameCharCount.Contains(pair.Key))
			{
				if (map_MaxGameCharCount[pair.Key] < pair.Value)
					map_MaxGameCharCount[pair.Key] = pair.Value;
			}
			else
			{
				map_MaxGameCharCount.Add(pair.Key, pair.Value);
			}
		}

		// SpawnPoint를 카피 후 Delay순으로 정렬
		spawnInfo.SpawnPointInfosSorted = spawnInfo.SpawnPointInfos;
		spawnInfo.SpawnPointInfosSorted.Sort([](const FSpawnPointInfo& x, const FSpawnPointInfo& y)
		{
			return x.SpawnDelayTime < y.SpawnDelayTime;
		});
	}
	
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Character Pooling
	for (auto& pair : map_MaxGameCharCount)
	{
		auto pGameCharacterData = Managers::GameData->GetData<CCharacterData>(pair.Key);
		if (!pGameCharacterData)
			continue;

		auto& chaContainer = m_map_SpawnCharacterContainer.Add(pGameCharacterData->ID, new CSpawnCharacterContainer());;

		for (int i = 0 ; i < pair.Value ; ++i)
		{
			auto pSpawnCha = Managers::World->GetWorld()->SpawnActor<ASpawnCharacter>(
				FVector(-500.f, 0.f, 100.f),
				FRotator::ZeroRotator,
				param);

			pSpawnCha->Init(pGameCharacterData);
#if WITH_EDITOR
			pSpawnCha->SetFolderPath(*FString::Printf(TEXT("SpawnSystem/ActorPool/GameCharacterData_%d"), pGameCharacterData->ID));
#endif
			pSpawnCha->SetActive(false);

			// 컨테이너에 저장
			chaContainer->PushGameCharacter(pSpawnCha);
		}
	}
}

void ASpawnSystem::Active(const int& idx)
{
	SetActorTickEnabled(false);
	m_State = ESpawnSystemState::None;
	if (m_Idx_CrrSpawnInfo == idx)
		return;

	// 기존 재생중인 퀘스트 종료
	if (0 <= m_Idx_CrrSpawnInfo && m_Idx_CrrSpawnInfo < m_SpawnInfos.Num())
	{
		auto& crrSpawnInfo = m_SpawnInfos[m_Idx_CrrSpawnInfo];
		if (crrSpawnInfo.Trigger)
			crrSpawnInfo.Trigger->SetActorEnableCollision(false);

		// Todo :: MonsterKill?
	}

	m_Idx_CrrSpawnInfo = idx;
	// 다음 재생 목록 On
	if (0 <= m_Idx_CrrSpawnInfo && m_Idx_CrrSpawnInfo < m_SpawnInfos.Num())
	{
		auto& crrSpawnInfo = m_SpawnInfos[m_Idx_CrrSpawnInfo];

		// 트리거가 없다면 즉시 트리거 발동
		if (crrSpawnInfo.Trigger)
		{
			m_State = ESpawnSystemState::WaitForTrigger;
			crrSpawnInfo.Trigger->SetActorEnableCollision(true);
		}
		else
		{
			OnTrigger();
		}
	}
}

void ASpawnSystem::OnTrigger()
{
	// 트리거 Off
	auto& crrSpawnInfo = m_SpawnInfos[m_Idx_CrrSpawnInfo];

	if (crrSpawnInfo.Trigger)
		crrSpawnInfo.Trigger->SetActorEnableCollision(false);

	PlayCutscene();
}

void ASpawnSystem::PlayCutscene()
{
	auto& crrSpawnInfo = m_SpawnInfos[m_Idx_CrrSpawnInfo];

	// 컷씬 유효성 체크
	if (!(crrSpawnInfo.LvSuquence_Start && crrSpawnInfo.LvSuquence_Start->GetSequence()))
	{
		// 컷씬이 유효하지 않다면 바로 Spawn 시작
		StartSpawn();
		return;
	}

	m_State = ESpawnSystemState::Cutscene;

	// 언리얼 버그 회피용 코드
	TSet<FGuid> set_GUID;
	
	auto allBindings = crrSpawnInfo.LvSuquence_Start->GetSequence()->GetMovieScene()->GetBindings();
	for (int i = 0 ; i < allBindings.Num() ; ++i)
	{
		auto& binding = allBindings[i];
		set_GUID.Add(binding.GetObjectGuid());
	}
	
	// Binding PlayerCharacter
	// Todo :: 캐릭터 바리에이션
	auto bindings_PlayerCha = crrSpawnInfo.LvSuquence_Start->FindNamedBindings("PlayerCharacter");

	// 바인딩 찌꺼기 제거
	for (int i = bindings_PlayerCha.Num() - 1 ; i >= 0; --i)
	{
		LOG_WARNING(TEXT("Check GUID :: %s"), *bindings_PlayerCha[i].GetGuid().ToString());

		if (set_GUID.Contains(bindings_PlayerCha[i].GetGuid()))
		{
			LOG_WARNING(TEXT("GUID is Not Valid"));
			continue;;
		}

		LOG_WARNING(TEXT("GUID is Valid"));
		bindings_PlayerCha.RemoveAt(i);
	}
	
	for (int i = 0 ; i < bindings_PlayerCha.Num(); ++i)
	{
		// Todo :: 일단 무식하게 가져와보자
		auto pUserCtrl = Cast<AUserInputController>(GetWorld()->GetFirstPlayerController());
		if (pUserCtrl)
		{
			auto pPlayerCha = pUserCtrl->GetPlayerCharacter();
			if (pPlayerCha)
			{
				// Todo :: Pause Debuff 등등
				pPlayerCha->GetActionCtrl()->StopAction();
				crrSpawnInfo.LvSuquence_Start->SetBinding(bindings_PlayerCha[i], {pPlayerCha});
				pPlayerCha->GetAnimCtrl()->Stop(0.1f, EAnimBlendOption::None);
			}
		}

		break;
	}

	// Binding SpawnedCharacter
	auto bindings_SpawnedCha = crrSpawnInfo.LvSuquence_Start->FindNamedBindings("SpawnedCharacter");

	// 바인딩 찌꺼기 제거
	for (int i = bindings_SpawnedCha.Num() - 1 ; i >= 0; --i)
	{
		LOG_WARNING(TEXT("Check GUID :: %s"), *bindings_SpawnedCha[i].GetGuid().ToString());

		if (set_GUID.Contains(bindings_SpawnedCha[i].GetGuid()))
		{
			LOG_WARNING(TEXT("GUID is Not Valid"));
			continue;;
		}

		LOG_WARNING(TEXT("GUID is Valid"));
		bindings_SpawnedCha.RemoveAt(i);
	}

	auto spawnPointCount = FMath::Min(bindings_SpawnedCha.Num(), crrSpawnInfo.SpawnPointInfos.Num());
	for (int i = 0 ; i < spawnPointCount; ++i)
	{
		auto spawnPointInfo = crrSpawnInfo.SpawnPointInfos[i];

		// 스폰 시킨다.
		auto pSpawnCha = SpawnCharacter(spawnPointInfo, false);
		if (!pSpawnCha)
			continue;

		// 바인딩 한다.
		crrSpawnInfo.LvSuquence_Start->SetBinding(bindings_SpawnedCha[i], {pSpawnCha});
	}

	m_Idx_CrrSpawnPointInfo = spawnPointCount;

	// Cutscene이 종료되면 OnStartCutsceneEnd가 EndCallback으로 호출
	auto pPlayer = crrSpawnInfo.LvSuquence_Start->GetSequencePlayer();
	pPlayer->Play();
}

void ASpawnSystem::OnEndCutscene()
{
	auto& crrSpawnInfo = m_SpawnInfos[m_Idx_CrrSpawnInfo];
	
	auto pSequence = crrSpawnInfo.LvSuquence_Start->GetSequence();

	// Play Action_Idle :: Player
	auto binding_PlayerCha = pSequence->FindBindingByTag("PlayerCharacter");
	if (binding_PlayerCha.IsValid())
	{
		// Todo :: 일단 무식하게 가져와보자
		auto pUserCtrl = Cast<AUserInputController>(GetWorld()->GetFirstPlayerController());
		if (pUserCtrl)
		{
			auto pPlayerCha = pUserCtrl->GetPlayerCharacter();
			if (pPlayerCha)
				pPlayerCha->GetActionCtrl()->PlayAction("ActionData_Idle");
		}
	}

	// Play Action_Idle :: Spawned
	auto node_SpawnedCha = m_llist_Alive_SpawnedCharacter.GetHead();
	while (node_SpawnedCha)
	{
		auto pSpawnedCha = node_SpawnedCha->GetValue();
		node_SpawnedCha = node_SpawnedCha->GetNextNode();
		pSpawnedCha->GetBrainCtrl()->StartAI();
	}
}

void ASpawnSystem::StartSpawn()
{
	// 몬스터 스폰
	auto& crrSpawnInfo = m_SpawnInfos[m_Idx_CrrSpawnInfo];

	if (crrSpawnInfo.SpawnPointInfos.Num() == 0)
	{
		OnEndBattle();
		return;
	}

	m_State = ESpawnSystemState::Spawn;
	m_fCrrSpawnPointInfoElapsedTime = 0.f;
	SetActorTickEnabled(true);
}

void ASpawnSystem::OnTickSpawn(const float& DeltaSeconds)
{
	if (m_State != ESpawnSystemState::Spawn)
		return;
	
	auto& crrSpawnInfo = m_SpawnInfos[m_Idx_CrrSpawnInfo];

	m_fCrrSpawnPointInfoElapsedTime += DeltaSeconds;
	while (m_Idx_CrrSpawnPointInfo < crrSpawnInfo.SpawnPointInfosSorted.Num() )
	{
		auto& spawnPointInfo = crrSpawnInfo.SpawnPointInfosSorted[m_Idx_CrrSpawnPointInfo];
		
		// 아직 스폰 시간이 안됬다면
		if (spawnPointInfo.SpawnDelayTime > m_fCrrSpawnPointInfoElapsedTime)
			return;

		// 스폰 시킨다.
		SpawnCharacter(spawnPointInfo, true);
		++m_Idx_CrrSpawnPointInfo;
	}

	// 여기까지 왔으면 모두다 스폰 된것 Tick == false
	OnEndSpawn();
}

void ASpawnSystem::OnEndSpawn()
{
	SetActorTickEnabled(false);
	StartBattle();
}

void ASpawnSystem::StartBattle()
{
	m_State = ESpawnSystemState::WaitForBattle;
}

void ASpawnSystem::OnEndBattle()
{
	// 다음 스폰 정보를 대기시킨다.
	Active(++m_Idx_CrrSpawnInfo);
}

ASpawnCharacter* ASpawnSystem::SpawnCharacter(const FSpawnPointInfo& spawnPointInfo, const bool& bStartAIImmediately)
{
	// 스폰 시킨다.
	if (m_map_SpawnCharacterContainer.Contains(spawnPointInfo.GameCharacterDataId))
	{
		auto& chaContainer = m_map_SpawnCharacterContainer[spawnPointInfo.GameCharacterDataId];
		auto pSpawnCha = chaContainer->PopGameCharacter();

		pSpawnCha->SetNavLocation(spawnPointInfo.Point->GetActorLocation());
		pSpawnCha->SetActorRotation(spawnPointInfo.Point->GetActorRotation());
#if WITH_EDITOR
		pSpawnCha->SetFolderPath(*FString::Printf(TEXT("SpawnSystem/Actor_Spawned_%d"), m_Idx_CrrSpawnInfo));
#endif

		auto& pBrainCtrl = pSpawnCha->GetBrainCtrl();
		
		// 패트롤 정보 세팅
		switch(spawnPointInfo.PatrolType)
		{
			case EPatrolTypes::None:
				{
					pBrainCtrl->ClearSpawnInfo();
					pBrainCtrl->SetDefaultAIBehavior(EAIDefaultBehaviorType::None);
				}
				break;
			case EPatrolTypes::Loop:
				{
					if (spawnPointInfo.Point->GetSplineComp())
					{
						pBrainCtrl->SetSpawnInfo(
							spawnPointInfo.Point->GetActorLocation(),
							spawnPointInfo.Point->GetActorRotation().Quaternion(),
							spawnPointInfo.Point->GetSplineComp());
						
						pBrainCtrl->SetDefaultAIBehavior(EAIDefaultBehaviorType::PatrolLoop);
					}
					else
					{
						// 경로가 없다면 걍 None으로
						pBrainCtrl->ClearSpawnInfo();
						pBrainCtrl->SetDefaultAIBehavior(EAIDefaultBehaviorType::None);
					}
				}
				break;
			case EPatrolTypes::PingPong:
				{
					if (spawnPointInfo.Point->GetSplineComp())
					{
						pBrainCtrl->SetSpawnInfo(
							spawnPointInfo.Point->GetActorLocation(),
							spawnPointInfo.Point->GetActorRotation().Quaternion(),
							spawnPointInfo.Point->GetSplineComp());
						
						pBrainCtrl->SetDefaultAIBehavior(EAIDefaultBehaviorType::PatrolPingPong);
					}
					else
					{
						// 경로가 없다면 걍 None으로
						pBrainCtrl->ClearSpawnInfo();
						pBrainCtrl->SetDefaultAIBehavior(EAIDefaultBehaviorType::None);
					}
				}
				break;
		}

		pSpawnCha->SetActive(true);
		pSpawnCha->ChangeTeam(1);

		if (bStartAIImmediately)
			pBrainCtrl->StartAI();
		else
			pSpawnCha->GetBrainCtrl()->StopAI();

		m_llist_Alive_SpawnedCharacter.AddTail(pSpawnCha->GetSpawnNode());

		return pSpawnCha;
	}

	return nullptr;
}