// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionTriggerRuntime.h"
#include "ActionTriggerData.h"
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"

ActionTriggerRuntime::ActionTriggerRuntime(const FActionTriggerData& data, UActionRuntime* nextActionRuntime, UActionData* pActionData)
	: m_Data(data), m_NextActionRuntime(nextActionRuntime)
{
	m_IsSameAsActionStartTime = data.fStartTime < FLT_EPSILON;
	m_IsSameAsActionEndTime = FMath::Abs(data.fEndTime - pActionData->fLength) < FLT_EPSILON;
}

ActionTriggerRuntime::~ActionTriggerRuntime()
{
}

const FActionTriggerData& ActionTriggerRuntime::GetData()
{
	return m_Data;
}

UActionRuntime* ActionTriggerRuntime::GetNextActionRuntime()
{
	return m_NextActionRuntime;
}

bool ActionTriggerRuntime::HasNextActionRuntime()
{
	return m_NextActionRuntime != nullptr;
}

bool ActionTriggerRuntime::CheckTime(const float& fElapsedTime_Action, const float& fLength_Action) const
{
	// 시작 시간 체크
	return ((m_IsSameAsActionStartTime || m_Data.fStartTime <= fElapsedTime_Action)
			&& (m_IsSameAsActionEndTime || m_Data.fEndTime >= fElapsedTime_Action));
}