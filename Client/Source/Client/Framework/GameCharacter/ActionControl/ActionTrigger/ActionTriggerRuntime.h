// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UActionData;

class CLIENT_API ActionTriggerRuntime
{
	const struct FActionTriggerData& m_Data;
	class UActionRuntime* m_NextActionRuntime;

	bool m_IsSameAsActionStartTime;
	bool m_IsSameAsActionEndTime;

public:
	ActionTriggerRuntime(const FActionTriggerData& data, UActionRuntime* nextActionRuntime, UActionData* pActionData);
	~ActionTriggerRuntime();


	const FActionTriggerData& GetData();
	UActionRuntime* GetNextActionRuntime();
	bool HasNextActionRuntime();
	bool CheckTime(const float& fElapsedTime_Action, const float& fLength_Action) const;
};
