// Contact person : NN

#ifndef RAILBASE_END_QUANTITY_HPP
#define RAILBASE_END_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElements
#include "RailBaseEndTypes.hpp"

// from PropertyOperations
#include "IRailBaseEndQuantityCalculator.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST RailBaseEndQuantityCalculator : public Property::IRailBaseEndQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	RailBaseEndQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~RailBaseEndQuantityCalculator ();

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

	const VBElem::RailBaseEndConstRef& GetRailBaseEnd () const;
};

}

#endif