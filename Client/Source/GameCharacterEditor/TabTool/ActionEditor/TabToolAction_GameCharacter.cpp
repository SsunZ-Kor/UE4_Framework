#include "TabToolAction_GameCharacter.h"

#include "Widget_ActionList.h"
#include "Widget_ActionData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Client/Framework/ClientGameBase.h"
#include "Client/Framework/GameCharacter/ActionControl/ActionData.h"
#include "GameCharacterEditor/GameCharacterEditor.h"

TabToolAction_GameCharacter::~TabToolAction_GameCharacter()
{
}

void TabToolAction_GameCharacter::OnStartupModule()
{
	TabToolBase_GameCharacter::OnStartupModule();
	FGameCharacterEditor::Get().AddMenuExtension(FMenuExtensionDelegate::CreateRaw(this, &TabToolAction_GameCharacter::MakeMenuEntry), FName("Action"));
}

void TabToolAction_GameCharacter::OnShutdownModule()
{
	TabToolBase_GameCharacter::OnShutdownModule();
}

void TabToolAction_GameCharacter::Init()
{
	m_TabName = "Action Tab";
	m_TabDisplayName = FText::FromString("Action");
	m_ToolTipText = FText::FromString("캐릭터 액션을 편집합니다.");
	
	// 액션 이벤트 타입 수집
	int nMaxActionEventTypeValue = static_cast<int>(EActionEventTypes::Max);
	
	m_AllEventTypes.Empty();
	for (int e = 1; e < nMaxActionEventTypeValue; ++e)
		m_AllEventTypes.Add(MakeShared<EActionEventTypes>(static_cast<EActionEventTypes>(e)));
}

TSharedRef<SDockTab> TabToolAction_GameCharacter::SpawnTab(const FSpawnTabArgs& TabSpawnArgs)
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SBox)
			.WidthOverride(300)
			[
				SAssignNew(m_pWidget_ActionList, Widget_ActionList).Tool(SharedThis(this))
			]
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.f)
		[
			SAssignNew(m_pWidget_ActionData, Widget_ActionData).Tool(SharedThis(this))
		]
	];

	//if (SpawnedTab->GetTabManager() != nullptr)
	//TSharedRef<SDockTab> widget_ActionData = SNew(SDockTab)
	//	.TabRole(ETabRole::DocumentTab)
	//	.Label(FText::FromString(TEXT("ActionList")))
	//
	//FTabManager();
	//
	//SpawnedTab->Tab()
	//SpawnedTab->GetTabManager()->InsertNewDocumentTab("DockedToolkit", FTabManager::ESearchPreference::Type::PreferLiveTab ,widget_ActionData);

	return SpawnedTab;
}

void TabToolAction_GameCharacter::RefreshAllActionDataInfo()
{
	// 기존 정보 삭제
	m_AllActionDataInfos.Empty();
	m_AllActionDataInfos_Filtered.Empty();
	m_StrFileter = nullptr;

	// Find All ActionData Assets
	auto dir_Root = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
	dir_Root = FPaths::Combine(dir_Root, TEXT("GameContents"));
	
	TArray<FString> paths_ActionData;
	GetAllFilesInDirectory(paths_ActionData, dir_Root, true, TEXT("ActionData_"), TEXT("uasset"));

	// Contain
	for(auto& path : paths_ActionData)
	{
		TSharedPtr<ActionDataInfo> pActionDataInfo = MakeShareable(new ActionDataInfo());

		// 이름
		FString name_Asset = FPaths::GetCleanFilename(path);

		// 캐릭터 이름 찾기
		TArray<FString> out;
		path.ParseIntoArray(out, TEXT("/"), true);
		name_Asset = name_Asset.Replace(TEXT(".uasset"), TEXT(""));
		FString name_Char;
		for (int i = out.Num() - 1 ; i >= 0; --i)
		{
			if (out[i].Contains(TEXT("Char_")))
			{
				name_Char = out[i];
				break;
			}
		}

		// 이름 세팅
		pActionDataInfo->Name = FString::Printf(TEXT("%s : %s"), *name_Char, *name_Asset);

		// 레퍼런스 경로
		pActionDataInfo->Path = FString::Printf(TEXT("/Game/GameContents%s"), *path.Replace(*dir_Root, TEXT("")));
		pActionDataInfo->Path = pActionDataInfo->Path.Replace(TEXT(".uasset"), *FString::Printf(TEXT(".%s"), *name_Asset));

		UE_LOG(LogTemp, Warning, TEXT("%s"), *pActionDataInfo->Path);

		// 추가
		m_AllActionDataInfos.Add(pActionDataInfo);
		m_AllActionDataInfos_Filtered.Add(pActionDataInfo);
	}
}

