// Generate By DataTool. 2021-12-04 오전 5:51:59
// Drum.

#include "CItemData.h"

void CItemData::SetInfo(const FRowDataInfo& fInfo)
{
	CDataFileBase::SetInfo(fInfo);

	Name = fInfo.arrColData[1];
	ImgNameIcon = fInfo.arrColData[2];
}

EDataFileEnum CItemData::GetEnum()
{
	return EDataFileEnum::ItemData;
}
