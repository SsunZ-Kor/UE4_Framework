// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"

#include "Components/SplineComponent.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_pOwner = nullptr;
	m_pSplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComp"));

	m_fDebugMeshDist = 100.f;

	m_pPatrolPoint = nullptr;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> objFinder_DebugMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (objFinder_DebugMesh.Succeeded())
		m_pDebugMesh = objFinder_DebugMesh.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> objFinder_DebugMat(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	if (objFinder_DebugMat.Succeeded())
		m_pDebugMat = objFinder_DebugMat.Object;
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	ComputeSpline();

	if (HasPatrol())
	{
		auto& tr = GetTransform();

		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		m_pPatrolPoint = GetWorld()->SpawnActor<AActor>(tr.GetLocation(), tr.Rotator(), param);
		
#if WITH_EDITOR
		m_pPatrolPoint->SetActorLabel(FString::Printf(TEXT("PatrolPoint_%s"), *this->GetActorLabel()));
#endif
		m_pPatrolPoint->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void ASpawnPoint::Init(ASpawnSystem* const& pOwner)
{
	m_pOwner = pOwner;
}

const USplineComponent* const& ASpawnPoint::GetSplineComp() const
{
	return m_pSplineComp;
}

bool ASpawnPoint::HasPatrol() const
{
	return m_PatrolType != ESpawnPointPatrolTypes::None && m_pSplineComp->GetSplineLength() > 0.f;
}

bool ASpawnPoint::IsCloseToPatrolPoint(const FVector& Vector, float fDist) const
{
	return ((m_pPatrolPoint ? m_pPatrolPoint->GetActorLocation() : GetActorLocation()) - Vector).SizeSquared() <= (fDist * fDist);
}

const AActor* const& ASpawnPoint::GetPatrolPoint() const
{
	return m_pPatrolPoint;
}

void ASpawnPoint::NextPatrolPoint()
{
	m_fCrrPatolPointLength += m_fDebugMeshDist;
}

void ASpawnPoint::ComputeSpline()
{
#if ENABLE_DRAW_DEBUG
	m_fDebugMeshDist = FMath::Max(100.f, m_fDebugMeshDist);

	auto trActor = GetActorTransform();
	auto nDebugMeshCount = FMath::CeilToInt(m_pSplineComp->GetSplineLength() / m_fDebugMeshDist);

	// 컴포넌트 갯수 맞추기
	if (m_DebugMeshComps.Num() != nDebugMeshCount)
	{
		// 많으면 삭제한다.
		for (int i = m_DebugMeshComps.Num() - 1; i > nDebugMeshCount; --i)
		{
			m_DebugMeshComps[i]->DestroyComponent();
			m_DebugMeshComps.RemoveAt(i);
		}

		// 적으면 추가한다.
		while (m_DebugMeshComps.Num() < nDebugMeshCount)
		{
			auto pMeshComp = NewObject<UStaticMeshComponent>(this);
			pMeshComp->SetupAttachment(m_pSplineComp);
			pMeshComp->SetStaticMesh(m_pDebugMesh);
			pMeshComp->SetMaterial(0, m_pDebugMat);
			pMeshComp->SetWorldScale3D(FVector::OneVector * 0.1f);
			m_DebugMeshComps.Add(pMeshComp);
		}
	}

	for (int i = 0 ; i < nDebugMeshCount; ++i)
	{
		FVector vWorldPos = m_pSplineComp->GetLocationAtDistanceAlongSpline(m_fDebugMeshDist * i, ESplineCoordinateSpace::World);
		FRotator qWorldRot = m_pSplineComp->GetRotationAtDistanceAlongSpline(m_fDebugMeshDist * i, ESplineCoordinateSpace::World);
		FVector vLocalPos = trActor.InverseTransformPosition(vWorldPos);

		auto pDebugMeshComp = m_DebugMeshComps[i];

		pDebugMeshComp->SetRelativeLocation(vLocalPos);
		pDebugMeshComp->SetWorldRotation(qWorldRot);
		pDebugMeshComp->SetHiddenInGame(false);
	}
#else
	for (int i = 0 ; i < m_DebugMeshComps.Num(); ++i)
		 m_DebugMeshComps[i]->SetHiddenInGame(true);
#endif
}

#if WITH_EDITOR
void ASpawnPoint::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	ComputeSpline();
}
#endif
