// Contact person : KiP

#ifndef RAILING_QUANTITY_HPP
#define RAILING_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElements
#include "RailingTypes.hpp"
#include "Railing.hpp"

// from PropertyOperations
#include "IRailingQuantityCalculator.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST RailingQuantityCalculator : public Property::IRailingQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	RailingQuantityCalculator (VBElem::ModelElementConstRef vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~RailingQuantityCalculator ();

	virtual double											GetArea								() const override;
	
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
	virtual void EnumerateModelElemSubElements (const std::function<void (const VBElem::ModelElementConstRef&)>& processor) const override;

	const VBElem::RailingConstRef& GetRailing () const;
};

}

#endif