TArray<TSharedPtr<ActionDataInfo>>& TabToolAction_GameCharacter::GetAllActionDataInfos()
{
	return m_AllActionDataInfos;
}

TArray<TSharedPtr<ActionDataInfo>>& TabToolAction_GameCharacter::GetFilteredActionDataInfos()
{
	return m_AllActionDataInfos_Filtered;
}

void TabToolAction_GameCharacter::RefreshFilteredActionDataInfos()
{
	m_AllActionDataInfos_Filtered.Empty();

	if (m_StrFileter.IsEmpty())
	{
		for (auto pActionDataInfo : m_AllActionDataInfos)
			m_AllActionDataInfos_Filtered.Add(pActionDataInfo);
	}
	else
	{
		for (auto pActionDataInfo : m_AllActionDataInfos)
		{
			if (pActionDataInfo->Name.Contains(m_StrFileter))
				m_AllActionDataInfos_Filtered.Add(pActionDataInfo);
		}
	}

	if (m_AllActionDataInfos_Filtered.Num() == 0)
	{
		TSharedPtr<ActionDataInfo> pActionDataInfo = MakeShareable(new ActionDataInfo());
		pActionDataInfo->Name = TEXT("Not Found");

		m_AllActionDataInfos_Filtered.Add(pActionDataInfo);
	}
}

FText TabToolAction_GameCharacter::GetFilterText()
{
	return FText::FromString(m_StrFileter);
}

void TabToolAction_GameCharacter::SetFilterText(const FText& txt)
{
	m_StrFileter = txt.ToString();
}

void TabToolAction_GameCharacter::LoadSelectedActionData(TSharedPtr<ActionDataInfo> pActionDataInfo)
{
	m_SelectedActionDataInfo = pActionDataInfo;
	if (!m_SelectedActionDataInfo)
		return;

	m_SelectedActionEventData.Empty();
	m_SelectedActionTriggerData.Empty();

	// Load Object
	FAssetRegistryModule& AssetRegistryModule =
	FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FAssetData AssetData =
		AssetRegistryModule.Get().GetAssetByObjectPath(*pActionDataInfo->Path);

	if (!AssetData.IsValid())
	{
		m_SelectedActionData = nullptr;
		return;
	}

	m_SelectedActionData = Cast<UActionData>(AssetData.GetAsset());
	m_SelectedActionData->GetActionEventsForEditor(m_SelectedActionEventData);
	m_SelectedActionData->GetActionTriggersForEditor(m_SelectedActionTriggerData);
	m_SelectedActionData->ResetDirty();
}

