// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Client/Framework/Managers/UIManager/UIBase/LoadingBase.h"
#include "Loading_ScreenOut.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API ULoading_ScreenOut : public ULoadingBase
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UTexture2D* pTex_Screen;

public:
	virtual void Open() override;
	virtual void Close() override;
};
