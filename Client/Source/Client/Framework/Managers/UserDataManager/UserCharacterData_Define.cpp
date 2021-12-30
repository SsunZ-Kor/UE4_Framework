#include "UserCharacterData_Define.h"

#include "Client/Framework/Managers/Managers.h"

UserItemInfo::UserItemInfo()
{
	m_nKey = 0;
	m_pItemData = nullptr;
	m_nCount = 0;
}

UserItemInfo::~UserItemInfo()
{
}

void UserItemInfo::Init(uint32 nKey, const int& itemDataId, const int& nCount)
{
	auto pItemData = Managers::GameData->GetData<CItemData>(itemDataId);
	Init(nKey, pItemData, nCount);
}

void UserItemInfo::Init(uint32 nKey, const CItemData*& pItemData, const int& nCount)
{
	m_nKey = nKey;
	m_pItemData = pItemData;
	m_nCount = nCount;
}

const CItemData* const& UserItemInfo::GetData() const
{
	return m_pItemData;
}

const int& UserItemInfo::GetCount() const
{
	return m_nCount;
}

void UserItemInfo::SetCount(const int& nCount)
{
	m_nCount = nCount;
}