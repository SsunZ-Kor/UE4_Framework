#pragma once

#include "NetworkDefine.h"

class CLIENT_API NetworkSession
{
	FSocket* m_pSocket;
	uint8 m_RecvPacket[PACKET_SIZE];
	uint8 m_SendPacket[PACKET_SIZE];

public:
	NetworkSession();
	~NetworkSession();
	
	bool ConnectSession(const FString& ip, const uint32& port);
	void CloseSession();

	bool Write(const int32& protocol, uint8* const& pPacket, int32& length);
	bool Read(int32& protocol, uint8* const& pPacket, int32& length);
};

class CLIENT_API PacketStream
{
public:
	PacketStream();
	~PacketStream();

private:
	uint8* m_Buffer;
	int32 m_Length;

public:
	void SetBuffer(uint8* Buffer);
	const int32& GetLength() const;

public:
	void Read(void* Data, const int32& Size);
	void Write(const void* Data, const int32& Size);
	void WriteTo(const void* Data, const int32& Start, const int32& Size);
	void WriteZero(const int32& Size);
};
