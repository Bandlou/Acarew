// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "MarchingCubesBlockGenerator.generated.h"

UCLASS()
class ACAREW_API AMarchingCubesBlockGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMarchingCubesBlockGenerator();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh parameters")
	float CubeRadius = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Marching cubes parameters")
	float IsoLevel = 0.5f;

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* ThisScene;
	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* ThisMesh;

	virtual void PostActorCreated() override;
	virtual void PostLoad() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

private:
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FProcMeshTangent> Tangents;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> Colors;

	static const int32 EdgeTable[256];
	static const int32 TriTable[256][16];

	void GenerateBlock();
	void GenerateCube(const TArray<TArray<TArray<float>>> WorldDensities, const FIntVector WorldCoordinates, int32&
	                  InOutVerticesIndexCounter);
	void AddVertexAndNormal(const FIntVector CoordinatesA, const FIntVector CoordinatesB,
	                        const TArray<TArray<TArray<float>>> WorldDensities);
	static float GetDensity(const FIntVector Coordinates, const TArray<TArray<TArray<float>>> Densities);
	static TArray<float> GetLocalDensities(const FIntVector Coordinates, const TArray<TArray<TArray<float>>> Densities);
	int32 GetDensityFlags(const TArray<float> LocalDensities) const;
	static float GenerateDensity(const FIntVector Coordinates);
	float InterpolateDensity(const FIntVector CoordinatesA, const FIntVector CoordinatesB,
							const TArray<TArray<TArray<float>>> Densities) const;
	FVector InterpolateEdge(const FIntVector CoordinatesA, const FIntVector CoordinatesB, const float Ratio) const;
	static FVector GetEdgeNormal(const FIntVector CoordinatesA, const FIntVector CoordinatesB, const float Ratio,
	                             const TArray<TArray<TArray<float>>> Densities);
};
