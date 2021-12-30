// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionData.h"

UActionData::UActionData()
{
	EventDatas_Anim.Add(FActionEventData_Animation());
	TriggerDatas.Add(FActionTriggerData());
}

UActionData::~UActionData()
{
}

void UActionData::ClearAllEvents()
{
	EventDatas_FindTarget				.Empty();
	EventDatas_MoveByInputEntered		.Empty();
	EventDatas_MoveByInputUpdated		.Empty();
	EventDatas_MoveToTargetEntered		.Empty();
	EventDatas_MoveToTargetUpdated		.Empty();
	EventDatas_MoveNavEntered			.Empty();
	EventDatas_MoveNavUpdated			.Empty();
	EventDatas_Rotate					.Empty();
	EventDatas_RotateByInputEntered		.Empty();
	EventDatas_RotateByInputUpdated		.Empty();
	EventDatas_RotateToTargetEntered	.Empty();
	EventDatas_RotateToTargetUpdated	.Empty();
	EventDatas_RotateToVelocity			.Empty();
	EventDatas_Anim						.Empty();
	EventDatas_PlaySFX					.Empty();
	EventDatas_PlayFX					.Empty();
	EventDatas_HitShape					.Empty();
}

void UActionData::ClearAllTriggers()
{
	TriggerDatas.Empty();
}

void UActionData::AddEvent(FActionEventDataBase* pEventData)
{
	switch(pEventData->GetActionEventType())
	{
	case EActionEventTypes::FindTarget				: EventDatas_FindTarget				.Add(*(FActionEventData_FindTarget*		)pEventData);	break;
				
	case EActionEventTypes::MoveByInputEntered		: EventDatas_MoveByInputEntered		.Add(*(FActionEventData_MoveInputE*		)pEventData);	break;
	case EActionEventTypes::MoveByInputUpdated		: EventDatas_MoveByInputUpdated		.Add(*(FActionEventData_MoveInputU*		)pEventData);	break;
	case EActionEventTypes::MoveToTargetEntered		: EventDatas_MoveToTargetEntered	.Add(*(FActionEventData_MoveTargetE*	)pEventData);	break;
	case EActionEventTypes::MoveToTargetUpdated		: EventDatas_MoveToTargetUpdated	.Add(*(FActionEventData_MoveTargetU*	)pEventData);	break;
	case EActionEventTypes::MoveNavEntered			: EventDatas_MoveNavEntered			.Add(*(FActionEventData_MoveNavE*		)pEventData);	break;
	case EActionEventTypes::MoveNavUpdated			: EventDatas_MoveNavUpdated			.Add(*(FActionEventData_MoveNavU*		)pEventData);	break;
				
	case EActionEventTypes::Rotate	 				: EventDatas_Rotate					.Add(*(FActionEventData_Rotate*			)pEventData);	break;
	case EActionEventTypes::RotateByInputEntered	: EventDatas_RotateByInputEntered	.Add(*(FActionEventData_RotateInputE*	)pEventData);	break;
	case EActionEventTypes::RotateByInputUpdated	: EventDatas_RotateByInputUpdated	.Add(*(FActionEventData_RotateInputU*	)pEventData);	break;
	case EActionEventTypes::RotateToTargetEntered	: EventDatas_RotateToTargetEntered	.Add(*(FActionEventData_RotateTargetE*	)pEventData);	break;
	case EActionEventTypes::RotateToTargetUpdated	: EventDatas_RotateToTargetUpdated	.Add(*(FActionEventData_RotateTargetU*	)pEventData);	break;
	case EActionEventTypes::RotateToVelocity		: EventDatas_RotateToVelocity		.Add(*(FActionEventData_RotateVel*		)pEventData);	break;
		
	case EActionEventTypes::Animation 				: EventDatas_Anim					.Add(*(FActionEventData_Animation*		)pEventData);	break;
	case EActionEventTypes::PlaySFX	 				: EventDatas_PlaySFX				.Add(*(FActionEventData_PlaySFX*		)pEventData);	break;
	case EActionEventTypes::PlayFX	 				: EventDatas_PlayFX					.Add(*(FActionEventData_PlayFX*			)pEventData);	break;
	case EActionEventTypes::HitShape	 			: EventDatas_HitShape				.Add(*(FActionEventData_HitShape*		)pEventData);	break;
	default:																																	break;
	}
}

