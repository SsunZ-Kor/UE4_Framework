// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ActionEventDataBase.h"
#include "ActionEventDurationDataBase.generated.h"

USTRUCT()
struct CLIENT_API FActionEventDurationDataBase : public FActionEventDataBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float fEndTime;

public:
	FActionEventDurationDataBase();
	virtual ~FActionEventDurationDataBase() override;

	virtual bool IsDuration() const override;
	
#if WITH_EDITOR
	virtual TSharedRef<SWidget> GetEditorTimeWidget(UActionData* pActionData) override;
#endif
};