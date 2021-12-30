// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ActionEvent/ActionEventDurationDataBase.h"
#include "ActionEventData_MoveTargetE.generated.h"

USTRUCT()
struct CLIENT_API FActionEventData_MoveTargetE : public FActionEventDurationDataBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float m_fMoveSpdPerSec;

	UPROPERTY(EditAnywhere)
	FString OnReachTargetPlay;
	UPROPERTY(EditAnywhere)
	float m_fOnReachDist;
	
public:
	FActionEventData_MoveTargetE();
	virtual ~FActionEventData_MoveTargetE() override;

	virtual CreateRuntimeResult CreateRuntime(AGameCharacter* owner, UActionData* pActionData) override;
	virtual EActionEventTypes GetActionEventType() const override;
	
#if WITH_EDITOR
	virtual TSharedRef<SWidget> GetEditorContentsWidget(UActionData* pActionData) override;
#endif
};