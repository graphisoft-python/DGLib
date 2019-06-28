// *****************************************************************************
// File:			OpenGLBlitTarget.hpp
//
// Description:
//
// Project:
//
// Contact person:	SZI, DGY
//
// SG compatible
// *****************************************************************************

#ifndef _OPENGLBLITTARGET_HPP_
#define _OPENGLBLITTARGET_HPP_

// --- Includes ----------------------------------------------------------------

#include "NativeContext.hpp"

namespace NewDisplay {
	class NativeImage;
}

namespace Graphix {

class ITexture;
class OpenGLNativeContextImpl;

class GRAPHIX_DLL_EXPORT OpenGLBlitTarget : public NewDisplay::BlitTarget
{
private:
	OpenGLNativeContextImpl* owner;

public:
	OpenGLBlitTarget (OpenGLNativeContextImpl* context);
	~OpenGLBlitTarget ();

	void DrawImage (
		const  NewDisplay::NativeImage& image,
		float scaleX,
		float scaleY,
		float rotation,
		float translationX,
		float translationY,
		bool transparent,
		double alpha = 1.0, 
		NewDisplay::Filtering filtering = NewDisplay::DefaultFilter,
		const  NewDisplay::BlitEffect* blitEffect = nullptr);

	bool BlitTo (
		ITexture* source,
		float scaleX,
		float scaleY,
		float rotation,
		float translationX,
		float translationY,
		float alpha,
		NewDisplay::BlendMode blendMode,
		NewDisplay::Filtering filtering,
		const NewDisplay::BlitEffect* blitEffect);

	bool CopyZBuffer (ITexture* source);
};

}

#endif
