// Generate By DataTool. 2021-10-22 오후 9:02:33
// Drum.

#include "CShelterData.h"

void CShelterData::SetInfo(const FRowDataInfo& fInfo)
{
	CDataFileBase::SetInfo(fInfo);

	Name = fInfo.arrColData[1].strValue;
	Desc = fInfo.arrColData[2].strValue;
	ZoneId = fInfo.arrColData[3].nValue;
	NeedLevel = fInfo.arrColData[4].nValue;
	NextShelterId = fInfo.arrColData[5].nValue;
	ShelterGrade = fInfo.arrColData[6].nValue;
	PlaceId = fInfo.arrColData[7].nValue;
	SetupTime = fInfo.arrColData[8].nValue;
	AttackTime = fInfo.arrColData[9].nValue;
	AttackObjectPartsPoint = fInfo.arrColData[10].nValue;
	AttackTimePartsPoint = fInfo.arrColData[11].nValue;
	AttackActorFoodPoint = fInfo.arrColData[12].nValue;
	AttackTimeFoodPoint = fInfo.arrColData[13].nValue;
	AttackWinMedalPoint = fInfo.arrColData[14].nValue;
	AttackLoseMedalPoint = fInfo.arrColData[15].nValue;
	MaxDefenseActor = fInfo.arrColData[16].nValue;
	BgmName = fInfo.arrColData[17].strValue;
	EnvName = fInfo.arrColData[18].strValue;
	MigrationCinema = fInfo.arrColData[19].strValue;
	AvailableWorldmap = fInfo.arrColData[20].nValue;
	Status = fInfo.arrColData[21].strValue;
}
