// Contact person : KiP

#ifndef I_FREESHAPE_QUANTITY_CALCULATOR_HPP
#define I_FREESHAPE_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// === Predeclarations =================================================================================================

namespace Property {
	class FreeShapeElemPartId;
}

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IFreeShapeQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IFreeShapeQuantityCalculator ();

	virtual double		GetVolume							(const FreeShapeElemPartId& elemPartId) const = 0;

	virtual double		GetFloorPlanArea					() const = 0;
	virtual double		GetFloorPlanArea					(const FreeShapeElemPartId& elemPartId) const = 0;
	virtual double		GetProjectedFloorPlanPerimeter		() const = 0;
	virtual double		GetSurfaceArea						() const = 0;
	virtual UInt32		GetNodesNumber						() const = 0;
	virtual UInt32		GetEdgesNumber						() const = 0;
	virtual UInt32		GetHiddenEdgesNumber				() const = 0;
	virtual UInt32		GetSoftEdgesNumber					() const = 0;
	virtual UInt32		GetVisibleEdgesNumber				() const = 0;
	virtual UInt32		GetFacesNumber						() const = 0;

	virtual double		GetBaseLevel						(const Property::FreeShapeElemPartId& elemPartId) const = 0;
	virtual double		GetBaseHight						(const Property::FreeShapeElemPartId& elemPartId) const = 0;
	virtual double		GetWholeHeight						(const Property::FreeShapeElemPartId& elemPartId) const = 0;
};

}

#endif
