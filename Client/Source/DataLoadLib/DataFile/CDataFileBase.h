// Generate By DataTool. 2021-12-04 오전 5:51:54
// Generated only one time when file is not exists.
// Drum
#pragma once

#include "DataFileEnum.h"
#include "DataLoadLib/GlobalDataStruct.h"
#include "DataStructure/DataTypeEnum.h"

class DATALOADLIB_API CDataFileBase
{
public:
	int32 ID;

	virtual ~CDataFileBase() { }

	virtual void SetInfo(const FRowDataInfo& fInfo);

	static EDataFileEnum GetEnum();
};
