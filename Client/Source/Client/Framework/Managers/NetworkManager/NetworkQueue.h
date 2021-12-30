// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Client/Framework/ClientGameBase.h"
#include "NetworkDefine.h"

struct CLIENT_API NetworkData
{
	int32	Protocol;
	int32	Length;
	uint8	Packet[PACKET_SIZE];
	
	NetworkData()	:
		Protocol(-1),
		Length(0),
		Packet{}
	{
	}
};

class CLIENT_API NetworkQueue
{
private:
	FCriticalSection	m_Crt;

	// 설마.. 200개 이상 쌓이진 않겠지?
	NetworkData			m_Queue[200];
	int32				m_Head;
	int32				m_Tail;
	int32				m_Size;

public:
	NetworkQueue();
	~NetworkQueue();
	
public:
	void Push(const int32& Protocol, uint8* const& Packet,  const int32& Length);
	bool Pop(int32& Protocol, uint8* Packet, int32& Length);
	bool IsEmpty() const;
	void Empty();
	int32 Size();
};