void UActionData::AddTrigger(FActionTriggerData* pTriggerData)
{
	TriggerDatas.Add(*pTriggerData);
}

void UActionData::AfterLoad()
{
	EventDatas.Empty();

	int nDataCount = 0;

	// Find
	nDataCount = EventDatas_FindTarget.Num();
	for (int i = 0 ; i < nDataCount; ++i)
		EventDatas.Add(&EventDatas_FindTarget[i]);

	// Move
	nDataCount = EventDatas_MoveByInputEntered.Num();
	for (int i = 0 ; i < nDataCount; ++i)
		EventDatas.Add(&EventDatas_MoveByInputEntered[i]);

	nDataCount = EventDatas_MoveByInputUpdated.Num();
	for (int i = 0 ; i < nDataCount; ++i)
		EventDatas.Add(&EventDatas_MoveByInputUpdated[i]);
	
	nDataCount = EventDatas_MoveToTargetEntered.Num();
	for (int i = 0 ; i < nDataCount; ++i)
		EventDatas.Add(&EventDatas_MoveToTargetEntered[i]);
	
	nDataCount = EventDatas_MoveToTargetUpdated.Num();
	for (int i = 0 ; i < nDataCount; ++i)
		EventDatas.Add(&EventDatas_MoveToTargetUpdated[i]);
	
	nDataCount = EventDatas_MoveNavEntered.Num();
	for (int i = 0 ; i < nDataCount; ++i)
		EventDatas.Add(&EventDatas_MoveNavEntered[i]);
	
	nDataCount = EventDatas_MoveNavUpdated.Num();
	for (int i = 0 ; i < nDataCount; ++i)
		EventDatas.Add(&EventDatas_MoveNavUpdated[i]);

	// Rotate
	nDataCount = EventDatas_Rotate.Num();
	for (int i = 0 ; i < nDataCount; ++i)
		EventDatas.Add(&EventDatas_Rotate[i]);

	nDataCount = EventDatas_RotateByInputEntered.Num();
	for (int i = 0 ; i < nDataCount; ++i)
		EventDatas.Add(&EventDatas_RotateByInputEntered[i]);

	nDataCount = EventDatas_RotateByInputUpdated.Num();
	for (int i = 0 ; i < nDataCount; ++i)
		EventDatas.Add(&EventDatas_RotateByInputUpdated[i]);
	
	nDataCount = EventDatas_RotateToTargetEntered.Num();
	for (int i = 0 ; i < nDataCount; ++i)
		EventDatas.Add(&EventDatas_RotateToTargetEntered[i]);
	
	nDataCount = EventDatas_RotateToTargetUpdated.Num();
	for (int i = 0 ; i < nDataCount; ++i)
		EventDatas.Add(&EventDatas_RotateToTargetUpdated[i]);
	
	nDataCount = EventDatas_RotateToVelocity.Num();
	for (int i = 0 ; i < nDataCount; ++i)
		EventDatas.Add(&EventDatas_RotateToVelocity[i]);

	// Anim
	nDataCount = EventDatas_Anim.Num();
	for (int i = 0 ; i < nDataCount; ++i)
		EventDatas.Add(&EventDatas_Anim[i]);

	// SFX
	nDataCount = EventDatas_PlaySFX.Num();
	for (int i = 0 ; i < nDataCount; ++i)
		EventDatas.Add(&EventDatas_PlaySFX[i]);

	// FX
	nDataCount = EventDatas_PlayFX.Num();
	for (int i = 0 ; i < nDataCount; ++i)
		EventDatas.Add(&EventDatas_PlayFX[i]);

	// HIT
	nDataCount = EventDatas_HitShape.Num();
	for (int i = 0 ; i < nDataCount; ++i)
		EventDatas.Add(&EventDatas_HitShape[i]);

	// Sorting
	Algo::Sort(EventDatas, [](const FActionEventDataBase* x, const FActionEventDataBase* y)
	{
		if (x->fStartTime != y->fStartTime)
			return x->fStartTime < y->fStartTime;
		
		return GetEventOrder(x->GetActionEventType()) <  GetEventOrder(y->GetActionEventType());
	});

	Algo::Sort(TriggerDatas, [](const FActionTriggerData& x, const FActionTriggerData& y)
	{
		return x.AxisType < y.AxisType;
	});
}

