#ifndef IMODELCONTOURWIDTHMODIFIER_HPP
#define IMODELCONTOURWIDTHMODIFIER_HPP

#pragma once

#include "GSModelerExport.h"
#include "CountedPtr.hpp"
#include "IModelVisualOverride.hpp"


class GSMODELER_DLL_EXPORT IModelContourWidthModifier
{
public:
	virtual ~IModelContourWidthModifier ();

	virtual void ModifyLineWidth (const VisualOverride::LineRole3D lineRole, short& lineWidth) const = 0;
	virtual short GetContourWidth () const = 0;
	virtual short GetSilhouetteWidth () const = 0;
	virtual short GetHatchLineWidth () const = 0;
	virtual short GetShadowContourWidth () const = 0;
};

typedef GS::CountedPtr<const IModelContourWidthModifier> IModelContourWidthModifierConstPtr;
typedef GS::CountedPtr<IModelContourWidthModifier> IModelContourWidthModifierPtr;



#endif
