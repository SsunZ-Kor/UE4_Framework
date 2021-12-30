#include "NetworkManager.h"

#include "NetworkModule.h"


NetworkManager::NetworkManager()
	: m_pSessionMoudle_Chat(nullptr)
{
}

NetworkManager::~NetworkManager()
{
	if(m_pSessionMoudle_Chat)
	{
		m_pSessionMoudle_Chat->Close();
		delete m_pSessionMoudle_Chat;
		m_pSessionMoudle_Chat = nullptr;
	}
}

void NetworkManager::Init()
{
	//if (!m_pSessionMoudle_Chat)
	//{
	//	m_pSessionMoudle_Chat = new NetworkModule(IP_ADDR_CHAT, IP_PORT_CHAT);
	//	m_pSessionMoudle_Chat->Connect();
	//}
}

void NetworkManager::OnGameModeTick()
{
	// 메인스레드에서 처리하도록 한다.
	if (m_pSessionMoudle_Chat)
		m_pSessionMoudle_Chat->ExecuteReceive();
}