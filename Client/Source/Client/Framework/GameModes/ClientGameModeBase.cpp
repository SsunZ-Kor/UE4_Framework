// Copyright Epic Games, Inc. All Rights Reserved.


#include "ClientGameModeBase.h"
#include "../Managers/Managers.h"

AClientGameModeBase::AClientGameModeBase()
{
	bUseSeamlessTravel = true;
	
	DefaultPawnClass = nullptr;
	HUDClass = nullptr;
	PlayerControllerClass = AUserInputController::StaticClass();
	GameStateClass = nullptr;
	//PlayerStateClass = nullptr;
	SpectatorClass = nullptr;

	PrimaryActorTick.bCanEverTick = true;
}

void AClientGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (!Managers::IsInit())
		Managers::Init(GetWorld());

	// 로드를 시작할 것임을 알림
	Managers::World->OnStart_GameModeInit(this);
	OnInit();
}

void AClientGameModeBase::GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList)
{
	Super::GetSeamlessTravelActorList(bToTransition, ActorList);
}

void AClientGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	Managers::OnGameModeTick(DeltaSeconds);
}

// 상속 후 리턴 직전에 꼭 호출해야함
void AClientGameModeBase::OnInit()
{
	// 로드가 끝났음을 알림
	Managers::World->OnEnd_GameModeInit();
}

void AClientGameModeBase::OnStartGame()
{
	// 컨트롤러 작동 가능하도록 변경, 만약 딜레이가 필요하다면 상속 후 적당한 타이밍에 열어줄 것
	Managers::UI->GetInputCtrl()->SetActorTickEnabled(true);
}

void AClientGameModeBase::OnEndGame()
{
	
}