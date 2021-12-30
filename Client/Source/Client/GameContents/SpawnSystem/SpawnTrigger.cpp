// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnTrigger.h"

#include "SpawnSystem.h"
#include "Components/CapsuleComponent.h"
#include "Components/ShapeComponent.h"

// Sets default values
ASpawnTrigger::ASpawnTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ASpawnTrigger::BeginPlay()
{
	Super::BeginPlay();

	m_pShapeComp->OnComponentBeginOverlap.AddDynamic(this, &ASpawnTrigger::OnTriggerBeginOverlap);
	m_pShapeComp->SetCollisionProfileName("PlayerTrigger");
}

void ASpawnTrigger::Init(ASpawnSystem* const& pOwner)
{
	m_pOwner = pOwner;
	SetActorEnableCollision(false);
}

void ASpawnTrigger::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (m_pOwner)
		m_pOwner->OnTrigger();
}
