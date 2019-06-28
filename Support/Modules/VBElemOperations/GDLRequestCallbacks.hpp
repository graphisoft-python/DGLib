// *********************************************************************************************************************
// Description:		GDL Request callbacks
//
// Module:			VBElemOperations
// Namespace:		GDLOperations
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GDLREQUESTCALLBACKS_HPP)
#define GDLREQUESTCALLBACKS_HPP

#pragma once

// from GSRoot
#include	"Definitions.hpp"

// from GDL
#include	"GDLProc.h"

// from VBElemOperations
#include	"VBElemOperationsExport.hpp"
#include	"GDLOperations.hpp"

// from VBElements
#include	"IPLGeneralAttributeList.hpp"
#include	"IPLBaseEnum.hpp"


// temporary
namespace VBES {
	class ElemSet;
	typedef ODB::ConstRef<ElemSet>	ElemSetConstRef; 
}

namespace EDB {
	class DefaultElem;
}

namespace IPL {
	class Property;
	class PropertySet;
	class ExternalReferenceBase;
	class ElementDefault;
	class PropertyChangeList;
	class Value;
}


namespace GDLOperations {

typedef std::function <void	(GS::Guid elemGuid, GS::UniString& catname, GS::UniString& catcode,
								 GS::UniString& number, GS::UniString& name,
								 GS::UniString& catname2, GS::UniString& catcode2,
								 GS::UniString& number2, GS::UniString& name2,
								 bool fromOwner)> ZoneDataReqFunc;


typedef std::function <void	(GS::Guid elemGuid, double *area)> ZoneColusAreaReqFunc;
typedef std::function <void (GS::Guid elemGuid, GS::UniString& name)> NameReqFunc;
typedef std::function <short (GS::Guid elemGuid, bool fromOwner)> WidoZoneRelevReqFunc;

typedef std::function <void	(GS::Guid elemGuid, bool ownProp,
							 Int32 nrvals, Int32 *retValue,
							 GS::Array<GdlValueRecord>& values, GS::Array<GS::UniString>& stringsHdl)> MatchPropReqFunc;

typedef	std::function <void	(const GS::UniString& fontname, short familytype, double face, double slant, double size,
							 double *height, double *descent, double *leading)> StyleInfoFunc;

typedef std::function <GSErr (GSHandle globHdl,
							  GS::Guid elemGuid,
							  Int32 nrData, char *order, Int32 nrVals, Int32 *retValue,
							  GS::Array<GdlValueRecord>& values, GS::Array<GS::UniString>& stringsHdl)> AssocElPropReqFunc;

typedef	std::function <GSErr (
						const GdlTextBlockData*					textBlockData,
						const GS::VAArray<GdlParagraphData>*	paragraphs,
						const GSHandle							tabsHdl,		// double
						const GS::VAArray<GdlStringData>*		stringsData,
						const GSHandle							stringsHdl,		// Layout
						double*									width,
						double*									height)> TextBlockInfoReqFunc;

// Layout effective id callback; will not be called during 3D conversion
typedef std::function <GS::UniString (const VBES::ElemSetConstRef&)> GetLayoutEffectiveIDFunc;

// MEP callbacks
typedef std::function <bool (	const GS::Array<Coord3D>&		cpCoords,
								const GS::Array<Int32>&			portIndices, 
								const GS::Array<Vector3D>&		dirVs, 
								const GS::Array<Vector3D>&		widthVs,
								GS::Array<double>&				flexDuctPoints, 
								const Int32						resolution)> DoSectioningFunc;

typedef std::function <void (const GS::UniString& str, double &value)> DgStringToDoubleFunc;

class	VB_ELEM_OPERATIONS_DLL_EXPORT	GDLRequestCallbacks {
public:
	ZoneDataReqFunc			zonedataReq;			// will not be called during 3D conversion
	NameReqFunc				customautolabelReq;		// calls VBElem::Label::GetConstLabel
	ZoneColusAreaReqFunc	zonecolusareaReq;		// uses VBTo3D::Updater 
	WidoZoneRelevReqFunc	widozonerelevReq;		// will not be called during 3D conversion
	MatchPropReqFunc		matchpropReq;			// listazast hiv
	AssocElPropReqFunc		assocelpropReq;			// listazast hiv

	// Layout effective id callback; will not be called during 3D conversion
	GetLayoutEffectiveIDFunc getLayoutEffectiveID;

	// MEP callbacks
	DoSectioningFunc doSectioning;
	DgStringToDoubleFunc dgStringToDouble;

};
	
}	// namespace GDLOperations

#endif	// GDLREQUESTCALLBACKS_HPP
