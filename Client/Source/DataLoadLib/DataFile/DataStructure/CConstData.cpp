// Generate By DataTool. 2021-12-04 오전 5:52:00
// Drum.

#include "CConstData.h"
#include "DataLoadLib/GlobalDataStruct.h"

void CConstData::SetInfo(const TArray<FRowDataInfo>& TableInfo)
{
	MIN_ACTOR_COUNT = FCString::Atoi(*TableInfo[0].arrColData[2]);
	GRADE_COLOR_MAIN_BASIC = TableInfo[1].arrColData[3];
	GOODS_PRODUCT_TICK = FCString::Atoi(*TableInfo[2].arrColData[2]);
	TALK_DEFAULT_ACTOR_ANIMATION = TableInfo[3].arrColData[3];
}
