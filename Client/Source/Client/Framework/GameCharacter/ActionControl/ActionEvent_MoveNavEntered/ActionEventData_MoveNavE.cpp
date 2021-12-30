// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionEventData_MoveNavE.h"
#include "ActionEventRuntime_MoveNavE.h"
#include "../ActionController.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#endif

FActionEventData_MoveNavE::FActionEventData_MoveNavE()
{
	m_fMoveSpdPerSec = 200.f;
	m_bRoateToMoveDir = true;
}

FActionEventData_MoveNavE::~FActionEventData_MoveNavE()
{
}

CreateRuntimeResult FActionEventData_MoveNavE::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	auto pNewRuntime = NewObject<UActionEventRuntime_MoveNavE>(owner->GetActionCtrl());
	pNewRuntime->Init(*this, owner, pActionData);
	
	CreateRuntimeResult result;

	result.pUObject = pNewRuntime;
	result.pRuntime = pNewRuntime;

	return result;
}

EActionEventTypes FActionEventData_MoveNavE::GetActionEventType() const
{
	return EActionEventTypes::MoveNavEntered;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventData_MoveNavE::GetEditorContentsWidget(UActionData* pActionData)
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