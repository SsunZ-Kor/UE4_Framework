// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Client/Framework/ClientGameBase.h"
#include "GameFramework/Actor.h"
#include "SpawnTrigger.generated.h"

class ASpawnSystem;

UCLASS(Abstract)
class CLIENT_API ASpawnTrigger : public AActor
{
	GENERATED_BODY()

protected:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ASpawnSystem* m_pOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UShapeComponent* m_pShapeComp;
	
public:	
	// Sets default values for this actor's properties
	ASpawnTrigger();

protected:
	virtual void BeginPlay() override;

public:
	void Init(ASpawnSystem* const& pOwner);
	
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};