#pragma once
#include "DataLoadLib/DataFile/CLocalizationData.h"
#include "DataLoadLib/DataFile/DataFileEnum.h"

class CLIENT_API LocalizationManager
{
private:
	const TMap<FString, CLocalizationData*>*	m_mapAllData;

	class CDataFileFactory*			m_pDataFactory;

	ELanguage						m_eCurLanguage;
public:

	LocalizationManager();
	~LocalizationManager();

	void Init();

	void ChangeLanguage(ELanguage eLanguage);

	const FString& Get(const FString& strKey, ELanguage eLanguage = ELanguage::None);
	

	const FString& operator[](const FString& strKey);	
};
