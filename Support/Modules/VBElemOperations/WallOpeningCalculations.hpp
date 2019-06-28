/****************************************************************************/
/*																			*/
/*		       				WallOpening Calculations	       				*/
/*																			*/
/****************************************************************************/

#ifndef	_WallOpeningCalculations_HPP_
#define	_WallOpeningCalculations_HPP_

#pragma once

// from GSRoot
#include "Array.hpp"

// from Geometry
#include "Coord3d.h"

// from ODB
#include "ODBDependencyNode.hpp"
#include "TWObject.hpp"

// from ElementManager
#include "EDBGeneralDefinitions.hpp"

// from VBElements
#include "VBElements/OpeningTypes.hpp"
#include "VBElements/WallOpeningTypes.hpp"
#include "VBElements/ProfileTypes.hpp"

#include "GDLGlobalCalculations.hpp"

class VBElemSurfaceDescriptor;

namespace VBCalculations {

// === namespace VBCalculations::WallOpeningFrame ======================================================================

// --- Declaration -----------------------------------------------------------------------------------------------------

#define	XMLTag_Left			"Left"
#define	XMLTag_Right		"Right"
#define	XMLTag_Top			"Top"
#define	XMLTag_Bottom		"Bottom"

class WallOpeningFrame;

typedef ODB::Ref<WallOpeningFrame>		WallOpeningFrameRef;
typedef ODB::ConstRef<WallOpeningFrame>	WallOpeningFrameConstRef;

class VB_ELEM_OPERATIONS_DLL_EXPORT WallOpeningFrame : public TW::Object
{
	DECLARE_DYNAMIC_CLASS (WallOpeningFrame)

#define _WALLOPENINGFRAME_MEMBERS_																							\
private:																													\
	double	left;																											\
	double	right;																											\
	double	top;																											\
	double	bottom;

	_WALLOPENINGFRAME_MEMBERS_

	// ... Transaction management class ................................................................................

private:
	class IsolatedState : public TW::Object::IsolatedState
	{
	private:
		friend class WallOpeningFrame;

		_WALLOPENINGFRAME_MEMBERS_

	public:
		virtual ~IsolatedState ();
	};

	// ... Constructors / destructors ..................................................................................

public:
	WallOpeningFrame ();
	WallOpeningFrame (double _left, double _right, double _top, double _bottom);
	WallOpeningFrame (const WallOpeningFrame& source);
	~WallOpeningFrame ();

private:
	WallOpeningFrame& operator= (const WallOpeningFrame& source);		// disabled

public:
	// ... Overridden virtual methods (GS::Object) .....................................................................

public:
	virtual WallOpeningFrame*			Clone (void) const override;

	// ... Transaction management methods ..............................................................................

public:
	virtual	GSErrCode					StoreIsolatedState		(ODB::Object::IsolatedState* isolatedState) const override;
	virtual	GSErrCode					RestoreIsolatedState	(const ODB::Object::IsolatedState* isolatedState) override;
	virtual	void						Isolate					(void) override;
	virtual	ODB::Object::IsolatedState*	CreateIsolatedState		(void) const override;
	virtual USize						GetIsolatedSize			(void) const override;
	virtual	GSErrCode					WriteIsolatedState		(GS::OChannel& oc) const override;
	virtual	GSErrCode					ReadIsolatedState		(GS::IChannel& ic) override;

	virtual	GSErrCode					WriteIsolatedStateXML	(GS::XMLOChannel& oc) const override;
	virtual	GSErrCode					ReadIsolatedStateXML	(GS::XMLIChannel& ic) override;

