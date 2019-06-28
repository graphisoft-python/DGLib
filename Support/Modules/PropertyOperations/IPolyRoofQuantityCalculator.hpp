// Contact person : KiP

#ifndef I_POLYROOF_QUANTITY_CALCULATOR_HPP
#define I_POLYROOF_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IPolyRoofQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IPolyRoofQuantityCalculator ();

	virtual double		GetSurfaceArea						(Int32 surfaceType) const = 0;
	virtual double		GetSurfaceTypeLength				(Int32 surfaceType) const = 0;
	virtual double		GetFloorPlanArea					() const = 0;

	virtual double		GetConditionalBottomSurfaceArea		() const = 0;
	virtual double		GetConditionalTopSurfaceArea		() const = 0;
	virtual double		GetConditionalVolume				() const = 0;
	virtual double		GetGrossBottomSurfaceArea			() const = 0;
	virtual double		GetGrossEdgeSurfaceArea				() const = 0;
	virtual double		GetGrossTopSurfaceArea				() const = 0;
	virtual double		GetGrossVolume						() const = 0;
	virtual double		GetHolesPerimeter					() const = 0;
	virtual double		GetHolesSurfaceArea					() const = 0;
	virtual double		GetInsulationSkinThickness			() const = 0;
	virtual double		GetNetBottomSurfaceArea				() const = 0;
	virtual double		GetNetEdgeSurfaceArea				() const = 0;
	virtual double		GetNetTopSurfaceArea				() const = 0;
	virtual Int32		GetHoleNumber						() const = 0;
	virtual Int32		GetSkylightNumber					() const = 0;
	virtual double		GetOpeningsSurfaceArea				() const = 0;
	virtual double		GetPerimeter						() const = 0;
};

}

#endif
