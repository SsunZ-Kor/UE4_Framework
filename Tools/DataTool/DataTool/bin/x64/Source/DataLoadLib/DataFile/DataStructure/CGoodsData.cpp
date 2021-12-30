// Generate By DataTool. 2021-11-09 오후 8:20:57
// Drum.

#include "CGoodsData.h"

void CGoodsData::SetInfo(const FRowDataInfo& fInfo)
{
	CDataFileBase::SetInfo(fInfo);

	GoodsType = static_cast<EGoodsType>(fInfo.arrColData[1].nValue);
	Bundle = fInfo.arrColData[2].strValue;
	SmallIcon = fInfo.arrColData[3].strValue;
	LargeIcon = fInfo.arrColData[4].strValue;
	IsUseShopShortCut = fInfo.arrColData[5].bValue;
	IsUseMaxValue = fInfo.arrColData[6].bValue;
}
