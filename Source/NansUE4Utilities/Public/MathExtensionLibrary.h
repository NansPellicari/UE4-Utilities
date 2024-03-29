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
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "NansCoreHelpers/Public/Math/MathUtilities.h"

#include "MathExtensionLibrary.generated.h"

struct NANSUE4UTILITIES_API FDrawLines
{
	FVector2D Position;
	FColor Color;

	FDrawLines(FVector2D _Position, FColor _Color) : Position(_Position),
													 Color(_Color) {}
};

USTRUCT(BlueprintType)
struct NANSUE4UTILITIES_API FTrigonometryDataForZone
{
	GENERATED_USTRUCT_BODY()

public:
	/**
	 * This is the pivot point align on the z-axis with other point,
	 * this to ease computation with single plan (X,Y)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "TrigonometryDataForZone")
	FVector PivotPointNormalized = FVector::ZeroVector;

	/** Length from the pivot point to the ZoneCenter */
	UPROPERTY(BlueprintReadOnly, Category = "TrigonometryDataForZone")
	float RadiusToZoneCenter = 0.f;

	/**
	 * The point at the intersection on the radius (pivot point > zone center)
	 * and the Zone border.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "TrigonometryDataForZone")
	FVector PointOnZoneBorder = FVector::ZeroVector;

	/** Length from the pivot point to the ZoneBorder */
	UPROPERTY(BlueprintReadOnly, Category = "TrigonometryDataForZone")
	float RadiusToZoneBorder = 0;

	/** Length from the pivot point to the Zone corner = Hypotenuse */
	UPROPERTY(BlueprintReadOnly, Category = "TrigonometryDataForZone")
	float PivotToCornerLength = 0;

	/** Hypotenuse = PivotToCornerLength, Radius = RadiusToZoneBorder */
	UPROPERTY(BlueprintReadOnly, Category = "TrigonometryDataForZone")
	float RadiusToHypotenuseDegree = 0;

	/** Point on corner coordinate (Z depends on the zone center @see PivotPointNormalized) */
	UPROPERTY(BlueprintReadOnly, Category = "TrigonometryDataForZone")
	FVector RightCorner = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "TrigonometryDataForZone")
	FVector LeftCorner = FVector::ZeroVector;

	TCorners GetCorners() const
	{
		return {LeftCorner, RightCorner};
	};
};

/**
 *
 */
UCLASS()
class NANSUE4UTILITIES_API UMathExtensionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Math|Extension", meta = (WorldContext = "WorldContextObject"))
	static FBox CreateBoxFromInitAndExtend(const FVector& Origin,
		const FVector& Extent,
		const FRotator& Rotation,
		bool bDebug = false,
		const UObject* WorldContextObject = nullptr,
		FColor Color = FColor(255, 255, 0));

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Extension")
	static bool IsBoxIntersect(const FBox& Box1, const FBox& Box2)
	{
		return Box1.Intersect(Box2);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Extension")
	static bool IsZoneBoxIntersect(const FZoneBox& Box1, const FZoneBox& Box2)
	{
		return Box1.Intersect(Box2);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Extension")
	static bool IsLeft(const FVector& A, const FVector& B, const FVector& Point)
	{
		return ((B.X - A.X) * (Point.Y - A.Y) - (B.Y - A.Y) * (Point.X - A.X)) < 0;
	}

	/**
	 * inspired by https://answers.unrealengine.com/questions/477185/rotate-vector-about-axis-with-pivot-point.html
	 */
	UFUNCTION(BlueprintCallable, Category = "Math|Extension")
	static FVector RotateVectorRelativeTo(
		const FVector& PivotPoint, const FVector& PointToRotate, const float& Degree, const FVector& Axis)
	{
		FTransform RelativeTransform(PivotPoint);
		FVector RotatedVect = RelativeTransform.InverseTransformPosition(PointToRotate);

		return RelativeTransform.TransformPosition(RotatedVect.RotateAngleAxis(Degree, Axis.GetSafeNormal()));
	}

	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "Math|Extension",
		meta = (WorldContext = "WorldContextObject", AdvancedDisplay = 1)
	)
	static FBox GetBox(const FZoneBox& ZoneBox);

	UFUNCTION(BlueprintCallable, Category = "Math|Extension", meta = (WorldContext = "WorldContextObject"))
	static FTrigonometryDataForZone GetTrigonometryDataForAZone(FVector PivotPoint,
		const FZoneBox& ZoneBox,
		float SafeDegree,
		UPARAM(meta = (Bitmask, BitmaskEnum = "ELateralityOrientation")) int32 Side,
		bool bDebug = false,
		const UObject* WorldContextObject = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Geometry")
	static FRotator GetRotation(const FVector FirstPoint, const FVector PivotPoint, const FVector SecondPoint);

#if WITH_EDITOR
	UFUNCTION(BlueprintCallable, Category = "Math|Extension", meta = (WorldContext = "WorldContextObject"))
	static void DebugZoneBox(const UObject* WorldContextObject,
		const FZoneBox& Box,
		bool bBoundingBox = false,
		bool bBox = false,
		bool bSphereXY = false,
		bool bSphere = false,
		bool bOrientedBox = false,
		FLinearColor ColorBoundingBox = FLinearColor(255, 0, 0),
		FLinearColor ColorBox = FLinearColor(0, 255, 0),
		FLinearColor ColorOrientedBox = FLinearColor(0, 0, 255),
		FLinearColor ColorSphereXY = FLinearColor(255, 0, 255),
		FLinearColor ColorSphere = FLinearColor(255, 255, 0),
		float LifeTime = 0.f,
		float Thickness = 0.f);
	UFUNCTION(BlueprintCallable, Category = "Math|Extension", meta = (WorldContext = "WorldContextObject"))
	static void DrawDebugBox(const UObject* WorldContextObject,
		const FBox& Box,
		FColor Color = FColor(255, 255, 255),
		float LifeTime = 0.f,
		float Thickness = 0.f);
#endif
};
