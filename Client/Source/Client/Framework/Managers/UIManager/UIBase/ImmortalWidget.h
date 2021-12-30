// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../ClientGameBase.h"
#include "Blueprint/UserWidget.h"
#include "ImmortalWidget.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API UImmortalWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UImmortalWidget(const FObjectInitializer& ObjectInitializer);

private:
	bool m_bIsInit_WidgetAnim;
	UPROPERTY()
	TMap<FString, UWidgetAnimation*> m_map_WidgetAnim;

protected:
	virtual void NativeConstruct() override;
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
	UWidgetAnimation* GetAnimation(const FString& animName);
};