int UActionData::GetEventOrder(EActionEventTypes actionEventType)
{
	switch(actionEventType)
	{
	case EActionEventTypes::FindTarget				: return 100;
	
	case EActionEventTypes::MoveByInputEntered		: return 200;
	case EActionEventTypes::MoveByInputUpdated		: return 200;
	case EActionEventTypes::MoveToTargetEntered		: return 200;
	case EActionEventTypes::MoveToTargetUpdated		: return 200;
	case EActionEventTypes::MoveNavEntered			: return 200;
	case EActionEventTypes::MoveNavUpdated			: return 200;
			
	case EActionEventTypes::Rotate	 				: return 300;
	case EActionEventTypes::RotateByInputEntered	: return 300;
	case EActionEventTypes::RotateByInputUpdated	: return 300;
	case EActionEventTypes::RotateToTargetEntered	: return 300;
	case EActionEventTypes::RotateToTargetUpdated	: return 300;
	case EActionEventTypes::RotateToVelocity		: return 300;

	case EActionEventTypes::HitShape	 			: return 400;
	case EActionEventTypes::Animation 				: return 500;
	case EActionEventTypes::PlaySFX	 				: return 600;
	case EActionEventTypes::PlayFX	 				: return 700;
	default							 				: return 10000;
	}
}

FString UActionData::GetEventName(EActionEventTypes eventType)
{
	return UEnumToString<EActionEventTypes>(eventType);
}

#if WITH_EDITOR
FActionEventDataBase* UActionData::CreateActionEventForEditor(const EActionEventTypes& actionEventType)
{
	switch(actionEventType)
	{
	case EActionEventTypes::FindTarget				: return new FActionEventData_FindTarget();
	
	case EActionEventTypes::MoveByInputEntered		: return new FActionEventData_MoveInputE();
	case EActionEventTypes::MoveByInputUpdated		: return new FActionEventData_MoveInputU();
	case EActionEventTypes::MoveToTargetEntered		: return new FActionEventData_MoveTargetE();
	case EActionEventTypes::MoveToTargetUpdated		: return new FActionEventData_MoveTargetU();
	case EActionEventTypes::MoveNavEntered			: return new FActionEventData_MoveNavE();
	case EActionEventTypes::MoveNavUpdated			: return new FActionEventData_MoveNavU();
			
	case EActionEventTypes::Rotate	 				: return new FActionEventData_Rotate();
	case EActionEventTypes::RotateByInputEntered	: return new FActionEventData_RotateInputE();
	case EActionEventTypes::RotateByInputUpdated	: return new FActionEventData_RotateInputU();
	case EActionEventTypes::RotateToTargetEntered	: return new FActionEventData_RotateTargetE();
	case EActionEventTypes::RotateToTargetUpdated	: return new FActionEventData_RotateTargetU();
	case EActionEventTypes::RotateToVelocity		: return new FActionEventData_RotateVel();

	case EActionEventTypes::HitShape	 			: return new FActionEventData_HitShape();
	case EActionEventTypes::Animation 				: return new FActionEventData_Animation();
	case EActionEventTypes::PlaySFX	 				: return new FActionEventData_PlaySFX();
	case EActionEventTypes::PlayFX	 				: return new FActionEventData_PlayFX();
	default							 				: return nullptr;
	}
}

FActionTriggerData* UActionData::CreateActionTriggerForEditor()
{
	return new FActionTriggerData();
}

