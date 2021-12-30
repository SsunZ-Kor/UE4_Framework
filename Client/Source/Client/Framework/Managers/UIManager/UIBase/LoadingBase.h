// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ImmortalWidget.h"
#include "LoadingBase.generated.h"

UCLASS()
class CLIENT_API ULoadingBase : public UImmortalWidget
{
	GENERATED_BODY()

public:	
	virtual void Open();
	virtual void Close();

public:
	UFUNCTION(BlueprintCallable)
	void OnEndAnim_Open() const;
	UFUNCTION(BlueprintCallable)
	void OnEndAnim_Close() const;
};