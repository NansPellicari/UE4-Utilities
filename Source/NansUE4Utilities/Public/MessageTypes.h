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

#include "MessageTypes.generated.h"

UENUM(BlueprintType)
enum class EFlashMessagePriorityLevel : uint8
{
	NORMAL,
	ERROR,
	HIGH,
	LOW
};


USTRUCT(BlueprintType)
struct NANSUE4UTILITIES_API FNFlashMessage
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Message")
	FText Message;
	// If TimeDuration > 0 the message will be display during the time specified(in seconds)
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Message")
	float TimeDuration = 0;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Message")
	EFlashMessagePriorityLevel PriorityLevel = EFlashMessagePriorityLevel::NORMAL;

	void Clear()
	{
		Message = FText::GetEmpty();
		TimeDuration = 0.f;
		PriorityLevel = EFlashMessagePriorityLevel::NORMAL;
	}
};

USTRUCT()

struct NANSUE4UTILITIES_API FNFlashMessageList
{
	GENERATED_BODY()

	TArray<FNFlashMessage> Low;
	TArray<FNFlashMessage> Normal;
	TArray<FNFlashMessage> High;
	TArray<FNFlashMessage> Error;

	void Add(FNFlashMessage Message)
	{
		switch (Message.PriorityLevel)
		{
			case EFlashMessagePriorityLevel::ERROR:
				Error.Add(Message);
				break;
			case EFlashMessagePriorityLevel::HIGH:
				High.Add(Message);
				break;
			case EFlashMessagePriorityLevel::LOW:
				Low.Add(Message);
				break;
			case EFlashMessagePriorityLevel::NORMAL:
			default:
				Normal.Add(Message);
				break;
		}
	}

	FNFlashMessage GetMessage()
	{
		if (Error.Num() > 0) return Error.Pop();
		if (High.Num() > 0) return High.Pop();
		if (Normal.Num() > 0) return Normal.Pop();
		if (Low.Num() > 0) return Low.Pop();
		return FNFlashMessage();
	}

	void Clear()
	{
		Low.Empty();
		Normal.Empty();
		High.Empty();
		Error.Empty();
	}

	bool IsEmpty() const
	{
		return Error.Num() <= 0 && High.Num() <= 0 && Normal.Num() <= 0 && Low.Num() <= 0;
	}
};
