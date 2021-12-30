// Generate By DataTool. 2021-10-22 오후 9:02:37
// Generated only one time when file is not exists.
// Drum
#include "CLocalizationData.h"
#include "DataFileEnum.h"
#include "DataLoadLib/GlobalDataStruct.h"

void CLocalizationData::SetInfo(const FRowDataInfo& fInfo)
{
	ID = fInfo.arrColData[0].strValue;
	KO = fInfo.arrColData[static_cast<int32>(ELanguage::KO)].strValue;
	EN = fInfo.arrColData[static_cast<int32>(ELanguage::EN)].strValue;
	JA = fInfo.arrColData[static_cast<int32>(ELanguage::JA)].strValue;
}

const FString CLocalizationData::GetLanguage(int nIndex) const
{
	return GetLanguage(static_cast<ELanguage>(nIndex));
}

const FString CLocalizationData::GetLanguage(ELanguage eLanguage) const
{
	switch (eLanguage)
	{
	case ELanguage::KO: return KO;
	case ELanguage::EN: return EN;
	case ELanguage::JA: return JA;
	}

	return "";
}
