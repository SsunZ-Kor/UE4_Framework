#pragma once

#include "EngineMinimal.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"
#include "EngineGlobals.h"
#include "Utils/GenericEx.h"
#include "Utils/UnrealEx.h"

DECLARE_LOG_CATEGORY_EXTERN(GAME, Log, All);
#define	LOG_CALLINFO	(FString(__FUNCTION__) + TEXT("{") + FString::FromInt(__LINE__) + TEXT("}"))
#define	LOG(Format, ...)	UE_LOG(GAME, Display, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define	LOG_WARNING(Format, ...)	UE_LOG(GAME, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define	LOG_ERROR(Format, ...)	UE_LOG(GAME, Error, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

void PrintViewport(float Time, const FColor& Color, const FString& Text);