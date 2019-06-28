
#ifndef _IRENDERINGCONTEXT_HPP_
#define _IRENDERINGCONTEXT_HPP_

#include "GPUStructures.hpp"

namespace Graphix {

class IBuffer;
class ITexture;
class ISamplerState;
class IRenderPass;
class IGraphicsPipeline;
class IComputePipeline;

class IFence
{
public:
	virtual ~IFence ();
};

// --- IRenderingContext definition --------------------------------------------

class IRenderingContext
{
	// NOTE: drop your concept of 'vertex buffers'; they no longer mean only vertex data, but any data
	//       that can be set in the pipeline's vertex stage (including uniform buffers, storage buffers, etc.)

public:
	virtual ~IRenderingContext ();

	// graphics pipeline related methods
	virtual void BeginRenderPass (IRenderPass* renderpass) = 0;
	virtual void BindGraphicsPipeline (IGraphicsPipeline* pipeline) = 0;
	virtual void BindIndexBuffer (IBuffer* buffer, uint64_t offset, IndexFormat format) = 0;
	virtual void Draw (uint32_t vertexcount, uint32_t instancecount, int32_t firstvertex, uint32_t firstinstance) = 0;
	virtual void DrawIndexed (uint32_t indexcount, uint32_t instancecount, uint32_t firstindex, int32_t vertexoffset, uint32_t firstinstance) = 0;
	virtual void EndRenderPass () = 0;

	virtual void SetDepthBias (float constant, float slope, float clamp) = 0;
	virtual void SetViewport (const Viewport& viewport) = 0;
	virtual void SetScissorRect (const Rect& rect) = 0;
	virtual void SetStencilReferenceValue (uint32_t frontvalue, uint32_t backvalue) = 0;

	virtual void SetVertexPushConstants (const void* data) = 0;
	virtual void SetVertexBuffer (uint32_t index, IBuffer* buffer, uint64_t offset) = 0;
	virtual void SetVertexBufferOffset (uint32_t index, uint64_t offset) = 0;
	virtual void SetVertexTexture (uint32_t index, ITexture* texture) = 0;
	virtual void SetVertexSamplerState (uint32_t index, ISamplerState* sampler) = 0;

	virtual void SetGeometryPushConstants (const void* data) = 0;
	virtual void SetGeometryBuffer (uint32_t index, IBuffer* buffer, uint64_t offset) = 0;
	virtual void SetGeometryBufferOffset (uint32_t index, uint64_t offset) = 0;

	virtual void SetFragmentPushConstants (const void* data) = 0;
	virtual void SetFragmentBuffer (uint32_t index, IBuffer* buffer, uint64_t offset) = 0;
	virtual void SetFragmentBufferOffset (uint32_t index, uint64_t offset) = 0;
	virtual void SetFragmentTexture (uint32_t index, ITexture* texture) = 0;
	virtual void SetFragmentSamplerState (uint32_t index, ISamplerState* sampler) = 0;

	// blit methods
	virtual void GenerateMipmaps (ITexture* texture) = 0;

	virtual void CopyTextureToTexture (
		ITexture* srctex, uint16_t srcslice, uint16_t srclevel, const Origin& srcorigin, const Size& srcsize,
		ITexture* dsttex, uint16_t dstslice, uint16_t dstlevel, const Origin& dstorigin) = 0;

	// compute pipeline related methods
	virtual void BindComputePipeline (IComputePipeline* pipeline) = 0;
	virtual void DispatchCompute (const Size& numworkgroups, const Size& workgroupsize) = 0;

	// synchronization methods (Vulkan concepts)
	virtual IFence* InsertFence () = 0;
	virtual void WaitForFence (IFence* fence, uint64_t timeout) = 0;
	virtual void WaitIdle (bool wait = true) = 0;

	// TODO:
};

}

#endif
