// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Client/Framework/ClientGameBase.h"
#include "Blueprint/UserWidget.h"
#include "UIBP_Logo.generated.h"

class UBorder;
class UMediaPlayer;
class UMediaSource;
class AMediaSound;

UCLASS()
class CLIENT_API UUIBP_Logo : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBorder* m_pBorder_Skip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UMediaPlayer* m_pMediaPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UMediaSource* m_pMediaSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AMediaSound* m_pMediaSoundActor;

public:
	UUIBP_Logo(const FObjectInitializer& ObjectInitializer);
protected:	
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	FEventReply OnClick_Skip(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
	UFUNCTION(BlueprintCallable)
	void OnEnd_MediaPlayer();
};