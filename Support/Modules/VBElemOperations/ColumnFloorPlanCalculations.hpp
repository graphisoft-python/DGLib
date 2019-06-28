// *********************************************************************************************************************
// Description:		Column calculation utilities
//
// Module:			VBElemOperations
// Namespace:		VBCalculations
// Contact person:	MA
//
// SG compatible
// *********************************************************************************************************************

#if !defined (COLUMN_FLOOR_PLAN_CALCULATIONS_HPP)
#define COLUMN_FLOOR_PLAN_CALCULATIONS_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------
#include	"GSRoot.hpp"
#include	"HandleLikeClass.hpp"

#include	"Definitions.hpp"
#include	"PG.h"
#include	"Poly2DTypes.hpp"

#include	"VBElementsBase.hpp"
#include	"VBElemOperationsExport.hpp"
#include	"WallFloorPlanCalculations.hpp"

#include	"basicgeometry.h"


class DetailHandler;

class VBElemSurfaceDescriptor;

namespace VBCalculations {


/*==========================		CONSTANTS		========================*/

#define	CWrapbit		0x00000001
#define	CArcWallbit		0x00000002
#define	CVenbit			0x00000004
#define	CColumnbit		0x00000008
#define	Column0Outbit	0x00000010
#define	Column1Outbit	0x00000020
#define	Column2Outbit	0x00000040
#define	Column3Outbit	0x00000080
#define	Column0Onbit	0x00000100
#define	Column1Onbit	0x00000200
#define	Column2Onbit	0x00000400
#define	Column3Onbit	0x00000800
#define	CWallRefCutbit	0x20000000
#define	CWallOppCutbit	0x40000000
#define	CAbsWrapbit		0x80000000

#define	ColumnOutbits	Column0Outbit + Column1Outbit + Column2Outbit + Column3Outbit
#define	ColumnOnbits	Column0Onbit + Column1Onbit + Column2Onbit + Column3Onbit
#define	OrigHatch		-1
#define	OrigInnerLine	-2


struct WCut {
	double	sectW;
	double	sectC;
	Int32	wEdge;
	Int32	cEdge;

	WCut ()
	{
		sectW	= 0.0;
		sectC	= 0.0;
		wEdge	= 0;
		cEdge	= 0;
	}

};


struct WColWallRec {
	Coord		*wPolyCoords;
	Int32		nwPoly;
	PGEDGE		*edgePtr;
};


class VB_ELEM_OPERATIONS_DLL_EXPORT IPolyPos {
public:
	virtual short PolyPos (const Coord* pos) const = 0;
	virtual ~IPolyPos ();
};

class VB_ELEM_OPERATIONS_DLL_EXPORT PGPolyPos : public IPolyPos {
	const	PGPOLY&			wallPoly;
	mutable WColWallRec		wrkcowa;

public:
	PGPolyPos (const PGPOLY& wallPoly, WColWallRec wrkcowa) : wallPoly (wallPoly), wrkcowa (wrkcowa) {}
	virtual short PolyPos (const Coord* pos) const override
	{
		return PGCoordInPoly (&wallPoly, WallEdge, reinterpret_cast<void*> (&wrkcowa), pos, true);
	}

	static PGEDGE* WallEdge  (void* wrkcowaPtr, Int32 ind)
	{
		DBASSERT (wrkcowaPtr != nullptr);
		WColWallRec& wrkcowa = *(reinterpret_cast<WColWallRec*> (wrkcowaPtr));

		PGEDGE* edgePtr;
		Coord	wCoord;

		edgePtr = wrkcowa.edgePtr;
		BNZeroMemory (edgePtr, sizeof (PGEDGE));

		edgePtr->status = Geometry::NormalEdgeStatus;
		if (ind == wrkcowa.nwPoly) {
			edgePtr->status.isEndContour = true;
		}
		wCoord = (wrkcowa.wPolyCoords) [ind];
		edgePtr->begPt = wCoord;
		edgePtr->invlen = INVLEN_NOTINITED;
		return edgePtr;
	}			/* WallEdge */

