#include "ActionEventData_RotateTargetU.h"
#include "ActionEventRuntime_RotateTargetU.h"
#include "../../ActionControl/ActionController.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#endif

FActionEventData_RotateTargetU::FActionEventData_RotateTargetU()
{
	m_fRotateSpdPerSec = 360.f;
}

FActionEventData_RotateTargetU::~FActionEventData_RotateTargetU()
{
}

CreateRuntimeResult FActionEventData_RotateTargetU::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	auto pNewRuntime = NewObject<UActionEventRuntime_RotateTargetU>(owner->GetActionCtrl());
	pNewRuntime->Init(*this, owner, pActionData);
	
	CreateRuntimeResult result;

	result.pUObject = pNewRuntime;
	result.pRuntime = pNewRuntime;

	return result;
}

EActionEventTypes FActionEventData_RotateTargetU::GetActionEventType() const
{
	return EActionEventTypes::RotateToTargetUpdated;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventData_RotateTargetU::GetEditorContentsWidget(UActionData* pActionData)
{
	return SNew(SVerticalBox)
	+SVerticalBox::Slot().AutoHeight()
	[
		EditorFloat(TEXT("RotSpdPerSec"), m_fRotateSpdPerSec, pActionData)
	];
}
#endif