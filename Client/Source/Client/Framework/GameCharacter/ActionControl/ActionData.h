// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ClientGameBase.h"

#include "ActionEvent_FindTarget/ActionEventData_FindTarget.h"

#include "ActionEvent_MoveInputEntered/ActionEventData_MoveInputE.h"
#include "ActionEvent_MoveInputUpdated/ActionEventData_MoveInputU.h"
#include "ActionEvent_MoveTargetEntered/ActionEventData_MoveTargetE.h"
#include "ActionEvent_MoveTargetUpdated/ActionEventData_MoveTargetU.h"
#include "ActionEvent_MoveNavEntered/ActionEventData_MoveNavE.h"
#include "ActionEvent_MoveNavUpdated/ActionEventData_MoveNavU.h"

#include "ActionEvent_Rotate/ActionEventData_Rotate.h"
#include "ActionEvent_RotateInputEntered/ActionEventData_RotateInputE.h"
#include "ActionEvent_RotateInputUpdated/ActionEventData_RotateInputU.h"
#include "ActionEvent_RotateTargetEntered/ActionEventData_RotateTargetE.h"
#include "ActionEvent_RotateTargetUpdated/ActionEventData_RotateTargetU.h"
#include "ActionEvent_RotateVelocity/ActionEventData_RotateVel.h"

#include "ActionEvent_Animation/ActionEventData_Animation.h"
#include "ActionEvent_PlaySFX/ActionEventData_PlaySFX.h"
#include "ActionEvent_PlayFX/ActionEventData_PlayFX.h"

#include "ActionEvent_HitShape/ActionEventData_HitShape.h"

#include "ActionTrigger/ActionTriggerData.h"

#include "ActionData.generated.h"

UCLASS()
class CLIENT_API UActionData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Action Data", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionTypes actionType;
	UPROPERTY(EditAnywhere, Category = "Action Data", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float fLength = 1.f;
	UPROPERTY(EditAnywhere, Category = "Action Data", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsLoop = false;

	TArray<FActionEventDataBase*> EventDatas;

	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionEventData_FindTarget> EventDatas_FindTarget;
	
	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionEventData_MoveInputE> EventDatas_MoveByInputEntered;
	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionEventData_MoveInputU> EventDatas_MoveByInputUpdated;
	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionEventData_MoveTargetE> EventDatas_MoveToTargetEntered;
	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionEventData_MoveTargetU> EventDatas_MoveToTargetUpdated;
	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionEventData_MoveNavE> EventDatas_MoveNavEntered;
	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionEventData_MoveNavU> EventDatas_MoveNavUpdated;
	
	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionEventData_Rotate> EventDatas_Rotate;
	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionEventData_RotateInputE> EventDatas_RotateByInputEntered;
	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionEventData_RotateInputU> EventDatas_RotateByInputUpdated;
	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionEventData_RotateTargetE> EventDatas_RotateToTargetEntered;
	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionEventData_RotateTargetU> EventDatas_RotateToTargetUpdated;
	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionEventData_RotateVel> EventDatas_RotateToVelocity;

	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionEventData_Animation> EventDatas_Anim;
	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionEventData_PlaySFX> EventDatas_PlaySFX;
	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionEventData_PlayFX> EventDatas_PlayFX;

	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionEventData_HitShape> EventDatas_HitShape;
	
	UPROPERTY(EditAnywhere, Category = "Action Event Data")
	TArray<FActionTriggerData> TriggerDatas;

public:
	UActionData();
	virtual ~UActionData() override;

	void ClearAllEvents();
	void ClearAllTriggers();
	void AddEvent(FActionEventDataBase* pEventData);
	void AddTrigger(FActionTriggerData* pTriggerData);
	void AfterLoad();

	static int GetEventOrder(EActionEventTypes eventType);
	static FString GetEventName(EActionEventTypes eventType);

#if WITH_EDITOR
private:
	bool m_IsDirty = false;
public:
	static FActionEventDataBase* CreateActionEventForEditor(const EActionEventTypes& actionEventType);
	static FActionTriggerData* CreateActionTriggerForEditor();
	void GetActionEventsForEditor(TArray<TSharedPtr<FActionEventDataBase>>& result);
	void GetActionTriggersForEditor(TArray<TSharedPtr<FActionTriggerData>>& result);
	void MakeDirty();
	void ResetDirty();
	const bool& IsDirty();
#endif
};