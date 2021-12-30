// Generate By DataTool. 2021-12-04 오전 5:51:59
// Drum.

#pragma once
#include "../CDataFileBase.h"

class DATALOADLIB_API CStatData : public CDataFileBase
{
public:
	int32 Atk;
	int32 AtkRate;
	int32 MaxHp;
	int32 MaxHpRate;

	virtual void SetInfo(const struct FRowDataInfo& fInfo) override;

	static EDataFileEnum GetEnum();
};
