// Generate By DataTool. 2021-10-22 오후 9:02:33
// Drum.

#pragma once
#include "../CDataFileBase.h"

class CZzDiseaseData : public CDataFileBase
{
public:
	FString Name;
	EDiseaseType DiseaseType;
	FString IconColorHex;
	int32 BuffId;

virtual void SetInfo(const struct FRowDataInfo& fInfo);
};
