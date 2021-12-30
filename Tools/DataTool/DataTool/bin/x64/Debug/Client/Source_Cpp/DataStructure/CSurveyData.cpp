// Generate By DataTool. 2021-10-22 오후 9:02:33
// Drum.

#include "CSurveyData.h"

void CSurveyData::SetInfo(const FRowDataInfo& fInfo)
{
	CDataFileBase::SetInfo(fInfo);

	Name = fInfo.arrColData[1].strValue;
	UiId = fInfo.arrColData[2].nValue;
	TargetIndex = fInfo.arrColData[3].nValue;
	SurveyType = fInfo.arrColData[4].nValue;
	NeedShelterId = fInfo.arrColData[5].nValue;
	StartDate = fInfo.arrColData[6].strValue;
	EndDate = fInfo.arrColData[7].strValue;
	Time1 = fInfo.arrColData[8].nValue;
	Time2 = fInfo.arrColData[9].nValue;
	Time3 = fInfo.arrColData[10].nValue;
	Duration = fInfo.arrColData[11].nValue;
	CheckBattlePower = fInfo.arrColData[12].nValue;
	AddRiskPoint = fInfo.arrColData[13].nValue;
	SurveyTime1 = fInfo.arrColData[14].nValue;
	SurveyReward1Cnt = fInfo.arrColData[15].nValue;
	SurveyTime2 = fInfo.arrColData[16].nValue;
	SurveyReward2Cnt = fInfo.arrColData[17].nValue;
	SurveyTime3 = fInfo.arrColData[18].nValue;
	SurveyReward3Cnt = fInfo.arrColData[19].nValue;
	SurveyRewardGroupId = fInfo.arrColData[20].nValue;
	AddGasolinePoint = fInfo.arrColData[21].nValue;
}
