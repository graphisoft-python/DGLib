
#ifndef _OPENGLRESOURCEFACTORY_HPP_
#define _OPENGLRESOURCEFACTORY_HPP_

// --- Includes ----------------------------------------------------------------

#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>

#include "IResourceFactory.hpp"
#include "OpenGLExtensionManager.hpp"
#include "OpenGLMaps.hpp"

namespace Graphix {

class OpenGLRenderingCore;
class OpenGLResourceFactory;
class OpenGLStateManager;
class OpenGLRenderPass;

// --- OpenGLBuffer definition -------------------------------------------------

class OpenGLBuffer : public IBuffer
{
	struct MappedData {
		void*		ptr;
		GLuint		flags;
		uint64_t	offset;
		uint64_t	size;

		MappedData () {
			ptr = 0;
			flags = 0;
			offset = 0;
			size = 0;
		}
	};

private:
	OpenGLResourceFactory*	creator;

	MappedData				mappedData;
	uint32_t				usageFlags;		// see BufferUsageFlags
	uint32_t				storageMode;	// see ResourceOptions
	uint64_t				dataSize;

	GLuint					bufferID;
	GLenum					target;
	GLenum					usage;

public:
	OpenGLBuffer (OpenGLResourceFactory* factory, uint64_t size, uint32_t usageflags, uint32_t options, const void* initialdata);
	~OpenGLBuffer ();

	// overrides
	void* MapContents (uint64_t offset, uint64_t size, uint32_t flags) override;
	void UnmapContents () override;

	uint64_t GetLength () const override		{ return dataSize; }

	// specific
	inline GLuint GetBuffer () const			{ return bufferID; }
	inline uint32_t GetUsage () const			{ return usageFlags; }
	inline uint64_t GetDataSize () const		{ return dataSize; }
};

// --- OpenGLTexture definition ------------------------------------------------

class OpenGLTexture : public ITexture
{
	friend class OpenGLRenderingContext;

private:
	TextureDescriptor		descriptor;
	OpenGLResourceFactory*	creator;
	GLuint					textureID;
	uint16_t				actualWidth;	// depth textures can be larger than requested
	uint16_t				actualHeight;

	GLenum					target;
	GLint					internalFormat;
	GLenum					format;
	GLenum					type;

public:
	OpenGLTexture (OpenGLResourceFactory* factory, const TextureDescriptor& desc);
	~OpenGLTexture ();

	void ReplaceRegion (const Region& region, uint16_t level, const void* bytes, uint64_t pitch) override;
	void ReplaceRegion (const Region& region, uint16_t level, uint16_t slice, const void* bytes, uint64_t pitch, uint64_t slicesize) override;

	void GetBytes (void* outbytes, const Region& region, uint16_t level, uint64_t pitch) override;
	void GetBytes (void* outbytes, const Region& region, uint16_t level, uint16_t slice, uint64_t pitch, uint64_t slicesize) override;

	void SetActualSize (uint16_t width, uint16_t height);

	inline GLuint GetTexture () const					{ return textureID; }
	inline GLint GetInternalFormat () const				{ return OpenGLMaps::map_InternalFormat[descriptor.pixelFormat]; }
	inline GLenum GetTarget () const					{ return target; }

	inline uint16_t GetSampleCount () const override	{ return descriptor.sampleCount; }
	inline uint16_t GetWidth () const override			{ return descriptor.width; }
	inline uint16_t GetHeight () const override			{ return descriptor.height; }
	inline uint16_t GetActualWidth () const				{ return actualWidth; }
	inline uint16_t GetActualHeight () const			{ return actualHeight; }

