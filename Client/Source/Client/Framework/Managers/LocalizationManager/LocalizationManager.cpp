#include "LocalizationManager.h"

#include "Client/Framework/Utils/GenericEx.h"
#include "DataLoadLib/DataFile/CDataFileFactory.h"

LocalizationManager::LocalizationManager()
{
	m_pDataFactory = CDataFileFactory::Instance();
	m_mapAllData = nullptr;// m_pDataFactory->GetLocalizationMap();
	
	m_eCurLanguage = ELanguage::Korean;	
}

LocalizationManager::~LocalizationManager()
{
	if(m_pDataFactory != nullptr)
	{
		m_pDataFactory->ClearAllDataFiles();
		m_pDataFactory = nullptr;
	}
}

void LocalizationManager::Init()
{
	if(m_pDataFactory == nullptr)
		m_pDataFactory = CDataFileFactory::Instance();

	//TODO : 경로 관련 리펙토링 고민
	FString strPath = TEXT("/game/GameContents/Localization");
	TArray<UBinaryDataSource*> arrAssets;

	LoadAllObject<UBinaryDataSource>(strPath, arrAssets);                                                    

	for(auto& uAsset : arrAssets)
	{
		if(!uAsset)
			continue;;

		m_pDataFactory->CreateLocalizationFile(uAsset);
	}

	m_mapAllData = m_pDataFactory->GetLocalizationMap();
}

void LocalizationManager::ChangeLanguage(ELanguage eLanguage)
{
	m_eCurLanguage = eLanguage;
}

const FString& LocalizationManager::Get(const FString& strKey, ELanguage eLanguage)
{
	if(eLanguage == ELanguage::None)
		eLanguage = m_eCurLanguage;

	if(m_mapAllData->Contains(strKey))
		return m_mapAllData->FindChecked(strKey)->GetLanguage(eLanguage);

	//TODO : Check
	//return CLocalizationData::KEY_EMPTY;
	return strKey;
}

const FString& LocalizationManager::operator[](const FString& strKey)
{
	return Get(strKey, m_eCurLanguage);
}
