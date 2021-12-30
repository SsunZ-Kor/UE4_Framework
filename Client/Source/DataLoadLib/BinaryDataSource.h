// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GlobalDataStruct.h"
#include "UObject/NoExportTypes.h"
#include "BinaryDataSource.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(BinaryData, Log, All);

UCLASS()
class DATALOADLIB_API UBinaryDataSource : public UObject
{
	GENERATED_BODY()
	
protected:	
	UPROPERTY(Category = SourceAsset, VisibleAnywhere)
	int32					m_nRowCount;
	UPROPERTY(Category = SourceAsset, VisibleAnywhere)
	int32					m_nColCount;
	
public:
	UPROPERTY(Category = SourceAsset, VisibleAnywhere)
	int32					DataFileType;
	UPROPERTY(Category = SourceAsset, VisibleAnywhere)
	TArray<FRowDataInfo>	TableInfo;
	
#if WITH_EDITORONLY_DATA
	UPROPERTY(Category = SourceAsset, VisibleAnywhere)
	FString					FilePath;
	UPROPERTY(Category = SourceAsset, VisibleAnywhere)
	int64					ModifyTick;
	
	bool SetDataFromFile(const FString& strFileName);

	FString ToString() const
	{
		FString RetValue = TEXT("================[BinaryData Source]================");

		for (auto value : TableInfo)
		{
			for(auto value2 : value.arrColData)
				RetValue += value2;

			RetValue += TEXT("\n");
		}
		
		return RetValue;
	}
#endif
};
