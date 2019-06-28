// *****************************************************************************
// Line items memo id
// VBAttributes, platform-independent
//
// Namespaces:        Contact person:
//	SeparatorItem			CSF
//	CenterDotItem			CSF
//	DotItem					CSF
//	RightAngleItem			CSF
//	ParallelItem			CSF
//	LineItem				CSF
//	CircleItem				CSF
//	ArcItem					CSF
//	GeneralLineItem			CSF
//	GeneralArcItem			CSF
//	LineItemStruct			CSF
//	GX::Pattern::LineItemDoubles			CSF
//	GX::Pattern::LineItemHead			CSF
//	GX::Pattern::LineItems				CSF
//	LineItemData			CSF
//
// [SG compatible]
// *****************************************************************************

#if !defined (LINEITEMSDATA_HPP)
#define LINEITEMSDATA_HPP

#pragma once

//============================== Includes =================================

#include	"VBAttributesEnv.hpp"
#include	"GSMemoData.hpp"
#include	"basicgeometry.h"
#include	"AttributeManager.hpp"

// Pattern
#include	"LineItems.hpp"

namespace GS {
	class XMLOChannel;
	class XMLIChannel;
}

//===================== Begin of the VBAttr namespace =====================

namespace VBAttr {

//============================ Definitions ================================

#define	TypeId_LineItems	'litm'

//======================= Class LineItemsIterator =========================

class LineItemsData;

class VBATTRIBUTES_DLL_EXPORT LineItemsIterator {
private:
		// data members

	GSHandle			lineItemsHandle;
	LineItemsData*		lineItems;
	GX::Pattern::LineItems*			lineItemsPtr;
	short				count;
	short				nLineItems;

public:
		// constructors

	LineItemsIterator (const LineItemsData& lineItems);
	LineItemsIterator (GSHandle lineItemsHandle, short nLineItems);
   ~LineItemsIterator ();

		// get methods

	bool			HasNextLineItems (void) const;
	GX::Pattern::LineItems*		GetNextLineItems (void);
};

//======================== Class LineItemsData ============================

class VBATTRIBUTES_DLL_EXPORT LineItemsData : public VBUtil::GSMemoData
{
	DECLARE_CLASS_INFO
private:
		// friend classes

	friend class LineItemsIterator;

public:
		// constructors

	LineItemsData ();
   ~LineItemsData ();

		// get methods

	bool				GetLineItems (GX::Pattern::LineItems*** lineItemsHandle, short* nLineItems) const;

	GX::Pattern::LineItems*			GetItemTypePtr (short itemType) const;
	bool				HasItemType (short itemType) const;

	short				GetLineItemsNumber () const;

	Int32				GetNParts (void) const override;
	GSType				GetSignal (void) const override;

	// check methods
	virtual bool		Check ();

		// set methods

	GSErrCode			Setup (const GX::Pattern::LineItems * const ** lineItemsHandle, short nLineItems);
	bool				UpdateLineItems (GX::Pattern::LineItems* data, short nLineItems);

		// I/O methods

	GSErrCode			Write (GS::OChannel& oc) const override;
	GSErrCode			Read (GS::IChannel& ic) override;
	GSErrCode			WriteXML (GS::XMLOChannel& oc) const override;
	GSErrCode			ReadXML (GS::XMLIChannel& ic);

private:
		// get methods

	GX::Pattern::LineItems*			GetLineItemsPtr () const;

		// set methods

	GSErrCode			CreateOffsets (const GX::Pattern::LineItems * const * lineItemsHandle, short nLineItems, Int32*** offsetsHandle);
	bool				PtrsToLineItems (GX::Pattern::LineItems* data, short nLineItems);

		// convert methods

	void				IVLineItemsData (GS::PlatformSign inplatform, VBUtil::TypeHead* pHead);
};

//====================== End of the VBAttr namespace ======================

}

#endif
