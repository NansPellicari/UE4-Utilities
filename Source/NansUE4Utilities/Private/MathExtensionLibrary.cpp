// Fill out your copyright notice in the Description page of Project Settings.

#include "MathExtensionLibrary.h"

#include "EngineGlobals.h"
#include "DrawDebugHelpers.h"
#include "EngineGlobals.h"

FBox UMathExtensionLibrary::CreateBoxFromInitAndExtend(const FVector& Origin,
	const FVector& Extent,
	const FRotator& Rotation,
	bool bDebug,
	const UObject* WorldContextObject,
	FColor Color)
{
	FTransform Transform = FTransform(Rotation);

	TArray<FVector> Vertices = {
		FVector(-Extent.X, -Extent.Y, -Extent.Z),
		FVector(-Extent.X, -Extent.Y, Extent.Z),
		FVector(-Extent.X, Extent.Y, -Extent.Z),
		FVector(-Extent.X, Extent.Y, Extent.Z),
		FVector(Extent.X, -Extent.Y, -Extent.Z),
		FVector(Extent.X, -Extent.Y, Extent.Z),
		FVector(Extent.X, Extent.Y, -Extent.Z),
		FVector(Extent.X, Extent.Y, Extent.Z),
	};

	FBox NewBox(ForceInit);

	for (FVector& Vertex : Vertices)
	{
		NewBox += Origin + Transform.TransformPosition(Vertex);
	}

#if WITH_EDITOR
	if (bDebug)
	{
		UMathExtensionLibrary::DrawDebugBox(WorldContextObject, NewBox, Color, 10.f, 1.f);
		UE_LOG(LogTemp, Warning, TEXT("%s create a box"), ANSI_TO_TCHAR(__FUNCTION__));
	}
#endif

	return NewBox;
}

