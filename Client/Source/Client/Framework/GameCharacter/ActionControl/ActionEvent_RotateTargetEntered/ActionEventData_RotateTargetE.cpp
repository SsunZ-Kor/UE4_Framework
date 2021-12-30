#include "ActionEventData_RotateTargetE.h"
#include "ActionEventRuntime_RotateTargetE.h"
#include "../../ActionControl/ActionController.h"

#if WITH_EDITOR
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#endif

FActionEventData_RotateTargetE::FActionEventData_RotateTargetE()
{
	m_fRotateSpdPerSec = 360.f;
}

FActionEventData_RotateTargetE::~FActionEventData_RotateTargetE()
{
	
}

CreateRuntimeResult FActionEventData_RotateTargetE::CreateRuntime(AGameCharacter* owner, UActionData* pActionData)
{
	auto pNewRuntime = NewObject<UActionEventRuntime_RotateTargetE>(owner->GetActionCtrl());
	pNewRuntime->Init(*this, owner, pActionData);
	
	CreateRuntimeResult result;

	result.pUObject = pNewRuntime;
	result.pRuntime = pNewRuntime;

	return result;
}

EActionEventTypes FActionEventData_RotateTargetE::GetActionEventType() const
{
	return EActionEventTypes::RotateToTargetEntered;
}

#if WITH_EDITOR
TSharedRef<SWidget> FActionEventData_RotateTargetE::GetEditorContentsWidget(UActionData* pActionData)
{
	return SNew(SVerticalBox)
	+SVerticalBox::Slot().AutoHeight()
	[
		EditorFloat(TEXT("RotSpdPerSec"), m_fRotateSpdPerSec, pActionData)
	];
}
#endif