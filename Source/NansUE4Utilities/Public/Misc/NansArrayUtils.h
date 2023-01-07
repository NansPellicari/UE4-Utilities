// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NansArrayUtils.generated.h"

template <typename ValueType>
struct FPermutationValue
{
public:
	FPermutationValue(int32 _Key, ValueType _Value) : Key(_Key), Value(_Value)
	{
	};
	int32 Key;
	ValueType Value;
};

struct FPermutationChances
{
public:
	FString Possibility;
	int32 TotalChances = 0;
};

/**
 * 
 */
UCLASS()
class NANSUE4UTILITIES_API UNansArrayUtils : public UObject
{
	GENERATED_BODY()

public:
	static TArray<FPermutationValue<TCHAR>> StringToPermutationArray(const FString Text)
	{
		TArray<FPermutationValue<TCHAR>> arr;
		int32 i = 0;
		for (TCHAR chara : Text)
		{
			FPermutationValue<TCHAR> val = FPermutationValue<TCHAR>(++i, chara);
			arr.Add(val);
		}

		return arr;
	}

	// Convert this from http://wordaligned.org/articles/next-permutation
	// To UE4 compatibility
	template <typename ValueType>
	static bool NextPermutation(TArray<FPermutationValue<ValueType>>& arr)
	{
		auto first = arr.CreateIterator();
		auto last = arr.CreateIterator();
		last.SetToEnd();

		if (first == last)
		{
			return false;
		}
		auto i1 = first;
		++i1;
		if (i1 == last)
		{
			return false;
		}

		auto i = last;
		--i;

		for (;;)
		{
			auto ii = i;
			--i;
			FPermutationValue<ValueType> iVal = *i;
			FPermutationValue<ValueType> iiVal = *ii;
			if (iVal.Key < iiVal.Key)
			{
				auto j = last;
				--j;
				FPermutationValue<ValueType> jVal = *j;
				while (!(iVal.Key < jVal.Key))
				{
					--j;
					jVal = *j;
				}
				arr.Swap(i.GetIndex(), j.GetIndex());
				UNansArrayUtils::ReverseRange(arr, ii, last);
				return true;
			}
			if (i == first)
			{
				UNansArrayUtils::ReverseRange(arr, first, last);
				return false;
			}
		}
	}

	template <typename Iter, typename ValueType>
	static void ReverseRange(TArray<FPermutationValue<ValueType>>& arr, Iter first, Iter last)
	{
		while ((first != last) && (first != --last))
		{
			arr.Swap(first.GetIndex(), last.GetIndex());
			++first;
		}
	}

	static FString ToString(TArray<int32> Arr)
	{
		FString Str = "";
		for (int32 Index = 0; Index != Arr.Num(); ++Index)
		{
			Str += FString::Printf(TEXT("%i"), Arr[Index]);
			if (Index < Arr.Num() - 1)
			{
				Str += ", ";
			}
		}
		return Str;
	}
};
