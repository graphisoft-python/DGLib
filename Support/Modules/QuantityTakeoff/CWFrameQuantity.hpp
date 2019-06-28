// Contact person : KiP

#ifndef CWFRAME_QUANTITY_HPP
#define CWFRAME_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "ICWFrameQuantityCalculator.hpp"

// from VBElements
#include "CWFrameTypes.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST CWFrameQuantityCalculator : public	Property::ICWFrameQuantityCalculator,
																	  protected	VBModelElemQuantityCalculator
{
public:
	CWFrameQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~CWFrameQuantityCalculator ();

	virtual	UIndex											GetClass							() const override;
	virtual	double											GetDirection						() const override;
	virtual	double											GetWidth							() const override;
	virtual	double											GetDepth							() const override;
	virtual	double											GetLength							() const override;
	virtual	short											GetMaterial							() const override;

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
	virtual VBEO::ModelElemComponentId	GetComponentId (const Modeler::MeshBody& body) const override;

	const VBElem::CWFrameConstRef&	GetCWFrame () const;
};

}

#endif
