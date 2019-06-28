// Contact person : AACS

#ifndef I_CWSEGMENT_QUANTITY_CALCULATOR_HPP
#define I_CWSEGMENT_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================


namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT ICWSegmentQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~ICWSegmentQuantityCalculator ();
};

}

#endif
