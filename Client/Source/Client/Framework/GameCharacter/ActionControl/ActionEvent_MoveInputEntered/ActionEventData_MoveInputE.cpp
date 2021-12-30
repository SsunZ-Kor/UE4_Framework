// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionEventData_MoveInputE.h"
#include "ActionEventRuntime_MoveInputE.h"
#include "../ActionController.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#endif

FActionEventData_MoveInputE::FActionEventData_MoveInputE()
{
	m_fMoveSpdPerSec = 200.f;
}

FActionEventData_MoveInputE::~FActionEventData_MoveInputE()
{
}

CreateRuntimeResult FActionEventData_MoveInputE::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	auto pNewRuntime = NewObject<UActionEventRuntime_MoveInputE>(owner->GetActionCtrl());
	pNewRuntime->Init(*this, owner, pActionData);
	
	CreateRuntimeResult result;

	result.pUObject = pNewRuntime;
	result.pRuntime = pNewRuntime;

	return result;
}

EActionEventTypes FActionEventData_MoveInputE::GetActionEventType() const
{
	return EActionEventTypes::MoveByInputEntered;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventData_MoveInputE::GetEditorContentsWidget(UActionData* pActionData)
{
	return 	SNew(SVerticalBox)
	+SVerticalBox::Slot().AutoHeight()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		[
			EditorFloat(TEXT("MoveSpdPerSec"), m_fMoveSpdPerSec, pActionData)
		]
		+SHorizontalBox::Slot()
		+SHorizontalBox::Slot()
	];
}
#endif