// Contact person : NN

#ifndef RailingPANELQUANTITY_HPP
#define RailingPANELQUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElements
#include "RailingPanelTypes.hpp"
#include "RailingPanel.hpp"

// from PropertyOperations
#include "IRailingPanelQuantityCalculator.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST RailingPanelQuantityCalculator : public Property::IRailingPanelQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	RailingPanelQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~RailingPanelQuantityCalculator ();

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
	
	const VBElem::RailingPanelConstRef&	GetRailingPanel () const;
};

}

#endif