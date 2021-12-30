#include "ActionEventData_RotateInputU.h"
#include "ActionEventRuntime_RotateInputU.h"
#include "../../ActionControl/ActionController.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#endif

FActionEventData_RotateInputU::FActionEventData_RotateInputU()
{
	m_fRotateSpdPerSec = 360.f;
}

FActionEventData_RotateInputU::~FActionEventData_RotateInputU()
{
}

CreateRuntimeResult FActionEventData_RotateInputU::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	auto pNewRuntime = NewObject<UActionEventRuntime_RotateInputU>(owner->GetActionCtrl());
	pNewRuntime->Init(*this, owner, pActionData);
	
	CreateRuntimeResult result;

	result.pUObject = pNewRuntime;
	result.pRuntime = pNewRuntime;

	return result;
}

EActionEventTypes FActionEventData_RotateInputU::GetActionEventType() const
{
	return EActionEventTypes::RotateByInputUpdated;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventData_RotateInputU::GetEditorContentsWidget(UActionData* pActionData)
{
	return SNew(SVerticalBox)
	+SVerticalBox::Slot().AutoHeight()
	[
		EditorFloat(TEXT("RotSpdPerSec"), m_fRotateSpdPerSec, pActionData)
	];
}
#endif