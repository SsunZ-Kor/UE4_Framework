// Generate By DataTool. 2021-10-22 오후 9:02:33
// Drum.

#include "CZzDiseaseData.h"

void CZzDiseaseData::SetInfo(const FRowDataInfo& fInfo)
{
	CDataFileBase::SetInfo(fInfo);

	Name = fInfo.arrColData[1].strValue;
	DiseaseType = static_cast<EDiseaseType>(fInfo.arrColData[2].nValue);
	IconColorHex = fInfo.arrColData[3].strValue;
	BuffId = fInfo.arrColData[4].nValue;
}
