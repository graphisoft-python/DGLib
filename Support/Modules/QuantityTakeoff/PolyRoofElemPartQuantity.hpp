// Contact person : KiP

#ifndef POLYROOF_ELEMPART_QUANTITY_HPP
#define POLYROOF_ELEMPART_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IPolyRoofQuantityCalculator.hpp"
#include "PolyRoofElemPartId.hpp"

// from QuantityTakeoff
#include "RoofQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST PolyRoofElemPartQuantityCalculator : public Property::IPolyRoofQuantityCalculator, public RoofQuantityCalculator
{
public:
	PolyRoofElemPartQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const Property::PolyRoofElemPartId& elemPartId, const QuantityModelConstPtr& quantityModel);
	virtual ~PolyRoofElemPartQuantityCalculator ();

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
	virtual	ModelCalculations::ProjectionSurfaceRef GetProjectionSurface (const VBEO::ModelElemComponentId& componentId) const override;
	virtual	IPolygonSurfaceType*					GetPolygonSurfaceType () const override;

	const VBElem::PolyRoofConstRef& GetPolyRoof () const;

	static CONV2LISTREC GetGrossModelListParams ();
	static CONV2LISTREC GetNetModelListParams ();
	static CONV2LISTREC GetComponentSeparatedModelListParams ();

	void CalculateNumberOfHolesAndSkylights (UInt32& holesNumber, UInt32& skylightsNumber) const;

	double CalculateComponentVolumeNoPBC (const VBEO::ModelElemComponentId& componentId) const;


	void EnumerateTopSurfaceContourEdges (const CONV2LISTREC& listParams, const std::function<void (const Modeler::MeshBody& body, const TRANMAT& tran, UIndex edgeIdx, Int32 edgeSurfaceType)>& enumerator) const;

	static const GS::HashTable<Int32, VBElem::ShellBase::Contour::EdgeType>& GetSurfaceTypeToEdgeType ();

	static double CalculateEdgeLength (const Modeler::MeshBody& body, const TRANMAT& tran, UIndex edgeIdx);	//#KiP_Refactor #KiP_QT #KiP_Urgency_Low #KiP_Severity_Low	ez lehetne a BodyCalculator-on

	GSErrCode	SumPolyRoofHoleAndSkylightNum (GS::HashTable<QT_ElemPartId, QT_ElementQuantity>&	quantitiesTable) const;

	double GetPlaneAngle () const;

	const Property::PolyRoofElemPartId m_elemPartId;

	virtual CONV2LISTREC	GetWithHoleListParams () const override;
	virtual CONV2LISTREC	GetWithoutHoleListParams () const override;
};

}

#endif
