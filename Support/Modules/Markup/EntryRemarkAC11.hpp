// *********************************************************************************************************************
// Remark data stucture of the MarkupEntry
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMUAC11
// Contact person:	VV
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (ENTRYREMARKAC11_HPP)
#define ENTRYREMARKAC11_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Object.hpp"
#include "String.hpp"

// from VBElements
#include "VBElements/WordTypes.hpp"

// own
#include "MarkupExport.hpp"


namespace PRMUAC11 {


// --- Type definitions	------------------------------------------------------------------------------------------------

class MARKUP_DLL_EXPORT EntryRemark : public GS::Object
{
	DECLARE_CLASS_INFO

private:
	friend class MarkupEntry;
	GS::String		text;				// the remark on the plan
	VBElem::WordRef	word;				// the Word element if placed; 0 otherwise
	bool			visible;			// true if it is placed and must be shown on the plan

public:
	EntryRemark ();
	EntryRemark (const GS::String& _string, VBElem::WordRef _word = nullptr, bool _visible = true);
	EntryRemark (const EntryRemark& source, const EDB::NewElemRefList& newElemList);
	~EntryRemark ();

		// operators
	EntryRemark&	operator=	(const EntryRemark& source);
	bool			operator==	(const EntryRemark& right);

		// accessors
	const GS::String&		GetText (void) const			{ return text; }
	VBElem::WordRef			GetWord (void)	const			{ return word; }
	bool					IsPlaced (void) const			{ return word != nullptr; }
	bool					IsVisible (void) const			{ return visible; }

		// Modifiers
	bool	SetText				(const GS::String& str);

	// Object realization
	virtual GSErrCode		Write	(GS::OChannel& oc, EDB::IElemDatabase* db = nullptr) const;
	virtual GSErrCode		Read	(GS::IChannel& ic, EDB::IElemDatabase* db = nullptr);

private:
	virtual GSErrCode		WriteVersion1	(GS::OChannel& oc, const GS::OutputFrame& frame, EDB::IElemDatabase* db) const;
	virtual GSErrCode		ReadVersion1	(GS::IChannel& ic, const GS::InputFrame& frame, EDB::IElemDatabase* db);
	virtual GSErrCode		WriteVersion2	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	virtual GSErrCode		ReadVersion2	(GS::IChannel& ic, const GS::InputFrame& frame);
};


} // namespace PRMUAC11

#endif
