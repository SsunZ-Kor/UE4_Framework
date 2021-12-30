#include "DataFileManager.h"
#include "../Managers.h"
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#include "Engine/ObjectLibrary.h"

DataFileManager::DataFileManager()
{
	m_pDataFactory = CDataFileFactory::Instance();
	ConstData = nullptr;
}

DataFileManager::~DataFileManager()
{
	if(m_pDataFactory != nullptr)
	{
		m_pDataFactory->ClearAllDataFiles();
		m_pDataFactory = nullptr;
	}

	if(ConstData != nullptr)
		ConstData = nullptr;		
}

void DataFileManager::Init()
{
	if(m_pDataFactory == nullptr)
		m_pDataFactory = CDataFileFactory::Instance();

	if(!Managers::IsInit())
		return;
	
	//TODO : 경로 관련 리펙토링 고민
	FString strPath = TEXT("/game/GameContents/Data");
	TArray<UBinaryDataSource*> arrAssets;

	LoadAllObject<UBinaryDataSource>(strPath, arrAssets);

	for(auto& uAsset : arrAssets)
	{
		if(!uAsset)
			continue;;

		EDataFileEnum eData = static_cast<EDataFileEnum>(uAsset->DataFileType);
	
		if(m_mapAllData.Contains(eData))
			continue;
	
		auto map = m_pDataFactory->CreateDataFile(eData, uAsset);
		if(map != nullptr)
			m_mapAllData.Add(eData, map);
	}
	
	ConstData = m_pDataFactory->GetConstData();
}

void DataFileManager::GetActionDatas(uint32 nDataID, TArray<UActionData*>& result)
{
	if (m_mapAllActionData.Contains(nDataID))
	{
		result = m_mapAllActionData[nDataID];
	}
	else
	{
		// Todo :: 나중에 리소스 매니저로 전부 교체
		const CCharacterData* cData = GetData<CCharacterData>(nDataID);
		if (!cData)
			return;

		FString strDir = FPaths::Combine(cData->RefPath, TEXT("ActionDatas"));

		LoadAllObject(strDir, result);

		for (int i = 0 ; i < result.Num(); ++i)
			result[i]->AfterLoad();
			
		m_mapAllActionData.Add(nDataID, result);
	}
}
