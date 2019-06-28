// Contact person : KiP

#ifndef CEIL_QUANTITY_HPP
#define CEIL_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElements
#include "CeilTypes.hpp"

// from PropertyOperations
#include "ICeilQuantityCalculator.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST CeilQuantityCalculator : public Property::ICeilQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	CeilQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~CeilQuantityCalculator ();

	virtual double											GetNetVolume						() const override final;
	virtual double											GetTotalSurfaceArea					() const override final;
 
	virtual double											GetBottomSurface					() const override;
	virtual double											GetTopSurface						() const override;
	virtual double											GetEdgeSurface						() const override;
	virtual double											GetSurfaceArea						(Int32 surfaceType) const override;
	virtual double											GetConditionalBottomSurface			() const override;
	virtual double											GetConditionalTopSurface			() const override;
	virtual double											GetConditionalVolume				() const override;
	virtual double											GetGrossBottomSurface				() const override;
	virtual double											GetGrossTopSurface					() const override;
	virtual double											GetGrossEdgeSurface					() const override;
	virtual double											GetGrossVolume						() const override;
	virtual double											GetGrossBottomSurfaceWithHoles		() const override;
	virtual double											GetGrossTopSurfaceWithHoles			() const override;
	virtual double											GetGrossEdgeSurfaceWithHoles		() const override;
	virtual double											GetGrossVolumeWithHoles				() const override;
	virtual double											GetHolesPerimeter					() const override;
	virtual double											GetHolesSurface						() const override;
	virtual double											GetPerimeter						() const override;

	virtual GS::HashSet<VBEO::ModelElemComponentId>			GetComponents						() const override;
	virtual	UIndex											GetComponentBuildingMaterialIdx		(const VBEO::ModelElemComponentId& componentId) const override;
	virtual double											GetComponentVolume					(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	bool											HasComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	double											GetComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;

	virtual GS::HashSet<ModelCalculations::SurfaceId>		GetVisibleSurfaces					() const override;
	virtual GS::HashSet<VBEO::ModelElemComponentSurfaceId>	GetComponentSurfaces				() const override;
	virtual	double											GetExposedSurfaceArea				(const VBEO::ModelElemComponentSurfaceId& componentSurfaceId) const override;

private:
	virtual VBEO::ModelElemComponentId					GetComponentId (const Modeler::MeshBody& body) const override;
	virtual	ModelCalculations::ProjectionSurfaceRef		GetProjectionSurface (const VBEO::ModelElemComponentId& componentId) const override;
	virtual	IPolygonSurfaceType*						GetPolygonSurfaceType () const override;

	void	GetConditionalQuantities (double& condVolume, double& condTopSurface, double& condBottomSurface) const;
	UInt32	GetContourHoleNum () const;
	double	CalculateComponentVolumeNoPBC (const VBEO::ModelElemComponentId& componentId) const;

	virtual CONV2LISTREC	GetWithHoleListParams () const override;
	virtual CONV2LISTREC	GetWithoutHoleListParams () const override;
			CONV2LISTREC	GetGrossModelListParams () const;
			CONV2LISTREC	GetGrossModelWithHolesListParams () const;

			const VBElem::CeilConstRef& GetCeil () const;
};

}

#endif