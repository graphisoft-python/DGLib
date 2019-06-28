#if !defined (SYHATCHOBJECT_HPP)
#define SYHATCHOBJECT_HPP

#pragma once

#include	"Definitions.hpp"
#include	"Array.hpp"
#include	"Point2D.hpp"
#include	"PolyArcRec.h"
#include	"Plane3DData.h"
#include	"HatchTran.hpp"
#include	"GSPix.h"
#include	"ExtendedPen.hpp"
#include	"VectorImageObject.hpp"

#include "PolygonDrawingDirection.hpp"
#include "ProfileAdditionalInfo.hpp"
#include "OverriddenAttributes.hpp"
#include "SyHatch.hpp"

struct ArcDivParams;


class VI_DLL_CLASS_EXPORT HatchObject : public VectorImageObject
{
	DECLARE_DYNAMIC_CLASS_INFO (HatchObject)
	friend class Sy_HatchType;
public:
	unsigned short		syFlags;			// See SyHatchFlag need for visualiztion
	unsigned short		buildMatFlags;		// See SyHatchBuildingMaterialFlag need for conversion only
private: 
	VBAttr::ExtendedPen	fillFgPen;			// Hatching color (0 if not hatched)
public: 
	short				fillIdx;			// Index of Fill attributum (0 if not hatched) when SyHatchFlag_FillHatch
	short				buildMatIdx;		// Index of Building Material attributum when SyHatchFlag_BuildingMaterialHatch
private:
	VBAttr::ExtendedPen	contPen;			// Contour line color
	bool				contVis;			// Contour line visibility
	short				contLType;			// Contour line type
public:
	short				fillBkgPen;			// if 0 transparent
	short				determine;			// It is always 0 in the library part files
	char				specFor3D;			//
	char				sy2dRenovationStatus;

	GS_RGBColor			bkgColorRGB;		// It is set if "SyHatchFlag_MillionColorBkg" set
	GS_RGBColor			fgColorRGB;			// 3 * sizeof (unsigend short) 3 * 2

private:
	UInt32					displayOrder;		// Display order
	GS::Array<Coord>		coords;
	GS::Array<PolyArcRec>	arcs;
	GS::Array<UInt32>		subPolyEnds;
	GSPtr					addInfo;
	GS::Guid				hatchUniqueId;

public:
	PlaneEq					origPlane;
	GX::Pattern::HatchTran	hatchTrafo;			// Transformation of hatch. (offset, 2x2 matrix, innerRadius, useGlobalOrigo)

private:
	GSErrCode	ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode	WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

public:
	HatchObject ();
	HatchObject (const GS::Guid& requiredId);
	HatchObject (const HatchObject& other);
	HatchObject (const GS::Guid& requiredId, const HatchObject& other);

	HatchObject& operator= (const HatchObject& other);
	~HatchObject ();

	bool operator!= (const HatchObject& other) const;
	bool operator== (const HatchObject& other) const;

	bool Compare (const VectorImageObject& other) const override;

	void				SetExtendedFillFgPen (const VBAttr::ExtendedPen& inPen);
	VBAttr::ExtendedPen	GetExtendedFillFgPen () const;

	VBAttr::ExtendedPen	GetContPenVal () const;		// GetContPenVal is supporting new workings of the code, when visibility and the pen are to be set and get independently!	
	VBAttr::ExtendedPen GetContPen () const;		// GetContPen is supporting old workings of the code, when pen value was encoding the visibility (value was 0). Use this, when you pass the pen to data structures still not supporting the visibility flag independently!
	bool				GetContVis () const;		// GetContVis is to be used wherever "pen != 0" condition was needed! 
	
	//setting contour pen to zero still means that the contour is not visible, this is supported here for compatibility with the old workings of the code
	void  SetContPen (const VBAttr::ExtendedPen& newPenVal); // In case you will call SetContVis () (see below) then you need no more to set the pen to 0! This means, set the pen here to whatever value you have and then set the visibility thereafter, independently! 	
	void  SetContVis (const bool newVal); // In general use this only after SetContPen, and only if the visibility-info is independently available for you, otherwise SetContPen (0) signalls the same.	

	void SetContLType (short lType);
	short GetContLType (void) const;

	inline const GS::Array<Coord>&		GetCoords (void) const { return coords; }
	inline const GS::Array<UInt32>&		GetSubPolyEnds (void) const { return subPolyEnds;  }
	inline const GS::Array<PolyArcRec>&	GetArcs (void) const { return arcs; }

	inline GS::Array<Coord>&		GetCoords (void) { return coords; }
	inline GS::Array<UInt32>&		GetSubPolyEnds (void) { return subPolyEnds; }
	inline GS::Array<PolyArcRec>&	GetArcs (void) { return arcs; }

	void SetPolygonGeometry (const GS::Array<Coord>& inCoords, const GS::Array<PolyArcRec>& inArcs, const GS::Array<UInt32>& inEnds);

	void				SetAddInfo (GSConstPtr inAddinfo);
	void				SetAddInfo (GSConstHandle inAddinfo);
	GSPtr				GetAddInfo (void);
	GSConstPtr			GetAddInfo (void) const;

