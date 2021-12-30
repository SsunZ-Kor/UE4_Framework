#include "ActionEventData_RotateInputE.h"
#include "ActionEventRuntime_RotateInputE.h"
#include "../../ActionControl/ActionController.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#endif

FActionEventData_RotateInputE::FActionEventData_RotateInputE()
{
	m_fRotateSpdPerSec = 360.f;
}

FActionEventData_RotateInputE::~FActionEventData_RotateInputE()
{
}

CreateRuntimeResult FActionEventData_RotateInputE::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	auto pNewRuntime = NewObject<UActionEventRuntime_RotateInputE>(owner->GetActionCtrl());
	pNewRuntime->Init(*this, owner, pActionData);
	
	CreateRuntimeResult result;

	result.pUObject = pNewRuntime;
	result.pRuntime = pNewRuntime;

	return result;
}

EActionEventTypes FActionEventData_RotateInputE::GetActionEventType() const
{
	return EActionEventTypes::RotateByInputEntered;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventData_RotateInputE::GetEditorContentsWidget(UActionData* pActionData)
{
	return SNew(SVerticalBox)
	+SVerticalBox::Slot().AutoHeight()
	[
		EditorFloat(TEXT("RotSpdPerSec"), m_fRotateSpdPerSec, pActionData)
	];
}
#endif