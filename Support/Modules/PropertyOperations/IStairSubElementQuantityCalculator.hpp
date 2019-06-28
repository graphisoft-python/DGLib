// Contact person : AACS

#ifndef I_STAIRSUBELEMENT_QUANTITY_CALCULATOR_HPP
#define I_STAIRSUBELEMENT_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "PropertyOperationsExport.hpp"
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IStairSubElementQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IStairSubElementQuantityCalculator ();
};

}

#endif
