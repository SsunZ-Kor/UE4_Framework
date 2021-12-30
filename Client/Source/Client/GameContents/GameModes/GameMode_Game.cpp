// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_Game.h"
// #include "../../GameContents/GameDatas/GameDataStructs.h"
#include "../../Framework/GameCharacter/GameCharacter.h"
#include "Client/Framework/GameCharacter/ActionControl/ActionController.h"
#include "Client/Framework/Camera/GameCamera.h"
#include "Client/Framework/GameCharacter/BrainControl/BrainController.h"
#include "Client/Framework/Managers/Managers.h"
#include "Client/Framework/Managers/UIManager/UserInputController.h"
#include "Client/Framework/Managers/UserDataManager/UserCharacterData.h"
#include "Client/GameContents/SpawnSystem/SpawnSystem.h"

class UWindow_GameMain;

AGameMode_Game::AGameMode_Game()
	: AClientGameModeBase()
{
}

void AGameMode_Game::OnInit()
{
	// 모든 UI 제거
	Managers::UI->ClearWindow(false);

	// 랜드 & 스폰 로드
	Managers::World->LoadLandAsync("Level_Land_0006");
	Managers::World->LoadSpawnAsync("Level_Spawn_0000");
	Managers::World->SetLevelAsyncEndCallback([this]() {OnInit_AfterLevelLoaded();});

	// OnInit_AfterLevelLoaded 에서 호출로 변경
	// Super::OnInit();
}

void AGameMode_Game::OnInit_AfterLevelLoaded()
{
	// 임시 유저 데이터 설정 :: 인벤토리
	Managers::User->CharacterData->AddItemInfo(0, 1, -1);
	Managers::User->CharacterData->AddItemInfo(1, 2, 0);
	Managers::User->CharacterData->AddItemInfo(2, 3, 1);
	Managers::User->CharacterData->AddItemInfo(3, 4, 2);
	Managers::User->CharacterData->AddItemInfo(4, 5, 3);
	Managers::User->CharacterData->AddItemInfo(5, 1, 4);
	Managers::User->CharacterData->AddItemInfo(6, 2, 5);
	Managers::User->CharacterData->AddItemInfo(7, 3, 6);
	Managers::User->CharacterData->AddItemInfo(8, 4, 7);
	Managers::User->CharacterData->AddItemInfo(9, 5, 8);
	Managers::User->CharacterData->AddItemInfo(10, 1, 9);
	Managers::User->CharacterData->AddItemInfo(11, 2, 10);
	Managers::User->CharacterData->AddItemInfo(12, 3, 11);
	Managers::User->CharacterData->AddItemInfo(13, 4, 12);
	Managers::User->CharacterData->AddItemInfo(14, 5, 13);

	// 임시 캐릭터 스폰 :: 데이터 로드
	const auto gameCharacterData = Managers::GameData->GetData<CCharacterData>(1);

	// 진영 설정, 최대 6개 팀
	//TArray<GameCharacterTeamInfo*> teamInfos = {
	//	new GameCharacterTeamInfo(0, {0, 1, 2}, {3, 4, 5}),
	//	new GameCharacterTeamInfo(1, {0, 1, 2}, {3, 4, 5}),
	//	new GameCharacterTeamInfo(2, {0, 1, 2}, {3, 4, 5}),
	//	new GameCharacterTeamInfo(3, {3, 4, 5}, {0, 1, 2}),
	//	new GameCharacterTeamInfo(4, {3, 4, 5}, {0, 1, 2}),
	//	new GameCharacterTeamInfo(5, {3, 4, 5}, {0, 1, 2})
	//};
	
	TArray<GameCharacterTeamInfo*> teamInfos = {
		new GameCharacterTeamInfo(0, {0}, {1}),
		new GameCharacterTeamInfo(1, {1}, {0}),
	};

	AGameCharacter::AllyInfo = new GameCharacterAllyInfo(teamInfos, 0);

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// 임시 캐릭터 스폰 :: 플레이어
	m_pPlayerCha = GetWorld()->SpawnActor<AGameCharacter>(
		FVector(500.f, 0.f, 100.f),
		FRotator(0.f, 180.f, 0.f),
		param);

	m_pPlayerCha->Init(gameCharacterData);
	m_pPlayerCha->ChangeTeam(0);
	m_pPlayerCha->GetActionCtrl()->PlayAction("ActionData_Idle");

	// Camera
	auto gameCam = GetWorld()->SpawnActor<AGameCamera>(
		FVector(500.f, 0.f, 100.f),
		FRotator(0.f, 180.f, 0.f),
		param);

	gameCam->SetTarget(m_pPlayerCha);

	// UserInput에다 생성된 캐릭터 등록
	auto pInputCtrl = Managers::UI->GetInputCtrl();
	if (pInputCtrl)
	{
		pInputCtrl->Possess(m_pPlayerCha);
		pInputCtrl->SetCamera(gameCam);
	}
	
	// UI Open
	Managers::UI->OpenWindow<UWindow_GameMain>();

	// Test :: Spawn System
	TArray<AActor*> SpawnSystems;
	UGameplayStatics::GetAllActorsOfClass(Managers::World->GetWorld(), ASpawnSystem::StaticClass(), SpawnSystems);
	for (auto& pActor : SpawnSystems)
	{
		auto pSpawnSystem = Cast<ASpawnSystem>(pActor);
		pSpawnSystem->Init();
		pSpawnSystem->Active(0);
	}

	Super::OnInit();
}

void AGameMode_Game::OnStartGame()
{
	Super::OnStartGame();
}

AGameCharacter* const& AGameMode_Game::GetPlayerCharacter() const
{
	return m_pPlayerCha;
}
