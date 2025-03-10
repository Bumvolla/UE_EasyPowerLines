/*
 * Copyright (c) 2025 Sora Mas
 * All rights reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SplineHelpers.h"

#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

#include "UtilityPolePreset.h"
#include "CatenaryBase.generated.h"

UCLASS(Abstract)
class UTILITYPOLES_API ACatenaryBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACatenaryBase();

protected:

	UPROPERTY()
	TArray<USplineComponent*> AllWires;
	UPROPERTY()
	TArray<USplineMeshComponent*> AllSplineMeshes;
	UPROPERTY()
	TArray<USplineMeshComponent*> AvailableSplineMeshes;

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Generate();

public:

	UPROPERTY(EditInstanceOnly, Category = "Catenary")
	float Slack = 100;

	UPROPERTY(EditInstanceOnly, Category = "Catenary")
	float SlackVariation = 2;

	UPROPERTY(EditInstanceOnly, Category = "Catenary")
	uint16 SplineResolution = 10;

	UPROPERTY(EditInstanceOnly, Category = "Mesh")
	UStaticMesh* WireMesh;

	UPROPERTY(EditInstanceOnly, Category = "Mesh")
	TEnumAsByte<EAxis::Type> WireMeshAxis = EAxis::X;

	UPROPERTY(EditInstanceOnly, Category = "Generation")
	bool autoGenerate = false;

	UPROPERTY(EditInstanceOnly, Category = "Debug")
	bool bCleanupSplines = false;

protected:

	float MeshLenght;

	void SetMeshLenght();

	void RemoveExcesSplines(int32 NeededSplines);

	void RemoveSplines();

	void RemoveSplineMeshes();

	void ReuseOrCreateSplines();

	TArray<FVector> CalculateSingleCatenary(TArray<FVector> ConectionPoints, bool bIsClosedLoop = false);

	TArray<TArray<FVector>> CalculateCatenariesParalel(const TArray<AUtilityPolePreset*>& ConectionPoints, bool bIsClosedLoop = false);

	void ConstructSplineMeshesAlongSplines(USplineComponent* Spline);

	void CleanupSplines();

	const TMap<EAxis::Type, ESplineMeshAxis::Type> EnumFinder =
	{
		{EAxis::None,ESplineMeshAxis::X},
		{EAxis::X,ESplineMeshAxis::X},
		{EAxis::Y,ESplineMeshAxis::Y},
		{EAxis::Z,ESplineMeshAxis::Z}
	};

	ESplineMeshAxis::Type FindAxis(EAxis::Type Axis)
	{
		const ESplineMeshAxis::Type* FoundAxis = EnumFinder.Find(Axis);
		return *FoundAxis;
	}

};