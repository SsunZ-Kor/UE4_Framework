#include "UserCharacterData.h"

#include "UserCharacterData_Define.h"
#include "Client/Framework/Managers/Managers.h"

UserCharacterData::UserCharacterData()
{
}

UserCharacterData::~UserCharacterData()
{
	for(auto& pair : m_map_UserItemInfo)
		delete pair.Value;

	m_map_UserItemInfo.Empty();
}

TMap<uint32, UserItemInfo*>& UserCharacterData::GetAllItemInfo()
{
	return m_map_UserItemInfo;
}

UserItemInfo* UserCharacterData::GetItemInfo(const uint32& key)
{
	if (m_map_UserItemInfo.Contains(key))
		return m_map_UserItemInfo[key];

	return nullptr;
}

UserItemInfo* UserCharacterData::AddItemInfo(const uint32& key, const int& itemDataId, const int& nCount)
{
	auto pItemData = Managers::GameData->GetData<CItemData>(itemDataId);
	if (pItemData)
	{
		auto pNewUserItemInfo = new UserItemInfo();
		pNewUserItemInfo->Init(key, pItemData, nCount);
		if (m_map_UserItemInfo.Contains(key))
			m_map_UserItemInfo.Remove(key);

		m_map_UserItemInfo.Add(key, pNewUserItemInfo);
		return pNewUserItemInfo;
	}

	return nullptr;
}

void UserCharacterData::RemoveItemInfo(uint32 key)
{
	if (m_map_UserItemInfo.Contains(key))
		m_map_UserItemInfo.Remove(key);
}
