// Fill out your copyright notice in the Description page of Project Settings.


#include "ULoading_AnimInOut.h"

void ULoading_AnimInOut::Open()
{
	PlayAnimation(GetAnimation("OpenAnim"));
}

void ULoading_AnimInOut::Close()
{
	PlayAnimation(GetAnimation("CloseAnim"));
}
