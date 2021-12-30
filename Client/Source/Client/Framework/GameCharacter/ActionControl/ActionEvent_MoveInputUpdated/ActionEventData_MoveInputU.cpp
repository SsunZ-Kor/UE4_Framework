// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionEventData_MoveInputU.h"
#include "ActionEventRuntime_MoveInputU.h"
#include "../ActionController.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#endif

FActionEventData_MoveInputU::FActionEventData_MoveInputU()
{
	m_fMoveSpdPerSec = 200.f;
	m_bUseInputScale = false;

	m_bUseUpdateAngleSpd = false;
	m_fUpdateAngleSpd = 360.f;

}

FActionEventData_MoveInputU::~FActionEventData_MoveInputU()
{
}

CreateRuntimeResult FActionEventData_MoveInputU::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	auto pNewRuntime = NewObject<UActionEventRuntime_MoveInputU>(owner->GetActionCtrl());
	pNewRuntime->Init(*this, owner, pActionData);
	
	CreateRuntimeResult result;

	result.pUObject = pNewRuntime;
	result.pRuntime = pNewRuntime;

	return result;
}

EActionEventTypes FActionEventData_MoveInputU::GetActionEventType() const
{
	return EActionEventTypes::MoveByInputUpdated;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventData_MoveInputU::GetEditorContentsWidget(UActionData* pActionData)
{
	return SNew(SVerticalBox)
	+SVerticalBox::Slot().AutoHeight()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			[
				EditorFloat(TEXT("MoveSpdPerSec"), m_fMoveSpdPerSec, pActionData)
			]
			+SVerticalBox::Slot()
			[
				EditorBool(TEXT("Use Update Angle"), m_bUseUpdateAngleSpd, pActionData)
			]
		]
		+SHorizontalBox::Slot()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			[
				EditorBool(TEXT("Use Input Scale"), m_bUseInputScale, pActionData)
			]
			+SVerticalBox::Slot()
			[
				SNew(SBox)
				.Visibility_Lambda([this](){return m_bUseUpdateAngleSpd ? EVisibility::Visible : EVisibility::Hidden; })
				.Content()
				[
					EditorFloat(TEXT("Update Angle Spd"), m_fUpdateAngleSpd, pActionData)
				]
			]
		]
		+SHorizontalBox::Slot()
	];
}
#endif