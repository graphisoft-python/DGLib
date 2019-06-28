
#ifndef _GPUENUMS_HPP_
#define _GPUENUMS_HPP_

#include <cstdint>

#define GRAPHIX_NUM_QUEUED_FRAMES	3

namespace Graphix {

// NOTE: these enums are (mostly) based on the Metal specification

enum ResourceOptions {
	// mutually exclusive
	ResourceStorageModePrivate = 1,
	ResourceStorageModeShared = 2,
	ResourceStorageModeManaged = 4,
	ResourceStorageModeMemoryless = 8,

	// mutually exclusive
	ResourceCPUCacheModeDefaultCache = 16,
	ResourceCPUCacheModeWriteCombined = 32
};

enum MemoryMapFlags {
	MemoryMapRead = 1,
	MemoryMapWrite = 2,
	MemoryMapInvalidate = 4,		// discard/orphan
	MemoryMapUnsynchronized = 8		// nooverwrite
};

enum IndexFormat {
	IndexFormat16 = 0,
	IndexFormat32
};

enum BufferUsageFlags {
	BufferUsageStorage = 1,
	BufferUsageVertex = 2,
	BufferUsageIndex = 4,
	BufferUsageUniform = 8
};

enum TextureType {
	TextureType1D = 0,
	TextureType1DArray,
	TextureType2D,
	TextureType2DArray,
	TextureType2DMultisample,
	TextureTypeCube,
	TextureTypeCubeArray,
	TextureType3D
};

enum TextureUsage {
	TextureUsageUnknown = 0,
	TextureUsageShaderRead = 1,
	TextureUsageShaderWrite = 2,
	TextureUsageRenderTarget = 4
};

enum PixelFormat {
	PixelFormatInvalid = 0,
	PixelFormatR8Unorm,
	PixelFormatRG8Unorm,
	PixelFormatA1BGR5Unorm,
	PixelFormatRGBA8Unorm,
	PixelFormatRGBA8Unorm_sRGB,
	PixelFormatBGRA8Unorm,
	PixelFormatBGRA8Unorm_sRGB,
	PixelFormatR16Float,
	PixelFormatRG16Float,
	PixelFormatRGBA16Float,
	PixelFormatR32Float,
	PixelFormatRG32Float,
	PixelFormatRGBA32Float,

	PixelFormatDepth32Float,
	PixelFormatStencil8,				// GL 4.4
	PixelFormatDepth24Unorm,			// GL only
	PixelFormatDepth24Unorm_Stencil8,
	PixelFormatDepth32Float_Stencil8	// Metal/Vulkan

	// TODO: other formats (if needed...)
};

enum ShaderStage {
	ShaderStageVertex = 0,
	ShaderStageTessellationControl = 1,
	ShaderStageTessellationEvaluation = 2,
	ShaderStageGeometry = 3,
	ShaderStageFragment = 4,
	ShaderStageCompute = 5				// compute pipeline only
};

enum LoadAction {
	LoadActionDontCare = 0,
	LoadActionLoad,
	LoadActionClear
};

enum StoreAction {
	StoreActionDontCare = 0,
	StoreActionStore,
	StoreActionMultisampleResolve,
	StoreActionStoreAndMultisampleResolve
};

enum MultisampleDepthResolveFilter {
	MultisampleDepthResolveFilterSample0 = 0,
	MultisampleDepthResolveFilterMin,
	MultisampleDepthResolveFilterMax
};

enum VertexInputType {
	VertexInputTypeUchar2 = 0,
	VertexInputTypeUChar3,
	VertexInputTypeUChar4,

	VertexInputTypeChar2,
	VertexInputTypeChar3,
	VertexInputTypeChar4,

	VertexInputTypeUChar2Normalized,
	VertexInputTypeUChar3Normalized,
	VertexInputTypeUChar4Normalized,

	VertexInputTypeUShort2,
	VertexInputTypeUShort3,
	VertexInputTypeUShort4,

