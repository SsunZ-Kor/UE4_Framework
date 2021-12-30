// Fill out your copyright notice in the Description page of Project Settings.


#include "ImmortalWidget.h"

UImmortalWidget::UImmortalWidget(const FObjectInitializer& ObjectInitializer)
	:UUserWidget(ObjectInitializer)
{
	m_bIsInit_WidgetAnim = false;
}

void UImmortalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!m_bIsInit_WidgetAnim)
	{
		// Animation Map Init
		m_bIsInit_WidgetAnim = true;

		UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();
		
		for (int i = 0; i < WidgetClass->Animations.Num(); i++) {
     
			FString Name = WidgetClass->Animations[i]->GetName();
			m_map_WidgetAnim.Add(Name.Replace(TEXT("_INST"), TEXT("")), WidgetClass->Animations[i]);
		}
	}
}

void UImmortalWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	// 레벨 변경시 UI를 제거하지 않도록 한다.
	//Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}

UWidgetAnimation* UImmortalWidget::GetAnimation(const FString& animName)
{
	if (m_map_WidgetAnim.Contains(animName))
		return m_map_WidgetAnim[animName];

	return nullptr;
}