	bool					HasProfileInfo () const		{ return addInfo != nullptr; }
	ProfileItem*			GetProfileItemPtr ();
	ProfileEdgeData*		GetProfileEdgeDataPtr ();
	const ProfileItem*		GetProfileItemPtr () const;
	const ProfileEdgeData*	GetProfileEdgeDataPtr () const;

	ProfileEdgeData*		GetProfileEdgeData (UIndex edgeIdx);
	const ProfileEdgeData*	GetProfileEdgeData (UIndex edgeIdx) const;

	GSErrCode ToPolygon2D						(Geometry::MultiPolygon2D&		result, IPolygonDrawingDirection** drawingDirection) const;
	GSErrCode ToIrregularPolygon2D				(Geometry::IrregularPolygon2D&	result, IPolygonDrawingDirection** drawingDirection) const;
	GSErrCode ToPolygon2DAndProfile				(Geometry::MultiPolygon2D&		result, IPolygonDrawingDirection** drawingDirection,	GS::HashTable<Geometry::PolyId, ProfileEdgeData>& profileEdgeData) const;
	GSErrCode ToIrregularPolygon2DAndProfile	(Geometry::IrregularPolygon2D&	result, IPolygonDrawingDirection** drawingDirection,	GS::HashTable<Geometry::PolyId, ProfileEdgeData>& profileEdgeData) const;
	GSErrCode ToPolyline2D						(Geometry::MultiPolyline2D&		result,													GS::HashTable<Geometry::PolyId, ProfileEdgeData>& profileEdgeData) const;
	short	  GetBuildingMaterialIdx			() const;
	void	  OffsetCoords						(const Geometry::Vector2d& offsetVector);
	GS::Array<Coord>	GetMainContoursSegmentedVertices (const ArcDivParams& arcDivParams) const;

	static GS::Array<Geometry::IrregularPolygon2D::ConstContourIterator> GetReversedContours (const Geometry::IrregularPolygon2D&	polygon,
																							  const IPolygonDrawingDirection*		drawingDirection);

	void SetGeometry (const Geometry::IrregularPolygon2D&										srcPolygon,
					  const IPolygonDrawingDirection*											srcDrawingDirection,
					  const GS::Array<Geometry::IrregularPolygon2D::ConstContourIterator>&		srcReversedContours,
					  const ProfileItem*														srcProfileItem,
					  const GS::HashTable<Geometry::PolyId, ProfileEdgeData>*					srcProfileEdgeData);

	// From VectorImageObject
	virtual Box2DData GetBounds (void) const override;
	virtual void Offset (const Geometry::Vector2d& offsCo) override;
	virtual void Transform (const TRANMAT& tran) override;
	virtual USize GetSizeInBytes (void)	const override;

	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const	override;
	virtual GSErrCode	ReadXML (GS::XMLIChannel& ic) override;
	virtual GSErrCode	WriteXML (GS::XMLOChannel& oc) const override;

	virtual HatchObject*	Clone (void) const	override;

	bool IsBuildingMaterialHatch	(void) const;
	bool IsFillHatch				(void) const;
	bool IsAreaSelectionOnlyHatch	(void) const;
	bool IsRGBFgColor				(void) const;
	bool IsRGBBkgColor				(void) const;
	bool OverrideFgPen				(void) const;
	bool OverrideBkgPen				(void) const;

	void SetBuildingMaterialHatch (short newBuildingMaterialIdx, short newFillIdx, VBAttr::OverriddenExtendedPen newFgPen, VBAttr::OverriddenPen newBkgPen);
	void SetFillHatch (short newFillIdx);
	void SetOverrideFgPen (const VBAttr::ExtendedPen& newFgPen);
	void SetOverrideBkgPen (short newBkgPen);
	void SetBkgPen (short newBkgPen);
	void ConvertGradientToNewStyle (IGetGradientFillType* getFillType);

	bool CheckAndRepair				(void);
	bool CheckAndRepairCoords		(void);
	bool CheckAndRepairSubPolyEnds	(void);
	bool CheckAndRepairArcs			(void);
	bool CheckAndRepairAddInfos		(void);

	UInt32	GetDisplayOrder () const;
	void	SetDisplayOrder (UInt32 value);
	void	IVDisplayOrder (GS::PlatformSign from, GS::PlatformSign to);
	bool	IsNear (const HatchObject& other) const;

	const GS::Guid&	GetUniqueId () const;
	void			SetNewUniqueId ();

	static void Create (Sy_HatchType&				hatchRef,
						HatchObject&				hatch,
						bool						ontVis,
						const VBAttr::ExtendedPen&	contPen,
						short						contLTyp,
						short						fragmentIdx,
						DrawIndex					drwIndex,
						GX::Pattern::HatchTran		hatchTrafo,
						Int32						npb,
						const UInt32*				boends,
						Int32						npc,
						const Coord*				coords,
						const double*				angles,
						const PlaneEq&				plane,
						UInt32						displayOrder,
						short						fillTypeDetermination,
						char						renovationStatus,
						char						specFor3D);
};

#endif // SYHATCHOBJECT_HPP
