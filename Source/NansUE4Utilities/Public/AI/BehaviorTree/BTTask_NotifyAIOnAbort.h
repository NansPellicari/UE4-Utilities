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

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"

#include "BTTask_NotifyAIOnAbort.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class NANSUE4UTILITIES_API UBTTask_NotifyAIOnAbort : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UBTTask_NotifyAIOnAbort(const FObjectInitializer& ObjectInitializer);
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
		EBTNodeResult::Type TaskResult) override;
};

UCLASS(Abstract, BlueprintType, Blueprintable)
class NANSUE4UTILITIES_API UBTTask_NotifyAIOnAbortBP : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

protected:
	UBTTask_NotifyAIOnAbortBP(const FObjectInitializer& ObjectInitializer);
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
		EBTNodeResult::Type TaskResult) override;
};
