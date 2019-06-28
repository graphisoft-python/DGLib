// Contact person : NN

#ifndef I_RAILING_QUANTITY_CALCULATOR_HPP
#define I_RAILING_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IRailingQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IRailingQuantityCalculator ();

	virtual double	GetArea	() const = 0;
};

}

#endif