	virtual ~PGPolyPos ();
};


class VB_ELEM_OPERATIONS_DLL_EXPORT PGPolyExtPos : public IPolyPos {
	const Geometry::PGPOLYEXT& wallPoly;
public:
	PGPolyExtPos (const Geometry::PGPOLYEXT& wallPoly) : wallPoly (wallPoly) {}
	virtual short PolyPos (const Coord* pos) const override
	{
		return ((short) Geometry::PGCoordInPolyExt (&wallPoly, pos, true));
	}
	virtual ~PGPolyExtPos ();
};


class VB_ELEM_OPERATIONS_DLL_EXPORT IrregularPolyPos : public IPolyPos {
	const Geometry::IrregularPolygon2D& wallPoly;
public:
	IrregularPolyPos (const Geometry::IrregularPolygon2D& wallPoly) : wallPoly (wallPoly) {}

	virtual short PolyPos (const Coord* pos) const override
	{
		Geometry::DetailedRelativePosition detRelPos = Geometry::DetailedRelativePosition_Unknown;
		Geometry::RelativePosition relpos = wallPoly.GetPosition (*pos, Geometry::Boundary_Closed, &detRelPos);
		if (relpos == Geometry::RelativePosition_Unknown || Geometry::IsDisjunct (relpos))
			return PGOutsidePoly;
		else if (detRelPos == Geometry::DetailedRelativePosition_Overlap_OnBoundary)
			return PGOnPolyEdge;
		else
			return PGInsidePoly;
	}

	virtual ~IrregularPolyPos ();
};



struct VB_ELEM_OPERATIONS_DLL_EXPORT ColumnSectRec {
	double							sectB;
	double							sectE;
	VBElem::ColumnConstRef			column;
	Int32							status;
	Circle							coluCircle;
	Sector							coluSector [4];
	Coord							coluC [4];
	Box2DData						bounds;
	VBCalculations::CW2StructRec	pCW2;

