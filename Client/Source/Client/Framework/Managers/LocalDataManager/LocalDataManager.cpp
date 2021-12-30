#include "LocalDataManager.h"
#include "SaveGame_Settings.h"
#include "Kismet/GameplayStatics.h"

void LocalDataManager::Init()
{
	LoadSettings();
}

bool LocalDataManager::LoadSettings()
{
	if (UGameplayStatics::DoesSaveGameExist("Settings", 0))
	{
		Settings = Cast<USaveGame_Settings>(UGameplayStatics::LoadGameFromSlot("Settings", 0));
	}
	else
	{
		Settings = CreateSettings();
	}

	return true;
}

void LocalDataManager::SaveSettings()
{
	if (!Settings)
		Settings = CreateSettings();

	UGameplayStatics::SaveGameToSlot(Settings, "Settings", 0);
}

USaveGame_Settings* LocalDataManager::CreateSettings()
{
	auto result = NewObject<USaveGame_Settings>();
	result->bBGM_Play = true;
	result->fBGM_Volume = 1.f;
	result->bSFX_Play = true;
	result->fSFX_Volume = 1.f;

	return result;
}