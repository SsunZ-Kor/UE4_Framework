// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ClientGameBase.h"
#include "Engine/GameInstance.h"
#include "ClientGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API UClientGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UPROPERTY()
	TSet<UUserWidget*> m_set_WidgetInst;
	UPROPERTY()
	TSet<UMaterialInterface*> m_set_Mat;
	UPROPERTY()
	TSet<UObject*> m_set_uObj;

	virtual void Init() override;
	virtual void BeginDestroy() override;

public:
	void AddWidget(UUserWidget* pUserWidget);
	void RemoveWidget(UUserWidget* pUserWidget);
	void ClearWidgets();
	
	void AddMat(UMaterialInterface* pMat);
	void RemoveMat(UMaterialInterface* pMat);
	void RemoveMat(const TArray<UMaterialInterface*>& mats);
	void RemoveMat(const TArray<UMaterialInstanceDynamic*>& mats);
	void ClearMat();

	void AddUObject(UObject* pMgr);
	void RemoveUObject(UObject* pMgr);

public: // Callback For Managers
	UFUNCTION(BlueprintCallable)
	void OnComplete_LoadLevel();
};