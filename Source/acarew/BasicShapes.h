// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "BasicShapes.generated.h"

UCLASS()
class ACAREW_API ABasicShapes : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasicShapes();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh parameters")
	FVector CubeRadius = FVector(100.f, 100.f, 100.f);

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* ThisScene;
	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* ThisMesh;

	virtual void PostActorCreated() override;
	virtual void PostLoad() override;
	void GenerateMesh();

private:
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FProcMeshTangent> Tangents;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> Colors;

	void AddTriangleMesh(FVector TopLeft, FVector BottomLeft, FVector BottomRight, int32& TriIndex,
	                     FProcMeshTangent Tangent);
};
