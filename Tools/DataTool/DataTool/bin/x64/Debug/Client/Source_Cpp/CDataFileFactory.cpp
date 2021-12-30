// Generate By DataTool. 2021-10-22 오후 9:02:37
// Drum
#include "CDataFileFactory.h"

void CDataFileFactory::ClearAllDataFiles()
{
	if(m_pContainer == nullptr)
		return;

	if(m_pContainer->ConstData != nullptr)
	{
		delete m_pContainer->ConstData;
		m_pContainer->ConstData = nullptr;
	}

	ClearAllDataFiles(m_pContainer->MapGoodsData);
	ClearAllDataFiles(m_pContainer->MapZzDiseaseData);
	ClearAllDataFiles(m_pContainer->MapSurveyData);
	ClearAllDataFiles(m_pContainer->MapShelterData);

	ClearAllDataFiles(m_pContainer->MapLocalizationData);

	delete m_pContainer;
	m_pContainer = nullptr;
}

void* CDataFileFactory::CreateDataFile(EDataFileEnum eData, const UBinaryDataSource* uData)
{
	if(uData == nullptr)
		return nullptr;

	if(m_pContainer == nullptr)
		m_pContainer = new CDataFileContainer();

	switch (eData)
	{
	case EDataFileEnum::ConstData:
		if(m_pContainer->ConstData == nullptr)
			m_pContainer->ConstData = new CConstData();
		m_pContainer->ConstData->SetInfo(uData->TableInfo);
		return nullptr;
	case EDataFileEnum::GoodsData:
		CreateDataFile<CGoodsData>(uData, m_pContainer->MapGoodsData);
		return &m_pContainer->MapGoodsData;
	case EDataFileEnum::ZzDiseaseData:
		CreateDataFile<CZzDiseaseData>(uData, m_pContainer->MapZzDiseaseData);
		return &m_pContainer->MapZzDiseaseData;
	case EDataFileEnum::SurveyData:
		CreateDataFile<CSurveyData>(uData, m_pContainer->MapSurveyData);
		return &m_pContainer->MapSurveyData;
	case EDataFileEnum::ShelterData:
		CreateDataFile<CShelterData>(uData, m_pContainer->MapShelterData);
		return &m_pContainer->MapShelterData;
	}

	return nullptr;
}

const CDataFileBase* CDataFileFactory::GetData(EDataFileEnum eData, int32 nKey) const
{
	if(m_pContainer == nullptr)
		return nullptr;

	switch (eData)
	{
	case EDataFileEnum::ConstData:
		return nullptr;
	case EDataFileEnum::GoodsData:
		return m_pContainer->MapGoodsData.Contains(nKey) ?
			m_pContainer->MapGoodsData[nKey] : nullptr;
	case EDataFileEnum::ZzDiseaseData:
		return m_pContainer->MapZzDiseaseData.Contains(nKey) ?
			m_pContainer->MapZzDiseaseData[nKey] : nullptr;
	case EDataFileEnum::SurveyData:
		return m_pContainer->MapSurveyData.Contains(nKey) ?
			m_pContainer->MapSurveyData[nKey] : nullptr;
	case EDataFileEnum::ShelterData:
		return m_pContainer->MapShelterData.Contains(nKey) ?
			m_pContainer->MapShelterData[nKey] : nullptr;
	}

	return nullptr;
}

const CConstData* CDataFileFactory::GetConstData() const
{
	if(m_pContainer == nullptr)
		return nullptr;

	return m_pContainer->ConstData;	
}

void CDataFileFactory::CreateLocalizationFile(const UBinaryDataSource* uData)
{
	if(uData == nullptr)
		return;

	if(m_pContainer == nullptr)
		m_pContainer = new CDataFileContainer();

	for(auto& rowData : uData->TableInfo)
	{
		CLocalizationData* cData = new CLocalizationData();
		cData->SetInfo(rowData);

		if(m_pContainer->MapLocalizationData.Contains(cData->ID))
		{
			delete cData;
			continue;
		}

		m_pContainer->MapLocalizationData.Add(cData->ID, cData);
	}
}

const TMap<FString, CLocalizationData*>* CDataFileFactory::GetLocalizationMap() const
{
	if(m_pContainer == nullptr)
		return nullptr;

	return &m_pContainer->MapLocalizationData;
}

