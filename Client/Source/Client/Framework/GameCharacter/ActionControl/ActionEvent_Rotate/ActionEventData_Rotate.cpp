// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionEventData_Rotate.h"
#include "ActionEventRuntime_Rotate.h"
#include "../ActionController.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#endif

FActionEventData_Rotate::FActionEventData_Rotate()
{
	m_RotateType = ERotateTypes::Left;
	m_fRotateSpdPerSec = 360.f;
}

FActionEventData_Rotate::~FActionEventData_Rotate()
{
}

CreateRuntimeResult FActionEventData_Rotate::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	auto pNewRuntime = NewObject<UActionEventRuntime_Rotate>(owner->GetActionCtrl());
	pNewRuntime->Init(*this, owner, pActionData);
	
	CreateRuntimeResult result;

	result.pUObject = pNewRuntime;
	result.pRuntime = pNewRuntime;

	return result;
}

EActionEventTypes FActionEventData_Rotate::GetActionEventType() const
{
	return EActionEventTypes::Rotate;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventData_Rotate::GetEditorContentsWidget(UActionData* pActionData)
{
	return SNew(SVerticalBox)
	+SVerticalBox::Slot().AutoHeight()
	[
		EditorFloat(TEXT("RotSpdPerSec"), m_fRotateSpdPerSec, pActionData)
	]
	+SVerticalBox::Slot().AutoHeight()
	[
		EditorEnum(TEXT("Rot Types"), m_RotateType, pActionData)
	];
}
#endif