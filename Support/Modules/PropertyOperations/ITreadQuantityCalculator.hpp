// Contact person : KiP

#ifndef I_TREAD_QUANTITY_CALCULATOR_HPP
#define I_TREAD_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IStairSubElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace GS {
	template <class Type>
	class HashSet;
}

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT ITreadQuantityCalculator : public IStairSubElementQuantityCalculator
{
public:
	virtual ~ITreadQuantityCalculator ();

	virtual	double		GetTopSurfaceArea		() const = 0;
	virtual	double		GetFrontSurfaceArea		() const = 0;
};

}

#endif
