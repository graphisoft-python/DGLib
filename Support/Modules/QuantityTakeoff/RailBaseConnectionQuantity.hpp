// Contact person : NN

#ifndef RAILBASE_CONNECTION_QUANTITY_HPP
#define RAILBASE_CONNECTION_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElements
#include "RailBaseConnectionTypes.hpp"

// from PropertyOperations
#include "IRailBaseConnectionQuantityCalculator.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST RailBaseConnectionQuantityCalculator : public Property::IRailBaseConnectionQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	RailBaseConnectionQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~RailBaseConnectionQuantityCalculator ();
	
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

	const VBElem::RailBaseConnectionConstRef& GetRailBaseConnection () const;
};

}

#endif