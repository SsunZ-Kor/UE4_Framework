// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionEventData_Animation.h"
#include "ActionEventRuntime_Animation.h"
#include "../ActionController.h"
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"

FActionEventData_Animation::FActionEventData_Animation()
{
	m_fFadeTime = 0.3f;
	m_fPlayRate = 1.f;
	m_bResetIfPlaying = false;
	m_BlendOption = EAnimBlendOption::None;
}

FActionEventData_Animation::~FActionEventData_Animation()
{
}

CreateRuntimeResult FActionEventData_Animation::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	auto pNewRuntime = NewObject<UActionEventRuntime_Animation>(owner->GetActionCtrl());
	pNewRuntime->Init(*this, owner, pActionData);
	
	CreateRuntimeResult result;

	result.pUObject = pNewRuntime;
	result.pRuntime = pNewRuntime;

	return result;
}

EActionEventTypes FActionEventData_Animation::GetActionEventType() const
{
	return EActionEventTypes::Animation;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventData_Animation::GetEditorContentsWidget(UActionData* pActionData)
{
	return SNew(SVerticalBox)
	+SVerticalBox::Slot().AutoHeight()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot().AutoHeight()
			[
				EditorString(TEXT("AnimName"), m_AnimName, pActionData)
			]
			+SVerticalBox::Slot().AutoHeight()
			[
				EditorFloat(TEXT("FadeTime"), m_fFadeTime, pActionData)
			]
		]
		+SHorizontalBox::Slot()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot().AutoHeight()
			[
				EditorEnum<EAnimBlendOption>("BlendOption", m_BlendOption, pActionData)
			]
			+SVerticalBox::Slot().AutoHeight()
			[
				EditorFloat(TEXT("PlaySpd"), m_fPlayRate, pActionData)
			]
		]
		+SHorizontalBox::Slot()
		[
			
			SNew(SVerticalBox)
			+SVerticalBox::Slot().AutoHeight()
			[
				EditorBool("Reset If Playing", m_bResetIfPlaying, pActionData)
			]
		]
	];
}
#endif
