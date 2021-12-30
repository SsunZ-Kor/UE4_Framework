// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ClientGameBase.h"
#include "GameFramework/PlayerController.h"
#include "UserInputController.generated.h"

class AGameCamera;
class AGameCharacter;

UENUM()
enum class EUserInputTypes : uint8
{
	None,
	KeyboardOnly,
	KeyboardAndMouse,
};

UCLASS()
class CLIENT_API AUserInputController : public APlayerController
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	AGameCharacter* m_TargetCharacter;

	UPROPERTY(VisibleAnywhere)
	AGameCamera* m_TargetGameCamera;

	float m_fCheckLandRemainTime;

public:
	AUserInputController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	void SetCamera(AGameCamera* cam);
	AGameCharacter* GetPlayerCharacter();

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	void OnInput_AxisMoveX(float scale);
	void OnInput_AxisMoveY(float scale);
	void OnInput_AxisLookX(float scale);
	void OnInput_AxisLookY(float scale);

	void OnInput_KeyDownAttack00();
	void OnInput_KeyUpAttack00();

	void OnInput_KeyDownAttack01();
	void OnInput_KeyUpAttack01();

	void OnInput_KeyDownJump();
	void OnInput_KeyUpJump();

	void OnInput_KeyDownDash();
	void OnInput_KeyUpDash();
	
	void OnInput_KeyDownLookNearTarget();
	void OnInput_KeyUpLookNearTarget();

	void OnInput_Escape();

	void ClearKey(const bool& bSave);
	void SaveKey();
	void AddKey_PlayCtrl(const EUserInputTypes& inputTypes, const bool& bReset,  const bool& bSave);

	template<class UserClass>
	void AddKey(const FKey& key, UserClass* Object, typename FInputActionHandlerSignature::TUObjectMethodDelegate< UserClass >::FMethodPtr Func, const bool& bSave);
	void SetMouseEnable(const bool& bEnable);
};
