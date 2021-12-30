#pragma once

#include <functional>

#include "Client/Framework/ClientGameBase.h"
#include "NetworkDefine.h"

class NetworkSession;
class NetworkThread;
class NetworkQueue;

class NetworkModule
{
private:
	FString m_Ip;
	uint32 m_Port;

	NetworkSession* m_pSession;
	NetworkThread* m_pReceiveThread;
	FRunnableThread* m_pRunnableThread;
	NetworkQueue* m_pQueue;

	bool m_bIsConnected;

	//TMap<int, std::function<void(PacketBase)>> map_StaticReceiveCall;
	//TMap<int, std::function<void(PacketBase)>> m_map_DynamicReceiveCall;

public:
	NetworkModule(const FString& ip, const uint32& port);
	~NetworkModule();

	const bool& Connect(const bool& bForcedReconnect = false);
	void Close();

	void Send(const int32& protocol, uint8* const& pPacket, int32& length);
	void ExecuteReceive();
};
