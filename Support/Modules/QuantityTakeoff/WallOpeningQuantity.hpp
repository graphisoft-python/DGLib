// Contact person : TaB, KiP

#ifndef WALLOPENINGQUANTITY_HPP
#define WALLOPENINGQUANTITY_HPP

#pragma once

// from VBElements
#include	"VBElements/WallOpeningTypes.hpp"

// from PropertyOperations
#include "IWallOpeningQuantityCalculator.hpp"

// from QuantityTakeoff
#include	"QuantityCalculator.hpp"
#include	"VBModelElemQuantity.hpp"
#include	"VBModelElemQuantity.hpp"

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST WallOpeningQuantityCalculator : public Property::IWallOpeningQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	WallOpeningQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~WallOpeningQuantityCalculator ();

	virtual double											GetOpeningVolume					() const override;
	virtual double											GetGrossVolume						() const override;
	virtual double											GetSurface							() const override;
	virtual double											GetGrossSurface						() const override;
	virtual double											GetRevealSideWidth					() const override;
	virtual double											GetOppositeRevealSideWidth			() const override;
	virtual double											GetRevealSideHeight					() const override;
	virtual double											GetOppositeRevealSideHeight			() const override;
	virtual double											GetRevealSideSurface				() const override;
	virtual double											GetOppositeRevealSideSurface		() const override;
	virtual double											GetNominalRevealSideWidth			() const override;
	virtual double											GetNominalOppositeRevealSideWidth	() const override;
	virtual double											GetNominalRevealSideHeight			() const override;
	virtual double											GetNominalOppositeRevealSideHeight	() const override;
	virtual double											GetNominalRevealSideSurface			() const override;
	virtual double											GetNominalOppositeRevealSideSurface	() const override;
	virtual double											GetSillHeight						() const override;
	virtual double											GetRevealSideSillHeight				() const override;
	virtual double											GetOppositeRevealSideSillHeight		() const override;
	virtual double											GetHeadHeight						() const override;
	virtual double											GetRevealSideHeadHeight				() const override;
	virtual double											GetOppositeRevealSideHeadHeight		() const override;

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


	void	CalcWallOpeningData (const Int32*				globalsBits,
								 double*					rsideWidth,
								 double*					oprsideWidth,
								 double*					rsideHeight,
								 double*					oprsideHeight,
								 double*					rsideSurf,
								 double*					oprsideSurf,
								 double*					n_rsideWidth,
								 double*					n_oprsideWidth,
								 double*					n_rsideHeight,
								 double*					n_oprsideHeight,
								 double*					n_rsideSurf,
								 double*					n_oprsideSurf,
								 double*					openingVol,
								 double*					grossSurf,
								 double*					grossVol,
								 double*					surface,
								 double*					volume,
								 double*					sillHeight,
								 double*					rSideSillHeight,
								 double*					oprSideSillHeight,
								 double*					headHeight,
								 double*					rSideHeadHeight,
								 double*					oprSideHeadHeight,
								 double*					sillHeightFromAnchor,
								 double*					headHeightFromAnchor) const;	// TODO TestEnv KiP csak tesztben hivjuk
private:
	virtual VBEO::ModelElemComponentId GetComponentId (const Modeler::MeshBody& body) const override;
	const VBElem::WallOpeningConstRef&	GetWallOpening () const;
};

}

#endif
