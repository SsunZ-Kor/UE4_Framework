#pragma once

class UserItemInfo;

class UserCharacterData
{
private:
	TMap<uint32, UserItemInfo*> m_map_UserItemInfo;
public:
	UserCharacterData();
	~UserCharacterData();

	TMap<uint32, UserItemInfo*>& GetAllItemInfo();
	UserItemInfo* GetItemInfo(const uint32& key);
	UserItemInfo* AddItemInfo(const uint32& key, const int& itemDataId, const int& nCount);
	void RemoveItemInfo(uint32 key);
};