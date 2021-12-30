// Fill out your copyright notice in the Description page of Project Settings.


#include "UIBP_Logo.h"

#include "Components/Border.h"
#include "MediaPlayer.h" // Build.cs -> "MediaAssets"
#include "MediaSound.h"

UUIBP_Logo::UUIBP_Logo(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	bIsFocusable = true;
}

void UUIBP_Logo::NativeConstruct()
{
	Super::NativeConstruct();

	// 스킵 보더 초기화
	m_pBorder_Skip = Cast<UBorder>(GetWidgetFromName((TEXT("Border_Skip"))));
	m_pBorder_Skip->OnMouseButtonDownEvent.BindDynamic(this, &UUIBP_Logo::OnClick_Skip);

	// 사운드 플레이용 액터 생성
	m_pMediaSoundActor = GetWorld()->SpawnActor<AMediaSound>();
	m_pMediaSoundActor->SetMediaPlayer(m_pMediaPlayer);

	// 재생
	m_pMediaPlayer->OpenSource(m_pMediaSource);
	m_pMediaPlayer->OnEndReached.AddDynamic(this, &UUIBP_Logo::OnEnd_MediaPlayer);
	m_pMediaPlayer->Play();

	// 마우스 활성화
	auto pPlayerCtrl = GetWorld()->GetFirstPlayerController();
	pPlayerCtrl->SetInputMode(FInputModeUIOnly());
	pPlayerCtrl->SetShowMouseCursor(true);
}

FEventReply UUIBP_Logo::OnClick_Skip(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	OnEnd_MediaPlayer();
	return FEventReply(true);
}

void UUIBP_Logo::OnEnd_MediaPlayer()
{
	if (IsValid(m_pMediaSoundActor))
		m_pMediaSoundActor->Destroy();
	
	m_pMediaPlayer->OnEndReached.RemoveDynamic(this, &UUIBP_Logo::OnEnd_MediaPlayer);
	this->RemoveFromParent();
	this->ConditionalBeginDestroy();
}