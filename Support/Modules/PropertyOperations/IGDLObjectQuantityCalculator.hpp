// Contact person : KiP

#ifndef I_GDLOBJECT_QUANTITY_CALCULATOR_HPP
#define I_GDLOBJECT_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IGDLObjectQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IGDLObjectQuantityCalculator ();
};

}

#endif
