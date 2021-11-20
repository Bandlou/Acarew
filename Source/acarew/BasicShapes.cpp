// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicShapes.h"

#include "MeshAttributes.h"
#include "StaticMeshAttributes.h"
#include "MarchingCubesCS.h"

// Sets default values
ABasicShapes::ABasicShapes()
{
	ThisScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = ThisScene;

	ThisMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GenerateMesh"));
	ThisMesh->SetupAttachment(RootComponent);
}

void ABasicShapes::PostActorCreated()
{
	Super::PostActorCreated();
	GenerateMesh();
}

void ABasicShapes::PostLoad()
{
	Super::PostLoad();
	GenerateMesh();
}

void ABasicShapes::GenerateMesh()
{
	// FMarchingCubesCS* mComputeShader = new FMarchingCubesCS(1.0f, BITONIC_BLOCK_SIZE, BITONIC_BLOCK_SIZE,
	//                                                         ERHIFeatureLevel::SM5);
	//
	// TArray<FLinearColor>* PosData = new TArray<FLinearColor>{
	// 	FLinearColor(.2f, .2f, .2f),
	// 	FLinearColor(.4f, .4f, .4f)
	// };
	// mComputeShader->SetPointPosDataReference(PosData);
	//
	// TArray<uint8>* ColorData = new TArray<uint8>{255, 3};
	// mComputeShader->SetPointColorDataReference(ColorData);
	//
	// mComputeShader->Save();
	// mComputeShader->ExecuteComputeShader(FVector4(0, 0, 0, 0));

	Vertices.Reset();
	Triangles.Reset();
	Normals.Reset();
	Tangents.Reset();
	UVs.Reset();
	Colors.Reset();

	int32 TriangleIndexCount = 0;
	FVector DefinedShape[3];

	DefinedShape[0] = FVector(CubeRadius.X, CubeRadius.Y, CubeRadius.Z);
	DefinedShape[1] = FVector(CubeRadius.X, CubeRadius.Y, -CubeRadius.Z);
	DefinedShape[2] = FVector(CubeRadius.X, -CubeRadius.Y, -CubeRadius.Z);

	const FProcMeshTangent TangentSetup = FProcMeshTangent(0.f, 1.f, 0.f);

	AddTriangleMesh(DefinedShape[0], DefinedShape[1], DefinedShape[2], TriangleIndexCount, TangentSetup);

	ThisMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
}

void ABasicShapes::AddTriangleMesh(const FVector TopLeft, const FVector BottomLeft, const FVector BottomRight,
                                   int32& TriIndex,
                                   const FProcMeshTangent Tangent)
{
	const int32 Point1 = TriIndex++;
	const int32 Point2 = TriIndex++;
	const int32 Point3 = TriIndex++;

	Vertices.Add(TopLeft);
	Vertices.Add(BottomLeft);
	Vertices.Add(BottomRight);

	Triangles.Add(Point1);
	Triangles.Add(Point2);
	Triangles.Add(Point3);

	const FVector ThisNorm = FVector::CrossProduct(TopLeft, BottomRight).GetSafeNormal();

	for (int i = 0; i < 3; ++i)
	{
		Normals.Add(ThisNorm);
		Tangents.Add(Tangent);
		Colors.Add(FLinearColor::Green);
	}

	UVs.Add(FVector2D(0.f, 1.f)); // Top left
	UVs.Add(FVector2D(1.f, 1.f)); // Bottom left
	UVs.Add(FVector2D(1.f, 0.f)); // Bottom right
}
