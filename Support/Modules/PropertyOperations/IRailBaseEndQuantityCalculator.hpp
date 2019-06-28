// Contact person : NN

#ifndef I_RAILBASE_END_QUANTITY_CALCULATOR_HPP
#define I_RAILBASE_END_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IRailBaseEndQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IRailBaseEndQuantityCalculator ();
};

}

#endif
