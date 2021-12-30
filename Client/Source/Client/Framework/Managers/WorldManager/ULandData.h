// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ULandData.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API UULandData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FString> NeighboringLandNames;
};