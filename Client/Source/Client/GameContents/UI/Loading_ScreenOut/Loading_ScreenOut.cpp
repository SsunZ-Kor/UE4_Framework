// Fill out your copyright notice in the Description page of Project Settings.


#include "Loading_ScreenOut.h"

#include "Animation/WidgetAnimationPlayCallbackProxy.h"

void ULoading_ScreenOut::Open()
{
	// Todo :: 머티리얼 공부좀 더하고 해보자
	//if (pTex_Screen == nullptr)
	//{
	//	pTex_Screen = UTexture2D::CreateTransient(
	//		GSystemResolution.ResX,
	//		GSystemResolution.ResY,
	//		PF_B8G8R8A8,
	//		TEXT("Tex_Screen")
	//		);
	//}

	// 끝났음을 알린다.
	OnEndAnim_Open();
}

void ULoading_ScreenOut::Close()
{
	PlayAnimation(GetAnimation("CloseAnim"));
}