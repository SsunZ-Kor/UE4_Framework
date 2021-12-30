// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ActionEvent/ActionEventDurationDataBase.h"
#include "ActionEventData_Rotate.generated.h"

UENUM(BlueprintType)
enum class ERotateTypes : uint8
{
	Left,
	Right,
};


USTRUCT()
struct CLIENT_API FActionEventData_Rotate : public FActionEventDurationDataBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	ERotateTypes m_RotateType;
	UPROPERTY(EditAnywhere)
	float m_fRotateSpdPerSec;
	
public:
	FActionEventData_Rotate();
	virtual ~FActionEventData_Rotate() override;
	
	virtual CreateRuntimeResult CreateRuntime(AGameCharacter* owner, UActionData* pActionData) override;

	virtual EActionEventTypes GetActionEventType() const override;
	
#if WITH_EDITOR
	virtual TSharedRef<SWidget> GetEditorContentsWidget(UActionData* pActionData) override;
#endif
};
