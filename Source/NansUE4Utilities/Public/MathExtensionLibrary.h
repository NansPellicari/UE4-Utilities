// Fill out your copyright notice in the Description page of Project Settings.

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
	FDrawLines(FVector2D _Position, FColor _Color) : Position(_Position), Color(_Color) {}
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
	FVector PivotPointNormalized;

	/** Length from the pivot point to the ZoneCenter */
	UPROPERTY(BlueprintReadOnly, Category = "TrigonometryDataForZone")
	float RadiusToZoneCenter;

	/**
	 * The point at the intersection on the radius (pivot point > zone center)
	 * and the Zone border.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "TrigonometryDataForZone")
	FVector PointOnZoneBorder;

	/** Length from the pivot point to the ZoneBorder */
	UPROPERTY(BlueprintReadOnly, Category = "TrigonometryDataForZone")
	float RadiusToZoneBorder;

	/** Length from the pivot point to the Zone corner = Hypotenuse */
	UPROPERTY(BlueprintReadOnly, Category = "TrigonometryDataForZone")
	float PivotToCornerLength;

	/** Hypotenuse = PivotToCornerLength, Radius = RadiusToZoneBorder */
	UPROPERTY(BlueprintReadOnly, Category = "TrigonometryDataForZone")
	float RadiusToHypotenuseDegree;

	/** Point on corner coordinate (Z depends on the zone center @see PivotPointNormalized) */
	UPROPERTY(BlueprintReadOnly, Category = "TrigonometryDataForZone")
	FVector RightCorner;

	UPROPERTY(BlueprintReadOnly, Category = "TrigonometryDataForZone")
	FVector LeftCorner;

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
	static void DrawDebugBox(const UObject* WorldContextObject,
		const FBox& Box,
		FColor Color = FColor(255, 255, 255),
		float LifeTime = 0.f,
		float Thickness = 0.f);

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

	UFUNCTION(BlueprintCallable, Category = "Math|Extension", meta = (WorldContext = "WorldContextObject"))
	static void DebugZoneBox(const UObject* WorldContextObject,
		const FZoneBox& Box,
		bool bBox = false,
		bool bSphereXY = false,
		bool bSphere = false,
		FLinearColor ColorBox = FLinearColor(255, 255, 0),
		FLinearColor ColorSphereXY = FLinearColor(255, 255, 0),
		FLinearColor ColorSphere = FLinearColor(255, 255, 0),
		float LifeTime = 0.f,
		float Thickness = 0.f);

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

	UFUNCTION(BlueprintCallable,
		BlueprintPure,
		Category = "Math|Extension",
		meta = (WorldContext = "WorldContextObject", AdvancedDisplay = 1))
	static FBox GetBox(const FZoneBox& ZoneBox);

	UFUNCTION(BlueprintCallable, Category = "Math|Extension", meta = (WorldContext = "WorldContextObject"))
	static FTrigonometryDataForZone GetTrigonometryDataForAZone(FVector PivotPoint,
		const FZoneBox& ZoneBox,
		float SafeDegree,
		UPARAM(meta = (Bitmask, BitmaskEnum = "ELateralityOrientation")) int32 Side,
		bool bDebug = false,
		const UObject* WorldContextObject = nullptr);
};