void UActionData::GetActionEventsForEditor(TArray<TSharedPtr<FActionEventDataBase>>& result)
{
	// Find
	for (int i = 0 ; i < EventDatas_FindTarget.Num(); ++i)
		result.Add(MakeShareable(new FActionEventData_FindTarget(EventDatas_FindTarget[i])));

	// Move
	for (int i = 0 ; i < EventDatas_MoveByInputEntered.Num(); ++i)
		result.Add(MakeShareable(new FActionEventData_MoveInputE(EventDatas_MoveByInputEntered[i])));

	for (int i = 0 ; i < EventDatas_MoveByInputUpdated.Num(); ++i)
		result.Add(MakeShareable(new FActionEventData_MoveInputU(EventDatas_MoveByInputUpdated[i])));
	
	for (int i = 0 ; i < EventDatas_MoveToTargetEntered.Num(); ++i)
		result.Add(MakeShareable(new FActionEventData_MoveTargetE(EventDatas_MoveToTargetEntered[i])));
	
	for (int i = 0 ; i < EventDatas_MoveToTargetUpdated.Num(); ++i)
		result.Add(MakeShareable(new FActionEventData_MoveTargetU(EventDatas_MoveToTargetUpdated[i])));
	
	for (int i = 0 ; i < EventDatas_MoveNavEntered.Num(); ++i)
		result.Add(MakeShareable(new FActionEventData_MoveNavE(EventDatas_MoveNavEntered[i])));

	for (int i = 0 ; i < EventDatas_MoveNavUpdated.Num(); ++i)
		result.Add(MakeShareable(new FActionEventData_MoveNavU(EventDatas_MoveNavUpdated[i])));

	// Rotate
	for (int i = 0 ; i < EventDatas_Rotate.Num(); ++i)
		result.Add(MakeShareable(new FActionEventData_Rotate(EventDatas_Rotate[i])));

	for (int i = 0 ; i < EventDatas_RotateByInputEntered.Num(); ++i)
		result.Add(MakeShareable(new FActionEventData_RotateInputE(EventDatas_RotateByInputEntered[i])));

	for (int i = 0 ; i < EventDatas_RotateByInputUpdated.Num(); ++i)
		result.Add(MakeShareable(new FActionEventData_RotateInputU(EventDatas_RotateByInputUpdated[i])));
	
	for (int i = 0 ; i < EventDatas_RotateToTargetEntered.Num(); ++i)
		result.Add(MakeShareable(new FActionEventData_RotateTargetE(EventDatas_RotateToTargetEntered[i])));
	
	for (int i = 0 ; i < EventDatas_RotateToTargetUpdated.Num(); ++i)
		result.Add(MakeShareable(new FActionEventData_RotateTargetU(EventDatas_RotateToTargetUpdated[i])));
	
	for (int i = 0 ; i < EventDatas_RotateToVelocity.Num(); ++i)
		result.Add(MakeShareable(new FActionEventData_RotateVel(EventDatas_RotateToVelocity[i])));

	// Anim
	for (int i = 0 ; i < EventDatas_Anim.Num(); ++i)
		result.Add(MakeShareable(new FActionEventData_Animation(EventDatas_Anim[i])));

	// SFX
	for (int i = 0 ; i < EventDatas_PlaySFX.Num(); ++i)
		result.Add(MakeShareable(new FActionEventData_PlaySFX(EventDatas_PlaySFX[i])));

	// FX
	for (int i = 0 ; i < EventDatas_PlayFX.Num(); ++i)
		result.Add(MakeShareable(new FActionEventData_PlayFX(EventDatas_PlayFX[i])));

	// HIT
	for (int i = 0 ; i < EventDatas_HitShape.Num(); ++i)
		result.Add(MakeShareable(new FActionEventData_HitShape(EventDatas_HitShape[i])));

	// Sorting
	Algo::Sort(result, [](const TSharedPtr<FActionEventDataBase> x, const TSharedPtr<FActionEventDataBase> y)
	{
		if (x->fStartTime != y->fStartTime)
			return x->fStartTime < y->fStartTime;
		
		return GetEventOrder(x->GetActionEventType()) <  GetEventOrder(y->GetActionEventType());
	});
}

void UActionData::GetActionTriggersForEditor(TArray<TSharedPtr<FActionTriggerData>>& result)
{
	for (int i = 0 ; i < TriggerDatas.Num(); ++i)
		result.Add(MakeShareable(new FActionTriggerData(TriggerDatas[i])));
}

void UActionData::MakeDirty()
{
	m_IsDirty = true;
}

void UActionData::ResetDirty()
{
	m_IsDirty = false;
}

const bool& UActionData::IsDirty()
{
	return m_IsDirty;
}
#endif
