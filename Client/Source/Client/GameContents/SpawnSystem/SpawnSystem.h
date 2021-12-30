// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Client/Framework/ClientGameBase.h"
#include "Client/Framework/GameCharacter/GameCharacter_Define.h"
#include "GameFramework/Actor.h"
#include "SpawnSystem.generated.h"

class ASpawnPoint;
class ASpawnTrigger;
class ASpawnCharacter;
class ALevelSequenceActor;

enum class ESpawnSystemState : uint8
{
	None,
	WaitForTrigger,
	Cutscene,
	Spawn,
	WaitForBattle,
};

UENUM()
enum class EPatrolTypes : uint8
{
	None,
	Loop,
	PingPong,
};

USTRUCT(BlueprintType)
struct FSpawnPointInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ASpawnPoint* Point = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int GameCharacterDataId = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float SpawnDelayTime = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPatrolTypes PatrolType = EPatrolTypes::None;
};

USTRUCT(BlueprintType)
struct FSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ASpawnTrigger* Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ALevelSequenceActor* LvSuquence_Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FSpawnPointInfo> SpawnPointInfos;

	// elay로 정렬, 원본을 유지하기 위해 Copy;
	TArray<FSpawnPointInfo> SpawnPointInfosSorted;
};

class CSpawnCharacterContainer
{
	TDoubleLinkedListEx<ASpawnCharacter*> Llist_Inactivate;

public:	
	~CSpawnCharacterContainer();
	ASpawnCharacter* PopGameCharacter();
	void PushGameCharacter(ASpawnCharacter* const& pSpawnCha);
};

UCLASS()
class CLIENT_API ASpawnSystem : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FSpawnInfo> m_SpawnInfos;

	TMap<int, CSpawnCharacterContainer*> m_map_SpawnCharacterContainer;
	TDoubleLinkedListEx<ASpawnCharacter*> m_llist_Alive_SpawnedCharacter;

	// 현재 Active된 SpawnInfo Index
	int m_Idx_CrrSpawnInfo;

	// SpawnInfo의 State
	ESpawnSystemState m_State;

	// 딜레이 대기중인 SpawnPointInfo의 Index;
	int m_Idx_CrrSpawnPointInfo;
	// Spawn이 시작되고 경과시간
	float m_fCrrSpawnPointInfoElapsedTime;

public:	
	// Sets default values for this actor's properties
	ASpawnSystem();

protected:	
	virtual void BeginPlay() override;
public:
	virtual void BeginDestroy() override;

public:	
	virtual void Tick(float DeltaSeconds) override;

public:
	void Init();

	// 0. 스폰 활성화
	void Active(const int& idx);
	// 1. 트리거를 밟음
	void OnTrigger();
	// 2. 컷신 플레이
	void PlayCutscene();
	// 3. 컷진 종료 콜백
	UFUNCTION()
	void OnEndCutscene();
	// 4. Spawn 시작
	void StartSpawn();
	// 5. Spawn 진행
	void OnTickSpawn(const float& DeltaSeconds);
	// 5. Spawn 종료 콜백
	void OnEndSpawn();
	// 6. 전투 시작(정확히는 현재 스폰 클리어 조건 체크 시작)
	void StartBattle();
	// 7. 전투 종료
	void OnEndBattle();

protected:
	ASpawnCharacter* SpawnCharacter(const FSpawnPointInfo& spawnInfo, const bool& bStartAIImmediately);
};