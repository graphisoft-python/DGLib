
#ifndef _IRESOURCEFACTORY_HPP_
#define _IRESOURCEFACTORY_HPP_

#include "GPUStructures.hpp"

namespace Graphix {

// --- Descriptor structures ---------------------------------------------------

class GRAPHIX_DLL_EXPORT TextureDescriptor
{
public:
	TextureType		textureType;
	PixelFormat		pixelFormat;
	uint16_t		width;
	uint16_t		height;
	uint16_t		depth;
	uint16_t		mipmapCount;
	uint16_t		sampleCount;
	uint16_t		arrayLength;
	uint32_t		options;		// see ResourceOptions
	uint32_t		usage;			// see TextureUsage

	TextureDescriptor ();
};

class GRAPHIX_DLL_EXPORT SamplerDescriptor
{
public:
	SamplerAddressMode	rAddressMode;
	SamplerAddressMode	sAddressMode;
	SamplerAddressMode	tAddressMode;

	SamplerMinMagFilter	minFilter;
	SamplerMinMagFilter	magFilter;
	SamplerMipFilter	mipFilter;

	float				lodMinClamp;
	float				lodMaxClamp;
	bool				lodAverage;				// Metal/Vulkan

	uint32_t			maxAnisotropy;
	bool				normalizedCoordinates;	// Metal/Vulkan
	CompareFunction		compareFunction;
	SamplerBorderColor	borderColor;

	SamplerDescriptor ();
};

// --- Resource classes --------------------------------------------------------

class IBuffer
{
public:
	virtual ~IBuffer ();

	virtual void* MapContents (uint64_t offset, uint64_t size, uint32_t flags) = 0;
	virtual void UnmapContents () = 0;

	virtual uint64_t GetLength () const = 0;
};

class ITexture
{
public:
	virtual ~ITexture ();

	virtual void ReplaceRegion (const Region& region, uint16_t level, const void* bytes, uint64_t pitch) = 0;
	virtual void ReplaceRegion (const Region& region, uint16_t level, uint16_t slice, const void* bytes, uint64_t pitch, uint64_t slicesize) = 0;

	virtual void GetBytes (void* outbytes, const Region& region, uint16_t level, uint64_t pitch) = 0;
	virtual void GetBytes (void* outbytes, const Region& region, uint16_t level, uint16_t slice, uint64_t pitch, uint64_t slicesize) = 0;

	virtual uint16_t GetSampleCount () const = 0;
	virtual uint16_t GetWidth () const = 0;
	virtual uint16_t GetHeight () const = 0;
	virtual PixelFormat GetPixelFormat () const = 0;
	virtual TextureType GetType () const = 0;
	virtual uint32_t GetOptions () const = 0;
	virtual uint32_t GetUsage () const = 0;
};

class ISamplerState
{
public:
	virtual ~ISamplerState ();
};

class IRenderPass
{
public:
	virtual ~IRenderPass ();

	virtual void SetupColorAttachment (uint8_t index, ITexture* tex, uint16_t level, uint16_t slice, const Color& clearcolor, LoadAction loadaction, StoreAction storeaction) = 0;
	virtual void SetupDepthStencilAttachment (ITexture* tex, uint16_t level, uint16_t slice, float cleardepth, uint8_t clearstencil, LoadAction loadaction, StoreAction storeaction) = 0;
	virtual void SetupMSAAColorResolveTarget (uint8_t index, ITexture* target, uint16_t level, uint16_t slice) = 0;
	virtual void SetupMSAADepthResolveTarget (ITexture* target, uint16_t level, uint16_t slice) = 0;
	//virtual void SetupVisibilityResultBuffer (IBuffer* buffer) = 0;

	// NOTE: OpenGL and Vulkan (Metal doesn't seem to support it)
	virtual void SetRenderArea (const Rect& renderarea) = 0;

	// TODO: other similar methods (if needed)
};

class IGraphicsPipeline
{
	// NOTE: API equivalence: GL 4.4+ <=> Metal <= Vulkan <=> GL 4.6+

	// NOTE: Vulkan is the only API that requires the renderpass (and subpass) to be provided
	//       in the Assemble method, therefore a nullptr is accepted when using any other API

