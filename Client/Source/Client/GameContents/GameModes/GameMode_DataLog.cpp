#include "GameMode_DataLog.h"
#include "Client/Framework/Managers/Managers.h"

AGameMode_DataLog::AGameMode_DataLog()
{
	//LOG(TEXT("%s"), *result.GetActor()->GetName());
	LOG(TEXT("ATestFrameworkGameModeBase::Initializer"));
}

void AGameMode_DataLog::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	LOG(TEXT("ATestFrameworkGameModeBase::InitGame(%s, %s, %s)"), *MapName, *Options, *ErrorMessage);

	auto& timer = GetWorldTimerManager();
	//Test
	PrintFPaths();

	TestCode();

	LOG(TEXT("ATestFrameworkGameModeBase::InitGame End"));
}

void AGameMode_DataLog::BeginPlay()
{
	Super::BeginPlay();
	
	LOG(TEXT("ATestFrameworkGameModeBase::BeginPlay"));
}

void AGameMode_DataLog::OnInit()
{
	Super::OnInit();
}

void AGameMode_DataLog::OnStartGame()
{
	Super::OnStartGame();
}

void AGameMode_DataLog::OnEndGame()
{
	Super::OnEndGame();
}

void AGameMode_DataLog:: PrintFPaths()
{
	LOG(TEXT("PrintFPaths"));
	LOG(TEXT("Root Dir : [%s]"), *FPaths::RootDir());
	LOG(TEXT("Engine Dir : [%s], [%s]"), *FPaths::EngineDir(), *FPaths::ConvertRelativePathToFull(*FPaths::EngineDir()));

	LOG(TEXT("Engine Contents Dir : [%s], [%s]"), *FPaths::ProjectContentDir(), *FPaths::ConvertRelativePathToFull(*FPaths::ProjectContentDir()));
	LOG(TEXT("Project Contents Dir : [%s], [%s]"), *FPaths::ProjectContentDir(), *FPaths::ConvertRelativePathToFull(*FPaths::ProjectContentDir()));

	LOG(TEXT("Project Dir : [%s]"), *FPaths::ProjectDir());
	LOG(TEXT("ProjectUser Dir : [%s]"), *FPaths::ProjectUserDir());
}

void AGameMode_DataLog::TestCode()
{
	TestCodeManagers();
	// TestCodeDataManager();
	// TestCodeLocalizationManager();
}

void AGameMode_DataLog::TestCodeManagers()
{
	if(!Managers::IsInit())
		Managers::Init(GetWorld());

	TestCodeDataManager();
	TestCodeLocalizationManager();
	
	Managers::Release();
}

void AGameMode_DataLog::TestCodeDataManager()
{
	auto& cMgr = Managers::GameData;
	
	const CItemData* cData = cMgr->GetData<CItemData>(1);
	
	if(cData != nullptr)
	{
		//cData->Name = TEXT("dd");
    	LOG(TEXT("ID : %d Name : %s"), cData->ID, *cData->Name);
		
    	auto& id = typeid(cData);
    	FString name = id.name();
    	FString RawName = id.raw_name();
    	LOG(TEXT("Type HashCode : %d Type Name : %s Raw Name : %s"), (int)id.hash_code(), *name, *RawName);	
	}

	auto* mapData = cMgr->GetMapData<CCharacterData>();
	if(mapData != nullptr)
	{
		for (auto& tuple : *mapData)
		{
			LOG(TEXT("ID : %d Name : %s ModelName : %s AIBT : %s StatID : %d Height : %d"),
			tuple.Value->ID, *tuple.Value->Name, *tuple.Value->FileNameModel,
			*tuple.Value->FileNameAIBT, tuple.Value->DataIdStat, tuple.Value->Height);
		}
	}
	
	// const TMap<int32, CZzDiseaseData*>* mapData = cMgr->GetMapData<TMap<int32, CZzDiseaseData*>>(EDataFileEnum::ZzDiseaseData);	
	//
	// if(mapData != nullptr)
	// {
	// 	for(TTuple<int, CZzDiseaseData*> t : *mapData)
	// 	{
	// 		LOG(TEXT("Key : %d Value : %s"), t.Key, *(t.Value->Name));
	// 		auto& id = typeid(cData);
	// 		FString name = id.name();
	// 		FString RawName = id.raw_name();
	// 		LOG(TEXT("Type HashCode : %d Type Name : %s Raw Name : %s"), (int)id.hash_code(), *name, *RawName);
	// 	}	
	// }
	
	int nValue = cMgr->ConstData->MIN_ACTOR_COUNT;
	FString strValue = cMgr->ConstData->GRADE_COLOR_MAIN_BASIC;
	LOG(TEXT("ConstData Test INT : %d STRING : %s"), nValue, *strValue);	
}

void AGameMode_DataLog::TestCodeLocalizationManager()
{
	auto& cMgr = *Managers::LZ;
		
	FString strValue = cMgr["actor_type"];
	
	LOG(TEXT("Localization Test KEY : actor_type STRING : %s"), *strValue);
}