	ColumnSectRec ();
};


bool VB_ELEM_OPERATIONS_DLL_EXPORT	GetRealConnBendColumns (const	Sector	*sectPtr,
															const	Circle	*circlePtr,
															double			compThick,
															double			coreSect,
															double			*arrange);


void VB_ELEM_OPERATIONS_DLL_EXPORT CalcBendConnPoints (	VBElem::ColumnConstRef			colu,
														VBCalculations::COLUWALLX		**coluxpoints,
														Int32							nConns,
														Int32							*nCoords,
														GSHandle						bitMasks,
														Int32							nWalls,
														double							*xCoord,
														double							*yCoord,
														short							*mask,
														VBElemSurfaceDescriptor			*mats,
														GS::Guid						*wallGuid,
														short							*hotsType,
														Int32							*nCorn,
														VBCalculations::BHATCHCORNERS	*corners,
														Int32							columnResol,
														bool							forceNoVeneer = false,
														bool							forceNoWrapping = false);


void VB_ELEM_OPERATIONS_DLL_EXPORT CalcSectBSectE (	VBElem::ColumnConstRef	origColumn,
													const Coord*			origcoluC,
													VBElem::WallConstRef	pWall,
													const Circle*			wallCircle,
													double					wrapWidth,
													const double*			wallLength,
													const double*			wallDir,
													Int32					status,
													double*					sectB,
													double*					sectE);


bool VB_ELEM_OPERATIONS_DLL_EXPORT ColumnCutWall (	const PGPOLY&		wallPoly,
													const WColWallRec&	wrkcowa,
													Sector*				wallSector,
													Int32				nWallSect,
													Sector*				coluSector,
													const Coord*		coluOrigo,
													WCut*				wcCut,
													short*				maxwcCut,
													Int32*				outside,
													const Circle*		columnCircle,
													bool				from3D);



bool VB_ELEM_OPERATIONS_DLL_EXPORT /*TODO_D-116_MA:ConnectWalls koltoztetes utan static*/ ColumnCutWall (	const Geometry::PGPOLYEXT&	wallPoly,
							Sector*						wallSector,
							Int32						nWallSect,
							Sector*						coluSector,
							const Coord*				coluOrigo,
							WCut*						wcCut,
							short*						maxwcCut,
							Int32*						outside,
							const Circle*				columnCircle,
							bool						from3D);


void  VB_ELEM_OPERATIONS_DLL_EXPORT /*TODO_D-116_MA:ConnectWalls koltoztetes utan static*/ ColumnCutArcWall (const Geometry::PGPOLYEXT&	wallPoly,
						GenArc*						wallArc,
						Sector*						wallSector,
						Sector*						coluSector,
						WCut*						wcCut,
						short*						maxwcCut,
						Int32*						outside,
						const Circle*				columnCircle);


bool VB_ELEM_OPERATIONS_DLL_EXPORT /*TODO_D-116_MA:ConnectWalls koltoztetes utan static*/ ColumnCutWall (	const Geometry::IrregularPolygon2D&	wallPoly,
							Sector*						wallSector,
							Int32						nWallSect,
							Sector*						coluSector,
							const Coord*				coluOrigo,
							WCut*						wcCut,
							short*						maxwcCut,
							Int32*						outside,
							const Circle*				columnCircle,
							bool						from3D);


void  VB_ELEM_OPERATIONS_DLL_EXPORT /*TODO_D-116_MA:ConnectWalls koltoztetes utan static*/ ColumnCutArcWall (const Geometry::IrregularPolygon2D&	wallPoly,
						GenArc*						wallArc,
						Sector*						wallSector,
						Sector*						coluSector,
						WCut*						wcCut,
						short*						maxwcCut,
						Int32*						outside,
						const Circle*				columnCircle);




bool VB_ELEM_OPERATIONS_DLL_EXPORT GetWall2SkinCoords (	const	VBElem::WallConstRef&									pWall2,
														const	Geometry::IrregularPolygon2D&							wPoly,
														const	VBCalculations::CW2StructRec*		const				pwCW2,
														const	VBCalculations::ColumnSectRec*		const				conCol,
														const	bool													nOnlyCore,
														const	bool													onlyGetPoly,
														const	Int32													skinInd,
																VBCalculations::WallComputingEnvir*	const				wce,		// e.g.: Calc_Wall2_H_Angle
														const	WallBeamConnectionEnvir*			const				wbce,
																GS::ArrayFB<DrawSectCN2Data, VBAttr::MaxSkinNumber>&	dataForDrawing);


bool VB_ELEM_OPERATIONS_DLL_EXPORT CheckWrapping ( short										showElemFloor,
												   VBElem::ColumnConstRef						colPtr,
												   VBElem::WallConstRef							myWall2,
												   const Geometry::IrregularPolygon2D&			wPoly,
												   VBCalculations::CW2StructRec*				pCW2,
												   double										refWidth,
												   double										oppWidth,
												   Int32*										status,
												   PolyArcRec*									coreArc,
												   SkinMergeMode								skinMergeMode,
												   const DetailHandler*							detailHandler,
												   const VBCalculations::GDLGlobalCalcEnvir&	gdlGlobals);


void VB_ELEM_OPERATIONS_DLL_EXPORT StoreConnPoints (VBCalculations::COLUWALLX		***coluxpoints,
													Int32							*nCoords,
													Int32							wallInd,
													char							edgeInd,
													char							wallEdge,
													double							xarrange,
													double							compThick,
													Coord							dirVect,
													const VBElemSurfaceDescriptor&		mater,
													const VBElemSurfaceDescriptor&		oppositeMat,
													bool							wallFlipped,
													const GS::Guid&					wallGuid);


static inline short SetBit (short origBitMask, Int32 bitIdx)
{
	return BSET (origBitMask,bitIdx);
}


// To ensure consistency between GetWall2SkinCoords and DrawSectCN2
static inline bool IsTrapezoidSkinReached (Int32 skinIdx, const VBCalculations::CW2StructRec* const pwCW2)
{
	const Int32 trapezoidInd = GetTrapezoidSkinInd (pwCW2, false);
	return skinIdx == trapezoidInd;
}


// To ensure consistency between GetWall2SkinCoords and DrawSectCN2
static inline bool IsValidSkinIdxInForwardLoop (Int32 skinIdx, const VBCalculations::CW2StructRec* const pwCW2)
{
	const Int32 trapezoidInd = GetTrapezoidSkinInd (pwCW2, false);
	return skinIdx < trapezoidInd || (skinIdx == trapezoidInd && skinIdx == pwCW2->nSkins - 1);
}


} // namespace VBTo3D
#endif