// Contact person : KiP

#ifndef POLYROOF_QUANTITY_HPP
#define POLYROOF_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IPolyRoofQuantityCalculator.hpp"
#include "PolyRoofElemPartId.hpp"

// from QuantityTakeoff
#include "RoofQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST PolyRoofQuantityCalculator : public Property::IPolyRoofQuantityCalculator, public RoofQuantityCalculator
{
public:
	PolyRoofQuantityCalculator (VBElem::ModelElementConstRef vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~PolyRoofQuantityCalculator ();

	virtual double											GetSurfaceArea						(Int32 surfaceType) const override;
	virtual double											GetSurfaceTypeLength				(Int32 surfaceType) const override;
	virtual double											GetFloorPlanArea					() const override;

	virtual double											GetConditionalBottomSurfaceArea		() const override;
	virtual double											GetConditionalTopSurfaceArea		() const override;
	virtual double											GetConditionalVolume				() const override;
	virtual double											GetGrossBottomSurfaceArea			() const override;
	virtual double											GetGrossEdgeSurfaceArea				() const override;
	virtual double											GetGrossTopSurfaceArea				() const override;
	virtual double											GetGrossVolume						() const override;
	virtual double											GetHolesPerimeter					() const override;
	virtual double											GetHolesSurfaceArea					() const override;
	virtual double											GetInsulationSkinThickness			() const override;
	virtual double											GetNetBottomSurfaceArea				() const override;
	virtual double											GetNetEdgeSurfaceArea				() const override;
	virtual double											GetNetTopSurfaceArea				() const override;
	virtual Int32											GetHoleNumber						() const override;
	virtual Int32											GetSkylightNumber					() const override;
	virtual double											GetOpeningsSurfaceArea				() const override;
	virtual double											GetPerimeter						() const override;

	virtual double											GetNetVolume						() const override;
	virtual double											GetTotalSurfaceArea					() const override;

	virtual GS::HashSet<VBEO::ModelElemComponentId>			GetComponents						() const override;
	virtual	UIndex											GetComponentBuildingMaterialIdx		(const VBEO::ModelElemComponentId& componentId) const override;
	virtual double											GetComponentVolume					(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	bool											HasComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	double											GetComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;

	virtual GS::HashSet<ModelCalculations::SurfaceId>		GetVisibleSurfaces					() const override;
	virtual GS::HashSet<VBEO::ModelElemComponentSurfaceId>	GetComponentSurfaces				() const override;
	virtual	double											GetExposedSurfaceArea				(const VBEO::ModelElemComponentSurfaceId& componentSurfaceId) const override;

private:
	virtual	ModelCalculations::ProjectionSurfaceRef	GetProjectionSurface (const VBEO::ModelElemComponentId& componentId) const override;
	virtual	IPolygonSurfaceType*					GetPolygonSurfaceType () const override;

	void EnumerateExistingElemParts (const std::function<void (const Property::PolyRoofElemPartId&)>& processor) const;

	virtual CONV2LISTREC GetWithHoleListParams () const override;
	virtual CONV2LISTREC GetWithoutHoleListParams () const override;
			CONV2LISTREC GetGrossModelListParams () const;

	const VBElem::PolyRoofConstRef& GetPolyRoof () const;

	GSErrCode	SumPolyRoofHoleAndSkylightNum (GS::HashTable<QT_ElemPartId, QT_ElementQuantity>&	quantitiesTable) const;

};

}

#endif
