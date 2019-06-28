// Contact person : KiP

#ifndef I_RISER_QUANTITY_CALCULATOR_HPP
#define I_RISER_QUANTITY_CALCULATOR_HPP

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

class PROPERTY_OPERATIONS_DLL_EXPORT IRiserQuantityCalculator : public IStairSubElementQuantityCalculator
{
public:
	virtual ~IRiserQuantityCalculator ();

	virtual	double		GetFrontSurfaceArea		() const = 0;
	virtual	double		GetHeight				() const = 0;
};

}

#endif