	inline PixelFormat GetPixelFormat () const override	{ return descriptor.pixelFormat; }
	inline TextureType GetType () const override		{ return descriptor.textureType; }
	inline uint32_t GetOptions () const override		{ return descriptor.options; }
	inline uint32_t GetUsage () const override			{ return descriptor.usage; }
};

// --- OpenGLSamplerState definition -------------------------------------------

class OpenGLSamplerState : public ISamplerState
{
	friend class OpenGLResourceFactory;
	friend class OpenGLRenderingContext;

private:
	SamplerDescriptor		descriptor;
	GLuint					samplerID;
	OpenGLStateManager*		stateManager;
	OpenGLSamplerState*		assembledState;

public:
	OpenGLSamplerState (OpenGLResourceFactory* factory, const SamplerDescriptor& desc);
	~OpenGLSamplerState ();
};

// --- OpenGLFramebuffer definition --------------------------------------------

class OpenGLFramebuffer
{
	// NOTE: must know about attached textures in case one of them gets destroyed...

	friend class OpenGLResourceFactory;
	friend class OpenGLRenderingContext;

private:
	OpenGLResourceFactory*	creator;
	OpenGLStateManager*		stateManager;
	ITexture*				attachments[9];		// 8 color + 1 depth/stencil
	GLuint					renderBuffers[9];	// specifically for offscreen MSAA
	GLuint					framebufferID;

	bool IsUsingTexture (ITexture* texture) const;

public:
	OpenGLFramebuffer (OpenGLResourceFactory* factory, OpenGLRenderPass* renderpass, bool isresolveframebuffer);
	~OpenGLFramebuffer ();
	
	inline GLuint GetFramebufferID () const	{ return framebufferID; }
};

// --- OpenGLRenderPass definition ---------------------------------------------

class OpenGLRenderPass : public IRenderPass
{
	friend class OpenGLFramebuffer;
	friend class OpenGLResourceFactory;
	friend class OpenGLRenderingContext;

	struct AttachmentDesc {
		ITexture*	texture;
		uint16_t	level;
		uint16_t	slice;
		uint16_t	depthPlane;	// when 3D texture
		LoadAction	loadAction;
		StoreAction	storeAction;

		// when multisampling
		ITexture*	resolveTexture;
		uint16_t	resolveLevel;
		uint16_t	resolveSlice;
		uint16_t	resolveDepthPlane;

		AttachmentDesc ();
	};

	struct ColorAttachmentDesc : AttachmentDesc {
		Color clearColor;

		ColorAttachmentDesc ();
	};

	struct DepthStencilAttachmentDesc : AttachmentDesc {
		float clearDepth;
		uint8_t clearStencil;
		MultisampleDepthResolveFilter depthResolveFilter;

		DepthStencilAttachmentDesc ();
	};

private:
	ColorAttachmentDesc			colorAttachments[8];
	DepthStencilAttachmentDesc	depthAttachment;
	Rect						renderArea;

	// TODO: occlusion query, layered rendering

	OpenGLResourceFactory*		creator;
	OpenGLStateManager*			stateManager;
	uint32_t					boundAttachments;
	uint32_t					resolveAttachments;

	// resulting objects
	OpenGLFramebuffer*			framebuffer;
	OpenGLFramebuffer*			resolveFramebuffer;

public:
	OpenGLRenderPass (OpenGLResourceFactory* factory, OpenGLStateManager* manager);
	~OpenGLRenderPass ();

	void SetupColorAttachment (uint8_t index, ITexture* tex, uint16_t level, uint16_t slice, const Color& clearcolor, LoadAction loadaction, StoreAction storeaction) override;
	void SetupDepthStencilAttachment (ITexture* tex, uint16_t level, uint16_t slice, float cleardepth, uint8_t clearstencil, LoadAction loadaction, StoreAction storeaction) override;
	void SetupMSAAColorResolveTarget (uint8_t index, ITexture* target, uint16_t level, uint16_t slice) override;
	void SetupMSAADepthResolveTarget (ITexture* target, uint16_t level, uint16_t slice) override;
	
	void SetRenderArea (const Rect& renderarea) override;

	// specific
	bool Assemble ();
};

// --- OpenGLInputLayout definition --------------------------------------------

struct InputAttribute {
	char			name[32];
	VertexInputType	type;
	uint32_t		offset;
	uint32_t		bufferIndex;
	
