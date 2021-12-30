#include "BGMManager.h"

#include "Client/Framework/Managers/Managers.h"
#include "Client/Framework/Managers/LocalDataManager/SaveGame_Settings.h"
#include "Kismet/GameplayStatics.h"

float UAudioModule::GetVolumeSetting()
{
	const auto& settings = *(Managers::LocalData->Settings);
	return settings.bBGM_Play ? settings.fBGM_Volume : 0.f;
}


void UAudioModule::BeginDestroy()
{
	UObject::BeginDestroy();

	if (m_pAudioComp)
	{
		m_pAudioComp->DestroyComponent();
		m_pAudioComp = nullptr;
	}
}

void UAudioModule::Init()
{
	m_pAudioComp = nullptr;
	m_bTickEnable = false;
}

const bool& UAudioModule::GetTickEnable()
{
	return m_bTickEnable;
}

const bool& UAudioModule::OnTick(const float fDeltaTime)
{
	if (!m_bTickEnable)
		return m_bTickEnable;

	m_fVolume += m_fFadePerSec * fDeltaTime;

	if (m_fFadePerSec > 0.f)
	{
		if (m_fVolume >= 1.f)
		{
			m_bTickEnable = false;
			m_fVolume = 1.f;
			m_pAudioComp->SetVolumeMultiplier(GetVolumeSetting());
			return m_bTickEnable;
		}
	}
	else
	{
		if (m_fVolume <= 0.f)
		{
			m_bTickEnable = false;
			m_fVolume = 0.f;
			m_pAudioComp->SetVolumeMultiplier(0.f);
			m_pAudioComp->Stop();
			m_pAudioComp->SetSound(nullptr);
			return m_bTickEnable;
		}
	}

	m_pAudioComp->SetVolumeMultiplier(m_fVolume * GetVolumeSetting());

	return m_bTickEnable;
}

void UAudioModule::Play(USoundBase* pSound, const float& fFadeTime)
{
	if (!pSound)
		return;

	if (!m_pAudioComp)
	{
		m_pAudioComp = UGameplayStatics::CreateSound2D(
			Managers::GameInst,
			pSound,
			1.f,
			1.f,
			0.f,
			nullptr,
			true,
			false
			);

		m_pAudioComp->SetSound(nullptr);
	}

	if (fFadeTime <= 0.f)
	{
		m_bTickEnable = false;
		m_fVolume = 1.f;

		if (pSound != m_pAudioComp->Sound)
		{
			m_pAudioComp->SetSound(pSound);
			m_pAudioComp->Play();
		}

		m_pAudioComp->SetVolumeMultiplier(UAudioModule::GetVolumeSetting());
	}
	else
	{
		m_bTickEnable = true;
		m_fFadePerSec = 1.f / fFadeTime;

		if (pSound != m_pAudioComp->Sound)
		{
			m_fVolume = 0.f;
			m_pAudioComp->SetVolumeMultiplier(0.f);

			m_pAudioComp->SetSound(pSound);
			m_pAudioComp->Play();
		}
	}
}

void UAudioModule::Stop(const float& fFadeTime)
{
	if (!(m_pAudioComp && m_pAudioComp->Sound))
		return;

	if (fFadeTime <= 0.f)
	{
		m_bTickEnable = false;
		m_fVolume = 0.f;

		m_pAudioComp->Stop();
		m_pAudioComp->SetSound(nullptr);
	}
	else
	{
		m_bTickEnable = true;
		m_fFadePerSec = -1.f / fFadeTime;
	}
}

USoundBase* UAudioModule::GetSound()
{
	return m_pAudioComp ? m_pAudioComp->Sound : nullptr;
}

void UBGMManager::BeginDestroy()
{
	UObject::BeginDestroy();

	if (m_pAudio_Main)
	{
		auto pDel = m_pAudio_Main;
		m_pAudio_Main = nullptr;
		pDel->ConditionalBeginDestroy();
	}

	if (m_pAudio_Out)
	{
		auto pDel = m_pAudio_Out;
		m_pAudio_Out = nullptr;
		pDel->ConditionalBeginDestroy();
	}
}

void UBGMManager::Init()
{
	m_pAudio_Main = NewObject<UAudioModule>();
	m_pAudio_Main->Init();
	m_pAudio_Out = NewObject<UAudioModule>();
	m_pAudio_Out->Init();
}

void UBGMManager::Play(USoundBase* pSound, const float& fInTime, const float& fOutTime)
{
	// 유효성 체크 및 현재 재생중인 사운드 체크
	if (!pSound || m_pAudio_Main->GetSound() == pSound)
		return;
	
	auto temp = m_pAudio_Main;
	m_pAudio_Main = m_pAudio_Out;
	m_pAudio_Out = temp;

	m_pAudio_Main->Play(pSound, fInTime);
	m_pAudio_Out->Stop(fOutTime);
}

void UBGMManager::Stop(const float& fOutTime)
{
	auto temp = m_pAudio_Main;
	m_pAudio_Main = m_pAudio_Out;
	m_pAudio_Out = temp;

	m_pAudio_Main->Stop(fOutTime);
	m_pAudio_Out->Stop(fOutTime);
}

void UBGMManager::OnGameModeTick(const float& fDeltaTime)
{
	m_pAudio_Main->OnTick(fDeltaTime);
	m_pAudio_Out->OnTick(fDeltaTime);
}
