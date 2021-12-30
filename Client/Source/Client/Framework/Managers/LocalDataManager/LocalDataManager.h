#pragma once

class USaveGame_Settings;

class LocalDataManager
{
public:
	USaveGame_Settings* Settings;

	void Init();

	bool LoadSettings();
	void SaveSettings();

private:
	USaveGame_Settings* CreateSettings();
};