void TabToolAction_GameCharacter::SaveSelectedActionData()
{
	if (!m_SelectedActionData)
		return;

	// 변경사항 반영
	m_SelectedActionData->ClearAllEvents();
	for (auto pActionEventData : m_SelectedActionEventData)
	{
		pActionEventData->AdjustEditorData();
		m_SelectedActionData->AddEvent(pActionEventData.Get());
	}

	m_SelectedActionData->ClearAllTriggers();
	for (auto pActionTriggerData : m_SelectedActionTriggerData)
	{
		m_SelectedActionData->AddTrigger(pActionTriggerData.Get());
	}
	
	// 저장
	FString OutClassName;
	FString OutPackageName;
	FString OutObjectName;
	FString OutSubObjectName;
	FPackageName::SplitFullObjectPath(m_SelectedActionData->GetFullName(), OutClassName, OutPackageName, OutObjectName, OutSubObjectName);

	UE_LOG(LogTemp, Error, TEXT("OutClassName : %s  OutPackageName : %s  OutObjectName : %s  OutSubObjectName : %s"),
		*OutClassName,
		*OutPackageName,
		*OutObjectName,
		*OutSubObjectName);

	FString PackageName = OutPackageName;
	UPackage* Package = CreatePackage(*PackageName);

	Package->FullyLoad();
	Package->MarkPackageDirty();
	
	FAssetRegistryModule::AssetCreated(m_SelectedActionData);

	FString PackageFileName = FPackageName::LongPackageNameToFilename(
		PackageName, FPackageName::GetAssetPackageExtension());

	bool bSaved = UPackage::SavePackage(
		Package,
		m_SelectedActionData,
		EObjectFlags::RF_Public | EObjectFlags::RF_Standalone,
		*PackageFileName,
		GError,
		nullptr,
		true,
		true,
		SAVE_NoError);

	// 에셋의 수정 내용을 에디터에도 적용시켜준다.
	TArray<UObject*> ObjectsToSync;
	ObjectsToSync.Add(m_SelectedActionData);
	GEditor->SyncBrowserToObjects(ObjectsToSync);
}

TSharedPtr<ActionDataInfo> TabToolAction_GameCharacter::GetSelectedActionDataInfo()
{
	return m_SelectedActionDataInfo;
}

UActionData*& TabToolAction_GameCharacter::GetSelectedActionData()
{
	return m_SelectedActionData;
}

TArray<TSharedPtr<FActionEventDataBase>>& TabToolAction_GameCharacter::GetSelectedActionEventData()
{
	return m_SelectedActionEventData;
}

TArray<TSharedPtr<FActionTriggerData>>& TabToolAction_GameCharacter::GetSelectedActionTriggerData()
{
	return m_SelectedActionTriggerData;
}

void TabToolAction_GameCharacter::GetAllFilesInDirectory(TArray<FString>& results, const FString& directory, const bool& fullPath, const FString& onlyFilesStartingWith, const FString& onlyFilesWithExtension)
{
	// Get all files in directory
	TArray<FString> directoriesToSkip;
	IPlatformFile &PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FLocalTimestampDirectoryVisitor Visitor(PlatformFile, directoriesToSkip, directoriesToSkip, false);    
	PlatformFile.IterateDirectory(*directory, Visitor);
 
	for (TMap<FString, FDateTime>::TIterator TimestampIt(Visitor.FileTimes); TimestampIt; ++TimestampIt)
	{
		const FString filePath = TimestampIt.Key();        
		const FString fileName = FPaths::GetCleanFilename(filePath);
		bool shouldAddFile = true;
 
		// Check if filename starts with required characters
		if (!onlyFilesStartingWith.IsEmpty())
		{
			const FString left = fileName.Left(onlyFilesStartingWith.Len());            
 
			if (!(fileName.Left(onlyFilesStartingWith.Len()).Equals(onlyFilesStartingWith)))
				shouldAddFile = false;
		}
 
		// Check if file extension is required characters
		if (!onlyFilesWithExtension.IsEmpty())
		{
			if (!(FPaths::GetExtension(fileName, false).Equals(onlyFilesWithExtension, ESearchCase::IgnoreCase)))
				shouldAddFile = false;
		}
 
		// Add full path to results
		if (shouldAddFile)
		{
			results.Add(fullPath ? filePath : fileName);
		}
	}
}

const TArray<TSharedRef<EActionEventTypes>>& TabToolAction_GameCharacter::GetAllActionEventTypes()
{
	return m_AllEventTypes;
}