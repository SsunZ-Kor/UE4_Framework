// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameCharacter_Define.h"
#include "ActionTriggerData.generated.h"

UENUM()
enum class ETriggerAreaTypes : uint8
{
	Any,
	Ground,
	Air,
	Water,
	GroundAndAir,
	GroundAndWater,
	AirAndWater
	
};

class UActionData;

USTRUCT()
struct CLIENT_API FActionTriggerData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	ETriggerAreaTypes AreaType;

	UPROPERTY(EditAnywhere)
	FString NextActionName;

	UPROPERTY(EditAnywhere)
	float fStartTime;
	UPROPERTY(EditAnywhere)
	float fEndTime;

	UPROPERTY(EditAnywhere)
	ETriggerAxisTypes AxisType;
	
	UPROPERTY(EditAnywhere)
	ETriggerEventTypes EventType;

public:
	FActionTriggerData();
	~FActionTriggerData();

	
#if WITH_EDITOR
	bool m_bIsFolded_EditorContentsWidget;
	
public:
	TSharedRef<SWidget> GetEditorTimeWidget(UActionData* pActionData);
	TSharedRef<SWidget> GetEditorContentsWidget(UActionData* pActionData);
	const bool& GetFolded_EditorContentsWidget();
	void SetFolded_EditorContentsWidget(const bool& bFolded);
	#endif
};