// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionEventData_PlayFX.h"
#include "ActionEventRuntime_PlayFX.h"
#include "../ActionController.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#endif

FActionEventData_PlayFX::FActionEventData_PlayFX()
{
	m_vLocation = FVector::ZeroVector;
	m_qRotation = FQuat::Identity;
	m_vScale = FVector::OneVector;
	m_bIsFollow = false;
}

FActionEventData_PlayFX::~FActionEventData_PlayFX()
{
}

CreateRuntimeResult FActionEventData_PlayFX::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	auto pNewRuntime = NewObject<UActionEventRuntime_PlayFX>(owner->GetActionCtrl());
	pNewRuntime->Init(*this, owner, pActionData);
	
	CreateRuntimeResult result;

	result.pUObject = pNewRuntime;
	result.pRuntime = pNewRuntime;

	return result;
}

EActionEventTypes FActionEventData_PlayFX::GetActionEventType() const
{
	return EActionEventTypes::PlayFX;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventData_PlayFX::GetEditorContentsWidget(UActionData* pActionData)
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
		EditorString(TEXT("RefPath FX"), m_ResPath_FX, pActionData)
	]
	+SVerticalBox::Slot().AutoHeight()
	[
		EditorVector(TEXT("Offset Loc"), m_vLocation, pActionData)
	]
	+SVerticalBox::Slot().AutoHeight()
	[
		EditorQuat(TEXT("Offset Rot"), m_qRotation, pActionData)
	]
	+SVerticalBox::Slot().AutoHeight()
	[
		EditorVector(TEXT("Size"), m_vScale, pActionData)
	];
}
#endif