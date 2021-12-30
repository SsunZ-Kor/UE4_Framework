// Generate By DataTool. 2021-10-22 오후 9:02:37
// Generated only one time when file is not exists.
// Drum
#pragma once

#include "CDataFileBase.h"
#include "DataFileEnum.h"
#include "CDataFileContainer.h"
#include "DataLoadLib/BinaryDataSource.h"

class CDataFileFactory
{
private:
	CDataFileContainer* m_pContainer;

	CDataFileFactory()
	{
		m_pContainer = new CDataFileContainer();
	}

	~CDataFileFactory()
	{
		ClearAllDataFiles();
	}

	template<typename TValue>
	void CreateDataFile(const UBinaryDataSource* uData, TMap<int32, TValue*>& map)
	{
		for(auto& rowData : uData->TableInfo)
		{
			TValue* cData = new TValue();
			cData->SetInfo(rowData);

			map.Add(cData->ID, cData);
		}
	}

	template<typename TKey, typename TValue>
	void ClearAllDataFiles(TMap<TKey, TValue*>& map)
	{
		for(auto& tuple : map)
		{
			if(tuple.Value != nullptr)
				delete tuple.Value;

			tuple.Value = nullptr;
		}

		map.Reset();
	}

public:
	void ClearAllDataFiles();

	void* CreateDataFile(EDataFileEnum eData, const UBinaryDataSource* uData);

	const CDataFileBase* GetData(EDataFileEnum eData, int32 nKey) const;

	const CConstData* GetConstData() const;

	void CreateLocalizationFile(const UBinaryDataSource* uData);

	const TMap<FString, class CLocalizationData*>* GetLocalizationMap() const;

	static CDataFileFactory* Instance() 
	{
		static CDataFileFactory* instance = new CDataFileFactory();
		return instance;
	}
};
