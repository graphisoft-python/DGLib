// Contact person : KiP

#ifndef I_WALL_QUANTITY_CALCULATOR_HPP
#define I_WALL_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IWallQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IWallQuantityCalculator ();

	virtual double		GetAnalyticalHoleVolume				() const = 0;
	virtual double		GetConditionalInsideSkinVolume		() const = 0;
	virtual double		GetConditionalOutsideSkinVolume		() const = 0;
	virtual double		GetConditionalVolume				() const = 0;
	virtual double		GetGrossVolume						() const = 0;
	virtual double		GetInsideSkinVolume					() const = 0;
	virtual double		GetOutsideSkinVolume				() const = 0;
	virtual double		GetColumnVolume_notCalculated		() const = 0;

	virtual double		GetArea								() const = 0;
	virtual double		GetAnalyticalOutsideSurfaceArea		() const = 0;
	virtual double		GetAnalyticalInsideSurfaceArea		() const = 0;
	virtual double		GetAnalyticalHoleOutsideSurfaceArea	() const = 0;
	virtual double		GetAnalyticalHoleInsideSurfaceArea	() const = 0;
	virtual double		GetConditionalInsideSurfaceArea		() const = 0;
	virtual double		GetConditionalOutsideSurfaceArea	() const = 0;
	virtual double		GetDoorSurfaceArea					() const = 0;
	virtual double		GetEmptyHolesSurfaceArea			() const = 0;
	virtual double		GetGrossInsideSurfaceArea			() const = 0;
	virtual double		GetGrossOutsideSurfaceArea			() const = 0;
	virtual double		GetNetEdgeSurfaceArea				() const = 0;
	virtual double		GetNetInsideSurfaceArea				() const = 0;
	virtual double		GetNetOutsideSurfaceArea			() const = 0;
	virtual double		GetWindowSurfaceArea				() const = 0;

	virtual double		GetCenterLength						() const = 0;
	virtual double		GetConditionalInsideLength			() const = 0;
	virtual double		GetConditionalOutsideLength			() const = 0;
	virtual double		GetInsideLength						() const = 0;
	virtual double		GetOutsideLength					() const = 0;
	virtual double		GetAverageLength					() const = 0;
	virtual	double		GetProjected3DLength				() const = 0;
	virtual double		GetPerimeter						() const = 0;
	virtual double		GetReferenceLineLength				() const = 0;

	virtual Int32		GetColumnNumber						() const = 0;
	virtual Int32		GetDoorNumber						() const = 0;
	virtual Int32		GetWindowNumber						() const = 0;
	virtual Int32		GetHoleNumber						() const = 0;

	virtual	double		GetTotalDoorWidth					() const = 0;
	virtual double		GetTotalWindowWidth					() const = 0;

	virtual double		GetMaxHeight						() const = 0;
	virtual double		GetMinHeight						() const = 0;
	virtual double		GetInsideMinHeight					() const = 0;
	virtual double		GetInsideMaxHeight					() const = 0;
	virtual double		GetOutsideMinHeight					() const = 0;
	virtual double		GetOutsideMaxHeight					() const = 0;

	virtual double		GetAirThickness						() const = 0;
	virtual double		GetInsulationThickness				() const = 0;
	virtual double		GetOutsideThickness					() const = 0;
	virtual double		GetInsideThickness					() const = 0;
};

}

#endif
