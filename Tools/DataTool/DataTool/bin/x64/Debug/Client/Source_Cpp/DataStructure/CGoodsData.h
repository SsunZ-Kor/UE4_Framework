// Generate By DataTool. 2021-10-22 오후 9:02:33
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
