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

#pragma once

#include "NansComparatorHelpers.generated.h"

UENUM(BlueprintType)
enum class ENConditionComparator : uint8
{
	Equals UMETA(DisplayName = "=="),
	Superior UMETA(DisplayName = ">"),
	SuperiorOrEquals UMETA(DisplayName = ">="),
	Inferior UMETA(DisplayName = "<"),
	InferiorOrEquals UMETA(DisplayName = "<="),
	NotEquals UMETA(DisplayName = "!=")
};

UENUM(BlueprintType)
enum class ENConditionOperator : uint8
{
	AND UMETA(DisplayName = "AND"),
	OR UMETA(DisplayName = "OR"),
	XOR UMETA(DisplayName = "XOR"),
	Save UMETA(DisplayName = "Save")
};

struct BoolStruct
{
	bool value;
	BoolStruct(bool _val = true) : value(_val) {};
};

/**
 * This is a structure to create a condition with 2 Operand
 */
USTRUCT(BlueprintType)
struct NANSUE4UTILITIES_API FNansConditionOperator
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Condition operator")
	ENConditionOperator OperatorWithPreviousCondition = ENConditionOperator::AND;

	// Can be a condition (eg. "C1") or a group of condition specified in previous Condition Operator (eg. "G1") 
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Condition operator")
	FString Operand1;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Condition operator")
	ENConditionOperator Operator = ENConditionOperator::AND;

	// Can be a condition (eg. "C1") or a group of condition specified in this kind of settings (eg. "G1")
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Condition operator")
	FString Operand2;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Condition operator")
	bool Inversed = false;

	// this allow to save this condition result and re-use it later on another Condition Operator (eg. "G1")
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Condition operator")
	FString GroupName = FString("None");
};
