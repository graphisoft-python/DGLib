// Contact person : AACS

#ifndef I_CWACCESSORY_QUANTITY_CALCULATOR_HPP
#define I_CWACCESSORY_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================


namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT ICWAccessoryQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~ICWAccessoryQuantityCalculator ();
};

}

#endif
