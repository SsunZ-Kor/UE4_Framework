#include "NetworkModule.h"

#include "NetworkQueue.h"
#include "NetworkSession.h"
#include "NetworkThread.h"

NetworkModule::NetworkModule(const FString& ip, const uint32& port)
{
	m_Ip = ip;
	m_Port = port;
	m_pSession = new NetworkSession();
	m_pReceiveThread = new NetworkThread();
	m_pRunnableThread = nullptr;
	m_pQueue = new NetworkQueue();

	m_bIsConnected = false;
}

NetworkModule::~NetworkModule()
{
	// 세션을 닫는다. 참조가 있으니 삭제는 마지막에
	if (m_pSession)
		m_pSession->CloseSession();

	if (m_pRunnableThread)
	{
		m_pRunnableThread->Kill();
		m_pRunnableThread->WaitForCompletion();
		delete m_pRunnableThread;
		m_pRunnableThread = nullptr;
	}

	if (m_pReceiveThread)
	{
		// m_pRunnableThread->Kill();에서 Stop을 호출함
		//m_pReceiveThread->Stop();
		delete 	m_pReceiveThread;
		m_pReceiveThread = nullptr;
	}

	if (m_pSession)
	{
		delete m_pSession;
		m_pSession = nullptr;
	}

	if (m_pQueue)
	{
		delete m_pQueue;
		m_pQueue = nullptr;
	}
}

const bool& NetworkModule::Connect(const bool& bForcedReconnect)
{
	if (m_bIsConnected)
	{
		// 강제 리커넥션
		if (bForcedReconnect)
			Close();
		else
			return m_bIsConnected;
	}
	
	m_bIsConnected = m_pSession->ConnectSession(m_Ip, m_Port);
	if (m_bIsConnected)
	{
		m_pReceiveThread->SetSession(m_pSession, m_pQueue);
		m_pRunnableThread = FRunnableThread::Create(m_pReceiveThread, *FString::Printf(TEXT("Session / %s:%d"), *m_Ip, m_Port));
	}

	return m_bIsConnected;	
}

void NetworkModule::Close()
{
	if (!m_bIsConnected)
		return;
		
	m_bIsConnected = false;
	
	if (m_pSession)
		m_pSession->CloseSession();

	if (m_pRunnableThread)
	{
		m_pRunnableThread->Kill();
		m_pRunnableThread->WaitForCompletion();
		delete m_pRunnableThread;
		m_pRunnableThread = nullptr;
	}
}

void NetworkModule::Send(const int32& protocol, uint8* const& pPacket, int32& length)
{
	if (m_bIsConnected)
		m_pSession->Write(protocol, pPacket, length);
}

void NetworkModule::ExecuteReceive()
{
	if (!m_pQueue || m_pQueue->IsEmpty())
		return;

	// Todo :: Static or Dynamic RecevieCall Container
	// m_pQueue->Pop();
	// 클래스로 주고받고.. 구글 프로토콜 버프 비슷하게 구성하기엔 나에게 시간이 너무 없다.
	// 일단 여기서 멈추자
	// 통신 테스트는 완료
}
