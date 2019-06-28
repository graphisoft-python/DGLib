// *****************************************************************************
//
//						Public Functions for Visualization
//
// Contact person:	BA
//
// *****************************************************************************

#ifndef	_VIS_H_
#define	_VIS_H_

#pragma once

#include	"GSModelerExport.h"
#include	"projCode.h"
#include	"Projection.h"

#include	"Draw2DProcs.h"
#include	"G2DProcs.h"

#include	"Model3D/ModelerAttributes.hpp"
#include	"SharedPtr.hpp"
#include	"IAttributeReader.hpp"
#include	"G3I.h"

struct		GS_RGBColor;

namespace	IO {
	class Location;
}

namespace	Modeler {
	class Camera;
	class Model3DViewer;
	class Model3DModifier;
	class SightViewer;
	class Sight;
	typedef GS::SharedPtr<Sight> SightPtr;
	class SightModifier;
	class Model3D;
	typedef GS::SharedPtr<Model3D> Model3DPtr;
	class Attributes;
	typedef GS::SharedPtr<Attributes> AttributesPtr;
}

namespace ModelerAPI {
	class Camera;
}

 class MDID;

namespace GX {
	class Image;
	typedef GS::Ref<Image> ImageRef;
}

class ModVisualizationEngine;

/****************************************************************************/
/*																			*/
/*								HPgonStatProc								*/
/*																			*/
/****************************************************************************/
/*
Call-back function to mark status of an edge.
It is called by the VISDrawModel function which can be activated after
projection of the 3D model.
----------------------------------------------------------------------------*/

typedef	GSErr	VI_CALL	HPgonStatProc (void* userDataPtr,
										   GS::Guid* elemGuid,
										   Int32	longvals[2],
										   short shrtvals[4],
										   UInt32 elemIdx, UInt32 bodyIdx, Int32 ihe,
										   double x1, double y1, double z1,
										   double x2, double y2, double z2);

/*----------------------------------------------------------------------------
Arguments:
	longvals:
	shortvals:	pointer to a long array with three values (longvals) and
				pointer to a short array with four values (shortvals) which
				were defined with the seven parameters of the VOCA statement
				in GDL script.
				These additional informations are stored in the body record of
				3D data structure. (see the SetVocaProc in GDLlib2.h)
				These values can be used to manage your own group.
	hpind:		index of the polygon in the hidden model
	ihe:		index of the edge in the hidden model
	x1:
	y1:
	z1:
	x2:
	y2:
	z2:			the coordinates of the line.
*/


struct VIS_Export_CallBacks {
	ExportLineProc*		 exportline;
	ExportLineProc*		 exporthatchline;
	ExportPolyProc*		 exportpoly;
	HPgonStatProc*		 hpgonstat;
};


GSMODELER_DLL_EXPORT
void	GSM_CALL		VISInit (	ModVisualizationEngine&	visEngine);

GSMODELER_DLL_EXPORT
void	GSM_CALL		VISExit (	ModVisualizationEngine&	visEngine);

GSMODELER_DLL_EXPORT
void	GSM_CALL		VISSetEnv (
							ModVisualizationEngine&		visEngine,
							Modeler::SightPtr			sight,
							short						projcode,
							double						projAngle,
							double						viewx,
							double						viewy,
							double						viewz,
							double						objx,
							double						objy,
							double						objz,
							double						rollAngle,
							double						eyeAngle,

							short						showtype,

							ContourMode			contour,

							double						sunAngxy,
							double						sunAngz,
							GS_RGBColor					sunRGB,
							GS_RGBColor					ambientRGB,

							short						r_hsiz,
							short						r_vsiz,

							bool						h_vhatchOn,
							bool						h_vshadowOn,

							bool						bckg3DasRend);


