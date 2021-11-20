/******************************************************************************
* The MIT License (MIT)
*
* Copyright (c) 2015 Fredrik Lindh
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
******************************************************************************/
// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GlobalShader.h"
#include "UniformBuffer.h"

//This buffer should contain variables that never, or rarely change
BEGIN_GLOBAL_SHADER_PARAMETER_STRUCT(FComputeShaderConstantParameters,)
	SHADER_PARAMETER(float, SimulationSpeed)
END_GLOBAL_SHADER_PARAMETER_STRUCT()

//This buffer is for variables that change very often (each frame for example)
BEGIN_GLOBAL_SHADER_PARAMETER_STRUCT(FComputeShaderVariableParameters,)
	SHADER_PARAMETER(FVector4, CurrentCamPos)
	SHADER_PARAMETER(int, g_iLevel)
	SHADER_PARAMETER(int, g_iLevelMask)
	SHADER_PARAMETER(int, g_iWidth)
	SHADER_PARAMETER(int, g_iHeight)
END_GLOBAL_SHADER_PARAMETER_STRUCT()

typedef TUniformBufferRef<FComputeShaderConstantParameters> FComputeShaderConstantParametersRef;
typedef TUniformBufferRef<FComputeShaderVariableParameters> FComputeShaderVariableParametersRef;

/***************************************************************************/
/* This class is what encapsulates the shader in the engine.               */
/* It is the main bridge between the HLSL located in the engine directory  */
/* and the engine itself.                                                  */
/***************************************************************************/
class FComputeShaderDeclaration : public FGlobalShader
{
	DECLARE_SHADER_TYPE(FComputeShaderDeclaration, Global);

public:
	FComputeShaderDeclaration() = default;

	explicit FComputeShaderDeclaration(const ShaderMetaType::CompiledShaderInitializerType& Initializer);

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return GetMaxSupportedFeatureLevel(Parameters.Platform) >= ERHIFeatureLevel::SM5;
	}

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters,
	                                         FShaderCompilerEnvironment& OutEnvironment);

	// Sets the main output texture UAV (the point position texture)
	void SetOutputTexture(FRHICommandList& RHICmdList, FUnorderedAccessViewRHIRef OutputTextureUAV);
	// This function is required to bind our constant / uniform buffers to the shader.
	void SetUniformBuffers(FRHICommandList& RHICmdList, FComputeShaderConstantParameters& ConstantParameters,
	                       FComputeShaderVariableParameters& VariableParameters);
	// This is used to clean up the buffer binds after each invocation to let them be changed and used elsewhere if needed.
	void UnbindBuffers(FRHICommandList& RHICmdList);

	// Sets the unsorted point position input data
	void SetPointPosData(FRHICommandList& RHICmdList, FUnorderedAccessViewRHIRef BufferUAV,
	                     FUnorderedAccessViewRHIRef BufferUAV2);
	// Sets the unsorted point color input data
	void SetPointColorData(FRHICommandList& RHICmdList, FUnorderedAccessViewRHIRef BufferUAV,
	                       FUnorderedAccessViewRHIRef BufferUAV2);
	// Sets the output texture for the sorted point colors
	void SetPointColorTexture(FRHICommandList& RHICmdList, FUnorderedAccessViewRHIRef BufferUAV);

private:
	//This is the actual output resource that we will bind to the compute shader
	LAYOUT_FIELD(FShaderResourceParameter, OutputTexture);
	LAYOUT_FIELD(FShaderResourceParameter, OutputColorTexture);
	LAYOUT_FIELD(FShaderResourceParameter, PointPosData);
	LAYOUT_FIELD(FShaderResourceParameter, PointPosDataBuffer);
	LAYOUT_FIELD(FShaderResourceParameter, PointColorData);
	LAYOUT_FIELD(FShaderResourceParameter, PointColorDataBuffer);
};

class FComputeShaderTransposeDeclaration : public FGlobalShader
{
	DECLARE_SHADER_TYPE(FComputeShaderTransposeDeclaration, Global);

public:
	FComputeShaderTransposeDeclaration() = default;

	explicit FComputeShaderTransposeDeclaration(const ShaderMetaType::CompiledShaderInitializerType& Initializer);

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return GetMaxSupportedFeatureLevel(Parameters.Platform) >= ERHIFeatureLevel::SM5;
	}

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters,
	                                         FShaderCompilerEnvironment& OutEnvironment);

	// This function is required to bind our constant / uniform buffers to the shader.
	void SetUniformBuffers(FRHICommandList& RHICmdList, FComputeShaderConstantParameters& ConstantParameters,
	                       FComputeShaderVariableParameters& VariableParameters);
	// This is used to clean up the buffer binds after each invocation to let them be changed and used elsewhere if needed.
	void UnbindBuffers(FRHICommandList& RHICmdList);

private:
	// This is the actual output resource that we will bind to the compute shader
	LAYOUT_FIELD(FShaderResourceParameter, PointPosData);
	LAYOUT_FIELD(FShaderResourceParameter, PointPosDataBuffer);
	LAYOUT_FIELD(FShaderResourceParameter, PointColorData);
	LAYOUT_FIELD(FShaderResourceParameter, PointColorDataBuffer);
};

class FMarchingCubesCSModule : public IModuleInterface
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
