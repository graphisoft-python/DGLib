// Contact person : KiP

#ifndef I_SKYLIGHT_QUANTITY_CALCULATOR_HPP
#define I_SKYLIGHT_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT ISkylightQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~ISkylightQuantityCalculator ();
};

}

#endif
