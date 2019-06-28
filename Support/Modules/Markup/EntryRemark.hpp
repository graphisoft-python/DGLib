// *********************************************************************************************************************
// Remark data stucture of the MarkupEntry
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	VV
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (ENTRYREMARK_HPP)
#define ENTRYREMARK_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Object.hpp"
#include "UniString.hpp"

// from VBElements
#include "VBElements/WordTypes.hpp"

// own
#include "MarkupExport.hpp"


namespace PRMU {


// --- Type definitions	------------------------------------------------------------------------------------------------

class MARKUP_DLL_EXPORT EntryRemark : public GS::Object
{
	DECLARE_CLASS_INFO
private:
	friend class MarkupEntry;
	GS::UniString	text;				// the remark on the plan
	VBElem::WordRef	word;				// the Word element if placed; 0 otherwise
	bool			visible;			// true if it is placed and must be shown on the plan

public:
	EntryRemark ();
	EntryRemark (const GS::UniString& _string, VBElem::WordRef _word = nullptr, bool _visible = true);
	EntryRemark (const EntryRemark& source, const EDB::NewElemRefList& newElemList);
	~EntryRemark ();

		// operators
	EntryRemark&	operator=	(const EntryRemark& source);
	bool			operator==	(const EntryRemark& right);

		// accessors
	const GS::UniString&	GetText (void) const			{ return text; }
	VBElem::WordRef			GetWord (void)	const			{ return word; }
	bool					IsPlaced (void) const			{ return !word.IsNull (); }
	bool					IsVisible (void) const			{ return visible; }

		// Modifiers
	bool	SetText				(const GS::UniString& str);

	// Object realization
	virtual GSErrCode		Write	(GS::OChannel& oc, EDB::IElemDatabase* db = nullptr) const;
	virtual GSErrCode		Read	(GS::IChannel& ic, EDB::IElemDatabase* db = nullptr);

private:

	virtual GSErrCode		ReadVersion1	(GS::IChannel& ic, const GS::InputFrame& frame, EDB::IElemDatabase* db);
	virtual GSErrCode		ReadVersion2	(GS::IChannel& ic, const GS::InputFrame& frame);
	virtual GSErrCode		ReadVersion3	(GS::IChannel& ic, const GS::InputFrame& frame);

	virtual GSErrCode		WriteVersion2	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	virtual GSErrCode		WriteVersion3	(GS::OChannel& oc, const GS::OutputFrame& frame) const;

};


} // namespace PRMU

#endif
