// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Framework/GameModes/ClientGameModeBase.h"
#include "GameMode_Game.generated.h"

class AGameCharacter;

UCLASS()
class CLIENT_API AGameMode_Game : public AClientGameModeBase
{
	GENERATED_BODY()

	UPROPERTY()
	AGameCharacter* m_pPlayerCha;

public:
	AGameMode_Game();

	virtual void OnInit() override;
	void OnInit_AfterLevelLoaded();
	virtual void OnStartGame() override;

public:	
	virtual AGameCharacter* const& GetPlayerCharacter() const;
};