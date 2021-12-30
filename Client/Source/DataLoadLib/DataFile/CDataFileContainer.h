// Generate By DataTool. 2021-12-04 오전 5:52:02
// Drum
#pragma once
#include "DataFileHeader.h"

class DATALOADLIB_API CDataFileContainer
{
public:
	CConstData* ConstData;
	TMap<int32, CCharacterData*> MapCharacterData;
	TMap<int32, CHelpData*> MapHelpData;
	TMap<int32, CStatData*> MapStatData;
	TMap<int32, CItemData*> MapItemData;
	TMap<int32, CHelpCategoryData*> MapHelpCategoryData;
	TMap<FString, CLocalizationData*> MapLocalizationData;
};
