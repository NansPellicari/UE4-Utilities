//  Copyright 2020-present Nans Pellicari (nans.pellicari@gmail.com).
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "CoreMinimal.h"
#include "NansComparatorHelpers.h"
#include "Logging/MessageLog.h"
#include "Runtime/CoreUObject/Public/Misc/UObjectToken.h"
#include "UObject/NoExportTypes.h"
#include "NansComparator.generated.h"

#define LOCTEXT_NAMESPACE "ServiceNansComparator"

/**
 * 
 */
UCLASS()
class NANSUE4UTILITIES_API UNansComparator : public UObject
{
	GENERATED_BODY()

public:
	static bool EvaluateOperators(const TArray<FNansConditionOperator>& ConditionsOperators,
		TMap<FString, BoolStruct*>& ConditionsResults, bool bDebug = false);
	static bool EvaluateOperator(const ENConditionOperator Operator, const bool Val1, const bool Val2);
	static FString BuildKeyFromIndex(const int32 Index);
	template <typename ValueToComp>
	static bool EvaluateComparator(const ENConditionComparator NansComparator, const ValueToComp Val1,
		const ValueToComp Val2);
	static FString ComparatorToString(ENConditionComparator NansComparator);
	static FString OperatorsToString(TArray<FNansConditionOperator> ConditionsOperators, FString PrefixChar = "\n");
	static FString OperatorToString(FNansConditionOperator Condition);
};

template <typename ValueToComp>
FORCEINLINE bool UNansComparator::EvaluateComparator(
	const ENConditionComparator NansComparator,
	const ValueToComp Val1,
	const ValueToComp Val2
)
{
	switch (NansComparator)
	{
		case ENConditionComparator::Equals:
			return Val1 == Val2;
		case ENConditionComparator::Inferior:
			return Val1 < Val2;
		case ENConditionComparator::InferiorOrEquals:
			return Val1 <= Val2;
		case ENConditionComparator::Superior:
			return Val1 > Val2;
		case ENConditionComparator::SuperiorOrEquals:
			return Val1 >= Val2;
		case ENConditionComparator::NotEquals:
			return Val1 != Val2;
		default:
#if WITH_EDITOR
			UE_LOG(
				LogTemp,
				Warning,
				TEXT("%s You need to set a comparator to allow comparison "),
				ANSI_TO_TCHAR(__FUNCTION__)
			);
#endif
			return false;
	}
}

#undef LOCTEXT_NAMESPACE
