// Generate By DataTool. 2021-10-22 오후 9:02:33
// Drum.

#pragma once
#include "../CDataFileBase.h"

class CShelterData : public CDataFileBase
{
public:
	FString Name;
	FString Desc;
	int32 ZoneId;
	int32 NeedLevel;
	int32 NextShelterId;
	int32 ShelterGrade;
	int32 PlaceId;
	int32 SetupTime;
	int32 AttackTime;
	int32 AttackObjectPartsPoint;
	int32 AttackTimePartsPoint;
	int32 AttackActorFoodPoint;
	int32 AttackTimeFoodPoint;
	int32 AttackWinMedalPoint;
	int32 AttackLoseMedalPoint;
	int32 MaxDefenseActor;
	FString BgmName;
	FString EnvName;
	FString MigrationCinema;
	int32 AvailableWorldmap;
	FString Status;

virtual void SetInfo(const struct FRowDataInfo& fInfo);
};
