#include "UserDataManager.h"

#include "UserAccountData.h"
#include "UserCharacterData.h"

UserDataManager::UserDataManager()
	: m_pUserAccountData(nullptr)
	, m_pUserCharacterData(nullptr)
	, AccountData(m_pUserAccountData)
	, CharacterData(m_pUserCharacterData)
{
}

UserDataManager::~UserDataManager()
{
	if (m_pUserAccountData)
	{
		delete m_pUserAccountData;
		m_pUserAccountData = nullptr;
	}
	
	if (m_pUserCharacterData)
	{
		delete m_pUserCharacterData;
		m_pUserCharacterData = nullptr;
	}
}

void UserDataManager::Init()
{
	m_pUserAccountData = new UserAccountData();
	m_pUserCharacterData = new UserCharacterData();
}