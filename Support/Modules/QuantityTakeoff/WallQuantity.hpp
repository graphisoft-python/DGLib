// Contact person : KiP

#ifndef WALL_QUANTITY_HPP
#define WALL_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IWallQuantityCalculator.hpp"

// from GSModeler
#include "SurfaceTypes.hpp"

// from VBElemOperations
#include "WallFloorPlanCalculations.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================


namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT WallQuantityCalculator : public Property::IWallQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	WallQuantityCalculator (VBElem::ModelElementConstRef	vbElem, 
							const QuantityModelConstPtr&	quantityModel,
						    const RoomPart*					roomParts,
						    const ZoneLimitData*			limitData,
						    double							minSurf);
	virtual ~WallQuantityCalculator ();

	virtual double		GetAnalyticalHoleVolume				() const override;
	virtual double		GetConditionalInsideSkinVolume		() const override;
	virtual double		GetConditionalOutsideSkinVolume		() const override;
	virtual double		GetConditionalVolume				() const override;
	virtual double		GetGrossVolume						() const override;
	virtual double		GetInsideSkinVolume					() const override;
	virtual double		GetOutsideSkinVolume				() const override;
	virtual double		GetColumnVolume_notCalculated		() const override;

	virtual double		GetArea								() const override;
	virtual double		GetAnalyticalOutsideSurfaceArea		() const override;
	virtual double		GetAnalyticalInsideSurfaceArea		() const override;
	virtual double		GetAnalyticalHoleOutsideSurfaceArea	() const override;
	virtual double		GetAnalyticalHoleInsideSurfaceArea	() const override;
	virtual double		GetConditionalInsideSurfaceArea		() const override;
	virtual double		GetConditionalOutsideSurfaceArea	() const override;
	virtual double		GetDoorSurfaceArea					() const override;
	virtual double		GetEmptyHolesSurfaceArea			() const override;
	virtual double		GetGrossInsideSurfaceArea			() const override;
	virtual double		GetGrossOutsideSurfaceArea			() const override;
	virtual double		GetNetEdgeSurfaceArea				() const override;
	virtual double		GetNetInsideSurfaceArea				() const override;
	virtual double		GetNetOutsideSurfaceArea			() const override;
	virtual double		GetWindowSurfaceArea				() const override;

	virtual double		GetCenterLength						() const override;
	virtual double		GetConditionalInsideLength			() const override;
	virtual double		GetConditionalOutsideLength			() const override;
	virtual double		GetInsideLength						() const override;
	virtual double		GetOutsideLength					() const override;
	virtual double		GetAverageLength					() const override;
	virtual	double		GetProjected3DLength				() const override;
	virtual double		GetPerimeter						() const override;
	virtual double		GetReferenceLineLength				() const override;

	virtual Int32		GetColumnNumber						() const override;
	virtual Int32		GetDoorNumber						() const override;
	virtual Int32		GetWindowNumber						() const override;
	virtual Int32		GetHoleNumber						() const override;

	virtual	double		GetTotalDoorWidth					() const override;
	virtual double		GetTotalWindowWidth					() const override;

	virtual double		GetMaxHeight						() const override;
	virtual double		GetMinHeight						() const override;
	virtual double		GetInsideMinHeight					() const override;
	virtual double		GetInsideMaxHeight					() const override;
	virtual double		GetOutsideMinHeight					() const override;
	virtual double		GetOutsideMaxHeight					() const override;

	virtual double		GetAirThickness						() const override;
	virtual double		GetInsulationThickness				() const override;
	virtual double		GetOutsideThickness					() const override;
	virtual double		GetInsideThickness					() const override;

	
	virtual double		GetNetVolume						() const override;
	virtual double		GetTotalSurfaceArea					() const override;

	virtual GS::HashSet<VBEO::ModelElemComponentId>			GetComponents						() const override;
	virtual	UIndex											GetComponentBuildingMaterialIdx		(const VBEO::ModelElemComponentId& componentId) const override;
	virtual double											GetComponentVolume					(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	bool											HasComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	double											GetComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;

	virtual GS::HashSet<ModelCalculations::SurfaceId>		GetVisibleSurfaces					() const override;
	virtual GS::HashSet<VBEO::ModelElemComponentSurfaceId>	GetComponentSurfaces				() const override;
	virtual	double											GetExposedSurfaceArea				(const VBEO::ModelElemComponentSurfaceId& componentSurfaceId) const override;

	void	CalcOneWall2Data (double	*actLength12,
							  double	*actLength34,
							  double	*actLength12_cond,
							  double	*actLength34_cond,
							  double	*actsurf12,
							  double	*actsurf34,
							  double	*actsurf12_cond,
							  double	*actsurf34_cond,
							  double	*wallDoorsSurf,
							  double	*wallDoorsWidth,
							  double	*wallWindsSurf,
							  double	*wallWindsWidth) const;

private:
	const VBElem::WallConstRef&						GetWall () const;
	virtual VBEO::ModelElemComponentId					GetComponentId (const Modeler::MeshBody& body) const override;
	virtual	ModelCalculations::ProjectionSurfaceRef	GetProjectionSurface (const VBEO::ModelElemComponentId& componentId) const override;
	virtual	IPolygonSurfaceType*					GetPolygonSurfaceType () const override;

	void CalcWallArcs (GenArc *pWallArc, const Geometry::IrregularPolygon2D& wPoly) const;

	double Wall2sTest (VBElem::WallConstRef pWall1, VBElem::WallConstRef pWall2) const;

	void WArcAreaTconns (const VBElem::WallConnectionList*					connT,
						 GenArc*											wArc,
						 bool												begFlg,
						 bool												xConnection,
						 double*											surf12T,
						 double*											surf34T,
						 bool												connTL,
						 VBCalculations::WallComputingEnvir* const			wce,
						 VBCalculations::WallBeamConnectionEnvir* const		wbce) const;

	void WLinAreaTconns (const VBElem::WallConnectionList*					connT,
						 Sector*                                			sector,
						 bool                                   			begFlg,
						 bool												xConnection,
						 double*                                			surf12T,
						 double*                                			surf34T,
						 bool                                   			connTL,
						 VBCalculations::WallComputingEnvir* const 	  		wce,
						 VBCalculations::WallBeamConnectionEnvir* const     wbce) const;

	void CalcAreaTconns (double*											surf12T,
						 double*											surf34T,
						 VBCalculations::WallComputingEnvir* const 			wce,
						 VBCalculations::WallBeamConnectionEnvir* const		wbce,
						 const Geometry::IrregularPolygon2D&				wPoly) const;

	void CountWallHoles (Int32					*wallDoorsNr,
						 Int32					*wallWindsNr,
						 Int32					*wallEmptyHolesNr,
						 double					*wallDoorsSurf,
						 double					*wallDoorsWidth,
						 double					*wallWindsSurf,
						 double					*wallWindsWidth,
						 double					*wallEmptyHolesSurf) const;

	GSErrCode	CalcWall22DData (double*									actLength,
								 double*									actLength12,
								 double*									actLength34,
								 double*									actCenterLength,
								 double*									actArea,
								 double*									actPerimeter,
								 const Geometry::IrregularPolygon2D* const	inWPoly = nullptr) const;

	Modeler::ConstElemPtr	CutWallSideSkin (const Modeler::ConstElemPtr& fullElem, bool refSide) const;

	void	CalcThicknessData (double *insuThickness, double *airThickness, double *skinAThickness, double *skinBThickness) const;

	void	GetWallProfileSkinData (PlaneEq*	plane,
									Vector3D*	norm,
									TRANMAT*	tm) const;

	bool	GetWallSkinPlane (PlaneEq* plane, VBAttr::CompWallConstRef compWallRef, Int32 iSkin, bool refSide) const;

	void	CalcOneWall22DData (double							surf12,
								double							surf34,
								const double					*edgeSurf,
								double							*actsurf12_cond,
								double							*actsurf34_cond,
								double							*cWallSurface1,
								double							*cWallSurface2,
								double							*actsurf12,
								double							*actsurf34,
								double							*actsurfedge,
								double							*actLength12_cond,
								double							*actLength34_cond,
								double							*actLength,
								double							*actLength12,
								double							*actLength34,
								Int32							*coluNr,
								Int32							*wallDoorsNr,
								Int32							*wallWindsNr,
								Int32							*wallEmptyHolesNr,
								double							*wallDoorsSurf,
								double							*wallDoorsWidth,
								double							*wallWindsSurf,
								double							*wallWindsWidth,
								double							*wallEmptyHolesSurf,
								double							*centerLength,
								double							*area,
								double							*perimeter,
								double							*refLineLength) const;

	void	CalcOneWall23DData (const Int32									*globalsBits,
								
								double										*minHeight,
								double										*maxHeight,
								double										*minHeightASkin,
								double										*maxHeightASkin,
								double										*minHeightBSkin,
								double										*maxHeightBSkin,
								double										*surface1,
								double										*surface2,
								double										*surface1_cond,
								double										*surface2_cond,
								double										*edgeSurf,
								double										*vol,
								double										*volume_cond,
								double										*actVolumeASkin_cond,
								double										*actVolumeBSkin_cond,
								double										*grossSurfA,
								double										*grossSurfB,
								double										*grossVolume,
								double										*wallHolesVolume,
								double										*wallHolesSurfA,
								double										*wallHolesSurfB,
								double										*wallHolesWidthA_cond,
								double										*wallHolesWidthB_cond,
								double										*insuThickness,
								double										*airThickness,
								double										*skinAThickness,
								double										*skinBThickness,
								Int32										*skinNumber,
								short**										skinBuildMatIndices,
								double**									skinProjectedAreas,
								short**										skinFlags) const;

	virtual CONV2LISTREC	GetWithHoleListParams () const override;
	virtual CONV2LISTREC	GetWithoutHoleListParams () const override;

	const RoomPart* const								roomParts;
	const ZoneLimitData* const							limitData;	
	const GS::HashTable<GS::Guid, RoomPart>				roomPartsMap;
	const GS::Array<ZoneLimitData>						limitDataArray;
	const double										minSurf;
};

}

#endif
