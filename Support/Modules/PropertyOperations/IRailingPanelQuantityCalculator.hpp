// Contact person : NN

#ifndef I_RAILINGPANEL_QUANTITY_CALCULATOR_HPP
#define I_RAILINGPANEL_QUANTITY_CALCULATOR_HPP

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

class PROPERTY_OPERATIONS_DLL_EXPORT IRailingPanelQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IRailingPanelQuantityCalculator ();
};

}

#endif
