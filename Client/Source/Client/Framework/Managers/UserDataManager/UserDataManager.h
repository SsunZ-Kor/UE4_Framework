#pragma once

#include "../../ClientGameBase.h"

class UserAccountData;
class UserCharacterData;

class CLIENT_API UserDataManager
{
private:
	UserAccountData* m_pUserAccountData;
	UserCharacterData* m_pUserCharacterData;

public:	
	UserAccountData* const& AccountData;
	UserCharacterData* const& CharacterData;

public:
	UserDataManager();
	~UserDataManager();

	void Init();
};