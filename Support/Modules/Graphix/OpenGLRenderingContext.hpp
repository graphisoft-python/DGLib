
#ifndef _OPENGLRENDERINGCONTEXT_HPP_
#define _OPENGLRENDERINGCONTEXT_HPP_

#include "IRenderingContext.hpp"

namespace Graphix {

class OpenGLRenderingCore;
class OpenGLRenderPass;
class OpenGLInputLayout;
class OpenGLShaderProgram;
class OpenGLGraphicsPipeline;

class OpenGLRenderingContext : public IRenderingContext
{
private:
	OpenGLRenderingCore*	renderCore;
	OpenGLRenderPass*		currentRenderPass;
	OpenGLInputLayout*		currentInputLayout;
	OpenGLShaderProgram*	currentShaderProgram;
	OpenGLGraphicsPipeline*	currentGraphicsPipeline;

	uint32_t				indexType;
	uint64_t				indexOffset;
	uint32_t				drawBuffers[8];
	int32_t					drawBufferCount;
	bool					defaultFramebufferOK;

public:
	OpenGLRenderingContext (OpenGLRenderingCore* core);

	// graphics pipeline related methods
	void BeginRenderPass (IRenderPass* renderpass) override;
	void BindGraphicsPipeline (IGraphicsPipeline* pipeline) override;
	void BindIndexBuffer (IBuffer* buffer, uint64_t offset, IndexFormat format) override;
	void Draw (uint32_t vertexcount, uint32_t instancecount, int32_t firstvertex, uint32_t firstinstance) override;
	void DrawIndexed (uint32_t indexcount, uint32_t instancecount, uint32_t firstindex, int32_t vertexoffset, uint32_t firstinstance) override;
	void EndRenderPass () override;

	void SetDepthBias (float constant, float slope, float clamp) override;
	void SetViewport (const Viewport& viewport) override;
	void SetScissorRect (const Rect& rect) override;
	void SetStencilReferenceValue (uint32_t frontvalue, uint32_t backvalue) override;

	void SetVertexPushConstants (const void* data) override;
	void SetVertexBuffer (uint32_t index, IBuffer* buffer, uint64_t offset) override;
	void SetVertexBufferOffset (uint32_t index, uint64_t offset) override;
	void SetVertexTexture (uint32_t index, ITexture* texture) override;
	void SetVertexSamplerState (uint32_t index, ISamplerState* sampler) override;

	void SetGeometryPushConstants (const void* data) override;
	void SetGeometryBuffer (uint32_t index, IBuffer* buffer, uint64_t offset) override;
	void SetGeometryBufferOffset (uint32_t index, uint64_t offset) override;

	void SetFragmentPushConstants (const void* data) override;
	void SetFragmentBuffer (uint32_t index, IBuffer* buffer, uint64_t offset) override;
	void SetFragmentBufferOffset (uint32_t index, uint64_t offset) override;
	void SetFragmentTexture (uint32_t index, ITexture* texture) override;
	void SetFragmentSamplerState (uint32_t index, ISamplerState* sampler) override;

	// blit methods
	void GenerateMipmaps (ITexture* texture) override;

	void CopyTextureToTexture (
		ITexture* srctex, uint16_t srcslice, uint16_t srclevel, const Origin& srcorigin, const Size& srcsize,
		ITexture* dsttex, uint16_t dstslice, uint16_t dstlevel, const Origin& dstorigin) override;

	// compute pipeline related methods
	void BindComputePipeline (IComputePipeline* pipeline) override;
	void DispatchCompute (const Size& numworkgroups, const Size& workgroupsize) override;

	// synchronization methods
	IFence* InsertFence () override;
	void WaitForFence (IFence* fence, uint64_t timeout) override;
	void WaitIdle (bool wait = true) override;
};

}

#endif
