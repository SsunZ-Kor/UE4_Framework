#include "ActionEventData_RotateVel.h"
#include "ActionEventRuntime_RotateVel.h"
#include "../../ActionControl/ActionController.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#endif

FActionEventData_RotateVel::FActionEventData_RotateVel()
{
	m_fRotateSpdPerSec = 360.f;
}

FActionEventData_RotateVel::~FActionEventData_RotateVel()
{
}

CreateRuntimeResult FActionEventData_RotateVel::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	auto pNewRuntime = NewObject<UActionEventRuntime_RotateVel>(owner->GetActionCtrl());
	pNewRuntime->Init(*this, owner, pActionData);
	
	CreateRuntimeResult result;

	result.pUObject = pNewRuntime;
	result.pRuntime = pNewRuntime;

	return result;
}

EActionEventTypes FActionEventData_RotateVel::GetActionEventType() const
{
	return EActionEventTypes::RotateToVelocity;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventData_RotateVel::GetEditorContentsWidget(UActionData* pActionData)
{
	return SNew(SVerticalBox)
	+SVerticalBox::Slot().AutoHeight()
	[
		EditorFloat(TEXT("RotSpdPerSec"), m_fRotateSpdPerSec, pActionData)
	];
}
#endif