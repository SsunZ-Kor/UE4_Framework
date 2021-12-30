// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Client/Framework/ClientGameBase.h"
#include "NetworkDefine.h"

class NetworkSession;
class NetworkQueue;

class CLIENT_API NetworkThread : public FRunnable
{
private:
	NetworkSession* m_pSession;
	NetworkQueue* m_pQueue;
	bool m_bRun;
	
public:
	NetworkThread();
	virtual ~NetworkThread() override;

public:
	void SetSession(NetworkSession* const& pSession, NetworkQueue* const& receiveQueue);
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
};