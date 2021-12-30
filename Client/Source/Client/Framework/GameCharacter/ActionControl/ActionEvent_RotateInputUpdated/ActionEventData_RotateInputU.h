#pragma once

#include "../ActionEvent/ActionEventDurationDataBase.h"
#include "ActionEventData_RotateInputU.generated.h"

USTRUCT()
struct CLIENT_API FActionEventData_RotateInputU: public FActionEventDurationDataBase
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere)
	float m_fRotateSpdPerSec;

public:
	FActionEventData_RotateInputU();
	virtual ~FActionEventData_RotateInputU() override;
	
	virtual CreateRuntimeResult CreateRuntime(AGameCharacter* owner, UActionData* pActionData) override;

	virtual EActionEventTypes GetActionEventType() const override;
	
#if WITH_EDITOR
	virtual TSharedRef<SWidget> GetEditorContentsWidget(UActionData* pActionData) override;
#endif
};
