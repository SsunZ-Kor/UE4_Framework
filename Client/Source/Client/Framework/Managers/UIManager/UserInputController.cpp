#include "UserInputController.h"

#include "Client/Framework/Camera/GameCamera.h"
#include "Client/Framework/GameCharacter/GameCharacter.h"
#include "Client/Framework/GameCharacter/BrainControl/BrainController.h"
#include "Client/Framework/Managers/Managers.h"
#include "Client/GameContents/SpawnSystem/SpawnSystem.h"

AUserInputController::AUserInputController(const FObjectInitializer& ObjectInitializer)
	: APlayerController(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	m_fCheckLandRemainTime = 0.5f;
}

void AUserInputController::SetCamera(AGameCamera* cam)
{
	m_TargetGameCamera = cam;
	if (m_TargetGameCamera)
		SetViewTarget(m_TargetGameCamera);
}

AGameCharacter* AUserInputController::GetPlayerCharacter()
{
	return m_TargetCharacter;
}

void AUserInputController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// Axis는 영구할당 한다. 삭제 메서드가 없음....
	InputComponent->BindAxis("AxisMoveX", this, &AUserInputController::OnInput_AxisMoveX);
	InputComponent->BindAxis("AxisMoveY", this, &AUserInputController::OnInput_AxisMoveY);
	InputComponent->BindAxis("AxisLookX", this, &AUserInputController::OnInput_AxisLookX);
	InputComponent->BindAxis("AxisLookY", this, &AUserInputController::OnInput_AxisLookY);
}

void AUserInputController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	m_TargetCharacter = Cast<AGameCharacter>(InPawn);
	
	if (m_TargetCharacter && IsValid(m_TargetCharacter))
	{
		m_TargetCharacter->GetBrainCtrl()->SetOrderByUserInput(true);
		m_TargetCharacter->GetBrainCtrl()->StopAI();
		m_TargetCharacter->RefreshCollisionProfile();
		AGameCharacter::AllyInfo->SetPlayerTeamInfo(m_TargetCharacter->GetTeamInfo());
	}
}

void AUserInputController::OnUnPossess()
{
	Super::OnUnPossess();

	if (m_TargetCharacter && IsValid(m_TargetCharacter))
	{
		// AI로 다시 빙의시킨다.
		m_TargetCharacter->GetBrainCtrl()->Possess(m_TargetCharacter);
		
		m_TargetCharacter->GetBrainCtrl()->SetOrderByUserInput(false);
		m_TargetCharacter->GetBrainCtrl()->StartAI();
		m_TargetCharacter->RefreshCollisionProfile();
		AGameCharacter::AllyInfo->SetPlayerTeamInfo(nullptr);
	}

	m_TargetCharacter = nullptr;
}

void AUserInputController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Managers::World -> 현재 어느 위치에 있는지 체크
	m_fCheckLandRemainTime -= DeltaSeconds;
	if (Managers::IsInit() && m_TargetCharacter && m_fCheckLandRemainTime <= 0.f)
	{
		m_fCheckLandRemainTime = 0.5f;
		Managers::World->CheckAndLoadLand(m_TargetCharacter);
	}

	if (WasInputKeyJustPressed(EKeys::One))
	{
		auto pSound = Managers::Asset->LoadObj<USoundBase>(TEXT("SoundWave'/Game/GameContents/BGMs/BGMSample_00.BGMSample_00'"));
		if (pSound)
		{
			Managers::BGM->Play(pSound, 5.f, 5.f);
			LOG_ERROR(TEXT("BGM 00"));
		}
	}
	else if(WasInputKeyJustPressed(EKeys::Two))
	{
		auto pSound = Managers::Asset->LoadObj<USoundBase>(TEXT("SoundWave'/Game/GameContents/BGMs/BGMSample_01.BGMSample_01'"));
		if (pSound)
		{
			Managers::BGM->Play(pSound, 5.f, 5.f);
			LOG_ERROR(TEXT("BGM 01"));
		}
	}
}

void AUserInputController::OnInput_AxisMoveX(float scale)
{
	if (m_TargetCharacter)
		m_TargetCharacter->GetBrainCtrl()->OnInput_MoveAxisX(scale);
}

void AUserInputController::OnInput_AxisMoveY(float scale)
{
	if (m_TargetCharacter)
		m_TargetCharacter->GetBrainCtrl()->OnInput_MoveAxisY(scale);
}

void AUserInputController::OnInput_AxisLookX(float scale)
{
	if (m_TargetGameCamera)
	{
		m_TargetGameCamera->OnInput_AxisLookX(scale);
		if (m_TargetCharacter)
			m_TargetCharacter->GetBrainCtrl()->SetLookInfo(m_TargetGameCamera->GetActorRotation().Quaternion());
	}
}

void AUserInputController::OnInput_AxisLookY(float scale)
{
	if (m_TargetGameCamera)
	{
		m_TargetGameCamera->OnInput_AxisLookY(scale);
	}
}

void AUserInputController::OnInput_KeyDownAttack00()
{
	if (m_TargetCharacter)
		m_TargetCharacter->GetBrainCtrl()->OnInput_Key(ETriggerEventTypes::Attack00_Down);
}

