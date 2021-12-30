// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkThread.h"

#include "NetworkQueue.h"
#include "NetworkSession.h"

NetworkThread::NetworkThread()
	: m_pSession(nullptr), m_pQueue(nullptr), m_bRun(false)
{
}

NetworkThread::~NetworkThread()
{
	m_pSession = nullptr;
	m_pQueue = nullptr;
}

void NetworkThread::SetSession(NetworkSession* const& pSession, NetworkQueue* const& receiveQueue)
{
	m_pSession = pSession;
	m_pQueue = receiveQueue;
}

uint32 NetworkThread::Run()
{
	m_bRun = true;
	while (m_bRun)
	{
		int32 protocol = -1;
		uint8 packet[PACKET_SIZE] = {};
		int32 length = 0;
		
		if (m_pSession->Read(protocol, packet, length))
			m_pQueue->Push(protocol, packet, length);
	}
	
	return 0;
}

void NetworkThread::Stop()
{
	FRunnable::Stop();
	m_bRun = false;
}

void NetworkThread::Exit()
{
	FRunnable::Exit();
	m_bRun = false;
}