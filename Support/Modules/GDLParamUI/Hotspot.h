// Hotspot.h
//

#ifndef HOTSPOT_H
#define HOTSPOT_H

#pragma once

#include "GSRoot.hpp"
#include "basicgeometry.h"
#include "GSPix.h"
#include "GDLParamList.hpp"
#include "HotspotTypes.h"
#include "GDLParamUIExport.h"

class GSUserData;

// DragSpace_t is a structure in which the HSInitDrag can return that in what subset of the whole 3D space can the dragging
// occur. HSInitDrag can decide this, based on the initially clicked point in space and the stored hotspots' parameters.
struct DragSpace_t {
	DragSpace_t () {
		memset (this, 0, sizeof (DragSpace_t));
		spType = undefined_e;
	}

	enum SpaceType_t {
		line_e = 0,
		plane_e,
		space_e,
		circle_e,
		undefined_e
	} spType;

	union {
		Vector3dData		lineDir;	// if spType == line_e

		struct {
			Vector3dData	normal;		// normal vector of the plane
			Vector3dData	axis1;		// first axis of the plane
			Vector3dData	axis2;		// second axis of the plane
		} plane;					// if spType == plane_e

		struct {
			Vector3dData	normal;		// normal vector of the plane of the circle
			double		radius;
		} circle;					// if spType == circle_e

		struct {
			Vector3dData	axis1;		// first axis of the space
			Vector3dData	axis2;		// second axis of the space
			Vector3dData	axis3;		// third axis of the space
		} space;					// if spType == space_e
	} spAttr;

	Coord3D dragOrigo; // fix point of line-drag OR origo of plane- or space-drag OR center of circle (arc-drag)
};

typedef void GPU_CALL	ExecValueScript_Proc (Int32 id, GSUserData* userDataPtr, GDL::ParamList* addPars);
typedef void GPU_CALL	RunScriptForWireFrame_Proc (Int32 id, GSUserData* userDataPtr, const GDL::ParamList& addPars, const TRANMAT* tran);
typedef void GPU_CALL	DrawWireFrame_Proc (Int32 id, GSUserData* userDataPtr, const GDL::ParamList& addPars, const TRANMAT* tran);
typedef void GPU_CALL	GenLine_Proc (Int32 id, GSUserData* userDataPtr, const Coord3D* fromCrd, const Coord3D* toCrd,
									  LineKind_t lnKind);


GDLPARAMUI_DLL_EXPORT
bool		GPU_CALL		HSInit ();

GDLPARAMUI_DLL_EXPORT
void		GPU_CALL		HSExit ();

GDLPARAMUI_DLL_EXPORT
bool		GPU_CALL		HSNewSight (Int32* pId, bool b3D);

GDLPARAMUI_DLL_EXPORT
void		GPU_CALL		HSSetCallbacks (Int32 id,
											ExecValueScript_Proc* evsProc,
											RunScriptForWireFrame_Proc* rswfProc,
											DrawWireFrame_Proc* dwfProc,
											GenLine_Proc* glProc);
GDLPARAMUI_DLL_EXPORT
void		GPU_CALL		HSSetScale (Int32 id, const Int32 scale);

GDLPARAMUI_DLL_EXPORT
void		GPU_CALL		HSFreeSight (Int32 id);

GDLPARAMUI_DLL_EXPORT
void		GPU_CALL		HSNewModel (Int32 id);

GDLPARAMUI_DLL_EXPORT
bool		GPU_CALL		HSGenerate (Int32 id, UInt32 hsUnID, double x, double y, double z, ULong paramIndex, ULong arrIndex1,
										ULong arrIndex2, Int32 flags, TRANMAT* tran = nullptr);

GDLPARAMUI_DLL_EXPORT
void		GPU_CALL		HSEndModel (Int32 id, const GDL::ParamList* addPars = nullptr);

GDLPARAMUI_DLL_EXPORT
bool		GPU_CALL		HSInitDrag (Int32 id, GSUserData* userDataPtr, ULong* hsUnIDs, ULong* hsNum, const Coord3D* firstClick,
										const GDL::ParamList& addPars, DragSpace_t* drSpace = nullptr);

GDLPARAMUI_DLL_EXPORT
bool		GPU_CALL		HSDragPrep (Int32 id, Coord3D* inoutCoord);

GDLPARAMUI_DLL_EXPORT
bool		GPU_CALL		HSDragSetParams (Int32 id, const GDL::ParamList& addPars, Coord3D* outCoord);

GDLPARAMUI_DLL_EXPORT
bool		GPU_CALL		HSDragDraw (Int32 id);

GDLPARAMUI_DLL_EXPORT
bool		GPU_CALL		HSGiveParams (Int32 id, TRANMAT* tran, GDL::ParamList* addPars);

GDLPARAMUI_DLL_EXPORT
bool		GPU_CALL		HSEndDrag (Int32 id);


#endif
