// Generate By DataTool. 2021-12-02 오후 6:29:10
// Drum.

#include "CConstData.h"
#include "DataLoadLib/GlobalDataStruct.h"

void CConstData::SetInfo(const TArray<FRowDataInfo>& TableInfo)
{
	PATH_GAMEDATA = TableInfo[0].arrColData[3];
}