void AUserInputController::OnInput_KeyUpAttack00()
{
	if (m_TargetCharacter)
		m_TargetCharacter->GetBrainCtrl()->OnInput_Key(ETriggerEventTypes::Attack00_Up);
}

void AUserInputController::OnInput_KeyDownAttack01()
{
	if (m_TargetCharacter)
		m_TargetCharacter->GetBrainCtrl()->OnInput_Key(ETriggerEventTypes::Attack01_Down);
}

void AUserInputController::OnInput_KeyUpAttack01()
{
	if (m_TargetCharacter)
		m_TargetCharacter->GetBrainCtrl()->OnInput_Key(ETriggerEventTypes::Attack01_Up);
}

void AUserInputController::OnInput_KeyDownJump()
{
	if (m_TargetCharacter)
		m_TargetCharacter->GetBrainCtrl()->OnInput_Key(ETriggerEventTypes::Jump_Down);
}

void AUserInputController::OnInput_KeyUpJump()
{
	if (m_TargetCharacter)
		m_TargetCharacter->GetBrainCtrl()->OnInput_Key(ETriggerEventTypes::Jump_Up);
}

void AUserInputController::OnInput_KeyDownDash()
{
	if (m_TargetCharacter)
		m_TargetCharacter->GetBrainCtrl()->OnInput_Key(ETriggerEventTypes::Dash_Down);
}

void AUserInputController::OnInput_KeyUpDash()
{
	if (m_TargetCharacter)
		m_TargetCharacter->GetBrainCtrl()->OnInput_Key(ETriggerEventTypes::Dash_Up);
}

void AUserInputController::OnInput_KeyDownLookNearTarget()
{
	if (m_TargetCharacter && m_TargetGameCamera)
	{
		// Todo
	}
}

void AUserInputController::OnInput_KeyUpLookNearTarget()
{
	if (m_TargetCharacter && m_TargetGameCamera)
	{
		// Todo
	}
}

void AUserInputController::OnInput_Escape()
{
	Managers::UI->CloseLastWindow();
}

void AUserInputController::ClearKey(const bool& bSave)
{
	auto pInput =  UInputSettings::GetInputSettings();
	if (!pInput)
	{
		LOG_ERROR(TEXT("UInputSettings is NULL"));
		return;
	}

	// 기존 맵핑 제거
	auto pActionMappings = const_cast<TArray<FInputActionKeyMapping>*>(&pInput->GetActionMappings());
	pActionMappings->Empty(pActionMappings->Num());
	auto pAxisMappings = const_cast<TArray<FInputAxisKeyMapping>*>(&pInput->GetAxisMappings());
	pAxisMappings->Empty(pActionMappings->Num());

	// 기존 바인딩 제거
	InputComponent->ClearActionBindings();

	// ESC는 무조건 할당
	auto name_Escape = EKeys::Escape.GetFName();
	pInput->AddActionMapping(FInputActionKeyMapping(name_Escape, EKeys::Escape), false);
	InputComponent->BindAction(name_Escape, EInputEvent::IE_Released,  this, &AUserInputController::OnInput_Escape);

	// 저장
	if (bSave)
	{
		pInput->ForceRebuildKeymaps();
		pInput->SaveKeyMappings();
	}
}

void AUserInputController::SaveKey()
{
	auto pInput =  UInputSettings::GetInputSettings();
	if (!pInput)
	{
		LOG_ERROR(TEXT("UInputSettings is NULL"));
		return;
	}

	pInput->ForceRebuildKeymaps();
	pInput->SaveKeyMappings();
}

