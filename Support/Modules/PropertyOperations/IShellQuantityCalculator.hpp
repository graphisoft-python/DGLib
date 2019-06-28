// Contact person : KiP

#ifndef I_SHELL_QUANTITY_CALCULATOR_HPP
#define I_SHELL_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IShellQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IShellQuantityCalculator ();

	virtual double		GetFloorPlanArea									() const = 0;
	virtual double		GetConditionalSurfaceAreaOfOppositeToReferenceSide	() const = 0;
	virtual double		GetConditionalSurfaceAreaOfReferenceSide			() const = 0;
	virtual double		GetConditionalVolume								() const = 0;
	virtual double		GetDomeConnectionLength								() const = 0;
	virtual double		GetEavesLength										() const = 0;
	virtual double		GetEndWallConnectionLength							() const = 0;
	virtual double		GetGablesLength										() const = 0;
	virtual double		GetGrossSurfaceAreaOfEdges							() const = 0;
	virtual double		GetGrossSurfaceAreaOfOppositeToReferenceSide		() const = 0;
	virtual double		GetGrossSurfaceAreaOfReferenceSide					() const = 0;
	virtual double		GetGrossVolume										() const = 0;
	virtual double		GetHipsLength										() const = 0;
	virtual double		GetHolesPerimeter									() const = 0;
	virtual double		GetHolesSurfaceArea									() const = 0;
	virtual double		GetHollowConnectionLength							() const = 0;
	virtual double		GetInsulationSkinThickness							() const = 0;
	virtual double		GetNetSurfaceAreaOfEdges							() const = 0;
	virtual double		GetNetSurfaceAreaOfOppositeToReferenceSide			() const = 0;
	virtual double		GetNetSurfaceAreaOfReferenceSide					() const = 0;
	virtual Int32		GetNumberOfHoles									() const = 0;
	virtual Int32		GetNumberOfSkylights								() const = 0;
	virtual double		GetOpeningsSurfaceArea								() const = 0;
	virtual double		GetPeaksLength										() const = 0;
	virtual double		GetPerimeter										() const = 0;
	virtual double		GetRidgesLength										() const = 0;
	virtual double		GetSideWallConnectionLength							() const = 0;
	virtual double		GetValleysLength									() const = 0;
};

}

#endif
