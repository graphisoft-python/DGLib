// Contact person : KiP

#ifndef I_RAILBASE_QUANTITY_CALCULATOR_HPP
#define I_RAILBASE_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IRailBaseQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IRailBaseQuantityCalculator ();

	virtual double		GetProjected3DLength () const = 0;
};

}

#endif
