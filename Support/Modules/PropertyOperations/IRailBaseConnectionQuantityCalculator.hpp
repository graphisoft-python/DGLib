// Contact person : NN

#ifndef I_RAILBASE_CONNECTION_QUANTITY_CALCULATOR_HPP
#define I_RAILBASE_CONNECTION_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IRailBaseConnectionQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IRailBaseConnectionQuantityCalculator ();
};

}

#endif
