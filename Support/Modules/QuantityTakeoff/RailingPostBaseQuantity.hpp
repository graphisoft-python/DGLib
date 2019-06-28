// Contact person : KiP

#ifndef RAILINGPOSTBASE_QUANTITY_HPP
#define RAILINGPOSTBASE_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElements
#include "RailingPostBaseTypes.hpp"

// from PropertyOperations
#include "IRailingPostBaseQuantityCalculator.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT RailingPostBaseQuantityCalculator : public Property::IRailingPostBaseQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	RailingPostBaseQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~RailingPostBaseQuantityCalculator ();

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

	const VBElem::RailingPostBaseConstRef& GetRailingPostBase () const;
};

}

#endif