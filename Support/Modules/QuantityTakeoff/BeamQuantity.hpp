// Contact person : KiP

#ifndef BEAM_QUANTITY_HPP
#define BEAM_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IBeamQuantityCalculator.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

#include "ProfileComposite.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST BeamQuantityCalculator : public Property::IBeamQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	BeamQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~BeamQuantityCalculator ();

	virtual	double											GetNetVolume						() const override;
	virtual double											GetTotalSurfaceArea					() const override;
	virtual double											GetSurfaceArea						(Int32 surfaceType) const override;
	virtual double											GetLengthLeft						() const override;
	virtual double											GetLengthRight						() const override;
	virtual double											GetProjected3DLength				() const override;
	virtual double											GetProjectedFloorPlanArea			() const override;
	virtual double											GetHolesSurface						() const override; // it makes sense only for basic beams
	virtual double											GetConditionalVolume				() const override;

	virtual GS::HashSet<VBEO::ModelElemComponentId>			GetComponents						() const override;
	virtual	UIndex											GetComponentBuildingMaterialIdx		(const VBEO::ModelElemComponentId& componentId) const override;
	virtual double											GetComponentVolume					(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	bool											HasComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	double											GetComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;

	virtual GS::HashSet<ModelCalculations::SurfaceId>		GetVisibleSurfaces					() const override;
	virtual GS::HashSet<VBEO::ModelElemComponentSurfaceId>	GetComponentSurfaces				() const override;
	virtual	double											GetExposedSurfaceArea				(const VBEO::ModelElemComponentSurfaceId& componentSurfaceId) const override;

	void	CalcOneBeamSurfVol (const Int32	*globalsBits,
								double		*rightLength,
								double		*leftLength,
								double		*bottomSurface,
								double		*topSurface,
								double		*edgeSurface1,
								double		*edgeSurface2,
								double		*edgeSurface3,
								double		*holesSurface,
								double		*holesEdgeSurface,
								Int32		*holesNumber,
								double		*volume,
								double		*volume_cond,
								Int32*		skinNumber = nullptr,
								short**		skinBuildMatIndices = nullptr,
								double**	skinProjectedAreas = nullptr,
								short**		skinFlags = nullptr) const;		// TODO TestEnv KiP ki lehet irtani, mert csak a tesztben hasznaljuk

private:
	const VBElem::BeamConstRef& GetBeam () const;

	virtual VBEO::ModelElemComponentId					GetComponentId			(const Modeler::MeshBody& body) const override;
	virtual	ModelCalculations::ProjectionSurfaceRef		GetProjectionSurface	(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	IPolygonSurfaceType*						GetPolygonSurfaceType	() const override;

	enum BeamSide
	{
		Left,
		Right
	};

	double		GetSideLength (BeamSide side) const;
	GSErrCode	GetSkinParameters (GS::Array<ProfileComposite::OrigProfileSkin>& skins) const;	// TODO KiP VBElemOperation Extension ?
	UInt32		GetHolesNumber () const;														// TODO KiP nem 3D-bol szamol, miert van itt ?

	virtual CONV2LISTREC	GetWithHoleListParams () const override;
	virtual CONV2LISTREC	GetWithoutHoleListParams () const override;
};

}

#endif