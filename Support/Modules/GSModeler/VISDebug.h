// *****************************************************************************
// GSModeler visualization debug functions.
// GSModeler, platform-independent
//
// Namespaces:        Contact person:
//    Modeler          FGY
//
// SG compatible
// *****************************************************************************

#if !defined(GS_VISDEBUG_HPP)
#define GS_VISDEBUG_HPP

#pragma once


#include	"GSModelerExport.h"
#include	"Draw2DProcs.h"
#include	"SharedPtr.hpp"
#include	"IAttributeReader.hpp"
#include	"G3I.h"

namespace	Modeler {
	class Sight;
	typedef GS::SharedPtr<Sight>	SightPtr;
}

namespace NewDisplay {
	class	NativeContext;
}

GSMODELER_DLL_EXPORT
void GSM_CALL VISdbgDrawNormalVectors (GS::ProcessControl& processControl, const Modeler::IAttributeReader& attReader, Modeler::SightPtr sight, GraphicsContext& gc);

GSMODELER_DLL_EXPORT
void GSM_CALL VISdbgDrawVertexNormals (GS::ProcessControl& processControl, const Modeler::IAttributeReader& attReader, Modeler::SightPtr sight, GraphicsContext& gc);

typedef void VISdbgGetHotspotTextProc (char* str,
									  double x, double y, double z,
									  short type, short subtype, Int32 unID, bool same, Int32 idx);

GSMODELER_DLL_EXPORT
void GSM_CALL VISdbgDrawAllHotspot (GS::ProcessControl& processControl, const Modeler::IAttributeReader& attReader, Modeler::SightPtr sight,
									GraphicsContext& gc, VISdbgGetHotspotTextProc* getHSTextProc);

GSMODELER_DLL_EXPORT
void GSM_CALL VISdbgDrawHotspot (const Modeler::IAttributeReader& attReader, Modeler::SightPtr sight, G3Line& g3Line, G3GCConsumer g3c, 
								 VISdbgGetHotspotTextProc* getHSTextProc, double x, double y, double z,
								 short type, short subtype, Int32 unID, bool same, Int32 idx = -1);


GSMODELER_DLL_EXPORT
void GSM_CALL VISdbgDrawOverlaps (const Modeler::SightPtr& sight, GraphicsContext& gc);

GSMODELER_DLL_EXPORT
void GSM_CALL VISdbgDrawLcoo (const Modeler::SightPtr& sight, GraphicsContext& gc);

GSMODELER_DLL_EXPORT
void GSM_CALL VISdbgPenAttrList (Modeler::SightPtr sight, const Modeler::IAttributeReader& attReader);

GSMODELER_DLL_EXPORT
void GSM_CALL VISdbgDrawcpols (Modeler::SightPtr sight, const Modeler::IAttributeReader& attReader, GraphicsContext& gc);

typedef void VISdbgDrawCString (NewDisplay::NativeContext& gc,
								const char* cString,
								const Int32 x,
								const Int32 y,
								const Int32 fontSize);

typedef enum { DrawIdsMode, DrawStatsMode } DrawIdsOrStatsMode;

GSMODELER_DLL_EXPORT
void GSM_CALL VISdbgDrawIdsOrStats (Modeler::SightPtr sight, NewDisplay::NativeContext& context, VISdbgDrawCString* drawCStringProc, const DrawIdsOrStatsMode& idsOrStatsMode);


GSMODELER_DLL_EXPORT
void	GSM_CALL VISdbgDrawShadowBodies (GS::ProcessControl& processControl, const Modeler::SightPtr& sight, GraphicsContext& gc, const Modeler::IAttributeReader& attReader, ModVisualizationEngine& visEngine);

GSMODELER_DLL_EXPORT
void	GSM_CALL VISdbgDrawLightLimits (const Modeler::SightPtr& sight, GraphicsContext& gc, const Modeler::IAttributeReader& attReader);

GSMODELER_DLL_EXPORT
void	GSM_CALL VISdbgDrawLights (Modeler::SightPtr& sight, GraphicsContext& gc, Modeler::IAttributeReader& attReader);




#endif // !defined(GS_VISDEBUG_HPP)
