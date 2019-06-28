// *****************************************************************************
// File:			OpenGLNativeContextInterface.hpp
//
// Description:		OpenGL native context implementation structures, handler functions
//
// Module:			Graphix
// Contact person:	DGY, SZI
//
// SG compatible
// *****************************************************************************

#ifndef	_OPENGLNATIVECONTEXTINTERFACE_HPP_
#define _OPENGLNATIVECONTEXTINTERFACE_HPP_

#define MAX_BUFFER_SIZE			(2*65536)	// vertex/index
#define MAX_UNIFORM_BUFFER_SIZE	4096	// uniform

// --- Includes ----------------------------------------------------------------

#include "GraphixDefinitions.hpp"		// GRAPHIX_DLL_EXPORT
#include "Rect.hpp"
#include "IRenderingCore.hpp"
#include "GPUStructures.hpp"
#include "IRenderingCore.hpp"
#include "NativeImage.hpp"

namespace NewDisplay {
	class INativeContextImpl;
}

namespace Graphix {

class ITexture;
class IBuffer;
class IRenderPass;
class OpenGLTextureCache;

// NOTE: dependencies for FlushPrimitivesTask (dependency injection)
struct GRAPHIX_DLL_EXPORT FlushDependencies
{
	ITexture*	colorTarget;
	ITexture*	depthTarget;
	IBuffer*	vertexBuffer;
	IBuffer*	indexBuffer;
	IBuffer*	instanceBuffer;
	IBuffer*	uniformBuffer;
	uint32_t	baseVertex;
	uint32_t	firstIndex;
	uint32_t	firstInstance;
	uint32_t	uniformOffset;

	FlushDependencies ();
};

// NOTE: requirements for external rendering (e.g. OpenGL addon)
struct GRAPHIX_DLL_EXPORT DataForExternalDraw
{
	ITexture*	colorTarget;
	ITexture*	depthTarget;
	int			universeID;

	DataForExternalDraw ();
};

// --- NativeContextDependenciesCreatorTask definition -------------------------

class GRAPHIX_DLL_EXPORT NativeContextDependenciesCreatorTask : public IRenderingTask
{
	// NOTE: creates/recreates/deletes OpenGLSurfaceImpl and OpenGLOffscreenContext textures
	// NOTE: implemented in OpenGLOffscreenContext.cpp

private:
	ITexture**		colorTarget;
	ITexture**		depthTarget;
	IBuffer**		vertexBuffer;
	IBuffer**		indexBuffer;
	IBuffer**		instanceBuffer;
	IBuffer**		uniformBuffer;
	IRenderPass*	renderPass;		// to fill textures
	Color			clearColor;
	UInt32			width;
	UInt32			height;
	bool			antialiasOn;

public:
	NativeContextDependenciesCreatorTask (int universeID, ITexture** outcolor, ITexture** outdepth, IBuffer** outvertex, IBuffer** outindex, IBuffer** outinstance, IBuffer** outuniform, UInt32 width_, UInt32 height_, const Color& clearcolor, bool antialiasing);
	NativeContextDependenciesCreatorTask (int universeID, ITexture** colortarget, ITexture** depthtarget, IBuffer** vertex, IBuffer** index, IBuffer** instance, IBuffer** uniform);
	~NativeContextDependenciesCreatorTask ();

	void Execute (IRenderingContext* context, IResourceFactory* factory) override;
	void Dispose () override;
};

// --- Function declarations ---------------------------------------------------

GRAPHIX_DLL_EXPORT NewDisplay::INativeContextImpl* CreateOpenGLNativeContext (
	int universe, FlushDependencies& injecteddepends, OpenGLTextureCache* texturecache,
	UInt32 width, UInt32 height, float scaleFactor, float lOriginX, float lOriginY,
	const GS::Rect<Int32>& rect, UInt32 clearcolor, bool multisampledTarget);

GRAPHIX_DLL_EXPORT void DrawAsImage (int universeID, ITexture* texture, double resolutionfactor, NewDisplay::NativeContext& contextToDrawTo);

GRAPHIX_DLL_EXPORT OpenGLTextureCache* CreateOpenGLTextureCache (int universe);
GRAPHIX_DLL_EXPORT void DestroyOpenGLTextureCache (OpenGLTextureCache* texcache);

}

#endif
