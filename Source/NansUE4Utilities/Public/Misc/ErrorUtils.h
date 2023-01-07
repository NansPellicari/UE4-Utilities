#pragma once

#include "CoreMinimal.h"
#include "Logging/MessageLog.h"
#include "Runtime/CoreUObject/Public/Misc/UObjectToken.h"
#include "UObject/NoExportTypes.h"
#include "Engine/Engine.h"
#include "EngineGlobals.h"


#define EDITOR_ERROR_1(MsgChannel, Text) UNErrorUtils::ThrowErrorToEditor(MsgChannel, Text, this, __LINE__);
#define EDITOR_ERROR_2(MsgChannel, Text, Object) UNErrorUtils::ThrowErrorToEditor(MsgChannel, Text, Cast<UObject>(Object), __LINE__);
#define EDITOR_ERROR_0()
#define EDITOR_WARN_1(MsgChannel, Text) UNErrorUtils::ThrowWarningToEditor(MsgChannel, Text, this, __LINE__);
#define EDITOR_WARN_2(MsgChannel, Text, Object) UNErrorUtils::ThrowWarningToEditor(MsgChannel, Text, Cast<UObject>(Object), __LINE__);
#define EDITOR_WARN_0()

// thanks to https://github.com/jason-deng/C99FunctionOverload
#define FUNC_CHOOSER(_f1, _f2, _f3, _f4, ...) _f4
#define FUNC_RECOMPOSER(argsWithParentheses) FUNC_CHOOSER argsWithParentheses

#define CHOOSE_FROM_ARG_COUNT(...) FUNC_RECOMPOSER((__VA_ARGS__, EDITOR_ERROR_2, EDITOR_ERROR_1, ))
#define NO_ARG_EXPANDER() , , EDITOR_ERROR_0
#define MACRO_CHOOSER(...) CHOOSE_FROM_ARG_COUNT(NO_ARG_EXPANDER __VA_ARGS__())

#define CHOOSE_FROM_ARG_COUNT_WARN(...) FUNC_RECOMPOSER((__VA_ARGS__, EDITOR_WARN_2, EDITOR_WARN_1, ))
#define NO_ARG_EXPANDER_WARN() , , EDITOR_WARN_0
#define MACRO_CHOOSER_WARN(...) CHOOSE_FROM_ARG_COUNT_WARN(NO_ARG_EXPANDER_WARN __VA_ARGS__())

#define EDITOR_ERROR(...) MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)
#define EDITOR_WARN(...) MACRO_CHOOSER_WARN(__VA_ARGS__)(__VA_ARGS__)

#define SCREEN_LOG(duration, color, format, ...) \
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, duration, color, FString::Printf(TEXT(format), ##__VA_ARGS__), false)


class UNErrorUtils
{
public:
	static void ThrowErrorToEditor(const FName& LogMsgChannel, const FText& Text, const UObject* Object,
		const int32& Line = -1)
	{
		bool bValidObject = IsValid(Object) && !Object->HasAnyFlags(
								EObjectFlags::RF_BeginDestroyed | EObjectFlags::RF_FinishDestroyed
							)
							&& IsValid(Object->GetOuter()) && IsValid(Object->GetWorld());
#if WITH_EDITOR
		if (bValidObject)
		{
			auto Message = FMessageLog(LogMsgChannel).Error();
			Message->AddToken(FTextToken::Create(Text))->AddToken(FUObjectToken::Create((UObject*)Object));
			if (Line >= 0)
			{
				Message->AddToken(
					FTextToken::Create(
						FText::Format(NSLOCTEXT("Error", "LineNumber", "- line {0}"), FText::AsNumber(Line))
					)
				);
			}
		}
#endif

		UE_LOG(
			LogTemp,
			Error,
			TEXT("%s (%s) - line %d"),
			*Text.ToString(),
			bValidObject ? *Object->GetName() : TEXT("Unknown"),
			Line
		);
	}

	static void ThrowWarningToEditor(const FName& InLogChannel, const FText& InText, const UObject* InObject,
	                                 const int32& InLine = -1)
	{
		bool bValidObject = IsValid(InObject) && !InObject->HasAnyFlags(
								EObjectFlags::RF_BeginDestroyed | EObjectFlags::RF_FinishDestroyed
							)
							&& IsValid(InObject->GetOuter()) && IsValid(InObject->GetWorld());
#if WITH_EDITOR
		if (bValidObject)
		{
			auto Message = FMessageLog(InLogChannel).Warning();
			Message->AddToken(FTextToken::Create(InText))->AddToken(FUObjectToken::Create((UObject*)InObject));
			if (InLine >= 0)
			{
				Message->AddToken(
					FTextToken::Create(
						FText::Format(NSLOCTEXT("Error", "LineNumber", "- line {0}"), FText::AsNumber(InLine))
					)
				);
			}
		}
#endif

		UE_LOG(
			LogTemp,
			Warning,
			TEXT("%s (%s) - line %d"),
			*InText.ToString(),
			bValidObject ? *InObject->GetName() : TEXT("Unknown"),
			InLine
		);
	}
};
