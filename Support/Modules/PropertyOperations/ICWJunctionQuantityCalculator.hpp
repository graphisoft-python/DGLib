// Contact person : AACS

#ifndef I_CWJUNCTION_QUANTITY_CALCULATOR_HPP
#define I_CWJUNCTION_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================


namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT ICWJunctionQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~ICWJunctionQuantityCalculator ();

	virtual GS::UniString	GetType () const = 0;
};

}

#endif
