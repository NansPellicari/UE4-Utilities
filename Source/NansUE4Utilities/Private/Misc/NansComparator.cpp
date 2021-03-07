// Copyright 2020-present Nans Pellicari (nans.pellicari@gmail.com).
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

#include "Misc/NansComparator.h"

#include "Misc/ErrorUtils.h"
#include "Misc/TextLibrary.h"

#define LOCTEXT_NAMESPACE "NansComparator"

bool UNansComparator::EvaluateOperator(const ENansConditionOperator Operator, const bool Val1, const bool Val2)
{
	bool Result = true;
	switch (Operator)
	{
		case ENansConditionOperator::XOR:
			Result = Val1 == !Val2;
			break;
		case ENansConditionOperator::OR:
			Result = Val1 || Val2;
			break;
		default:
			Result = Val1 && Val2;
			break;
	}

	return Result;
}

bool UNansComparator::EvaluateOperators(
	const TArray<FNansConditionOperator>& ConditionsOperators, TMap<FString, BoolStruct*>& ConditionsResults,
	bool bDebug)
{
	bool FinalResult = true;
	for (FNansConditionOperator ConditionOperator : ConditionsOperators)
	{
		BoolStruct* ValueOfGroup = ConditionsResults.FindRef(ConditionOperator.GroupName);

		if (!ConditionOperator.GroupName.Equals(TEXT("None"), ESearchCase::IgnoreCase) && !ConditionOperator.GroupName.
			IsEmpty() &&
			ValueOfGroup != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s The group name %s has been already set"), ANSI_TO_TCHAR(__FUNCTION__));
			return false;
		}

		BoolStruct* Operand1 = ConditionsResults.FindRef(ConditionOperator.Operand1);
		BoolStruct* Operand2 = ConditionsResults.FindRef(ConditionOperator.Operand2);

		if (Operand1 == nullptr || Operand2 == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s Operand %s does not exists"), ANSI_TO_TCHAR(__FUNCTION__));
			return false;
		}

		bool Result = EvaluateOperator(ConditionOperator.Operator, Operand1->value, Operand2->value);

		Result = ConditionOperator.Inversed ? !Result : Result;
		if (ConditionOperator.OperatorWithPreviousCondition == ENansConditionOperator::Save)
		{
			FinalResult = Result;
		}
		else
		{
			FinalResult = EvaluateOperator(ConditionOperator.OperatorWithPreviousCondition, FinalResult, Result);
		}
		if (bDebug)
		{
			UE_LOG(
				LogTemp,
				Display,
				TEXT("%s %s == %i"),
				ANSI_TO_TCHAR(__FUNCTION__),
				*OperatorToString(ConditionOperator),
				FinalResult
			);
		}

		if (ConditionOperator.GroupName.Equals(TEXT("None"), ESearchCase::IgnoreCase) || ConditionOperator.GroupName.
			IsEmpty())
		{
			continue;
		}

		ConditionsResults.Add(ConditionOperator.GroupName, new BoolStruct(Result));
	}

	return FinalResult;
}

FString UNansComparator::BuildKeyFromIndex(const int32 Index)
{
	return FString("C") + FString::FromInt(Index);
}

FString UNansComparator::ComparatorToString(ENansConditionComparator NansComparator)
{
	switch (NansComparator)
	{
		case ENansConditionComparator::Inferior:
			return FString("<");
		case ENansConditionComparator::InferiorOrEquals:
			return FString("<=");
		case ENansConditionComparator::Superior:
			return FString(">");
		case ENansConditionComparator::SuperiorOrEquals:
			return FString(">=");
		case ENansConditionComparator::NotEquals:
			return FString("!=");
		case ENansConditionComparator::Equals:
		default:
			return FString("==");
	}
}

FString UNansComparator::OperatorsToString(TArray<FNansConditionOperator> ConditionsOperators, FString PrefixChar)
{
	FString ReturnDesc;

	for (int32 Index = 0; Index != ConditionsOperators.Num(); ++Index)
	{
		FNansConditionOperator Condition = ConditionsOperators[Index];

		ReturnDesc += FString::Printf(
			TEXT("%s%s"),
			*PrefixChar,
			*OperatorToString(Condition)
		);
	}
	return ReturnDesc;
}

FString UNansComparator::OperatorToString(FNansConditionOperator Condition)
{
	return FString::Printf(
		TEXT("(%s) %s %s %s%s GroupName: %s"),
		*ENUM_TO_STRING(ENansConditionOperator, Condition.OperatorWithPreviousCondition),
		*Condition.Operand1,
		*ENUM_TO_STRING(ENansConditionOperator, Condition.Operator),
		*Condition.Operand2,
		*(Condition.Inversed ? FString("(IsInversed)") : FString("")),
		*Condition.GroupName
	);
}

#undef LOCTEXT_NAMESPACE
