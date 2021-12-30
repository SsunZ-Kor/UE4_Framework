#pragma once

#include "../ActionEvent/ActionEventDurationDataBase.h"
#include "ActionEventData_RotateVel.generated.h"

USTRUCT()
struct CLIENT_API FActionEventData_RotateVel : public FActionEventDurationDataBase
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere)
	float m_fRotateSpdPerSec = 360.f;

public:
	FActionEventData_RotateVel();
	virtual ~FActionEventData_RotateVel() override;

	virtual CreateRuntimeResult CreateRuntime(AGameCharacter* owner, UActionData* pActionData) override;

	virtual EActionEventTypes GetActionEventType() const override;
	
#if WITH_EDITOR
	virtual TSharedRef<SWidget> GetEditorContentsWidget(UActionData* pActionData) override;
#endif
};
