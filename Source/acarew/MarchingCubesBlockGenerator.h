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
	AMarchingCubesBlockGenerator();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Marching cubes parameters")
	float IsoLevel = 0.5f; // TODO: REGENERATE every block if edited
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Marching cubes parameters")
	uint8 VoxelsPerBlockRow = 32; // The block's edge length. TODO: REGENERATE every block if edited
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Marching cubes parameters")
	uint8 BlockSize = 10; // TODO: RESCALE & REPOSITION every block if edited + UPDATE draw radius around player

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

	static const int32 EdgeTable[256];
	static const int8 TriTable[256][16];

	void GenerateBlock();
	void GenerateCube(const TArray<TArray<TArray<float>>> WorldDensities, const FIntVector WorldCoordinates, int32&
	                  InOutVerticesIndexCounter);
	void AddVertexAndNormal(const FIntVector CoordinatesA, const FIntVector CoordinatesB,
	                        const TArray<TArray<TArray<float>>> WorldDensities);
	static float GetDensity(const FIntVector Coordinates, const TArray<TArray<TArray<float>>> Densities);
	static TArray<float> GetLocalDensities(const FIntVector Coordinates, const TArray<TArray<TArray<float>>> Densities);
	uint8 GetCubeCase(const TArray<float> LocalDensities) const;
	static float GenerateDensity(const FIntVector Coordinates);
	float InterpolateDensity(const FIntVector CoordinatesA, const FIntVector CoordinatesB,
	                         const TArray<TArray<TArray<float>>> Densities) const;
	FVector InterpolateEdge(const FIntVector CoordinatesA, const FIntVector CoordinatesB, const float Ratio) const;
	static FVector GetEdgeNormal(const FIntVector CoordinatesA, const FIntVector CoordinatesB, const float Ratio,
	                             const TArray<TArray<TArray<float>>> Densities);

	// Method 3
	TArray<uint32> ListNonemptyCells(const TArray<TArray<TArray<float>>> WorldDensities);
	TArray<uint32> ListVerticesToGenerate(const TArray<uint32> NonemptyCellList);
	void GenerateVertices(const TArray<uint32> VertexList, const TArray<TArray<TArray<float>>> WorldDensities);
	TMap<FVector, uint32> SplatVertexIds(const TArray<uint32> VertexList);
	void GenerateIndices(const TArray<uint32> NonemptyCellList);
};
