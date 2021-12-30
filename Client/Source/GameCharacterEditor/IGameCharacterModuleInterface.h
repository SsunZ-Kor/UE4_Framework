#pragma once

#include "Modules/ModuleManager.h"

class IGameCharacterModuleListenerInterface
{
public:
	virtual ~IGameCharacterModuleListenerInterface() {};
	virtual void OnStartupModule() {};
	virtual void OnShutdownModule() {};
};

class IGameCharacterModuleInterface : public IModuleInterface
{
protected:
	TArray<TSharedRef<IGameCharacterModuleListenerInterface>> ModuleListeners;

public:
	virtual void StartupModule() override
	{
		if (!IsRunningCommandlet())
		{
			AddModuleListeners();
			for (int32 i = 0; i < ModuleListeners.Num(); ++i)
			{
				ModuleListeners[i]->OnStartupModule();
			}
		}
	}

	virtual void ShutdownModule() override
	{
		for (int32 i = 0; i < ModuleListeners.Num(); ++i)
		{
			ModuleListeners[i]->OnShutdownModule();
		}
	}

	virtual void AddModuleListeners() {};

};