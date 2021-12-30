// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkQueue.h"

NetworkQueue::NetworkQueue()
	: m_Head(0), m_Tail(0), m_Size(0)
{
}

NetworkQueue::~NetworkQueue()
{
}

void NetworkQueue::Push(const int32& Protocol, uint8* const& Packet, const int32& Length)
{
	// 동시 참조 방지용 락
	FScopeLock lock(&m_Crt);

	int32 Tail = (m_Tail + 1) % 200;
	if (Tail == m_Head)
		return;

	m_Queue[Tail].Protocol = Protocol;
	m_Queue[Tail].Length = Length;

	FMemory::Memset(m_Queue[Tail].Packet, 0, PACKET_SIZE);
	FMemory::Memcpy(m_Queue[Tail].Packet, Packet, Length);

	m_Tail = Tail;
	++m_Size;
}

bool NetworkQueue::Pop(int32& Protocol, uint8* Packet, int32& Length)
{
	// 동시 참조 방지용 락
	FScopeLock lock(&m_Crt);

	if (IsEmpty())
		return false;

	int32 Head = (m_Head + 1) % 200;

	Protocol = m_Queue[Head].Protocol;
	Length = m_Queue[Head].Length;

	FMemory::Memcpy(Packet, m_Queue[Head].Packet, Length);

	m_Head = Head;
	--m_Size;

	return true;
}

bool NetworkQueue::IsEmpty() const
{
	return m_Size == 0;
}

void NetworkQueue::Empty()
{
	m_Head = 0;
	m_Tail = 0;
	m_Size = 0;
}

int32 NetworkQueue::Size()
{
	return m_Size;
}
