// Contact person :	KiP

#ifndef MESH_QUANTITY_HPP
#define MESH_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IMeshQuantityCalculator.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST MeshQuantityCalculator : public Property::IMeshQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	MeshQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~MeshQuantityCalculator ();

	virtual double											GetSurfaceArea						(Int32 surfaceType) const override;
	virtual double											GetHolePerimeter					() const override;
	virtual double											GetHoleSurface						() const override;
	virtual double											GetProjectedArea					() const override;

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

	void	CalcMesh (const Int32		*globalsBits,	// TODO TestEnv KiP csak tesztben hasznaljuk
					  Int32				*actSegmentsNr,
					  double			*perimeter,
					  double			*holesPrm,
					  double			*bottomSurface,
					  double			*topSurface,
					  double			*edgeSurface,	// without holes
					  double			*holesSurface,
					  double			*volume,
					  double			*projectedArea) const;			// tp99.02.25


private:
	virtual VBEO::ModelElemComponentId						GetComponentId				(const Modeler::MeshBody& body) const override;
	virtual	ModelCalculations::ProjectionSurfaceRef			GetProjectionSurface		(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	IPolygonSurfaceType*							GetPolygonSurfaceType		() const override;

	const VBElem::MeshConstRef& GetMesh () const;
};

}

#endif