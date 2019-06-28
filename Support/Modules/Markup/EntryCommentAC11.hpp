// *********************************************************************************************************************
// A comment of the MarkupEntry
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMUAC11
// Contact person:	VV
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (ENTRYCOMMENTAC11_HPP)
#define ENTRYCOMMENTAC11_HPP

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Object.hpp"
#include "String.hpp"
#include "GSTime.hpp"

// own
#include "MarkupExport.hpp"


namespace PRMUAC11 {


// --- Type definitions	------------------------------------------------------------------------------------------------

class MARKUP_DLL_EXPORT EntryComment : public GS::Object
{
	DECLARE_CLASS_INFO
private:
	friend class MarkupEntry;
	GS::String	text;
	short		userId;
	GSTime		creaTime;

public:
	EntryComment ();
	EntryComment (const GS::String& comment, short userId);
	EntryComment (const EntryComment& source);
	~EntryComment ();

		// operators
	EntryComment& operator= (const EntryComment &source);

		// accessors
	const GS::String&		GetText (void) const			{ return text; }
	short					GetUserId (void) const			{ return userId; }
	GSTime					GetCreationTime (void) const	{ return creaTime; }

		// Object realization
	virtual GSErrCode		Write (GS::OChannel& oc) const override;
	virtual GSErrCode		Read (GS::IChannel& ic) override;
};


} // namespace PRMUAC11

#endif
