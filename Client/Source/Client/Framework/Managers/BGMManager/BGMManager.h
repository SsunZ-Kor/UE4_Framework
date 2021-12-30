#pragma once

#include "Client/Framework/ClientGameBase.h"
#include "BGMManager.generated.h"

UCLASS()
class CLIENT_API UAudioModule : public UObject
{
	GENERATED_BODY()
	
	UPROPERTY()
	UAudioComponent* m_pAudioComp;

	bool m_bTickEnable;

	float m_fVolume;
	float m_fFadePerSec;

public:
	virtual void BeginDestroy() override;

public:
	void Init();
	const bool& GetTickEnable();
	const bool& OnTick(const float fDeltaTime);
	void Play(USoundBase* pSound, const float& fFadeTime);
	void Stop(const float& fFadeTime);

	USoundBase* GetSound();

private:
	static float GetVolumeSetting();
};

UCLASS()
class CLIENT_API UBGMManager : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	UAudioModule* m_pAudio_Main;
	UPROPERTY()
	UAudioModule* m_pAudio_Out;

public:
	virtual void BeginDestroy() override;
public:
	void Init();
	void Play(USoundBase* pSound, const float& fInTime, const float& fOutTime);
	void Stop(const float& fOutTime);
	void OnGameModeTick(const float& fDeltaTime);

};
