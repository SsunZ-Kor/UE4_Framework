// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IActionEventRuntime.h"
#include "ActionEventDataBase.generated.h"

class AGameCharacter;
class UActionData;

// 인덱스로 사용중 값 변경 금지
UENUM()
enum class EActionEventTypes : uint32
{
	None,
	FindTarget,
	
	MoveByInputEntered,
	MoveByInputUpdated,
	MoveToTargetEntered,
	MoveToTargetUpdated,
	MoveNavEntered,
	MoveNavUpdated,

	Rotate,
	RotateByInputEntered,
	RotateByInputUpdated,
	RotateToTargetEntered,
	RotateToTargetUpdated,
	RotateToVelocity,

	Animation,
	PlaySFX,
	PlayFX,

	HitShape,
	Max,
};

USTRUCT()
struct CLIENT_API FActionEventDataBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float fStartTime;

public:
	FActionEventDataBase();
	virtual ~FActionEventDataBase();

	virtual CreateRuntimeResult CreateRuntime(AGameCharacter* owner, UActionData* pActionData);

	virtual EActionEventTypes GetActionEventType() const;
	FString GetActionEventName() const;

	virtual bool IsDuration() const;

#if WITH_EDITOR
	static const float MAX_LABEL_WIDTH;
	bool m_bIsFolded_EditorContentsWidget;

public:
	virtual TSharedRef<SWidget> GetEditorTimeWidget(UActionData* pActionData);
	virtual TSharedRef<SWidget> GetEditorContentsWidget(UActionData* pActionData);
	const bool& GetFolded_EditorContentsWidget();
	void SetFolded_EditorContentsWidget(const bool& bFolded);

	virtual void AdjustEditorData();
public:
	static  TSharedRef<SWidget> EditorInt(FString fieldName, int& val, UActionData* pActionData);
	static  TSharedRef<SWidget> EditorInt(FString fieldName, int& val, const int& min, const int& max, UActionData* pActionData);
	
	static  TSharedRef<SWidget> EditorFloat(FString fieldName, float& val, UActionData* pActionData);
	static  TSharedRef<SWidget> EditorFloat(FString fieldName, float& val, const float& min, const float& max, UActionData* pActionData);

	static  TSharedRef<SWidget> EditorVector(FString fieldName, FVector& val, UActionData* pActionData);
	static  TSharedRef<SWidget> EditorRotator(FString fieldName, FRotator& val, UActionData* pActionData);
	static  TSharedRef<SWidget> EditorQuat(FString fieldName, FQuat& val, UActionData* pActionData);

	static  TSharedRef<SWidget> EditorName(FString fieldName, FName& val, UActionData* pActionData);
	static  TSharedRef<SWidget> EditorText(FString fieldName, FText& val, UActionData* pActionData);
	static  TSharedRef<SWidget> EditorString(FString fieldName, FString& val, UActionData* pActionData);
	static  TSharedRef<SWidget> EditorBool(FString fieldName, bool& val, UActionData* pActionData);

	template<typename T>
	static  TSharedRef<SWidget> EditorEnum(FString fieldName, T& val, UActionData* pActionData);

	template<typename T>
	static TSharedRef<SWidget> EditorList(FString fieldName, TArray<T>& item, bool& bIsFolded, typename SListView<T>::FOnGenerateRow onGenerateRow, typename SListView<T>::FOnSelectionChanged onSelectionChenged, FOnClicked onClicked_Create, UActionData* pActionData);
#endif
};
