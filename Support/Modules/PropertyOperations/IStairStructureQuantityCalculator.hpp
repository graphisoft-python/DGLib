// Contact person : KiP

#ifndef I_STAIRSTRUCTURE_QUANTITY_CALCULATOR_HPP
#define I_STAIRSTRUCTURE_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IStairSubElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IStairStructureQuantityCalculator : public IStairSubElementQuantityCalculator
{
public:
	virtual ~IStairStructureQuantityCalculator ();

	virtual double		GetHeight		() const = 0;
	virtual double		Get3DLength		() const = 0;
};

}

#endif
