// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaSound.h"

#include "MediaSoundComponent.h"
#include "MediaPlayer.h"

// Sets default values
AMediaSound::AMediaSound()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pMediaSound = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("UMediaSoundComponent"));
	SetRootComponent(m_pMediaSound);
}

// Called when the game starts or when spawned
void AMediaSound::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMediaSound::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMediaSound::SetMediaPlayer(UMediaPlayer* pMediaPlayer)
{
	m_pMediaSound->SetMediaPlayer(pMediaPlayer);
}