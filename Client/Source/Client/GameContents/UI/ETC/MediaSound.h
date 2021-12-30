// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Client/Framework/ClientGameBase.h"
#include "GameFramework/Actor.h"
#include "MediaSound.generated.h"

class UMediaSoundComponent;
class UMediaPlayer;

UCLASS()
class CLIENT_API AMediaSound : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess  = "true"))
	UMediaSoundComponent* m_pMediaSound;
	
public:	
	// Sets default values for this actor's properties
	AMediaSound();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetMediaPlayer(UMediaPlayer* pMediaPlayer);
};
