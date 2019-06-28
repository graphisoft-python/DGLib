// Contact person : KiP

#ifndef I_ROOM_QUANTITY_CALCULATOR_HPP
#define I_ROOM_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IRoomQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IRoomQuantityCalculator ();

	virtual double		GetArea					() const = 0;
	virtual Int32		GetNumberOfBeams		() const = 0;
	virtual Int32		GetNumberOfColumns		() const = 0;
	virtual Int32		GetNumberOfDoors		() const = 0;
	virtual Int32		GetNumberOfLamps		() const = 0;
	virtual Int32		GetNumberOfObjects		() const = 0;
	virtual Int32		GetNumberOfWindows		() const = 0;
	virtual Int32		GetNumberOfWallParts	() const = 0;
};

}

#endif
