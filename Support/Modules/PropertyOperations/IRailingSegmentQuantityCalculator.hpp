// Contact person : NN

#ifndef I_RAILINGSEGMENT_QUANTITY_CALCULATOR_HPP
#define I_RAILINGSEGMENT_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace GS {
	template <class Type>
	class HashSet;
}

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IRailingSegmentQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IRailingSegmentQuantityCalculator ();
};

}

#endif
