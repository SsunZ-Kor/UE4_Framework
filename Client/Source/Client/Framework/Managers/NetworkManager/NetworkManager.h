#pragma once

#include "Client/Framework/ClientGameBase.h"
#include "NetworkDefine.h"

class NetworkModule;

class CLIENT_API NetworkManager
{
#define IP_ADDR_CHAT TEXT("127.0.0.1")
#define IP_PORT_CHAT 2000

private:
	NetworkModule* m_pSessionMoudle_Chat;

public:
	NetworkManager();
	~NetworkManager();
	
	void Init();
	void OnGameModeTick();
};