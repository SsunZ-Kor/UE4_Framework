// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBoxTrigger.h"

ASpawnBoxTrigger::ASpawnBoxTrigger()
{
	m_pShapeComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(m_pShapeComp);
}