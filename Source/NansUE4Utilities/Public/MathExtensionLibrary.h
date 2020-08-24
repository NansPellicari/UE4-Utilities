// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "MathExtensionLibrary.generated.h"

#define TOFLAG(Enum) (1 << static_cast<uint8>(Enum))

/** This is relative to the zone, not the player */
UENUM(BlueprintType, Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum ELateralityOrientation
{
	None = 0 UMETA(Hidden),
	Left = 0x00000001,
	Right = 0x00000002,
};

ENUM_CLASS_FLAGS(ELateralityOrientation)

struct NANSUE4UTILITIES_API FDrawLines
{
	FVector2D Position;
	FColor Color;
	FDrawLines(FVector2D _Position, FColor _Color) : Position(_Position), Color(_Color) {}
};

USTRUCT(BlueprintType)
struct NANSUE4UTILITIES_API FZoneBox
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZoneBox|Settings")
	FVector Origin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZoneBox|Settings")
	FVector Extent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZoneBox|Settings")
	FRotator Rotation;

	FZoneBox();

	FZoneBox(FVector _Origin, FVector _Extent, FRotator _Rotation) : Origin(_Origin), Extent(_Extent), Rotation(_Rotation) {}

	FBox GetBox(bool bDebug = false, const UObject* WorldContextObject = nullptr, FColor Color = FColor(255, 255, 0)) const;
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
	FVector PointOnCorner;
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
	static FBox CreateBoxFronInitAndExtend(const FVector& Origin,
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

	UFUNCTION(BlueprintCallable, Category = "Math|Extension", meta = (WorldContext = "WorldContextObject"))
	static FTrigonometryDataForZone GetTrigonometryDataForAZone(const UObject* WorldContextObject,
		FVector PivotPoint,
		FVector ZoneBoxCenter,
		FVector ZoneBoxVolume,
		float SafeDegree,
		ELateralityOrientation Side = ELateralityOrientation::Left,
		bool bDebug = false);
};
