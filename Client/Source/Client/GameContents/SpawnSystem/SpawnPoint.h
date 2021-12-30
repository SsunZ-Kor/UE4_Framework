// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Client/Framework/ClientGameBase.h"
#include "Engine/TargetPoint.h"
#include "SpawnPoint.generated.h"

class ASpawnSystem;
class USplineComponent;

UENUM()
enum class ESpawnPointPatrolTypes : uint8
{
	None,
	PingPong,
	Loop,
};

UCLASS()
class CLIENT_API ASpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

	UPROPERTY()
	ASpawnSystem* m_pOwner;

	/* 패트롤용 변수들 */
	UPROPERTY(EditAnywhere, Category="Patrol", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESpawnPointPatrolTypes m_PatrolType;
	UPROPERTY(EditAnywhere, Category="Patrol", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USplineComponent* m_pSplineComp;

	/*패트롤 디버깅용 변수들 */
	UPROPERTY(EditAnywhere, Category="Patrol Debug", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMesh* m_pDebugMesh;
	UPROPERTY(EditAnywhere, Category="Patrol Debug", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* m_pDebugMat;
	UPROPERTY(EditAnywhere, Category="Patrol Debug", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_fDebugMeshDist;
	
	UPROPERTY(VisibleAnywhere, Category="Patrol Debug", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*>	m_DebugMeshComps;

	/* 패트롤 런타임용 변수들 */
	UPROPERTY()
	AActor* m_pPatrolPoint;
	float m_fCrrPatolPointLength;
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void Init(ASpawnSystem* const& pOwner);
	const USplineComponent* const&  GetSplineComp() const;

	bool HasPatrol() const;
	bool IsCloseToPatrolPoint(const FVector& Vector, float fDist) const;
	const AActor* const& GetPatrolPoint() const;
	void NextPatrolPoint();

private :
	void ComputeSpline();

public:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};