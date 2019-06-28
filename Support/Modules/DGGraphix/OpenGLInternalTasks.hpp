
#ifndef _OPENGLINTERNALTASKS_HPP_
#define _OPENGLINTERNALTASKS_HPP_

#include "Array.hpp"
#include "Rect.hpp"
#include "IRenderingCore.hpp"
#include "IResourceFactory.hpp"
#include "IRenderingContext.hpp"
#include "Condition.hpp"
#include "Lock.hpp"
#include <atomic>

// --- ScrollSurfaceTask definition --------------------------------------------

class ScrollSurfaceTask : public Graphix::IRenderingTask
{
private:
	Graphix::ITexture*	colorTarget;
	Graphix::ITexture*	tempTexture;
	double				translateX;
	double				translateY;

public:
	ScrollSurfaceTask (int universeID, Graphix::ITexture* colortarget, double offsetx, double offsety);

	void Execute (Graphix::IRenderingContext* context, Graphix::IResourceFactory* factory) override;
	void Dispose () override;
};

// --- RecomposeLayersTask definition ------------------------------------------

class RecomposeLayersTask : public Graphix::IRenderingTask
{
	// NOTE: resolves multisampled textures, recomposes them and presents to window

private:
	GS::Array<Graphix::ITexture*>	layersToCombine;
	GS::Array<Graphix::ITexture*>	resolvedLayers;
	GS::Array<float>				alphaValues;

	Graphix::Rect					renderArea;
	Graphix::ISamplerState*			samplerState;
	Graphix::IRenderPass*			renderPass;
	Graphix::IGraphicsPipeline*		framePipeline;	// for dialog frame
	Graphix::IGraphicsPipeline*		copyPipeline;	// for bottom layer
	Graphix::IGraphicsPipeline*		blendPipeline;	// for overlays


public:
	RecomposeLayersTask (int universe);

	// overrides
	void Execute (Graphix::IRenderingContext* context, Graphix::IResourceFactory* factory) override;
	void Dispose () override;

	// specific
	void SetLayerState (const GS::Array<Graphix::ITexture*>& layers);
	void SetAlphaState (const GS::Array<float>& alphas);
	void SetRenderArea (const Graphix::Rect& renderarea);
};

#endif
