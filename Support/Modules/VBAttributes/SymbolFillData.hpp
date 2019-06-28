// *****************************************************************************
// Symbol Fill memo id
// VBAttributes, platform-independent
//
// Namespaces:        Contact person:
//	GX::Pattern::SFHotspot				CSF
//	GX::Pattern::SFLine					CSF
//	GX::Pattern::SFArc					CSF
//	GX::Pattern::SFFill					CSF
//	GX::Pattern::SFPolyArc				CSF
//	GX::Pattern::SFMotifs				CSF
//	GX::Pattern::SymbolFillDetails		CSF
//	SymbolFillIterator		CSF
//	SymbolFillData			CSF
//
// [SG compatible]
// *****************************************************************************

#if !defined (SYMBOLFILLDATA_HPP)
#define SYMBOLFILLDATA_HPP

#pragma once

//============================== Includes =================================

#include	"VBAttributesEnv.hpp"
#include	"GSMemoData.hpp"
#include	"basicgeometry.h"
#include	"AttributeManager.hpp"

// Pattern
#include	"SymbolFillDetails.hpp"

namespace GS {
	class XMLOChannel;
	class XMLIChannel;
}

//===================== Begin of the VBAttr namespace =====================

namespace VBAttr {

//============================ Definitions ================================

#define	TypeId_SymbolFill	'sfil'

//====================== Class SymbolFillIterator =========================

class SymbolFillData;

class VBATTRIBUTES_DLL_EXPORT SymbolFillIterator {
private:
		// data members

	SymbolFillData*		symbolFills;
	short				count;
	Int32				nFills;
	GX::Pattern::SFFill*				fillPtr;
	Int32				currentCoord;
	Coord*				coordPtr;
	Int32				currentSubPoly;
	Int32*				subPoliesPtr;
	Int32				currentPolyArc;
	GX::Pattern::SFPolyArc*			polyArcsPtr;

public:
		// constructors

	SymbolFillIterator (const SymbolFillData& symbolFills);
   ~SymbolFillIterator ();

		// get methods

	bool				HasNextFill (void) const;
	GX::Pattern::SFFill*				GetNextFill (void);

		// get methods (for the current fill)

	Coord*				GetFillCoordsPtr (void);
	Int32*				GetSubPoliesPtr (void);
	GX::Pattern::SFPolyArc*			GetPolyArcsPtr (void);
};

//========================= Class SymbolFillData ==========================

class VBATTRIBUTES_DLL_EXPORT SymbolFillData : public VBUtil::GSMemoData
{
	DECLARE_CLASS_INFO
private:
		// friend classes

	friend class SymbolFillIterator;

public:
		// constructors

	SymbolFillData ();
   ~SymbolFillData ();

		// get methods

	bool				GetSymbolFillDetails (GX::Pattern::SymbolFillDetails* fillDetails) const;
	bool				GetMotifs (GX::Pattern::SFMotifs* motifs) const;

	GX::Pattern::SFHotspot*			GetHotSpotPtr () const;
	GX::Pattern::SFLine*				GetLinesPtr () const;
	GX::Pattern::SFArc*				GetArcsPtr () const;

	Int32				GetHotSpotNumber () const;
	Int32				GetLineNumber () const;
	Int32				GetArcNumber () const;
	Int32				GetFillNumber () const;

	Int32				GetNParts (void) const override;
	GSType				GetSignal (void) const override;
	char				GetBlockTyp (void) const;

		// set methods

	GSErrCode			Setup (const GX::Pattern::SymbolFillDetails& fillDetails);
	GSErrCode			Setup (const GX::Pattern::SFMotifs& fillMotifs);

	bool				UpdateSymbolFillDetails (const GX::Pattern::SymbolFillDetails& data);

		// operators

	bool				operator== (const SymbolFillData& other) const;
	bool				operator!= (const SymbolFillData& other) const;

		// I/O methods

	GSErrCode			Write (GS::OChannel& oc) const override;
	GSErrCode			Read ( GS::IChannel& ic) override;
	GSErrCode			WriteXML ( GS::XMLOChannel& oc) const override;
	GSErrCode			ReadXML ( GS::XMLIChannel& ic);

		// convert methods

	GSErrCode			SplitFillDataToHandles (Int32		nFills,
												GSHandle	fillHandle,
												GSHandle*	sfFillsHandle,
												GSHandle*	fillCoordsHandle,
												GSHandle*	subPoliesHandle,
												GSHandle*	polyArcsHandle,
												GS::PlatformSign		inplatform);

	GSErrCode			AssembleFillHandles (GSHandle	sfFillsHandle,
											 GSHandle	fillCoordsHandle,
											 GSHandle	subPoliesHandle,
											 GSHandle	polyArcsHandle,
											 GSHandle*	fillHandle) const;

	void				GetBoundingBox (Box2DData*	sRect) const;

private:
		// get methods

	GX::Pattern::SFFill*				GetFillsPtr () const;
	Coord*				GetFillCoordsPtr () const;
	Int32*				GetSubPoliesPtr () const;
	GX::Pattern::SFPolyArc*			GetPolyArcsPtr () const;

		// set methods

	bool				PtrsToSymbolFillDetails (const GX::Pattern::SymbolFillDetails& data);

		// I/O methods
	GSErrCode			WriteVersion1	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode			ReadVersion1	(GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode			WriteVersion2	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode			ReadVersion2	(GS::IChannel& ic, const GS::InputFrame& frame);


		// convert methods

	void				IVSymbolFillData (GS::PlatformSign inplatform, VBUtil::TypeHead* pHead);
};

//====================== End of the VBAttr namespace ======================

}

#endif
