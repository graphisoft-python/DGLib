// Contact person : KiP

#ifndef I_MODELELEMENT_QUANTITY_CALCULATOR_HPP
#define I_MODELELEMENT_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from GSRoot
#include "HashSet.hpp"
#include "Array.hpp"

// from PropertyOperations
#include "PropertyOperationsTypes.hpp"
#include "PropertyOperationsExport.hpp"

// === Predeclarations =================================================================================================

namespace ModelCalculations {
	class SurfaceId;
}

namespace VBEO {
	class ModelElemComponentId;
	class ModelElemComponentSurfaceId;
}

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IModelElementQuantityCalculator
{
public:
	virtual ~IModelElementQuantityCalculator ();

	virtual	double											GetNetVolume						() const = 0;
	virtual	double											GetTotalSurfaceArea					() const = 0;

	virtual GS::HashSet<VBEO::ModelElemComponentId>			GetComponents						() const = 0;
	virtual	UIndex											GetComponentBuildingMaterialIdx		(const VBEO::ModelElemComponentId& componentId) const = 0;
	virtual double											GetComponentVolume					(const VBEO::ModelElemComponentId& componentId) const = 0;
	virtual	bool											HasComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const = 0;
	virtual	double											GetComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const = 0;

	virtual GS::HashSet<ModelCalculations::SurfaceId>		GetVisibleSurfaces					() const = 0;
	virtual GS::HashSet<VBEO::ModelElemComponentSurfaceId>	GetComponentSurfaces				() const = 0;
	virtual	double											GetExposedSurfaceArea				(const VBEO::ModelElemComponentSurfaceId& componentSurfaceId) const = 0;
};

}

#endif
