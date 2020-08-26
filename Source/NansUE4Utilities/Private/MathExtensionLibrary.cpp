// Fill out your copyright notice in the Description page of Project Settings.

#include "MathExtensionLibrary.h"

#include "DrawDebugHelpers.h"
#include "EngineGlobals.h"

FZoneBox::FZoneBox()
{
	Origin = FVector::ZeroVector;
	Extent = FVector::ZeroVector;
	Rotation = FRotator::ZeroRotator;
}

FBox FZoneBox::GetBox() const
{
	return UMathExtensionLibrary::CreateBoxFromInitAndExtend(Origin, Extent, Rotation);
}

FSphere FZoneBox::GetSphere() const
{
	float W = (Origin - (Origin + Extent)).Size();
	FSphere Sphere(Origin, W);

	return Sphere;
}
FSphere FZoneBox::GetSphereXY() const
{
	FVector OToE = Origin + Extent;
	float W = (Origin - FVector(OToE.X, OToE.Y, Origin.Z)).Size();
	FSphere Sphere(Origin, W);
	return Sphere;
}

bool FZoneBox::Intersect(const FZoneBox& Other) const
{
	bool bIsIntersect = false;
	if (GetBox().Intersect(Other.GetBox()))
	{
		bIsIntersect = GetSphereXY().Intersects(Other.GetSphereXY());
	}

	return bIsIntersect;
}

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

FTrigonometryDataForZone UMathExtensionLibrary::GetTrigonometryDataForAZone(const UObject* WorldContextObject,
	FVector PivotPoint,
	FVector ZoneBoxCenter,
	FVector ZoneBoxVolume,
	float SafeDegree,
	ELateralityOrientation Side,
	bool bDebug)
{
	FTrigonometryDataForZone TrigoData;
	TrigoData.PivotPointNormalized = FVector(PivotPoint.X, PivotPoint.Y, ZoneBoxCenter.Z);

	FVector ZoneCenterToPivot = (ZoneBoxCenter - TrigoData.PivotPointNormalized);
	TrigoData.RadiusToZoneCenter = ZoneCenterToPivot.Size();
	TrigoData.RadiusToZoneBorder = TrigoData.RadiusToZoneCenter - ZoneBoxVolume.Y;
	TrigoData.PointOnZoneBorder =
		TrigoData.PivotPointNormalized + (ZoneCenterToPivot.GetSafeNormal() * TrigoData.RadiusToZoneBorder);

	// TOA --> Tangent =  Oposite / Adjacent --> T = ZoneBoxVolume Half size / RadiusToZoneBorder
	TrigoData.RadiusToHypotenuseDegree = UKismetMathLibrary::DegAtan(ZoneBoxVolume.X / TrigoData.RadiusToZoneBorder) + SafeDegree;

	// C = A / H --> H = A / C --> PivotToCornerLength = RadiusToZoneBorder / Cos(RadiusToHypotenuseDegree)
	TrigoData.PivotToCornerLength = TrigoData.RadiusToZoneBorder / UKismetMathLibrary::DegCos(TrigoData.RadiusToHypotenuseDegree);

	FVector TmpVect = UMathExtensionLibrary::RotateVectorRelativeTo(
		TrigoData.PivotPointNormalized, TrigoData.PointOnZoneBorder, TrigoData.RadiusToHypotenuseDegree, FVector(0, 0, 1));

	TrigoData.PointOnCorner = TrigoData.PivotPointNormalized +
							  ((TmpVect - TrigoData.PivotPointNormalized).GetSafeNormal() * TrigoData.PivotToCornerLength);

#if WITH_EDITOR
	if (bDebug)
	{
		UE_LOG(LogTemp,
			Warning,
			TEXT("%s - tan(RadiusToHypotenuseDegree): %f"),
			ANSI_TO_TCHAR(__FUNCTION__),
			ZoneBoxVolume.X / TrigoData.RadiusToZoneBorder);
		UE_LOG(LogTemp, Warning, TEXT("%s - ZoneBoxVolume: %s"), ANSI_TO_TCHAR(__FUNCTION__), *ZoneBoxVolume.ToString());
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
		UE_LOG(LogTemp, Warning, TEXT("%s - PointOnCorner: %s"), ANSI_TO_TCHAR(__FUNCTION__), *TrigoData.PointOnCorner.ToString());
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

		DrawDebugLine(WorldContextObject->GetWorld(),
			FVector(TrigoData.PivotPointNormalized.X, TrigoData.PivotPointNormalized.Y, TrigoData.PivotPointNormalized.Z + 50),
			FVector(TrigoData.PointOnCorner.X, TrigoData.PointOnCorner.Y, TrigoData.PointOnCorner.Z + 50),
			FColor(0, 255, 0),
			false,
			10.f,
			SDPG_World,
			1.f);
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
	bool bBox,
	bool bSphereXY,
	bool bSphere,
	FLinearColor ColorBox,
	FLinearColor ColorSphereXY,
	FLinearColor ColorSphere,
	float LifeTime,
	float Thickness)
{
	if (bBox)
	{
		UMathExtensionLibrary::DrawDebugBox(WorldContextObject, Box.GetBox(), ColorBox.ToFColor(true), LifeTime, Thickness);
	}

	if (bSphere)
	{
		FSphere Sphere = Box.GetSphere();
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
		DrawDebugSphere(World, Sphere.Center, Sphere.W, 12, ColorSphere.ToFColor(true), false, LifeTime, SDPG_World, Thickness);
	}

	if (bSphereXY)
	{
		FSphere SphereXY = Box.GetSphereXY();
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
		DrawDebugSphere(
			World, SphereXY.Center, SphereXY.W, 12, ColorSphereXY.ToFColor(true), false, LifeTime, SDPG_World, Thickness);
	}
}
