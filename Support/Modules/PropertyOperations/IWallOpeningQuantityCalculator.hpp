// Contact person : KiP

#ifndef I_WALLOPENING_QUANTITY_CALCULATOR_HPP
#define I_WALLOPENING_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IWallOpeningQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IWallOpeningQuantityCalculator ();

	virtual double		GetOpeningVolume						() const = 0;
	virtual double		GetGrossVolume							() const = 0;
	virtual double		GetSurface								() const = 0;
	virtual double		GetGrossSurface							() const = 0;
	virtual double		GetRevealSideWidth						() const = 0;
	virtual double		GetOppositeRevealSideWidth				() const = 0;
	virtual double		GetRevealSideHeight						() const = 0;
	virtual double		GetOppositeRevealSideHeight				() const = 0;
	virtual double		GetRevealSideSurface					() const = 0;
	virtual double		GetOppositeRevealSideSurface			() const = 0;
	virtual double		GetNominalRevealSideWidth				() const = 0;
	virtual double		GetNominalOppositeRevealSideWidth		() const = 0;
	virtual double		GetNominalRevealSideHeight				() const = 0;
	virtual double		GetNominalOppositeRevealSideHeight		() const = 0;
	virtual double		GetNominalRevealSideSurface				() const = 0;
	virtual double		GetNominalOppositeRevealSideSurface		() const = 0;
	virtual double		GetSillHeight							() const = 0;
	virtual double		GetRevealSideSillHeight					() const = 0;
	virtual double		GetOppositeRevealSideSillHeight			() const = 0;
	virtual double		GetHeadHeight							() const = 0;
	virtual double		GetRevealSideHeadHeight					() const = 0;
	virtual double		GetOppositeRevealSideHeadHeight			() const = 0;
};

}

#endif
