// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionEventData_MoveNavU.h"
#include "ActionEventRuntime_MoveNavU.h"
#include "../ActionController.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#endif

FActionEventData_MoveNavU::FActionEventData_MoveNavU()
{
	m_bRoateToMoveDir = false;
	m_fMoveSpdPerSec = 200.f;
}

FActionEventData_MoveNavU::~FActionEventData_MoveNavU()
{
}

CreateRuntimeResult FActionEventData_MoveNavU::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	auto pNewRuntime = NewObject<UActionEventRuntime_MoveNavU>(owner->GetActionCtrl());
	pNewRuntime->Init(*this, owner, pActionData);
	
	CreateRuntimeResult result;

	result.pUObject = pNewRuntime;
	result.pRuntime = pNewRuntime;

	return result;
}

EActionEventTypes FActionEventData_MoveNavU::GetActionEventType() const
{
	return EActionEventTypes::MoveNavUpdated;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventData_MoveNavU::GetEditorContentsWidget(UActionData* pActionData)
{
	return SNew(SVerticalBox)
	+SVerticalBox::Slot().AutoHeight()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		[
			EditorFloat(TEXT("MoveSpdPerSec"), m_fMoveSpdPerSec, pActionData)
		]
		+SHorizontalBox::Slot()
		[
			EditorBool(TEXT("Rotate To Move Dir"), m_bRoateToMoveDir, pActionData)
		]
		+SHorizontalBox::Slot()
	];
}
#endif