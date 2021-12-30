#include "UnrealEx.h"
#include "GameFramework/Character.h"
#include "Misc/LocalTimestampDirectoryVisitor.h"

FBodyInstance* HitResultToBodyInst(const FHitResult* const pHitResult)
{
	if (!pHitResult)
		return nullptr;

	return HitResultToBodyInst(*pHitResult);
}

FBodyInstance* HitResultToBodyInst(const FHitResult& hitResult)
{
	auto pChar = Cast<ACharacter>(hitResult.GetActor());

	// 캐릭터고 Bone에 맞은 경우
	if (pChar && hitResult.BoneName != NAME_None)
		return pChar->GetMesh()->GetBodyInstance(hitResult.BoneName);

	// 아닐 경우 Component에서 찾는다
	return hitResult.GetComponent()->GetBodyInstance();
}

void GetAllFilesInDirectory(TArray<FString>& results, const FString directory, const bool fullPath, const FString onlyFilesStartingWith, const FString onlyFilesWithExtension)
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