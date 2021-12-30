// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ActionEventRuntimeBase.h"
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"

template<typename T>
class CLIENT_API ActionEventDurationRuntimeBase : public ActionEventRuntimeBase<T>
{
protected:
	TDoubleLinkedListEx<IActionEventRuntime*>::TDoubleLinkedListExNode* m_LlistNode;

	bool m_IsSameAsActionEndTime;

public:
	ActionEventDurationRuntimeBase();
	virtual ~ActionEventDurationRuntimeBase() override;

	virtual void Init(T& data, AGameCharacter* owner, UActionData* pActionData) override;
	virtual bool IsDuration() override;
	virtual float GetEndTime() override;
	virtual const bool IsSameAsActionEndTime() override;

	virtual TDoubleLinkedListEx<IActionEventRuntime*>::TDoubleLinkedListExNode* GetNode() override;
};

template<typename T>
ActionEventDurationRuntimeBase<T>::ActionEventDurationRuntimeBase()
{
	m_LlistNode = new TDoubleLinkedListEx<IActionEventRuntime*>::TDoubleLinkedListExNode(this);
}

template<typename T>
ActionEventDurationRuntimeBase<T>::~ActionEventDurationRuntimeBase()
{
	m_LlistNode->RemoveSelf();
	delete m_LlistNode;
}

template <typename T>
void ActionEventDurationRuntimeBase<T>::Init(T& Data, AGameCharacter* Owner, UActionData* pActionData)
{
	ActionEventRuntimeBase<T>::Init(Data, Owner, pActionData);

	m_IsSameAsActionEndTime = FMath::Abs(Data.fEndTime - pActionData->fLength) < FLT_EPSILON;
}

template<typename T>
bool ActionEventDurationRuntimeBase<T>::IsDuration()
{
	return true;
}

template<typename T>
float ActionEventDurationRuntimeBase<T>::GetEndTime()
{
	return m_pData->fEndTime;
}

template <typename T>
const bool ActionEventDurationRuntimeBase<T>::IsSameAsActionEndTime()
{
	return m_IsSameAsActionEndTime;
}

template<typename T>
TDoubleLinkedListEx<IActionEventRuntime*>::TDoubleLinkedListExNode* ActionEventDurationRuntimeBase<T>::GetNode()
{
	return m_LlistNode;
}

