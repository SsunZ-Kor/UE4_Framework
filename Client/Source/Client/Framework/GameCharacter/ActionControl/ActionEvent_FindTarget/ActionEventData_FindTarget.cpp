// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionEventData_FindTarget.h"
#include "ActionEventRuntime_FindTarget.h"
#include "../ActionController.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#endif

FActionEventData_FindTarget::FActionEventData_FindTarget()
{
	m_fRadius = 1000.f;
	m_TargetType = EGameCharacterFindTargetTypes::Enemy;
	m_TargetStateType = EGameCharacterStateTypes::Alive;
}

FActionEventData_FindTarget::~FActionEventData_FindTarget()
{
}

CreateRuntimeResult FActionEventData_FindTarget::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	auto pNewRuntime = NewObject<UActionEventRuntime_FindTarget>(owner->GetActionCtrl());
	pNewRuntime->Init(*this, owner, pActionData);
	
	CreateRuntimeResult result;

	result.pUObject = pNewRuntime;
	result.pRuntime = pNewRuntime;

	return result;
}

EActionEventTypes FActionEventData_FindTarget::GetActionEventType() const
{
	return EActionEventTypes::FindTarget;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventData_FindTarget::GetEditorContentsWidget(UActionData* pActionData)
{
	return 	SNew(SVerticalBox)
	+SVerticalBox::Slot().AutoHeight()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot().AutoHeight()
			[
				EditorEnum<EGameCharacterFindTargetTypes>(TEXT("TargetTypes"), m_TargetType, pActionData)
			]
			+SVerticalBox::Slot().AutoHeight()
			[
				EditorFloat(TEXT("Radius"), m_fRadius, pActionData)
			]
		]
		+SHorizontalBox::Slot()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot().AutoHeight()
			[
				EditorEnum<EGameCharacterStateTypes>(TEXT("StateTypes"), m_TargetStateType, pActionData)
			]
			+SVerticalBox::Slot().AutoHeight()
			[
				EditorString(TEXT("ActionNameIfNotFound"), m_ifNotFoundPlay, pActionData)
			]			
		]
		+SHorizontalBox::Slot()
	];
}
#endif
	