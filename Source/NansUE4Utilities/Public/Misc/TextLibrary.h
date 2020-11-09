#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/SecureHash.h"
#include "UObject/NoExportTypes.h"

#include "TextLibrary.generated.h"

#define ENUM_TO_STRING(EnumClassName, ValueOfEnum) \
	UNTextLibrary::GetEnumValueAsString<EnumClassName>(FString(TEXT(#EnumClassName)), (ValueOfEnum))

UCLASS()
class NANSUE4UTILITIES_API UNTextLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	template <typename TEnum>
	static FORCEINLINE FString GetEnumValueAsString(const FString& Name, TEnum Value)
	{
		const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!enumPtr)
		{
			return FString("(Invalid Enum)");
		}
		return enumPtr->GetNameStringByValue((int64) Value);
	}
	template <typename TEnum>
	static FORCEINLINE FString GetEnumValueAsString(const FString& Name, TArray<TEnum> Values)
	{
		FString JoinedStr;
		for (int32 Index = 0; Index != Values.Num(); ++Index)
		{
			JoinedStr += "(" + FString::FromInt(Index) + ")";
			JoinedStr += GetEnumValueAsString(Name, Values[Index]);
			JoinedStr += Index < Values.Num() - 1 ? TEXT(",") : TEXT("");
		}
		return JoinedStr;
	}

	UFUNCTION(BlueprintCallable, Category = "Utilities|Text")
	static FString UniqueStringFromName(const FName& Text)
	{
		return UNTextLibrary::UniqueString(Text);
	}

	UFUNCTION(BlueprintCallable, Category = "Utilities|Text")
	static FString UniqueStringFromText(const FText& Text)
	{
		return UNTextLibrary::UniqueString(Text);
	}

	// Return true is they are Permutations, false otherwise
	UFUNCTION(BlueprintCallable, Category = "Utilities|Text")
	static bool ComparePermutations(const FString& StringFrom, const FString& StringToCompare, TMap<FString, int32>& Results)
	{
		if (ArePermutations(StringFrom, StringToCompare) == false)
		{
			return false;
		}

		TMap<int32, TCHAR> ToCompareMap;
		int32 i = 0;
		for (auto& Str : StringToCompare)
		{
			ToCompareMap.Add(i, Str);
			i++;
		}
		i = 0;
		int32 Distance = 0;
		for (TCHAR Char : StringFrom)
		{
			const int32* Index = ToCompareMap.FindKey(Char);
			ToCompareMap[*Index] = *TEXT("");
			Distance = *Index - i;
			Results.Add(FString("") + Char, Distance);
			i++;
		}

		ToCompareMap.Empty();
		return true;
	}

	UFUNCTION(BlueprintCallable, Category = "Utilities|Text")
	static bool ArePermutations(const FString& String1, const FString& String2)
	{
		TArray<TCHAR> Chars1 = String1.TrimStart().GetCharArray();
		TArray<TCHAR> Chars2 = String2.TrimStart().GetCharArray();

		if (Chars1.Num() != Chars2.Num())
		{
			Chars1.Empty();
			Chars2.Empty();
			return false;
		}

		Chars1.Sort();
		Chars2.Sort();

		if (Chars1 != Chars2)
		{
			Chars1.Empty();
			Chars2.Empty();
			return false;
		}

		Chars1.Empty();
		Chars2.Empty();
		return true;
	}

	UFUNCTION(BlueprintCallable, Category = "Utilities|Text")
	static bool LettersAreInString(const FString& StringFrom, const FString& StringToCompare)
	{
		bool isIn = true;

		for (TCHAR Char : StringToCompare)
		{
			int32 Index;
			isIn = StringFrom.FindChar(Char, Index) && isIn;
		}

		return isIn;
	}

	template <typename T>
	static FORCEINLINE FString UniqueString(const T& Text)
	{
		return FMD5::HashAnsiString(*Text.ToString());
	}

	UFUNCTION(BlueprintCallable, Category = "Utilities|Text")
	static TArray<FString> StringTotWordsArray(const FString Text)
	{
		TArray<FString> Words;
		const FString Delimiter = FString(TEXT(" "));
		Text.ParseIntoArray(Words, *Delimiter);
		return Words;
	}

	UFUNCTION(BlueprintCallable, Category = "Utilities|Text")
	static TArray<FString> StringToLinesArray(const FString Text, int32 MaxCharPerLine = 100)
	{
		TArray<FString> CurrentLines;
		Text.ParseIntoArrayLines(CurrentLines);
		TArray<FString> Lines;

		for (FString CurLine : CurrentLines)
		{
			TArray<FString> Words = UNTextLibrary::StringTotWordsArray(CurLine);
			int32 CharCounter = 0;
			FString TempLine;

			for (FString Word : Words)
			{
				CharCounter += Word.Len() + 1;	  // +1 for empty space
				if (CharCounter >= MaxCharPerLine)
				{
					CharCounter = 0;
					Lines.Add(TempLine.TrimEnd());
					TempLine.Empty();
				}
				TempLine.Append(Word + " ");
			}

			if (!TempLine.IsEmpty())
			{
				Lines.Add(TempLine.TrimEnd());
				TempLine.Empty();
			}
		}

		return Lines;
	}

	UFUNCTION(BlueprintCallable, Category = "Utilities|Text")
	static FString StringToLines(
		const FString Text, int32 MaxCharPerLine = 100, FString PrependLine = "", FString AppendLine = "\n")
	{
		TArray<FString> Lines = UNTextLibrary::StringToLinesArray(Text, MaxCharPerLine);
		FString FinalText;

		for (FString Line : Lines)
		{
			FinalText.Append(PrependLine + Line + AppendLine);
		}

		return FinalText.TrimEnd();
	}
};
