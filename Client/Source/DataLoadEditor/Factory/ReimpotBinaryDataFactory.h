// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BinaryDataFactory.h"
#include "EditorReimportHandler.h"
#include "ReimpotBinaryDataFactory.generated.h"

UCLASS()
class DATALOADEDITOR_API UReimpotBinaryDataFactory : public UBinaryDataFactory, public FReimportHandler
{
	GENERATED_BODY()

	// Begin FReimportHandler interface
	virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;
	virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;
	virtual EReimportResult::Type Reimport(UObject* Obj) override;
	// End FReimportHandler interface
};