FTrigonometryDataForZone UMathExtensionLibrary::GetTrigonometryDataForAZone(
	FVector PivotPoint, const FZoneBox& ZoneBox, float SafeDegree, int32 Side, bool bDebug, const UObject* WorldContextObject)
{
	FTrigonometryDataForZone TrigoData;
	TrigoData.PivotPointNormalized = FVector(PivotPoint.X, PivotPoint.Y, ZoneBox.Origin.Z);

	FVector ZoneCenterToPivot = (ZoneBox.Origin - TrigoData.PivotPointNormalized);
	TrigoData.RadiusToZoneCenter = ZoneCenterToPivot.Size();
	TrigoData.RadiusToZoneBorder = TrigoData.RadiusToZoneCenter;
	TrigoData.PointOnZoneBorder =
		TrigoData.PivotPointNormalized + (ZoneCenterToPivot.GetSafeNormal() * TrigoData.RadiusToZoneBorder);

	// TOA --> Tangent =  Oposite / Adjacent --> T = ZoneBox.Extent Half size / RadiusToZoneBorder
	TrigoData.RadiusToHypotenuseDegree = UKismetMathLibrary::DegAtan(ZoneBox.Extent.X / TrigoData.RadiusToZoneBorder) + SafeDegree;

	// C = A / H --> H = A / C --> PivotToCornerLength = RadiusToZoneBorder / Cos(RadiusToHypotenuseDegree)
	TrigoData.PivotToCornerLength = TrigoData.RadiusToZoneBorder / UKismetMathLibrary::DegCos(TrigoData.RadiusToHypotenuseDegree);

	if (Side & ELateralityOrientation::Right)
	{
		if (bDebug) UE_LOG(LogTemp, Warning, TEXT("%s - compute for right side"), ANSI_TO_TCHAR(__FUNCTION__));
		FVector TmpVect = UMathExtensionLibrary::RotateVectorRelativeTo(
			TrigoData.PivotPointNormalized, TrigoData.PointOnZoneBorder, TrigoData.RadiusToHypotenuseDegree, FVector(0, 0, 1));

		TrigoData.RightCorner = TrigoData.PivotPointNormalized +
								((TmpVect - TrigoData.PivotPointNormalized).GetSafeNormal() * TrigoData.PivotToCornerLength);
	}
	if (Side & ELateralityOrientation::Left)
	{
		if (bDebug) UE_LOG(LogTemp, Warning, TEXT("%s - compute for left side"), ANSI_TO_TCHAR(__FUNCTION__));

		FVector TmpVect = UMathExtensionLibrary::RotateVectorRelativeTo(
			TrigoData.PivotPointNormalized, TrigoData.PointOnZoneBorder, -TrigoData.RadiusToHypotenuseDegree, FVector(0, 0, 1));

		TrigoData.LeftCorner = TrigoData.PivotPointNormalized +
							   ((TmpVect - TrigoData.PivotPointNormalized).GetSafeNormal() * TrigoData.PivotToCornerLength);
	}

#if WITH_EDITOR
	if (bDebug)
	{
		UE_LOG(LogTemp,
			Warning,
			TEXT("%s - tan(RadiusToHypotenuseDegree): %f"),
			ANSI_TO_TCHAR(__FUNCTION__),
			ZoneBox.Extent.X / TrigoData.RadiusToZoneBorder);
		UE_LOG(LogTemp, Warning, TEXT("%s - ZoneBox.Extent: %s"), ANSI_TO_TCHAR(__FUNCTION__), *ZoneBox.Extent.ToString());
		UE_LOG(LogTemp, Warning, TEXT("%s - RadiusToZoneCenter: %f"), ANSI_TO_TCHAR(__FUNCTION__), TrigoData.RadiusToZoneCenter);
		UE_LOG(LogTemp, Warning, TEXT("%s - RadiusToZoneBorder: %f"), ANSI_TO_TCHAR(__FUNCTION__), TrigoData.RadiusToZoneBorder);
		UE_LOG(LogTemp,
			Warning,
			TEXT("%s - PointOnZoneBorder: %s"),
			ANSI_TO_TCHAR(__FUNCTION__),
			*TrigoData.PointOnZoneBorder.ToString());
		UE_LOG(LogTemp,
			Warning,
			TEXT("%s - PivotPointNormalized: %s"),
			ANSI_TO_TCHAR(__FUNCTION__),
			*TrigoData.PivotPointNormalized.ToString());
		UE_LOG(LogTemp, Warning, TEXT("%s - RightCorner: %s"), ANSI_TO_TCHAR(__FUNCTION__), *TrigoData.RightCorner.ToString());
		UE_LOG(LogTemp, Warning, TEXT("%s - LeftCorner: %s"), ANSI_TO_TCHAR(__FUNCTION__), *TrigoData.LeftCorner.ToString());
		UE_LOG(LogTemp,
			Warning,
			TEXT("%s - RadiusToHypotenuseDegree: %f"),
			ANSI_TO_TCHAR(__FUNCTION__),
			TrigoData.RadiusToHypotenuseDegree);

		DrawDebugLine(WorldContextObject->GetWorld(),
			FVector(TrigoData.PivotPointNormalized.X, TrigoData.PivotPointNormalized.Y, TrigoData.PivotPointNormalized.Z + 50),
			FVector(TrigoData.PointOnZoneBorder.X, TrigoData.PointOnZoneBorder.Y, TrigoData.PointOnZoneBorder.Z + 50),
			FColor(255, 0, 255),
			false,
			10.f,
			SDPG_World,
			1.f);

		if (Side & ELateralityOrientation::Right)
		{
			DrawDebugLine(WorldContextObject->GetWorld(),
				FVector(TrigoData.PivotPointNormalized.X, TrigoData.PivotPointNormalized.Y, TrigoData.PivotPointNormalized.Z + 50),
				FVector(TrigoData.RightCorner.X, TrigoData.RightCorner.Y, TrigoData.RightCorner.Z + 50),
				FColor(0, 255, 0),
				false,
				10.f,
				SDPG_World,
				1.f);
		}
		if (Side & ELateralityOrientation::Left)
		{
			DrawDebugLine(WorldContextObject->GetWorld(),
				FVector(TrigoData.PivotPointNormalized.X, TrigoData.PivotPointNormalized.Y, TrigoData.PivotPointNormalized.Z + 50),
				FVector(TrigoData.LeftCorner.X, TrigoData.LeftCorner.Y, TrigoData.LeftCorner.Z + 50),
				FColor(0, 0, 255),
				false,
				10.f,
				SDPG_World,
				1.f);
		}
	}
#endif

	return TrigoData;
}

FBox UMathExtensionLibrary::GetBox(const FZoneBox& ZoneBox)
{
	return ZoneBox.GetBox();
}