	VertexInputTypeShort2,
	VertexInputTypeShort3,
	VertexInputTypeShort4,

	VertexInputTypeUShort2Normalized,
	VertexInputTypeUShort3Normalized,
	VertexInputTypeUShort4Normalized,

	VertexInputTypeShort2Normalized,
	VertexInputTypeShort3Normalized,
	VertexInputTypeShort4Normalized,

	VertexInputTypeHalf2,
	VertexInputTypeHalf3,
	VertexInputTypeHalf4,

	VertexInputTypeFloat,
	VertexInputTypeFloat2,
	VertexInputTypeFloat3,
	VertexInputTypeFloat4

	// TODO: other, if needed
};

enum VertexStepFunction {
	VertexStepFunctionPerVertex = 0,
	VertexStepFunctionPerInstance,
	VertexStepFunctionConstant
};

enum PrimitiveType {
	PrimitiveTypePoint = 0,
	PrimitiveTypeLine,
	PrimitiveTypeLineStrip,
	PrimitiveTypeLineAdjacency,
	PrimitiveTypeLineStripAdjacency,
	PrimitiveTypeTriangle,
	PrimitiveTypeTriangleStrip,
	PrimitiveTypeTriangleAdjacency,
	PrimitiveTypeTriangleStripAdjacency,
	PrimitiveTypePatches
};

enum PolygonMode {
	PolygonModeFill = 0,
	PolygonModeLine,
	PolygonModePoint
};

enum CullMode {
	CullModeNone = 0,
	CullModeFront,
	CullModeBack,
	CullModeFrontAndBack
};

enum BlendOperation {
	BlendOperationAdd = 0,
	BlendOperationSubtract,
	BlendOperationReverseSubtract,
	BlendOperationMin,
	BlendOperationMax
};

enum BlendFactor {
	BlendFactorZero = 0,
	BlendFactorOne,
	BlendFactorSrcColor,
	BlendFactorInvSrcColor,
	BlendFactorDstColor,
	BlendFactorInvDstColor,
	BlendFactorSrcAlpha,
	BlendFactorInvSrcAlpha,
	BlendFactorDstAlpha,
	BlendFactorInvDstAlpha,
	BlendFactorConstantColor,
	BlendFactorInvConstantColor,
	BlendFactorConstantAlpha,
	BlendFactorInvConstantAlpha

	// ...
};

enum CompareFunction {
	CompareFunctionNever = 0,
	CompareFunctionLess,
	CompareFunctionEqual,
	CompareFunctionLessEqual,
	CompareFunctionGreater,
	CompareFunctionNotEqual,
	CompareFunctionGreaterEqual,
	CompareFunctionAlways
};

enum StencilFace {
	StencilFaceFront = 0,
	StencilFaceBack,
	StencilFaceFrontAndBack
};

enum StencilOperation {
	StencilOperationKeep = 0,
	StencilOperationZero,
	StencilOperationReplace,
	StencilOperationIncrClamp,
	StencilOperationDecrClamp,
	StencilOperationInvert,
	StencilOperationIncrWrap,
	StencilOperationDecrWrap
};

enum SamplerAddressMode {
	SamplerAddressModeClampToEdge = 0,
	SamplerAddressModeMirrorClampToEdge,	// GL 4.4
	SamplerAddressModeRepeat,
	SamplerAddressModeMirrorRepeat,
	SamplerAddressModeClampToZero,			// Metal/Vulkan
	SamplerAddressModeClampToBorderColor
};

enum SamplerMinMagFilter {
	SamplerMinMagFilterNearest = 0,
	SamplerMinMagFilterLinear
};

enum SamplerMipFilter {
	SamplerMipFilterNotMipmapped = 0,
	SamplerMipFilterNearest,
	SamplerMipFilterLinear
};

enum SamplerBorderColor {
	SamplerBorderColorTransparentBlack = 0,
	SamplerBorderColorOpaqueBlack,
	SamplerBorderColorOpaqueWhite
};

}

#endif
