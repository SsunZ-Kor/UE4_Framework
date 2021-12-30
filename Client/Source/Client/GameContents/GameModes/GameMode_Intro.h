// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Client/Framework/GameModes/ClientGameModeBase.h"
#include "Client/Framework/Managers/AssetManager/ClientAssetManager.h"
#include "GameMode_Intro.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API AGameMode_Intro : public AClientGameModeBase
{
	GENERATED_BODY()

public:
	AGameMode_Intro();

	virtual void OnInit() override;
};