	// ... Isolated state management methods ...........................................................................

private:
	GSErrCode							ReadIsolatedStateVersion1		(GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode							WriteIsolatedStateVersion1		(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode							ReadCoreIsolatedStateVersion1	(GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode							WriteCoreIsolatedStateVersion1	(GS::OChannel& oc, const GS::OutputFrame& frame) const;

	// ... TWObject methods ............................................................................................

public:
	virtual GSErrCode					ReadTWIsolatedState				(GS::IChannel& ic) override;
	virtual GSErrCode					WriteTWIsolatedState			(GS::OChannel& oc) const override;

private:
	GSErrCode							ReadTWIsolatedStateVersionLast	(GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode							WriteTWIsolatedStateVersionLast	(GS::OChannel& oc, const GS::OutputFrame& frame) const;

	// ... Accessors ...................................................................................................

public:
	double								GetLeft		(void) const	{ return left;		}
	double								GetRight	(void) const	{ return right;		}
	double								GetTop		(void) const	{ return top;		}
	double								GetBottom	(void) const	{ return bottom;	}

public:
	static	void						AttachFrame					(VBElem::WallOpeningConstRef opening, double left, double right, double top, double bottom);
	static	WallOpeningFrameConstRef	GetFrameFromWallOpening		(VBElem::WallOpeningConstRef opening);
};

// === WallOpeningCalculations functions ===============================================================================


class CurrentStoryCutLevels;

VB_ELEM_OPERATIONS_DLL_EXPORT
void						CalcWD2Wall						(VBElem::WallOpeningConstRef opening, const VBCalculations::GDLGlobalCalcEnvir& gdlGlobals, double* minLoc, double* pluLoc, double* topFram, double* botFram);

VB_ELEM_OPERATIONS_DLL_EXPORT
void						CalcWD2ArcWall					(VBElem::WallOpeningConstRef opening, const VBCalculations::GDLGlobalCalcEnvir& gdlGlobals,
															 short showElemFloor,
															 double* mb, double* me, double* actRadius, double* topFram, double* botFram, bool cutToEnd = true);

VB_ELEM_OPERATIONS_DLL_EXPORT
VBElem::OpeningHoleStatus	GetWD2Poly						(VBElem::WallOpeningConstRef opening, const VBCalculations::GDLGlobalCalcEnvir& gdlGlobals,
															 short showElemFloor,
															 Coord* frameCo, short* nReveCo, Coord* reveaCo, double* topFram, double* botFram, Coord* frCutCo = nullptr, Coord* reCutCo = nullptr, Int32* indices = nullptr, bool fullThick = false, double *pWThickness = nullptr, double *pWOffset = nullptr, double *pWThickCorr = nullptr, double *pWOffsCorr = nullptr);

VB_ELEM_OPERATIONS_DLL_EXPORT
bool						GetWD2WallContourXYA			(VBElem::WallOpeningConstRef opening, const VBCalculations::GDLGlobalCalcEnvir& gdlGlobals,
															 short showElemFloor, GS::Array<Coord3D>* outXYAlpha, Int32* indices);

VB_ELEM_OPERATIONS_DLL_EXPORT
void						GetSillHeight					(VBElem::WallOpeningConstRef opening, const VBCalculations::GDLGlobalCalcEnvir& gdlGlobals, double *sillHeight, double *rSideSillHeight, double *oprSideSillHeight);

VB_ELEM_OPERATIONS_DLL_EXPORT
void						GetWidoSillHeadHeightFromAnchor (VBElem::WallOpeningConstRef opening, double *sillHeight, double *headHeight);

VB_ELEM_OPERATIONS_DLL_EXPORT
GSErr						CalculateHoleGlobals			(VBElem::WallConstRef			pWall2,
															 VBElem::WallOpeningConstRef	pHole,
															 const VBCalculations::GDLGlobalCalcEnvir&		gdlGlobals,
															 short											showElemFloor,
															 double											wThick,
															 double											refRadius,
															 short*											refSideDir,			/* Gdl_WIDO_REVEAL_SIDE */
															 double*										wdMirThick,			/* Gdl_WIDO_FRAME_THICKNESS */
															 double*										wdPWallInset,		/* Gdl_WIDO_PWALL_INSET */
															 double*										radius,				/* 2D like Gdl_WIDO_ORIG_DIST */
															 double*										position,			/* Gdl_WIDO_POSITION */
															 double*										wHoleThick,			/* Gdl_WALL_THICKNESS */
															 GS::UniString*									widoOrientation,	/* Gdl_WIDO_ORIENTATION */
															 double*										wallDir,			/* Gdl_WALL_DIRECTION */
															 double*										wdangle,			/* Gdl_SYMB_ROTANGLE */
															 double*										wdsymbz,			/* Gdl_SYMB_POS_Z */
															 short*											pat,				/* Gdl_WALL_FILL if it is Composite */
															 GS::UniString*									compositName,		/* Gdl_WALL_COMPS_NAME */
															 short*											nSkins,				/* Gdl_WALL_SKINS_NR */
															 double*										skinspars,			/* Gdl_WALL_SKINS_PARAMS */
															 GS::UniChar::Layout**							skins_bmat_names,	/* Gdl_WALL_SKINS_BMAT_NAMES */
															 double*										globelevation,		/* Gdl_GLOB_ELEVATION */
															 bool											setFrameExpr,
															 bool											setThickExpr,
															 bool											setInsetExpr);

VB_ELEM_OPERATIONS_DLL_EXPORT
void						CalcComplexOpening3DParameters (VBElem::WallConstRef						pWall2,
															VBElem::WallOpeningConstRef					pHole,
															bool										isWallEnd,
															const VBCalculations::GDLGlobalCalcEnvir&	gdlGlobals,
															double										logicalZLevel,
															double										wido_Yposition,
															double										wido_Direction,
															double*										wdsymbz,
															double*										sill_modifier,
															double*										wHoleThick,
															VBElemSurfaceDescriptor*					leftMat,
															VBElemSurfaceDescriptor*					rightMat,
															GS::UniString*								compositeName,
															short*										nSkins,
															double*										skinspars,
															double**									skinParsBuffer);

VB_ELEM_OPERATIONS_DLL_EXPORT
bool						IsWDNeed (	const short                    					showElemFloor,
										const VBElem::WallConstRef&						pWall,
										const VBElem::WallOpeningConstRef&				pHole,
										const VBCalculations::CurrentStoryCutLevels&	gFloorPlanCutLevels,
										const VBCalculations::GDLGlobalCalcEnvir&		gdlGlobals,
										const Phasing::PlanTypeValueConstRef&			actPlanType,
										const Phasing::PlanTypeConstRef&				planTypeCategory,
										const Phasing::RenovationStatusConstRef&		renovationStatusCategory,
										VBElem::ElemDisplayOptions*						displayOption,
										bool*                    						noCutWall,
										bool*                    						noCutWD);
}

#endif
