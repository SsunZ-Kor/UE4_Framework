// Generate By DataTool. 2021-11-09 오후 8:20:57
// Drum.

#pragma once
#include "../CDataFileBase.h"

class CGoodsData : public CDataFileBase
{
public:
	EGoodsType GoodsType;
	FString Bundle;
	FString SmallIcon;
	FString LargeIcon;
	bool IsUseShopShortCut;
	bool IsUseMaxValue;

virtual void SetInfo(const struct FRowDataInfo& fInfo);
};