void AUserInputController::AddKey_PlayCtrl(const EUserInputTypes& inputTypes, const bool& bReset = true, const bool& bSave = true)
{
	auto pInput =  UInputSettings::GetInputSettings();
	if (!pInput)
	{
		LOG_ERROR(TEXT("UInputSettings is NULL"));
		return;
	}

	if (bReset)
		ClearKey(false);

	// 타입별 세팅
	switch (inputTypes)
	{
	case EUserInputTypes::None:
		{
			// 저장하고 탈출
			if (bSave)
			{
				pInput->ForceRebuildKeymaps();
				pInput->SaveKeyMappings();
			}
		}
		return;
	case EUserInputTypes::KeyboardOnly:
		{
			// KeyboardOnly :: Axis
			pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisMoveX"), EKeys::Right, 1), false);
			pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisMoveX"), EKeys::Left, -1), false);
			pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisMoveY"), EKeys::Up, 1), false);
			pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisMoveY"), EKeys::Down, -1), false);
			pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisLookX"), EKeys::E, 1), false);
			pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisLookX"), EKeys::Q, -1), false);
			pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisLookY"), EKeys::T, 1), false);
			pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisLookY"), EKeys::G, -1), false);

			// KeyboardOnly :: Action
			pInput->AddActionMapping(FInputActionKeyMapping(FName("Attack00"), EKeys::D), false);
			pInput->AddActionMapping(FInputActionKeyMapping(FName("Attack01"), EKeys::F), false);
			pInput->AddActionMapping(FInputActionKeyMapping(FName("Jump"), EKeys::S), false);
			pInput->AddActionMapping(FInputActionKeyMapping(FName("Dash"), EKeys::A), false);
			pInput->AddActionMapping(FInputActionKeyMapping(FName("LookNearTarget"), EKeys::SpaceBar), false);
		}
		break;
	case EUserInputTypes::KeyboardAndMouse:
		{
			// KeyboardAndMouse :: Axis
			pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisMoveX"), EKeys::D, 1), false);
			pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisMoveX"), EKeys::A, -1), false);
			pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisMoveY"), EKeys::W, 1), false);
			pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisMoveY"), EKeys::S, -1), false);
			pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisLookX"), EKeys::MouseX, 1), false);
			pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisLookY"), EKeys::MouseY, 1), false);

			// KeyboardAndMouse :: Action
			pInput->AddActionMapping(FInputActionKeyMapping(FName("Attack00"), EKeys::LeftMouseButton), false);
			pInput->AddActionMapping(FInputActionKeyMapping(FName("Attack01"), EKeys::RightMouseButton), false);
			pInput->AddActionMapping(FInputActionKeyMapping(FName("Jump"), EKeys::LeftShift), false);
			pInput->AddActionMapping(FInputActionKeyMapping(FName("Dash"), EKeys::SpaceBar), false);
		}
		break;
	}

	// 조이스틱은 항상 포함
	
	// 조이스틱 :: Axis
	pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisMoveX"), EKeys::Gamepad_LeftX, 1), false);
	pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisMoveY"), EKeys::Gamepad_LeftY, 1), false);
	pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisLookX"), EKeys::Gamepad_RightX, 1), false);
	pInput->AddAxisMapping(FInputAxisKeyMapping(FName("AxisLookY"), EKeys::Gamepad_RightY, 1), false);

	// 조이스틱 :: Action
	pInput->AddActionMapping(FInputActionKeyMapping(FName("Attack00"), EKeys::Gamepad_FaceButton_Left), false);
	pInput->AddActionMapping(FInputActionKeyMapping(FName("Attack01"), EKeys::Gamepad_FaceButton_Top), false);
	pInput->AddActionMapping(FInputActionKeyMapping(FName("Jump"), EKeys::Gamepad_FaceButton_Right), false);
	pInput->AddActionMapping(FInputActionKeyMapping(FName("Dash"), EKeys::Gamepad_FaceButton_Bottom), false);
	pInput->AddActionMapping(FInputActionKeyMapping(FName("LookNearTarget"), EKeys::Gamepad_RightShoulder), false);

	// 키 바인딩
	InputComponent->BindAction("Attack00", EInputEvent::IE_Pressed,  this, &AUserInputController::OnInput_KeyDownAttack00	);
	InputComponent->BindAction("Attack00", EInputEvent::IE_Released, this, &AUserInputController::OnInput_KeyUpAttack00	);

	InputComponent->BindAction("Attack01", EInputEvent::IE_Pressed,  this, &AUserInputController::OnInput_KeyDownAttack01	);
	InputComponent->BindAction("Attack01", EInputEvent::IE_Released, this, &AUserInputController::OnInput_KeyUpAttack01	);

	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed,  this, &AUserInputController::OnInput_KeyDownJump		);
	InputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AUserInputController::OnInput_KeyUpJump		);

	InputComponent->BindAction("Dash", EInputEvent::IE_Pressed,  this, &AUserInputController::OnInput_KeyDownDash	);
	InputComponent->BindAction("Dash", EInputEvent::IE_Released, this, &AUserInputController::OnInput_KeyUpDash );

	InputComponent->BindAction("LookNearTarget", EInputEvent::IE_Pressed, this, &AUserInputController::OnInput_KeyDownLookNearTarget);
	InputComponent->BindAction("LookNearTarget", EInputEvent::IE_Released, this, &AUserInputController::OnInput_KeyUpLookNearTarget);

	// 저장
	if (bSave)
	{
		pInput->ForceRebuildKeymaps();
		pInput->SaveKeyMappings();
	}
}

void AUserInputController::SetMouseEnable(const bool& bEnable)
{
	if (bEnable)
		SetInputMode(FInputModeGameAndUI());
	else
		SetInputMode(FInputModeGameOnly());

	SetShowMouseCursor(bEnable);
}

template <class UserClass>
void AUserInputController::AddKey(const FKey& key, UserClass* Object, typename FInputActionHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr Func, const bool& bSave = true)
{
	auto pInput =  UInputSettings::GetInputSettings();
	if (!pInput)
	{
		LOG_ERROR(TEXT("UInputSettings is NULL"));
		return;
	}

	auto name = key.GetFName();

	// 세팅 & 저장
	pInput->AddActionMapping(FInputActionKeyMapping(name, key), false);
	if (bSave)
	{
		pInput->ForceRebuildKeymaps();
		pInput->SaveKeyMappings();
	}

	// 키 바인딩
	InputComponent->BindAction(name, EInputEvent::IE_Pressed, Object, Func);
};