	InputAttribute ();
};

struct BufferLayout {
	uint64_t			offset;
	IBuffer*			buffer;
	VertexStepFunction	stepFunction;
	uint32_t			stepRate;
	uint32_t			stride;

	BufferLayout ();
};

typedef std::vector<InputAttribute> InputLayout;
typedef std::vector<BufferLayout> InputBufferLayout;

class OpenGLInputLayout
{
	// NOTE: this and program object are to be cached in a pipeline

	friend class OpenGLResourceFactory;
	friend class OpenGLRenderingContext;
	friend class OpenGLGraphicsPipeline;

private:
	InputLayout			inputLayout;	// vertex description
	InputBufferLayout	bufferLayouts;	// input streams description
	OpenGLStateManager*	stateManager;
	GLuint				inputLayoutID;	// vertex array object

public:
	OpenGLInputLayout (OpenGLStateManager* manager, const InputLayout& inputlayout, const InputBufferLayout& bufferlayouts);
	~OpenGLInputLayout ();

	bool IsUsingVertexBuffer (IBuffer* vertexbuffer) const;
};

// --- OpenGLShaderProgram definition ------------------------------------------

struct SignatureElement {
	char			name[32];
	GLint			location;		// binding
	GLint			size;			// element size in bytes
	GLenum			type;			// element type

	SignatureElement ();
	SignatureElement (const SignatureElement& other);

	SignatureElement& operator =(const SignatureElement& other);
};

struct BufferBinding {
	uint32_t		usageFlags;
	uint32_t		binding;
};

struct PushConstantBlock {
	ShaderStage		stage;
	uint32_t		offset;
	uint32_t		size;
	uint32_t		binding;
};

typedef std::vector<SignatureElement> InputSignature;
typedef std::vector<PushConstantBlock> PushConstantBlocks;
typedef std::unordered_map<std::string, BufferBinding> InputBufferBindings;
typedef std::vector<GLint> InputBufferSizes;

class OpenGLShaderProgram
{
	// NOTE: this and input layout are to be cached in a pipeline

	friend class OpenGLResourceFactory;
	friend class OpenGLRenderingContext;
	friend class OpenGLGraphicsPipeline;

private:
	InputSignature		signature;
	InputBufferBindings	bufferBindings;
	InputBufferSizes	bufferSizes;			// obtained via shader reflection
	PushConstantBlocks	pushConstantBlocks;
	OpenGLStateManager*	stateManager;
	IBuffer*			pushConstantBuffer;		// OpenGL has no (portable) push constant support
	GLuint				programID;

public:
	OpenGLShaderProgram (OpenGLStateManager* manager, const InputBufferBindings& bufferbindings, const PushConstantBlocks& pushconstantblocks);
	~OpenGLShaderProgram ();
};

// --- OpenGLGraphicsPipeline definition ---------------------------------------

class OpenGLGraphicsPipeline : public IGraphicsPipeline
{
	friend class OpenGLResourceFactory;
	friend class OpenGLRenderingContext;

	struct InputAssemblerState {
		GLenum		topology;
		GLboolean	primitiveRestartEnable;

		InputAssemblerState ();
	};

	struct RasterizerState {
		GLenum		polygonMode;
		GLenum		cullFace;
		bool		scissorTest;
		bool		sRGBFramebuffer;
		bool		depthBiasEnable;		// polygon offset
		bool		depthClampEnable;		// if enabled, near/far clipping is disabled
		bool		clipDistanceEnable[8];	// user-defined clipping

		RasterizerState ();
	};

	struct BlendState {
		GLboolean		blendEnable;
		GLubyte			colorWriteMask;
		GLenum			colorBlendOp;
		GLenum			alphaBlendOp;
		GLenum			colorSrcBlend;
		GLenum			colorDstBlend;
		GLenum			alphaSrcBlend;
		GLenum			alphaDstBlend;

		BlendState ();
	};

