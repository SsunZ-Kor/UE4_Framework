// Generate By DataTool. 2021-12-04 오전 5:51:54
// Generated only one time when file is not exists.
// Drum
#include "CDataFileBase.h"

void CDataFileBase::SetInfo(const FRowDataInfo& fInfo)
{
	ID = FCString::Atoi(*fInfo.arrColData[0]);
}

EDataFileEnum CDataFileBase::GetEnum()
{
	return EDataFileEnum::MAX;
}
