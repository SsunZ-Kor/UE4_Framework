// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Client/Framework/GameModes/ClientGameModeBase.h"
#include "GameMode_DataLog.generated.h"

UCLASS()
class CLIENT_API AGameMode_DataLog : public AClientGameModeBase
{
	GENERATED_BODY()
public:	
	AGameMode_DataLog();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void BeginPlay();

	// 상속 후 리턴 직전에 꼭 호출해야함
	virtual void OnInit();
	virtual void OnStartGame();
	virtual void OnEndGame();
	
	private:
	void PrintFPaths();
	void TestCode();

	void TestCodeManagers();
	void TestCodeDataManager();
	void TestCodeLocalizationManager();
};
