// Contact person : KiP

#ifndef ROOM_QUANTITY_HPP
#define ROOM_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IRoomQuantityCalculator.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST RoomQuantityCalculator : public Property::IRoomQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	RoomQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~RoomQuantityCalculator ();

	virtual double											GetArea								() const override;
	virtual Int32											GetNumberOfBeams					() const override;
	virtual Int32											GetNumberOfColumns					() const override;
	virtual Int32											GetNumberOfDoors					() const override;
	virtual Int32											GetNumberOfLamps					() const override;
	virtual Int32											GetNumberOfObjects					() const override;
	virtual Int32											GetNumberOfWindows					() const override;
	virtual Int32											GetNumberOfWallParts				() const override;

	virtual double											GetNetVolume						() const override;
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

	const VBElem::RoomConstRef& GetRoom () const;
};

}

#endif