	struct DepthStencilState {
		GLboolean		depthWriteEnable;
		GLboolean		stencilTestEnable;
		GLboolean		depthClampEnable;
		GLenum			depthFunc;

		GLenum			frontStencilFunc;
		GLenum			frontStencilPassOp;
		GLenum			frontStencilFailOp;
		GLenum			frontStencilZFailOp;
		GLuint			frontStencilMask;
		GLuint			frontStencilWriteMask;

		GLenum			backStencilFunc;
		GLenum			backStencilPassOp;
		GLenum			backStencilFailOp;
		GLenum			backStencilZFailOp;
		GLuint			backStencilMask;
		GLuint			backStencilWriteMask;

		DepthStencilState ();
	};

	struct MultisampleState {
		GLuint			rasterizationSamples;
		GLboolean		sampleShadingEnable;		// per-sample or per-fragment
		GLboolean		alphaToCoverageEnable;
		GLfloat			minSampleShading;

		// ...

		MultisampleState ();
	};

private:
	OpenGLResourceFactory*	creator;

	// descriptor objects
	InputLayout				inputLayout;			// vertex description
	InputBufferLayout		bufferLayouts;			// input streams description
	InputBufferBindings		bufferBindings;			// bindings for uniforms blocks (and/or 4.3 storage buffers)
	PushConstantBlocks		pushConstantBlocks;		// Metal/Vulkan: directly encoded into command buffer
	std::string				shaderCodes[5];

	// pipeline state
	InputAssemblerState		inputState;
	RasterizerState			rasterState;
	BlendState				blendStates[8];
	DepthStencilState		depthState;
	MultisampleState		multisampleState;

	// resulting pipeline objects
	OpenGLShaderProgram*	assembledProgram;		// from program cache
	OpenGLInputLayout*		assembledInputLayout;	// from input layout cache

public:
	OpenGLGraphicsPipeline (OpenGLResourceFactory* factory);
	~OpenGLGraphicsPipeline ();

	bool AddShader (ShaderStage stage, const char* source) override;
	bool AddPushConstantBlock (ShaderStage stage, uint32_t size) override;
	bool Assemble (IRenderPass* renderpass) override;

	// vertex input state
	void ClearInputLayout () override;
	void SetInputAttribute (const char* name, uint32_t bufferindex, VertexInputType type, uint32_t offset) override;

	// NOTE: buffer is only needed for GL 3.3; the param should be removed after GL 4.3/Metal/Vulkan
	void SetInputBufferLayout (uint32_t bufferindex, IBuffer* buffer, VertexStepFunction stepfunction, uint32_t steprate, uint64_t offset, uint32_t stride) override;
	//void SetInputBufferLayout (uint32_t bufferindex, VertexStepFunction stepfunction, uint32_t steprate, uint64_t offset, uint32_t stride) override;
	void SetBufferBinding (const char* buffername, uint32_t usageflags, uint32_t binding) override;

	// input assembler state
	void SetPrimitiveTopology (PrimitiveType topology) override;
	void EnablePrimitiveRestart (bool enable) override;

	// rasterizer state
	void SetPolygonMode (PolygonMode mode) override;
	void SetCullMode (CullMode mode) override;
	void EnableScissorTest (bool enable) override;
	void EnableSRGB (bool enable) override;
	void EnableDepthBias (bool enable) override;
	void EnableDepthClamp (bool enable) override;
	void EnableClipDistance (uint8_t index, bool enable) override;

	// blend state
	void EnableBlend (uint8_t attachment, bool enable) override;
	void SetColorWriteMask (uint8_t attachment, uint8_t mask) override;
	void SetColorBlend (uint8_t attachment, BlendOperation blendop, BlendFactor srcfactor, BlendFactor dstfactor) override;
	void SetAlphaBlend (uint8_t attachment, BlendOperation blendop, BlendFactor srcfactor, BlendFactor dstfactor) override;

