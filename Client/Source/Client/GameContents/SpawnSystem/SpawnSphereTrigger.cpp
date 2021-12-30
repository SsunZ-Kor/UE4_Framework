// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnSphereTrigger.h"

ASpawnSphereTrigger::ASpawnSphereTrigger()
{
	m_pShapeComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(m_pShapeComp);
}