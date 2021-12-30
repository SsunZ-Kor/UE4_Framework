// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ClientGameBase.h"
#include "FXActor.h"
#include "FXManager.generated.h"

UCLASS()
class UFXContainer : public UObject
{
	GENERATED_BODY()
	
	friend class FXManager;
private:
	UPROPERTY()
	UClass* m_StaticClass;
	TDoubleLinkedListEx<AFXActor*> m_llist_Active;
	TDoubleLinkedListEx<AFXActor*> m_llist_Inactive;

	int m_nRefCount;
	bool m_bIsLoop;

public:
	UFXContainer();
	virtual ~UFXContainer() override;

	virtual void BeginDestroy() override;

	const bool& IsLooping() const;
};

class CLIENT_API FXManager
{
private:
	TMap<FString, UFXContainer*> m_map_FXContainer;

public:
	FXManager();
	~FXManager();

public:
	void Init();

	void OnPrevChangeLevel();

	AFXActor* PlayFX(FString FxName, const FVector& location, const FQuat& rotation, const FVector& scale);
	AFXActor* PlayFX(FString FxName, const FVector& location, const FQuat& rotation, const FVector& scale, const FOnFXReturn& onReturn);
	AFXActor* PlayFX(FString FxName, AActor* parent, const FName& socketName, const bool& bFollowParent, const FVector& location, const FQuat& rotation, const FVector& scale);
	AFXActor* PlayFX(FString FxName, AActor* parent, const FName& socketName, const bool& bFollowParent, const FVector& location, const FQuat& rotation, const FVector& scale, const FOnFXReturn& onReturn);
	
	AFXActor* PlayFX(UFXContainer* fxContainer, const FVector& location, const FQuat& rotation, const FVector& scale);
	AFXActor* PlayFX(UFXContainer* fxContainer, const FVector& location, const FQuat& rotation, const FVector& scale, const FOnFXReturn& onReturn);
	AFXActor* PlayFX(UFXContainer* fxContainer, AActor* parent, const FName& socketName,  const bool& bFollowParent, const FVector& location, const FQuat& rotation, const FVector& scale);
	AFXActor* PlayFX(UFXContainer* fxContainer, AActor* parent, const FName& socketName,  const bool& bFollowParent, const FVector& location, const FQuat& rotation, const FVector& scale, const FOnFXReturn& onReturn);
	void RetrieveFX(AFXActor* fxActor);

	UFXContainer* RegistFX(UClass* fxClass, int nDefaultCount);
	void ReleaseFX(FString fxName);
	void ReleaseFX(UFXContainer* fxName);

private:
	AFXActor* GenerateFX(UFXContainer* const fxContainer);
};