	// depth-stencil state
	void EnableDepthWrite (bool enable) override;
	void EnableStencilTest (bool enable) override;
	void SetDepthCompare (CompareFunction compareop) override;
	void SetStencilFunction (StencilFace face, CompareFunction compareop, StencilOperation pass, StencilOperation fail, StencilOperation zfail) override;
	void SetStencilMask (StencilFace face, uint8_t comparemask, uint8_t writemask) override;

	// multisample state
	void SetRasterizationSamples (uint32_t samples) override;
	void SetMinSampleShading (bool enable, float value) override;

	// query methods
	uint64_t GetBufferBlockStride (uint32_t binding) override;
};

// --- OpenGLStateManager definition -------------------------------------------

class OpenGLStateManager
{
	// NOTE: can be extended later

private:
	int		universeID;
	GLuint	readFramebuffer;
	GLuint	drawFramebuffer;
	GLuint	currentProgram;
	GLuint	currentSamplers[16];
	GLuint	currentVAO;

public:
	OpenGLStateManager (int universe);

	void BindFramebuffer (GLenum target, GLuint framebuffer);
	void BindSampler (GLuint unit, GLuint sampler);
	void BindVertexArray (GLuint vao);
	void UseProgram (GLuint program);

	void Zero_If_Framebuffer (GLuint framebuffer);
	void Zero_If_Sampler (GLuint sampler);
	void Zero_If_VertexArray (GLuint vao);
	void Zero_If_Program (GLuint program);
};

// --- OpenGLResourceFactory definition ----------------------------------------

class OpenGLResourceFactory : public IResourceFactory
{
private:
	std::map<std::pair<int, uint64_t>, OpenGLInputLayout*> inputLayoutCache;
	std::map<std::pair<int, uint64_t>, OpenGLShaderProgram*> programCache;
	std::map<std::pair<int, uint64_t>, OpenGLSamplerState*> samplerCache;
	std::map<std::pair<int, uint64_t>, OpenGLFramebuffer*> framebufferCache;
	std::map<int, std::set<ITexture*> > depthBufferCache;

	OpenGLRenderingCore* renderCore;

public:
	OpenGLResourceFactory (OpenGLRenderingCore* core);
	~OpenGLResourceFactory ();

	// overrides
	IBuffer* CreateBuffer (uint64_t size, uint32_t usageflags, uint32_t options, const void* initialdata = nullptr) override;
	ITexture* CreateTexture (const TextureDescriptor& descriptor) override;
	ISamplerState* CreateSamplerState (const SamplerDescriptor& descriptor) override;
	IRenderPass* CreateRenderPass () override;
	IGraphicsPipeline* CreateGraphicsPipeline () override;

	bool HACK_ShelveDepthBuffer (ITexture* texture) override;
	
	// specific
	OpenGLInputLayout* FindInputLayout (uint64_t hashkey);
	OpenGLShaderProgram* FindProgram (uint64_t hashkey);
	OpenGLSamplerState* FindSamplerState (uint64_t hashkey);
	OpenGLFramebuffer* FindFramebuffer (uint64_t hashkey);

	void CacheInputLayout (uint64_t hashkey, OpenGLInputLayout* layout);
	void CacheProgram (uint64_t hashkey, OpenGLShaderProgram* program);
	void CacheSamplerState (uint64_t hashkey, OpenGLSamplerState* samplerstate);
	void CacheFramebuffer (uint64_t hashkey, OpenGLFramebuffer* framebuffer);

	void DeleteInputLayouts (int universe);
	void DeleteInputLayoutsUsing (IBuffer* vertexbuffer);
	void DeletePrograms (int universe);
	void DeleteSamplerStates (int universe);
	void DeleteFramebuffers (int universe);
	void DeleteFramebuffersUsing (ITexture* texture);
	void DeleteShelvedDepthBuffers (int universe);

	// other
	int GetActiveUniverseID () const;
	OpenGLStateManager* GetActiveStateManager ();
};

bool CheckFramebufferStatus ();
	
}

#endif
