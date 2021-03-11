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

#include "AI/BehaviorTree/BTTask_NotifyAIOnAbort.h"

#include "AIController.h"
#include "AI/AITaskAbortAware.h"

UBTTask_NotifyAIOnAbort::UBTTask_NotifyAIOnAbort(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bNotifyTaskFinished = true;
}

void UBTTask_NotifyAIOnAbort::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	if (TaskResult != EBTNodeResult::Aborted) return;

	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!IsValid(Pawn)) return;

	TArray<UActorComponent*> Comps = Pawn->GetComponentsByInterface(UAITaskAbortAware::StaticClass());

	for (auto Comp : Comps)
	{
		IAITaskAbortAware* AITaskAware = Cast<IAITaskAbortAware>(Comp);
		AITaskAware->OnBTTaskAbort(OwnerComp, NodeMemory);
	}
}

UBTTask_NotifyAIOnAbortBP::UBTTask_NotifyAIOnAbortBP(const FObjectInitializer& ObjectInitializer) : Super(
	ObjectInitializer
)
{
	bNotifyTaskFinished = true;
}

void UBTTask_NotifyAIOnAbortBP::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	if (TaskResult != EBTNodeResult::Aborted) return;

	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!IsValid(Pawn)) return;

	TArray<UActorComponent*> Comps = Pawn->GetComponentsByInterface(UAITaskAbortAware::StaticClass());

	for (auto Comp : Comps)
	{
		IAITaskAbortAware* AITaskAware = Cast<IAITaskAbortAware>(Comp);
		AITaskAware->OnBTTaskAbort(OwnerComp, NodeMemory);
	}
}
