// Copyright Epic Games, Inc. All Rights Reserved.

#include "MarchingCubesComputeShader.h"

#define LOCTEXT_NAMESPACE "FMarchingCubesComputeShaderModule"

void FMarchingCubesComputeShaderModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	const FString ShaderDir = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("MarchingCubesComputeShader/Shaders"));
	AddShaderSourceDirectoryMapping("/Plugin/MarchingCubesComputeShader", ShaderDir);
}

void FMarchingCubesComputeShaderModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMarchingCubesComputeShaderModule, MarchingCubesComputeShader)
