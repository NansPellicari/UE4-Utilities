#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "EngineGlobals.h"
#include "Logging/MessageLog.h"
#include "Runtime/CoreUObject/Public/Misc/UObjectToken.h"
#include "UObject/NoExportTypes.h"

#if WITH_EDITOR
#define EDITOR_ERROR(MsgChannel, Text, Object) UNErrorUtils::ThrowErrorToEditor(MsgChannel, Text, Object, __LINE__);
#define EDITOR_WARN(...) UNErrorUtils::ThrowWarningToEditor(__VA_ARGS__, this, __LINE__);
#define SCREEN_LOG(duration, color, format, ...) \
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, duration, color, FString::Printf(TEXT(format), ##__VA_ARGS__), false)
#else
#define EDITOR_ERROR(...)
#define EDITOR_WARN(...)
#define SCREEN_LOG(duration, color, format, ...)
#endif

#if WITH_EDITOR
class UNErrorUtils
{
public:
	static void ThrowErrorToEditor(const FName& LogMsgChannel, const FText& Text, const UObject* Object, const int32& Line = -1)
	{
		auto Message = FMessageLog(LogMsgChannel).Error();
		Message->AddToken(FTextToken::Create(Text))->AddToken(FUObjectToken::Create((UObject*) Object));
		if (Line >= 0)
		{
			Message->AddToken(
				FTextToken::Create(FText::Format(NSLOCTEXT("Error", "LineNumber", "- line {0}"), FText::AsNumber(Line))));
		}

		UE_LOG(LogTemp, Error, TEXT("%s (%s) - line %d"), *Text.ToString(), *Object->GetName(), Line);
	}
	static void ThrowWarningToEditor(const FName& LogChannel, const FText& Text, const UObject* Object, const int32& Line = -1)
	{
		auto Message = FMessageLog(LogChannel).Warning();
		Message->AddToken(FTextToken::Create(Text))->AddToken(FUObjectToken::Create((UObject*) Object));
		if (Line >= 0)
		{
			Message->AddToken(
				FTextToken::Create(FText::Format(NSLOCTEXT("Error", "LineNumber", "- line {0}"), FText::AsNumber(Line))));
		}

		UE_LOG(LogTemp, Warning, TEXT("%s (%s) - line %d"), *Text.ToString(), *Object->GetName(), Line);
	}
};
#endif
