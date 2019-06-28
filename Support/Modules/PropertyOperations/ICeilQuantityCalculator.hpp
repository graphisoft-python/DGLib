// Contact person : KiP

#ifndef I_CEIL_QUANTITY_CALCULATOR_HPP
#define I_CEIL_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT ICeilQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~ICeilQuantityCalculator ();

	virtual double		GetBottomSurface					() const = 0;
	virtual double		GetTopSurface						() const = 0;
	virtual double		GetEdgeSurface						() const = 0;
	virtual double		GetSurfaceArea						(Int32 surfaceType) const = 0;
	virtual double		GetConditionalBottomSurface			() const = 0;
	virtual double		GetConditionalTopSurface			() const = 0;
	virtual double		GetConditionalVolume				() const = 0;
	virtual double		GetGrossBottomSurface				() const = 0;
	virtual double		GetGrossTopSurface					() const = 0;
	virtual double		GetGrossEdgeSurface					() const = 0;
	virtual double		GetGrossVolume						() const = 0;
	virtual double		GetGrossBottomSurfaceWithHoles		() const = 0;
	virtual double		GetGrossTopSurfaceWithHoles			() const = 0;
	virtual double		GetGrossEdgeSurfaceWithHoles		() const = 0;
	virtual double		GetGrossVolumeWithHoles				() const = 0;
	virtual double		GetHolesPerimeter					() const = 0;
	virtual double		GetHolesSurface						() const = 0;
	virtual double		GetPerimeter						() const = 0;
};

}

#endif
