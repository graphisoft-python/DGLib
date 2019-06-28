// Contact person : KiP

#ifndef I_STAIR_QUANTITY_CALCULATOR_HPP
#define I_STAIR_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IStairQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IStairQuantityCalculator ();

	virtual double		GetArea					() const = 0;
	virtual double		GetFrontSurfaceArea		() const = 0;
};

}

#endif
