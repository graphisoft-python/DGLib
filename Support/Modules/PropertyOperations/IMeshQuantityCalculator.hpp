// Contact person : KiP

#ifndef I_MESH_QUANTITY_CALCULATOR_HPP
#define I_MESH_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IMeshQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IMeshQuantityCalculator ();

	virtual double		GetSurfaceArea		(Int32 surfaceType) const = 0;
	virtual double		GetHolePerimeter	() const = 0;
	virtual double		GetHoleSurface		() const = 0;
	virtual double		GetProjectedArea	() const = 0;
};

}

#endif
