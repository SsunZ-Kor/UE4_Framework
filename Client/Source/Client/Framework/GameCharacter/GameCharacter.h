// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ClientGameBase.h"
#include "GameCharacter_Define.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

UCLASS()
class CLIENT_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	static GameCharacterAllyInfo* AllyInfo;

protected: // GameCharacter_Team

	TDoubleLinkedListEx<AGameCharacter*>::TDoubleLinkedListExNode* m_pNode_State;
	GameCharacterTeamInfo* m_pMyTeamInfo;
	EGameCharacterStateTypes m_State;
	EGameCharacterAreaTyeps m_Area;
	
protected:
	UPROPERTY()
	class UActionController* m_ActionCtrl;
	UPROPERTY()
	class UAnimController* m_AnimCtrl;
	UPROPERTY()
	class UStatController* m_StatCtrl;
	UPROPERTY()
	class ABrainController* m_BrainCtrl;

protected:
	const class CCharacterData* m_Data;

public:
	// Sets default values for this character's properties
	AGameCharacter();
	virtual ~AGameCharacter() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	class UActionController* const& GetActionCtrl();
	class UAnimController* const& GetAnimCtrl();
	class UStatController* const& GetStatCtrl();
	class ABrainController* const& GetBrainCtrl();

	void SetActive(const bool& bActive);
	const EGameCharacterAreaTyeps& GetArea();

	void Hit(AGameCharacter* pAttacker, const FVector& hitPoint, const FQuat& hitNormal, USoundBase* hitSFX, class UFXContainer* hitFX);
	void SetNavLocation(const FVector& vLocation);
	FVector CalNavLocation(const FVector& vLocation) const;

public: // GameCharacter_Init.cpp
	void Init(const CCharacterData* gameCharacterData);
	const CCharacterData* GetData();
	void RefreshName();

public: // GameCharacter_Team
	void ChangeTeam(const int& idx_Team);
	void RefreshCollisionProfile();
	void ChangeState(const EGameCharacterStateTypes& state);
	const GameCharacterTeamInfo* GetTeamInfo() const;

};