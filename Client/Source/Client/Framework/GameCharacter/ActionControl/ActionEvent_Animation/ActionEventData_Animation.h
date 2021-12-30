// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ActionEvent/ActionEventDataBase.h"
#include "../../AnimControl/AnimInst.h"
#include "ActionEventData_Animation.generated.h"

USTRUCT()
struct CLIENT_API FActionEventData_Animation : public FActionEventDataBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FString m_AnimName;
	UPROPERTY(EditAnywhere)
	float m_fFadeTime;
	UPROPERTY(EditAnywhere)
	float m_fPlayRate;
	UPROPERTY(EditAnywhere)
	bool m_bResetIfPlaying;
	UPROPERTY(EditAnywhere)
	EAnimBlendOption m_BlendOption;

public:
	FActionEventData_Animation();
	virtual ~FActionEventData_Animation() override;

	virtual CreateRuntimeResult CreateRuntime(AGameCharacter* owner, UActionData* pActionData) override;
	virtual EActionEventTypes GetActionEventType() const override;

#if WITH_EDITOR
	virtual TSharedRef<SWidget> GetEditorContentsWidget(UActionData* pActionData) override;
#endif
};