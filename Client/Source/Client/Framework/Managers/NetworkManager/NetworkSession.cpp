#include "NetworkSession.h"

#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"


NetworkSession::NetworkSession()
	: m_pSocket(nullptr)
{
	FMemory::Memzero(m_SendPacket, sizeof(m_SendPacket));
	FMemory::Memzero(m_RecvPacket, sizeof(m_RecvPacket));
}

NetworkSession::~NetworkSession()
{
}

bool NetworkSession::ConnectSession(const FString& ip, const uint32& port)
{
	// 세션 정리
	CloseSession();

	// Ip 세팅
	auto pSocketSys = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

	FIPv4Address ipAddr;
	FIPv4Address::Parse(ip, ipAddr);

	TSharedPtr<FInternetAddr> pAddr = pSocketSys->CreateInternetAddr();
	pAddr->SetIp(ipAddr.Value);
	pAddr->SetPort(port);

	// Socket 연결
	m_pSocket = pSocketSys->CreateSocket(NAME_Stream, TEXT("default"), false);
	if (!m_pSocket->Connect(*pAddr))
	{
		pSocketSys->DestroySocket(m_pSocket);
		m_pSocket = nullptr;
		return false;
	}

	return true;
}

void NetworkSession::CloseSession()
{
	// Socket 정리
	if (m_pSocket)
	{
		m_pSocket->Close();

		auto pSocketSys = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
		pSocketSys->DestroySocket(m_pSocket);

		m_pSocket = nullptr;

		FMemory::Memzero(m_SendPacket, sizeof(m_SendPacket));
		FMemory::Memzero(m_RecvPacket, sizeof(m_RecvPacket));
	}
}

bool NetworkSession::Write(const int32& protocol, uint8* const& pPacket, int32& length)
{
	PacketStream	stream;
	stream.SetBuffer(m_SendPacket);

	stream.Write(&protocol, sizeof(int32));
	stream.Write(&length, sizeof(int32));
	stream.Write(pPacket, length);

	return m_pSocket->Send(m_SendPacket, stream.GetLength(), length);
}

bool NetworkSession::Read(int32& protocol, uint8* const& pPacket, int32& length)
{
	bool bResult = m_pSocket->Recv(m_RecvPacket, PACKET_SIZE, length, ESocketReceiveFlags::None);

	if (!bResult || length <= 0)
		return false;

	PacketStream	stream;
	stream.SetBuffer(m_RecvPacket);

	stream.Read(&protocol, sizeof(int32));
	stream.Read(&length, sizeof(int32));
	stream.Read(pPacket, length);

	return true;
}

PacketStream::PacketStream()
	: m_Buffer(nullptr), m_Length(0)
{
}

PacketStream::~PacketStream()
{
}

void PacketStream::SetBuffer(uint8* Buffer)
{
	m_Buffer = Buffer;
}

const int32& PacketStream::GetLength() const
{
	return m_Length;
}

void PacketStream::Read(void* Data, const int32& Size)
{
	FMemory::Memcpy(Data, m_Buffer + m_Length, Size);
	m_Length += Size;
}

void PacketStream::Write(const void* Data, const int32& Size)
{
	FMemory::Memcpy(m_Buffer + m_Length, Data, Size);
	m_Length += Size;
}

void PacketStream::WriteTo(const void* Data, const int32& Start, const int32& Size)
{
	FMemory::Memcpy(m_Buffer + Start, Data, Size);
	if (m_Length < Start + Size)
		m_Length = Start + Size;
}

void PacketStream::WriteZero(const int32& Size)
{
	FMemory::Memzero(m_Buffer + m_Length, Size);
	m_Length += Size;
}

