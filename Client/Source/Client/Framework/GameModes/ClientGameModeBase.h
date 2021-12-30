// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "../ClientGameBase.h"
#include "GameFramework/GameModeBase.h"
#include "ClientGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API AClientGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AClientGameModeBase();
	
	virtual void BeginPlay() override;
	virtual void GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList) override;
	
public:
	/* LoadingPage On Start
	 * LoadingPage On End
	 * 
	 * prevGameMode->OnEndGame
	 * currGameMode->OnInit
	 * 
	 * LoadingPage Off Start
	 * LoadingPage Off End
	 *
	 * currGameMode->OnStartGame
	 */

	virtual void Tick(float DeltaSeconds) override;

	// 상속 후 리턴 직전에 꼭 호출해야함
	virtual void OnInit();
	virtual void OnStartGame();
	virtual void OnEndGame();
};