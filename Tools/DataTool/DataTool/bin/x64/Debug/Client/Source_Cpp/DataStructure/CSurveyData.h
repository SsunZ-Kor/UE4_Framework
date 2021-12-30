// Generate By DataTool. 2021-10-22 오후 9:02:33
// Drum.

#pragma once
#include "../CDataFileBase.h"

class CSurveyData : public CDataFileBase
{
public:
	FString Name;
	int32 UiId;
	int32 TargetIndex;
	int32 SurveyType;
	int32 NeedShelterId;
	FString StartDate;
	FString EndDate;
	int32 Time1;
	int32 Time2;
	int32 Time3;
	int32 Duration;
	int32 CheckBattlePower;
	int32 AddRiskPoint;
	int32 SurveyTime1;
	int32 SurveyReward1Cnt;
	int32 SurveyTime2;
	int32 SurveyReward2Cnt;
	int32 SurveyTime3;
	int32 SurveyReward3Cnt;
	int32 SurveyRewardGroupId;
	int32 AddGasolinePoint;

virtual void SetInfo(const struct FRowDataInfo& fInfo);
};
