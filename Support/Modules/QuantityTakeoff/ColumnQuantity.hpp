// Contact person :	KiP

#ifndef COLUMN_QUANTITY_HPP
#define COLUMN_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElements
#include "ColumnTypes.hpp"

// from PropertyOperations
#include "IColumnQuantityCalculator.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST ColumnQuantityCalculator : public Property::IColumnQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	ColumnQuantityCalculator (VBElem::ModelElementConstRef vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~ColumnQuantityCalculator ();

	virtual double											GetNetVolume						() const override final;
	virtual double											GetTotalSurfaceArea					() const override final;

	virtual double											GetCoreVolume						() const override;
	virtual double											GetVeneerVolume						() const override;
	virtual double											GetGrossVolume						() const override;
	virtual double											GetGrossCoreVolume					() const override;
	virtual double											GetGrossVeneerVolume				() const override;

	virtual double											GetCoreSurfaceArea					(Int32 surfaceType) const override;
	virtual double											GetVeneerSurfaceArea				(Int32 surfaceType) const override;
	virtual double											GetGrossCoreSurfaceArea				(Int32 surfaceType) const override;
	virtual double											GetGrossVeneerSurfaceArea			(Int32 surfaceType) const override;

	virtual double											GetArea								() const override;
	virtual double											GetPerimeter						() const override;
	virtual double											GetMinimumHeight					() const override;
	virtual double											GetMaximumHeight					() const override;
	virtual	double											GetProjected3DLength				() const override;

	virtual GS::HashSet<VBEO::ModelElemComponentId>			GetComponents						() const override;
	virtual	UIndex											GetComponentBuildingMaterialIdx		(const VBEO::ModelElemComponentId& componentId) const override;
	virtual double											GetComponentVolume					(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	bool											HasComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	double											GetComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;

	virtual GS::HashSet<ModelCalculations::SurfaceId>		GetVisibleSurfaces					() const override;
	virtual GS::HashSet<VBEO::ModelElemComponentSurfaceId>	GetComponentSurfaces				() const override;
	virtual	double											GetExposedSurfaceArea				(const VBEO::ModelElemComponentSurfaceId& componentSurfaceId) const override;

private:
	const VBElem::ColumnConstRef& GetColumn () const;

	virtual VBEO::ModelElemComponentId					GetComponentId (const Modeler::MeshBody& body) const override;
	virtual	ModelCalculations::ProjectionSurfaceRef	GetProjectionSurface (const VBEO::ModelElemComponentId& componentId) const override;
	virtual	IPolygonSurfaceType*					GetPolygonSurfaceType () const override;

	static CONV2LISTREC		GetNormalModelListParams ();
	static CONV2LISTREC		GetGrossModelListParams ();
	static CONV2LISTREC		GetCoreModelListParams ();
	static CONV2LISTREC		GetGrossCoreModelListParams ();
	static CONV2LISTREC		GetDetailedModelListParams ();

	double	GetCoreGrossTopBotSurface () const;
	double	GetVeneerGrossTopBotSurface () const;	
	void CalculateElevations (double& bottom, double& highestTopPoint, double& lowestTopPoint) const;

	double	GetSquareColumnProjectedArea (const VBEO::ModelElemComponentId& componentId, const CONV2LISTREC& listParams = CreateListParams (DetailedFinalModel)) const;

	Geometry::MultiPolygon2D	GetUnifiedProfilePolygon () const;

	void	CalculateSkinvolumesNoPBC_Deprecated (double** skinVolumes) const;
};

}

#endif
