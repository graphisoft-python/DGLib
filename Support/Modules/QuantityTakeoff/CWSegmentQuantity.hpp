// Contact person : KiP

#ifndef CWSEGMENT_QUANTITY_HPP
#define CWSEGMENT_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "ICWSegmentQuantityCalculator.hpp"

// from VBElements
#include "CWSegmentTypes.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST CWSegmentQuantityCalculator : public Property::ICWSegmentQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	CWSegmentQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~CWSegmentQuantityCalculator ();

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
	virtual VBEO::ModelElemComponentId	GetComponentId (const Modeler::MeshBody& body) const override;

	void	CalcCWSegmentData (const Int32*	globalsBits, GS::uchar_t* typeText) const;

	const VBElem::CWSegmentConstRef&	GetCWSegment () const;
};

}

#endif