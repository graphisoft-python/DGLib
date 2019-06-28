// Contact person : KiP

#ifndef STAIRQUANTITY_HPP
#define STAIRQUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElements
#include "VBElements/StairTypes.hpp"
#include "VBElements/Stair.hpp"

// from PropertyOperations
#include "IStairQuantityCalculator.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST StairQuantityCalculator : public Property::IStairQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	StairQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~StairQuantityCalculator ();

	virtual double											GetArea								() const override;
	virtual double											GetFrontSurfaceArea					() const override;

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
	virtual void EnumerateModelElemSubElements (const std::function<void (const VBElem::ModelElementConstRef&)>& processor) const override;

	const VBElem::StairConstRef& GetStair () const;
};

}

#endif