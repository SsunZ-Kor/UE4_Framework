// Generate By DataTool. 2021-12-04 오전 5:51:59
// Drum.

#pragma once
#include "../CDataFileBase.h"

class DATALOADLIB_API CHelpData : public CDataFileBase
{
public:
	int32 CategoryDataId;
	FString Name;
	FString TxtContents;

	virtual void SetInfo(const struct FRowDataInfo& fInfo) override;

	static EDataFileEnum GetEnum();
};
