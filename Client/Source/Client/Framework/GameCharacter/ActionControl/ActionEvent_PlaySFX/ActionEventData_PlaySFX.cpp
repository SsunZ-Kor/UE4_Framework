// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionEventData_PlaySFX.h"
#include "ActionEventRuntime_PlaySFX.h"
#include "../ActionController.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#endif

FActionEventData_PlaySFX::FActionEventData_PlaySFX()
{
	m_vLocation = FVector::ZeroVector;
	m_qRotation = FQuat::Identity;
	m_bIsFollow = false;
}

FActionEventData_PlaySFX::~FActionEventData_PlaySFX()
{
}

CreateRuntimeResult FActionEventData_PlaySFX::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	auto pNewRuntime = NewObject<UActionEventRuntime_PlaySFX>(owner->GetActionCtrl());
	pNewRuntime->Init(*this, owner, pActionData);
	
	CreateRuntimeResult result;

	result.pUObject = pNewRuntime;
	result.pRuntime = pNewRuntime;

	return result;
}

EActionEventTypes FActionEventData_PlaySFX::GetActionEventType() const
{
	return EActionEventTypes::PlaySFX;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventData_PlaySFX::GetEditorContentsWidget(UActionData* pActionData)
{
	return SNew(SVerticalBox)
	+SVerticalBox::Slot().AutoHeight()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		[
			EditorName("SocketName", m_SocketName, pActionData)	
		]
		+SHorizontalBox::Slot()
		[
			EditorBool(TEXT("Follow FX"), m_bIsFollow, pActionData)
		]
	]
	+SVerticalBox::Slot().AutoHeight()
	[
		EditorString(TEXT("RefPath SFX"), m_ResPath_SFX, pActionData)
	]
	+SVerticalBox::Slot().AutoHeight()
	[
		EditorVector(TEXT("Offset Loc"), m_vLocation, pActionData)
	]
	+SVerticalBox::Slot().AutoHeight()
	[
		EditorQuat(TEXT("Offset Rot"), m_qRotation, pActionData)
	];
}
#endif