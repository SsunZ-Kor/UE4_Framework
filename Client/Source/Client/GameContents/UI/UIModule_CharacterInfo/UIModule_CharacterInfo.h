// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Client/Framework/Managers/UIManager/UIBase/UIModuleBase.h"
#include "UIModule_CharacterInfo.generated.h"

class AGameCharacter;
UCLASS()
class CLIENT_API UUIModule_CharacterInfo : public UUIModuleBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIModule CharacterInfo", meta=(AllowPrivateAccess="true", DisplayName="TexTarget"))
	UTextureRenderTarget2D* m_TexTarget;

	UPROPERTY()
	ASceneCapture2D* m_pSceneCapture;

public:
	void Init(AGameCharacter* pCharacter);

virtual void OnUIModuleClosed() override;

private:
	ASceneCapture2D* GetSceneCapture();
	void ReleaseSceneCapture();
};