void UMathExtensionLibrary::DrawDebugBox(
	const UObject* WorldContextObject, const FBox& Box, FColor Color, float LifeTime, float Thickness)
{
	TArray<FDrawLines> Edges = {
		FDrawLines(FVector2D(0, 1), FColor(0, 255, 255)),	   // turquoise
		FDrawLines(FVector2D(1, 3), FColor(255, 0, 255)),	   // pink
		FDrawLines(FVector2D(3, 2), FColor(255, 255, 0)),	   // yellow
		FDrawLines(FVector2D(2, 0), FColor(255, 0, 0)),		   // red
		FDrawLines(FVector2D(6, 4), FColor(0, 0, 0)),		   // black
		FDrawLines(FVector2D(7, 6), FColor(255, 255, 255)),	   // white
		FDrawLines(FVector2D(3, 7), FColor(0, 0, 124)),		   // deep blue
		FDrawLines(FVector2D(2, 6), FColor(124, 0, 0)),		   // deep red
		FDrawLines(FVector2D(0, 4), FColor(124, 124, 124)),	   // grey
		FDrawLines(FVector2D(5, 7), FColor(0, 0, 255)),		   // blue
		FDrawLines(FVector2D(4, 5), FColor(0, 255, 0)),		   // green
		FDrawLines(FVector2D(1, 5), FColor(0, 124, 0)),		   // deep green
	};

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	TArray<FVector> Vertices = {FVector(Box.Min.X, Box.Min.Y, Box.Min.Z),
		FVector(Box.Min.X, Box.Min.Y, Box.Max.Z),
		FVector(Box.Min.X, Box.Max.Y, Box.Min.Z),
		FVector(Box.Min.X, Box.Max.Y, Box.Max.Z),
		FVector(Box.Max.X, Box.Min.Y, Box.Min.Z),
		FVector(Box.Max.X, Box.Min.Y, Box.Max.Z),
		FVector(Box.Max.X, Box.Max.Y, Box.Min.Z),
		FVector(Box.Max)};

	for (FDrawLines& Edge : Edges)
	{
		FVector& Node1 = Vertices[Edge.Position.X];
		FVector& Node2 = Vertices[Edge.Position.Y];
		DrawDebugLine(World, Node1, Node2, Color, false, LifeTime, SDPG_World, Thickness);
	}
}

void UMathExtensionLibrary::DebugZoneBox(const UObject* WorldContextObject,
	const FZoneBox& Box,
	bool bBoundingBox,
	bool bBox,
	bool bSphereXY,
	bool bSphere,
	bool bOrientedBox,
	FLinearColor ColorBoundingBox,
	FLinearColor ColorBox,
	FLinearColor ColorOrientedBox,
	FLinearColor ColorSphereXY,
	FLinearColor ColorSphere,
	float LifeTime,
	float Thickness)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (bBoundingBox || Box.CollideOn == EZoneCollider::AABB)
	{
		UMathExtensionLibrary::DrawDebugBox(
			WorldContextObject, Box.GetBoundingBox(), ColorBoundingBox.ToFColor(true), LifeTime, Thickness);
	}

	if (bOrientedBox || Box.CollideOn == EZoneCollider::OBB)
	{
		::DrawDebugBox(
			World, Box.Origin, Box.Extent, Box.Rotation.Quaternion(), ColorOrientedBox.ToFColor(true), false, LifeTime, 0, Thickness);
	}

	if (bBox || Box.CollideOn == EZoneCollider::AAB)
	{
		UMathExtensionLibrary::DrawDebugBox(WorldContextObject, Box.GetBox(), ColorBox.ToFColor(true), LifeTime, Thickness);
	}

	if (bSphere || Box.CollideOn == EZoneCollider::Sphere)
	{
		FSphere Sphere = Box.GetSphere();
		DrawDebugSphere(World, Sphere.Center, Sphere.W, 12, ColorSphere.ToFColor(true), false, LifeTime, SDPG_World, Thickness);
	}

	if (bSphereXY || Box.CollideOn == EZoneCollider::SphereXY)
	{
		FSphere SphereXY = Box.GetSphereXY();
		DrawDebugSphere(
			World, SphereXY.Center, SphereXY.W, 12, ColorSphereXY.ToFColor(true), false, LifeTime, SDPG_World, Thickness);
	}
}
