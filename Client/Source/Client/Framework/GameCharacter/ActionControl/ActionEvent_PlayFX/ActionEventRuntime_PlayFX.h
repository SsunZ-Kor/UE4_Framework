#pragma once

#include "../ActionEvent/ActionEventRuntimeBase.h"
#include "ActionEventData_PlayFX.h"
#include "ActionEventRuntime_PlayFX.generated.h"

class UFXContainer;
class AFXActor;

UCLASS()
class CLIENT_API UActionEventRuntime_PlayFX : public UObject, public ActionEventRuntimeBase<FActionEventData_PlayFX>
{
	GENERATED_BODY()
	private:	
	UFXContainer* m_pFXContainer;
	AFXActor* m_pFXActor;
	
public:
	UActionEventRuntime_PlayFX();
	virtual ~UActionEventRuntime_PlayFX() override;

	virtual void Init(FActionEventData_PlayFX& data, AGameCharacter* owner, UActionData*pActionLength) override;
	virtual bool OnStart(float elapsedTime) override;

	UFUNCTION()
	void OnReturnFX(AFXActor* pFXReturned);
};