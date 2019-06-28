// Contact person : TaB, KiP

#ifndef FREESHAPE_QUANTITY_HPP
#define FREESHAPE_QUANTITY_HPP

#pragma  once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IFreeShapeQuantityCalculator.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST FreeShapeQuantityCalculator : public Property::IFreeShapeQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	FreeShapeQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~FreeShapeQuantityCalculator ();

	virtual double											GetVolume							(const Property::FreeShapeElemPartId& elemPartId) const override;

	virtual double											GetFloorPlanArea					() const override;
	virtual double											GetFloorPlanArea					(const Property::FreeShapeElemPartId& elemPartId) const override;
	Geometry::MultiPolygon2D								GetFloorPlanPolygon					() const;
	Geometry::MultiPolygon2D								GetFloorPlanPolygon					(const Property::FreeShapeElemPartId& elemPartId) const;
	virtual double											GetProjectedFloorPlanPerimeter		() const override;
	virtual double											GetSurfaceArea						() const override;
	virtual UInt32											GetNodesNumber						() const override;
	virtual UInt32											GetEdgesNumber						() const override;
	virtual UInt32											GetHiddenEdgesNumber				() const override;
	virtual UInt32											GetSoftEdgesNumber					() const override;
	virtual UInt32											GetVisibleEdgesNumber				() const override;
	virtual UInt32											GetFacesNumber						() const override;

	virtual double											GetBaseLevel						(const Property::FreeShapeElemPartId& elemPartId) const override;
	virtual double											GetBaseHight						(const Property::FreeShapeElemPartId& elemPartId) const override;
	virtual double											GetWholeHeight						(const Property::FreeShapeElemPartId& elemPartId) const override;

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

	ModelCalculations::MeshBodyCuttingResult				GetOneFloorBodies					(const GSIndex floorIndex) const;

private:
	virtual VBEO::ModelElemComponentId	GetComponentId (const Modeler::MeshBody& body) const override;

	void	CalcOneFreeShapeSurfVol (const Int32						*globalsBits,
									 double								*surface,
									 double								*volume,
									 double								*floorPlanArea,
									 double								*floorPlanPerimeter,
									 double 							*baseLevel,
									 double 							*height,
									 UInt32								*nodesNr,
									 UInt32								*edgesNr,
									 UInt32								*hiddenEdgesNr,
									 UInt32								*softEdgesNr,
									 UInt32								*visibleEdgesNr,
									 UInt32								*facesNr) const;

	const VBElem::FreeShapeConstRef& GetFreeShape () const;

	
	ModelCalculations::MeshBodyCuttingResult GetOneFloorBodies (GSIndex floorIdx, const EDB::FloorStructureConstRef& floorStructure, const Modeler::ConstElemPtr& elem) const;
};

}

#endif