// Generate By DataTool. 2021-10-22 오후 9:02:30
// Generated only one time when file is not exists.
// Drum
#pragma once

#include "DataLoadLib/GlobalDataStruct.h"
#include "DataStructure/DataTypeEnum.h"

class CDataFileBase
{
public:
	virtual ~CDataFileBase() { }

	int32 ID;

	virtual void SetInfo(const FRowDataInfo& fInfo);
};
