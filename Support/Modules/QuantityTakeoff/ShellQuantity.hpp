// Contact person : KiP, TaB

#ifndef SHELLQUANTITY_HPP
#define SHELLQUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IShellQuantityCalculator.hpp"

// from QuantityTakeoff
#include "ShellBaseQuantity.hpp"

// =====================================================================================================================

typedef		GS::HashTable<UIndex, UIndex>	BodyIdxToComponentIdxMap;

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST ShellQuantityCalculator : public Property::IShellQuantityCalculator, public ShellBaseQuantityCalculator
{

public:
	ShellQuantityCalculator (VBElem::ModelElementConstRef vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~ShellQuantityCalculator ();

	virtual double				GetFloorPlanArea												() const override;
	virtual double				GetConditionalSurfaceAreaOfOppositeToReferenceSide				() const override;
	virtual double				GetConditionalSurfaceAreaOfReferenceSide						() const override;
	virtual double				GetConditionalVolume											() const override;
	virtual double				GetDomeConnectionLength											() const override;
	virtual double				GetEavesLength													() const override;
	virtual double				GetEndWallConnectionLength										() const override;
	virtual double				GetGablesLength													() const override;
	virtual double				GetGrossSurfaceAreaOfEdges										() const override;
	virtual double				GetGrossSurfaceAreaOfOppositeToReferenceSide					() const override;
	virtual double				GetGrossSurfaceAreaOfReferenceSide								() const override;
	virtual double				GetGrossVolume													() const override;
	virtual double				GetHipsLength													() const override;
	virtual double				GetHolesPerimeter												() const override;
	virtual double				GetHolesSurfaceArea												() const override;
	virtual double				GetHollowConnectionLength										() const override;
	virtual double				GetInsulationSkinThickness										() const override;
	virtual double				GetNetSurfaceAreaOfEdges										() const override;
	virtual double				GetNetSurfaceAreaOfOppositeToReferenceSide						() const override;
	virtual double				GetNetSurfaceAreaOfReferenceSide								() const override;
	virtual Int32				GetNumberOfHoles												() const override;
	virtual Int32				GetNumberOfSkylights											() const override;
	virtual double				GetOpeningsSurfaceArea											() const override;
	virtual double				GetPeaksLength													() const override;
	virtual double				GetPerimeter													() const override;
	virtual double				GetRidgesLength													() const override;
	virtual double				GetSideWallConnectionLength										() const override;
	virtual double				GetValleysLength												() const override;

	virtual	double											GetNetVolume						() const override;
	virtual	double											GetTotalSurfaceArea					() const override;

	virtual GS::HashSet<VBEO::ModelElemComponentId>			GetComponents						() const override;
	virtual	UIndex											GetComponentBuildingMaterialIdx		(const VBEO::ModelElemComponentId& componentId) const override;
	virtual double											GetComponentVolume					(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	bool											HasComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	double											GetComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;

	virtual GS::HashSet<ModelCalculations::SurfaceId>		GetVisibleSurfaces					() const override;
	virtual GS::HashSet<VBEO::ModelElemComponentSurfaceId>	GetComponentSurfaces				() const override;
	virtual	double											GetExposedSurfaceArea				(const VBEO::ModelElemComponentSurfaceId& componentSurfaceId) const override;

private:
	virtual	ModelCalculations::ProjectionSurfaceRef GetProjectionSurface (const VBEO::ModelElemComponentId& componentId) const override;
	virtual	Int32	GetNumberOfContourHoles () const override;
	BodyIdxToComponentIdxMap	GetBodyIdxToComponentIdxMap (const Modeler::ConstElemPtr& elem) const;

	virtual CONV2LISTREC	GetWithHoleListParams () const override;
	virtual CONV2LISTREC	GetWithoutHoleListParams () const override;
	
	const VBElem::ShellConstRef& GetShell () const;
};

}

#endif