	// NOTE: the SetInputBufferLayout method requires the buffer parameter prior to GL 4.4,
	//       therefore newer APIs accept nullptr. Provided, the buffer must be set on the
	//       rendering context with the SetVertexBuffer method

	// NOTE: Assemble() is the last method you want to call; prior to that, all shader stages,
	//       input layouts and shader buffer bindings MUST be provided

	// NOTE: input attribute/buffer names must be the same as in the shader (OpenGL)
	// NOTE: push constant blocks are allocated in one continuous buffer (OpenGL)
	// NOTE: unlisted states are implicitly dynamic (Vulkan)

public:
	virtual ~IGraphicsPipeline ();

	virtual bool AddShader (ShaderStage stage, const char* source) = 0;
	virtual bool AddPushConstantBlock (ShaderStage stage, uint32_t size) = 0;
	virtual bool Assemble (IRenderPass* renderpass) = 0;

	// vertex input state
	virtual void ClearInputLayout () = 0;
	virtual void SetInputAttribute (const char* name, uint32_t bufferindex, VertexInputType type, uint32_t offset) = 0;
	virtual void SetInputBufferLayout (uint32_t bufferindex, IBuffer* buffer, VertexStepFunction stepfunction, uint32_t steprate, uint64_t offset, uint32_t stride) = 0;
	virtual void SetBufferBinding (const char* buffername, uint32_t usageflags, uint32_t binding) = 0;

	// input assembler state
	virtual void SetPrimitiveTopology (PrimitiveType topology) = 0;
	virtual void EnablePrimitiveRestart (bool enable) = 0;

	// rasterizer state
	virtual void SetPolygonMode (PolygonMode mode) = 0;
	virtual void SetCullMode (CullMode mode) = 0;
	virtual void EnableScissorTest (bool enable) = 0;
	virtual void EnableSRGB (bool enable) = 0;	// don't enable this in ARCHICAD!!!
	virtual void EnableDepthBias (bool enable) = 0;
	virtual void EnableDepthClamp (bool enable) = 0;
	virtual void EnableClipDistance (uint8_t index, bool enable) = 0;

	// blend state
	virtual void EnableBlend (uint8_t attachment, bool enable) = 0;
	virtual void SetColorWriteMask (uint8_t attachment, uint8_t mask) = 0;
	virtual void SetColorBlend (uint8_t attachment, BlendOperation blendop, BlendFactor srcfactor, BlendFactor dstfactor) = 0;
	virtual void SetAlphaBlend (uint8_t attachment, BlendOperation blendop, BlendFactor srcfactor, BlendFactor dstfactor) = 0;

	// depth-stencil state
	virtual void EnableDepthWrite (bool enable) = 0;
	virtual void EnableStencilTest (bool enable) = 0;
	virtual void SetDepthCompare (CompareFunction compareop) = 0;
	//virtual void SetDepthBounds (bool enable, float boundmin, float boundmax) = 0;
	virtual void SetStencilFunction (StencilFace face, CompareFunction compareop, StencilOperation pass, StencilOperation fail, StencilOperation zfail) = 0;
	virtual void SetStencilMask (StencilFace face, uint8_t comparemask, uint8_t writemask) = 0;

	// multisample state
	virtual void SetRasterizationSamples (uint32_t samples) = 0;
	virtual void SetMinSampleShading (bool enable, float value) = 0;

	// query methods
	virtual uint64_t GetBufferBlockStride (uint32_t binding) = 0;
};

// --- IResourceFactory definition ---------------------------------------------

class IResourceFactory
{
public:
	virtual ~IResourceFactory ();

	virtual IBuffer* CreateBuffer (uint64_t size, uint32_t usageflags, uint32_t options, const void* initialdata = nullptr) = 0;
	virtual ITexture* CreateTexture (const TextureDescriptor& descriptor) = 0;
	virtual ISamplerState* CreateSamplerState (const SamplerDescriptor& descriptor) = 0;
	virtual IRenderPass* CreateRenderPass () = 0;
	virtual IGraphicsPipeline* CreateGraphicsPipeline () = 0;
	//virtual IComputePipeline* CreateComputePipeline () = 0;
	
	// because of macOS 10.12 driver bug; caches large depth textures
	virtual bool HACK_ShelveDepthBuffer (ITexture* texture) = 0;

	// TODO:
};

}

#endif
