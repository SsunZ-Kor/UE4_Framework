// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ActionEvent/ActionEventDataBase.h"
#include "Client/Framework/GameCharacter/GameCharacter_Define.h"
#include "ActionEventData_HitShape.generated.h"

UENUM()
enum class EDirTypes : uint8
{
	MyForward,
	Input,	
};

UENUM()
enum class ECastTypes : uint8
{
	MyPos_Sphere,
	MyPos_Box,
	Target_Sphere,
	Target_Box,
};

USTRUCT()
struct CLIENT_API FHitShapeInfo
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	ECastTypes m_CastType;

	UPROPERTY(EditAnywhere)
	FVector m_vOffsetPos;
	UPROPERTY(EditAnywhere)
	FQuat m_qOffsetRot;
	UPROPERTY(EditAnywhere)
	FVector m_Size;

	UPROPERTY(EditAnywhere)
	float m_fDist;

	FHitShapeInfo();
	~FHitShapeInfo();
};

USTRUCT()
struct CLIENT_API FActionEventData_HitShape : public FActionEventDataBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	EGameCharacterFindTargetTypes m_TargetType;
	UPROPERTY(EditAnywhere)
	TArray<FHitShapeInfo> m_hitInfos;

	UPROPERTY(EditAnywhere)
	FString m_ResPath_SFX;
	UPROPERTY(EditAnywhere)
	FString m_ResPath_FX;

	UPROPERTY(EditAnywhere)
	bool m_bIsFollow;

public:
	FActionEventData_HitShape();
	virtual ~FActionEventData_HitShape() override;
	
	virtual CreateRuntimeResult CreateRuntime(AGameCharacter* owner, UActionData* pActionData) override;
	virtual EActionEventTypes GetActionEventType() const override;
	
#if WITH_EDITOR
	bool m_bIsFolded_HitInfos;
	TArray<TSharedPtr<FHitShapeInfo>> m_hitInfos_Editor;
	
	virtual TSharedRef<SWidget> GetEditorContentsWidget(UActionData* pActionData) override;
	virtual void AdjustEditorData() override;
#endif
};