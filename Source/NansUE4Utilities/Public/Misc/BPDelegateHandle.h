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

#include "BPDelegateHandle.generated.h"

// #define CONCAT_NAME(a,b) a ## b
//
// #define BINDTO_BODY() \
// auto Delegate = TBaseDelegate<void>::CreateLambda( \
// 	[Functor]() \
// 	{ \
// 		Functor.ExecuteIfBound(); \
// 	});
//
// #define BINDTO_BODY_OneParam(ParamType1) \
// 	auto Delegate = TBaseDelegate<void, ParamType1>::CreateLambda( \
// 		[Functor](ParamType1 param1) \
// 		{ \
// 			Functor.ExecuteIfBound(param1); \
// 		});
// #define BINDTO_BODY_TwoParams(ParamType1, ParamType2) \
// 	auto Delegate = TBaseDelegate<void, ParamType1, ParamType2>::CreateLambda( \
// 		[Functor](ParamType1 Param1, ParamType2 Param2) \
// 		{ \
// 			Functor.ExecuteIfBound(Param1, Param2); \
// 		});
// #define BINDTO_BODY_ThreeParams(ParamType1, ParamType2, ParamType3) \
// 	auto Delegate = TBaseDelegate<void, ParamType1, ParamType2>::CreateLambda( \
// 		[Functor](ParamType1 Param1, ParamType2 Param2, ParamType3 Param3) \
// 		{ \
// 			Functor.ExecuteIfBound(Param1, Param2, Param3); \
// 		});
// #define BINDTO_BODY_FourParams(ParamType1, ParamType2, ParamType3, ParamType4) \
// 	auto Delegate = TBaseDelegate<void, ParamType1, ParamType2>::CreateLambda( \
// 		[Functor](ParamType1 Param1, ParamType2 Param2, ParamType3 Param3, ParamType4 Param4) \
// 		{ \
// 			Functor.ExecuteIfBound(Param1, Param2, Param3, Param4); \
// 		});
//
// // thanks to https://github.com/jason-deng/C99FunctionOverload
// #define MYDELEGATE_FUNC_CHOOSER(_f1, _f2, _f3, _f4, _f5, ...) _f5
// #define MYDELEGATE_FUNC_RECOMPOSER(argsWithParentheses) MYDELEGATE_FUNC_CHOOSER argsWithParentheses
// #define MYDELEGATE_CHOOSE_FROM_ARG_COUNT(...) MYDELEGATE_FUNC_RECOMPOSER((__VA_ARGS__, BINDTO_BODY_FourParams, BINDTO_BODY_ThreeParams, BINDTO_BODY_TwoParams, BINDTO_BODY_OneParam, ))
// #define MYDELEGATE_NO_ARG_EXPANDER() ,,,,BINDTO_BODY
// #define MYDELEGATE_MACRO_CHOOSER(...) MYDELEGATE_CHOOSE_FROM_ARG_COUNT(MYDELEGATE_NO_ARG_EXPANDER __VA_ARGS__())
//
// #define DECLARE_UNBIND_TO_IMPL(DelegateName) \
// 	virtual void CONCAT_NAME(UnbindTo,DelegateName)_Implementation(FBPDelegateHandle& Handle) override\
// 	{\
// 		if (Handle.RealHandle.IsValid())\
// 		{\
// 			CONCAT_NAME(DelegateName,Event).Remove(Handle.RealHandle);\
// 			Handle.RealHandle.Reset();\
// 		}\
// 	}
// #define DECLARE_BIND_TO_IMPL(DelegateName, EventType, ...) \
// 	virtual FBPDelegateHandle CONCAT_NAME(BindTo,DelegateName)_Implementation(const EventType& Functor) override \
// 	{ \
// 		MYDELEGATE_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__) \
// 		return FBPDelegateHandle(CONCAT_NAME(DelegateName,Event).Add(Delegate)); \
// 	}
// #define DECLARE_BIND_UNBIND_TO_IMPL(DelegateName, EventType, NativeEventType, ...) \
//  	DECLARE_BIND_TO_IMPL(CONCAT_NAME(On,DelegateName), EventType, __VA_ARGS__) \
//  	DECLARE_UNBIND_TO_IMPL(CONCAT_NAME(On,DelegateName))\
// 	virtual NativeEventType CONCAT_NAME(OnNative,DelegateName)() override\
// 	{\
// 		return CONCAT_NAME(On,DelegateName)Event;\
// 	}


USTRUCT(BlueprintType)
struct NANSUE4UTILITIES_API FBPDelegateHandle
{
	GENERATED_BODY()
public:
	FBPDelegateHandle() {};
	FBPDelegateHandle(FDelegateHandle MyHandle) : RealHandle(MyHandle) {};
	FDelegateHandle RealHandle;
};
