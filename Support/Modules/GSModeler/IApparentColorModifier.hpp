#ifndef IMODELRGBMODIFIER_HPP
#define IMODELRGBMODIFIER_HPP

#pragma once

#include "CountedPtr.hpp"
#include "GSModelerExport.h"

struct GS_RGBColor;

class GSMODELER_DLL_EXPORT IApparentColorModifier		//Rename to IApparentColorModifier
{
public:
	virtual ~IApparentColorModifier ();

	virtual bool				IsMonochromeEnabled		() const = 0;
	virtual const GS_RGBColor*	GetMonochromeSurfaceRGB	() const = 0;  //returns not-nullptr only if it must be applied!
	virtual const GS_RGBColor*	GetMonochromeContourRGB	() const = 0;  //returns not-nullptr only if it must be applied!
	virtual bool				IsShadingOn				() const = 0;
	virtual double				GetCastShadowIntensity	() const = 0;
	virtual double				GetShadingIntensity		() const = 0;
};

typedef GS::CountedPtr<const IApparentColorModifier> IApparentColorModifierConstPtr;
typedef GS::CountedPtr<IApparentColorModifier> IApparentColorModifierPtr;

#endif
