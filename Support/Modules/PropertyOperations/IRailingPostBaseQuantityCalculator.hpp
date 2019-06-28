// Contact person : KiP

#ifndef I_RAILINGPOSTBASE_QUANTITY_CALCULATOR_HPP
#define I_RAILINGPOSTBASE_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IRailingPostBaseQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IRailingPostBaseQuantityCalculator ();

	virtual double		GetProjected3DLength () const = 0;
};

}

#endif
