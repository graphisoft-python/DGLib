// Contact person : KiP

#ifndef PLANEROOF_QUANTITY_HPP
#define PLANEROOF_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IPlaneRoofQuantityCalculator.hpp"

// from QuantityTakeoff
#include "RoofQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST PlaneRoofQuantityCalculator : public Property::IPlaneRoofQuantityCalculator, public RoofQuantityCalculator
{

public:
	PlaneRoofQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~PlaneRoofQuantityCalculator ();

	virtual double											GetSurfaceArea						(Int32 surfaceType) const override;

	virtual double											GetConditionalBottomSurfaceArea		() const override;
	virtual double											GetConditionalTopSurfaceArea		() const override;
	virtual double											GetConditionalVolume				() const override;
	virtual double											GetDomeConnectionLength				() const override;
	virtual double											GetEavesLength						() const override;
	virtual double											GetEndWallConnectionLength			() const override;
	virtual double											GetGablesLength						() const override;
	virtual double											GetGrossBottomSurfaceArea			() const override;
	virtual double											GetGrossEdgeSurfaceArea				() const override;
	virtual double											GetGrossTopSurfaceArea				() const override;
	virtual double											GetGrossVolume						() const override;
	virtual double											GetHipsLength						() const override;
	virtual double											GetHolesPerimeter					() const override;
	virtual double											GetHolesSurfaceArea					() const override;
	virtual double											GetHollowConnectionLength			() const override;
	virtual double											GetInsulationSkinThickness			() const override;
	virtual double											GetNetBottomSurfaceArea				() const override;
	virtual double											GetNetEdgeSurfaceArea				() const override;
	virtual double											GetNetTopSurfaceArea				() const override;
	virtual Int32											GetHoleNumber						() const override;
	virtual Int32											GetSkylightNumber					() const override;
	virtual double											GetOpeningsSurfaceArea				() const override;
	virtual double											GetPeaksLength						() const override;
	virtual double											GetPerimeter						() const override;
	virtual double											GetRidgesLength						() const override;
	virtual double											GetSideWallConnectionLength			() const override;
	virtual double											GetValleysLength					() const override;

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
	void	CalcOneRoofSurfVol		   (const Int32									*globalsBits,
										double										*topSurface,
										double										*bottomSurface,
										double										*edgeSurface,
										double										*topSurface_cond,
										double										*bottomSurface_cond,
										double										*grossTopSurf,
										double										*grossBotSurf,
										double										*grossEdgeSurf,
										double										*contourArea,
										double										*volume,
										double										*volume_cond,
										double										*grossVolume,
										double										*insuThickness,
										double										*ridgesLength,
										double										*valleysLength,
										double										*gablesLength,
										double										*hipsLength,
										double										*eavesLength,
										double										*peaksLength,
										double										*sideWallConLength,
										double										*endWallConLength,
										double										*domeConLength,
										double										*hollowConLength,
										double										*perimeter,
										double										*holesSurf,
										double										*holesPrm,
										double										*openingSurf,
										Int32										*holesNr,
										Int32										*openingNr,
										Int32										*segmentsNr,
										Int32										*skinNumber = nullptr,
										short										**skinBuildMatIndices = nullptr,
										double										**skinVolumes = nullptr,
										double										**skinProjectedAreas = nullptr,
										short										**skinFlags = nullptr) const;

	const VBElem::PlaneRoofConstRef& GetPlaneRoof () const;

	virtual	ModelCalculations::ProjectionSurfaceRef GetProjectionSurface (const VBEO::ModelElemComponentId& componentId) const override;

	double CalculateComponentVolumeNoPBC (const VBEO::ModelElemComponentId& componentId) const;

	virtual CONV2LISTREC	GetWithHoleListParams () const override;
	virtual CONV2LISTREC	GetWithoutHoleListParams () const override;
};

}

#endif