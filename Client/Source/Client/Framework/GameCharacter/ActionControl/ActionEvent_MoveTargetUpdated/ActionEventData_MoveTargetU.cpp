// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionEventData_MoveTargetU.h"
#include "ActionEventRuntime_MoveTargetU.h"
#include "../ActionController.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#endif

FActionEventData_MoveTargetU::FActionEventData_MoveTargetU()
{
	m_fMoveSpdPerSec = 200.f;
	
	m_bUseUpdateAngleSpd = false;
	m_fUpdateAngleSpd = 360.f;
	
	m_fOnReachDist = 0.f;
}

FActionEventData_MoveTargetU::~FActionEventData_MoveTargetU()
{
}

CreateRuntimeResult FActionEventData_MoveTargetU::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	auto pNewRuntime = NewObject<UActionEventRuntime_MoveTargetU>(owner->GetActionCtrl());
	pNewRuntime->Init(*this, owner, pActionData);
	
	CreateRuntimeResult result;

	result.pUObject = pNewRuntime;
	result.pRuntime = pNewRuntime;

	return result;
}

EActionEventTypes FActionEventData_MoveTargetU::GetActionEventType() const
{
	return EActionEventTypes::MoveToTargetUpdated;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventData_MoveTargetU::GetEditorContentsWidget(UActionData* pActionData)
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
				EditorBool(TEXT("Use Update Angle"),m_bUseUpdateAngleSpd, pActionData)
			]
		]
		+SHorizontalBox::Slot()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			[
				EditorFloat(TEXT("On Reach Dist"), m_fOnReachDist, pActionData)
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
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			[
				EditorString(TEXT("ActionNameOnReached"), OnReachTargetPlay, pActionData)
			]
			+SVerticalBox::Slot()
		]
	];
}
#endif