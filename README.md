# Acarew

## Description
[WIP] Marching Cubes basic implementation.

## Resources
- Marching Cubes for procedural terrain generation: https://developer.nvidia.com/gpugems/gpugems3/part-i-geometry/chapter-1-generating-complex-procedural-terrains-using-gpu
- Shader in plugin: https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/Rendering/ShaderInPlugin/QuickStart/
- Global shaders: https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/Rendering/ShaderDevelopment/AddingGlobalShaders/
- Compute shaders: http://www.valentinkraft.de/compute-shader-in-unreal-tutorial/

UE5 migration:
- https://forums.unrealengine.com/t/4-25-transition-guide/142969/2
  - FShader serialize: replaced with LAYOUT_FIELD
  - FShader helpers: need to be called on a TShaderMapRef
    - TShaderMapRef<_MY-CUSTOM-FSHADER_> ComputeShader(GetGlobalShaderMap(ERHIFeatureLevel::SM5))
  - END_UNIFORM_BUFFER_STRUCT: no longer takes parameters
  - UNIFORM_MEMBER: replaced with SHADER_PARAMETER
- https://dawnarc.com/2020/06/ue4rhi-rendering-hardware-interface-notes/
  - ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER: replaced with ENQUEUE_RENDER_COMMAND
- https://github.com/ValentinKraft/UE4_SortingComputeShader/tree/master_4.24_transition
  - _FShaderResourceViewRHIParamRef_: replaced with _new FRHIShaderResourceView_
  - 