GSMODELER_DLL_EXPORT
void	GSM_CALL		VISDrawModel (GS::ProcessControl&					processControl,
									  ModVisualizationEngine&				visEngine,
									  G3EdgeControl							g3EdgeControl,
									  G3ShadingControl						g3ShadingControl,
									  const G3ModelModifierInterfaces&		modelModifiers,
									  const Modeler::IAttributeReader&		attReader,
									  Modeler::SightPtr						sight,
									  short									viewerId,
									  G3GCConsumer							g3c,
								  	  const RENDSETS&						rendsets,
									  const HIDDSETS&						hiddSets,
									  GSRect*								drawingRect,
								 	  const VIS_Export_CallBacks*			visgl);

GSMODELER_DLL_EXPORT
void	GSM_CALL		VISRealDraw (GS::ProcessControl&				processControl,
									 ModVisualizationEngine&			visEngine,
									 G3EdgeControl						g3EdgeControl,
									 G3ShadingControl					g3ShadingControl,
									 const IModelVisualOverrideConstPtr& overrideManager,
									 const Modeler::IAttributeReader&	attReader,
									 Modeler::SightPtr					sight,
									 short								viewerId,
									 G3GCConsumer						windowG3C,
									 const RENDSETS&					rendSets,
							  		 const HIDDSETS&					hiddSets,
									 GSRect*							drawingRect,
									 bool								lastFrame);

GSMODELER_DLL_EXPORT
void	GSM_CALL		VISPhotoRendering (GS::ProcessControl& processControl, ModVisualizationEngine&	visEngine, const Modeler::IAttributeReader& attReader, Modeler::SightPtr sight, const RENDSETS& rendSets,
										   const MDID& rendererId, GraphicsContext& renderingGC, GX::ImageRef& hPixMap);


GSMODELER_DLL_EXPORT
void	GSM_CALL		VISAllElems (GS::ProcessControl& processControl,
									 ModVisualizationEngine& visEngine,
									 G3EdgeControl g3EdgeControl,
									 G3ShadingControl g3ShadingControl,
									 const IModelVisualOverrideConstPtr& overrideManager,
									 const Modeler::IAttributeReader& attReader,
									 Modeler::SightPtr sight, const HIDDSETS& hiddSets,
									 void* userDataPtr,
									 double xmin, double xmax, double ymin, double ymax,
									 bool clipPgons, bool redundantLines,
									 short elemFilter,
									 const short* showType,
									 const bool* h_vhatchOn,
									 const bool* h_vshadowOn,
									 const bool forceShadowContours,
									 bool forceContours,
									 bool createSelfShadow,
									 const VIS_Export_CallBacks* visgl);

GSMODELER_DLL_EXPORT
Modeler::SightPtr	GSM_CALL	VISNewSight (const GS::UniString& name);

GSMODELER_DLL_EXPORT
const ZOOMDEF&	GSM_CALL	VISGetZoomData (const Modeler::ConstSightPtr& sight);

GSMODELER_DLL_EXPORT
void	GSM_CALL			VISSetZoomData (const Modeler::SightPtr& sight, const ZOOMDEF& zoomdef);

GSMODELER_DLL_EXPORT
void	GSM_CALL		VISGetModel3DBox (const Modeler::Model3DViewer& viewer,
										  double* xmin, double* ymin, double* zmin,
										  double* xmax, double* ymax, double* zmax);

GSMODELER_DLL_EXPORT
void	GSM_CALL		VISModelToScreen (const Modeler::Camera& cam, const COORD3* cm, COORD3* cs);

GSMODELER_DLL_EXPORT
void 	GSM_CALL		VISScreenToModel (const Modeler::Camera& cam, const COORD3* cs, COORD3* cm);

GSMODELER_DLL_EXPORT
void 	GSM_CALL		VISScreenToModel (const ModelerAPI::Camera& cam, const COORD3 *cs, COORD3 *cm);

GSMODELER_DLL_EXPORT
bool GSM_CALL			VISClickInfo (GS::ProcessControl& processControl,
									  Modeler::SightPtr sight,
									  GSPoint click,
									  Int32 *elemIdx, Int32 *bodyIdx, ULong* polygonIdx,
									  COORD3* refCoord, COORD3* normal, GS::Guid* elemGuid);


GSMODELER_DLL_EXPORT
void	GSM_CALL		VISClearSight (Modeler::SightPtr sight);

#endif
