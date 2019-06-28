// *****************************************************************************
// File:			BlitEffects.hpp
//
// Description:
//
// Project:
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef BLITEFFECTS_HPP
#define BLITEFFECTS_HPP

// --- Includes ----------------------------------------------------------------

#include "GraphixDefinitions.hpp"					// GRAPHIX_DLL_EXPORT
#include "Color.hpp"

#if defined(_MSC_VER)
#pragma warning (disable : 4512)
#endif

// --- Class declarations ------------------------------------------------------

namespace NewDisplay {

class GRAPHIX_DLL_EXPORT BlitEffect
{
protected:
	BlitEffect ();

public:
	virtual ~BlitEffect ();

	virtual BlitEffect* Clone () const = 0;
};


class GRAPHIX_DLL_EXPORT FalseColorBlitEffect: public BlitEffect
{
public:
	const Gfx::Color blackColor;
	const Gfx::Color whiteColor;

public:
	FalseColorBlitEffect (const Gfx::Color blackColor, const Gfx::Color whiteColor);
	virtual ~FalseColorBlitEffect ();

	virtual BlitEffect* Clone () const override { return new FalseColorBlitEffect (blackColor, whiteColor);  }
};

}

#endif
