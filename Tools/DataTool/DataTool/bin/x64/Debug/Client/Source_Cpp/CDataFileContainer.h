// Generate By DataTool. 2021-10-22 오후 9:02:37
// Drum
#pragma once
#include "DataFileHeader.h"

class CDataFileContainer
{
public:
	CConstData* ConstData;
	TMap<int32, CGoodsData*> MapGoodsData;
	TMap<int32, CZzDiseaseData*> MapZzDiseaseData;
	TMap<int32, CSurveyData*> MapSurveyData;
	TMap<int32, CShelterData*> MapShelterData;
	TMap<FString, CLocalizationData*> MapLocalizationData;
};
