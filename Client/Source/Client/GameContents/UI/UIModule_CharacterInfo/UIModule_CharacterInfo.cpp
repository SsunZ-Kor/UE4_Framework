#include "UIModule_CharacterInfo.h"
#include "../../../Framework/GameCharacter/GameCharacter.h"

void UUIModule_CharacterInfo::Init(AGameCharacter* pCharacter)
{
	if (!pCharacter)
		return;

	// 씬 캡처 스폰 및 위치
	auto pSceneCapture = GetSceneCapture();

	FAttachmentTransformRules attachmentRules =
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	
	pSceneCapture->AttachToActor(pCharacter, attachmentRules, TEXT("head"));
	pSceneCapture->SetActorRelativeLocation(FVector::ForwardVector * 50);
	pSceneCapture->SetActorRelativeRotation(FRotator(0.f, 180.f, 0.f));

	// 캡처 설정
	auto pCaptureComp = pSceneCapture->GetCaptureComponent2D();
	
	pCaptureComp->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	pCaptureComp->CaptureSource = ESceneCaptureSource::SCS_SceneColorSceneDepth; // 머티리얼 뎁스 알파처리
	pCaptureComp->ShowOnlyActors.Add(pCharacter);
}

void UUIModule_CharacterInfo::OnUIModuleClosed()
{
	Super::OnUIModuleClosed();

	ReleaseSceneCapture();
}

ASceneCapture2D* UUIModule_CharacterInfo::GetSceneCapture()
{
	if (IsValid(m_pSceneCapture))
		return m_pSceneCapture;

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	m_pSceneCapture = GetWorld()->SpawnActor<ASceneCapture2D>(param);
	m_pSceneCapture->GetCaptureComponent2D()->TextureTarget = m_TexTarget;
	return m_pSceneCapture;
}

void UUIModule_CharacterInfo::ReleaseSceneCapture()
{
	if (IsValid(m_pSceneCapture))
	{
		m_pSceneCapture->Destroy();
		m_pSceneCapture = nullptr;
	}
}
