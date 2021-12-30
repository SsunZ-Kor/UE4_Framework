// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Client/Framework/ClientGameBase.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "PhysicalMaterialLandscape.generated.h"

UENUM()
enum class ELandscapeTypes
{
	Glass,
};

UCLASS()
class CLIENT_API UPhysicalMaterialLandscape : public UPhysicalMaterial
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ELandscapeTypes m_LandscapeType;

public:
	const ELandscapeTypes& GetLandscapeTypes() const; 
};