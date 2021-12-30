// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionEventData_MoveTargetE.h"
#include "ActionEventRuntime_MoveTargetE.h"
#include "../ActionController.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#include "Widgets/Input/SNumericEntryBox.h"
#endif

FActionEventData_MoveTargetE::FActionEventData_MoveTargetE()
{
	m_fMoveSpdPerSec = 200.f;
	m_fOnReachDist = 0.f;
}

FActionEventData_MoveTargetE::~FActionEventData_MoveTargetE()
{
}

CreateRuntimeResult FActionEventData_MoveTargetE::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	auto pNewRuntime = NewObject<UActionEventRuntime_MoveTargetE>(owner->GetActionCtrl());
	pNewRuntime->Init(*this, owner, pActionData);
	
	CreateRuntimeResult result;

	result.pUObject = pNewRuntime;
	result.pRuntime = pNewRuntime;

	return result;
}

EActionEventTypes FActionEventData_MoveTargetE::GetActionEventType() const
{
	return EActionEventTypes::MoveToTargetEntered;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventData_MoveTargetE::GetEditorContentsWidget(UActionData* pActionData)
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
			EditorFloat(TEXT("On Reach Dist"), m_fOnReachDist, pActionData)
		]
		+SHorizontalBox::Slot()
		[
			EditorString(TEXT("ActionNameOnReached"), OnReachTargetPlay, pActionData)
		]
	];
}
#endif