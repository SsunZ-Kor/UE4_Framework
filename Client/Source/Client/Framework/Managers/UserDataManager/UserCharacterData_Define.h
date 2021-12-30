#pragma once

// #include "Client/GameContents/GameDatas/GameDataStructs.h"

class CItemData;
class UserItemInfo
{
private:
	uint32 m_nKey;
	const CItemData* m_pItemData;
	int m_nCount;
	
public:
	UserItemInfo();
	~UserItemInfo();

	void Init(uint32 nKey, const int& itemDataId, const int& nCount);
	void Init(uint32 nKey, const CItemData*& pItemData, const int& nCount);

	const CItemData* const& GetData() const;
	const int& GetCount() const;
	void SetCount(const int& nCount);
};