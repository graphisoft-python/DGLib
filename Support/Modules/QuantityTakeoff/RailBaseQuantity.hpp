// Contact person : KiP

#ifndef RAILBASE_QUANTITY_HPP
#define RAILBASE_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElements
#include "RailBaseTypes.hpp"

// from PropertyOperations
#include "IRailBaseQuantityCalculator.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST RailBaseQuantityCalculator : public Property::IRailBaseQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	RailBaseQuantityCalculator (VBElem::ModelElementConstRef vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~RailBaseQuantityCalculator ();

	virtual double											GetProjected3DLength				() const override;

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
	virtual VBEO::ModelElemComponentId GetComponentId (const Modeler::MeshBody& body) const override;

	const VBElem::RailBaseConstRef& GetRailBase () const;
};

}

#endif