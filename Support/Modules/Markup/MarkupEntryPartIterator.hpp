// *********************************************************************************************************************
// Scan all the corrected/highlighted elements of a MarkupEntry
// Compare all the corrected/highlighted elements of a MarkupEntry
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	VV
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (MARKUPENTRYPARTITERATOR_HPP)
#define MARKUPENTRYPARTITERATOR_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"

// from VBUtil
#include	"UnId.hpp"
#include	"UnIdList.hpp"

// from VBElements
#include	"EDBGeneralDefinitions.hpp"

// own
#include	"MarkupEntry.hpp"


// --- Predeclarations	------------------------------------------------------------------------------------------------


namespace PRMU {

// --- Type definitions	------------------------------------------------------------------------------------------------

class MARKUP_DLL_EXPORT MarkupEntryPartIterator
{
public:
	enum {
		Highlight	= 0x01,
		Correction	= 0x02,
		Remark		= 0x04,

		Owned		= 0x06,
		All			= 0xff
	};

private:
	PRMU::MarkupEntryConstRef									entry;
	ODB::ConstRefList<EDB::GeneralElem> 						corrections;
	ODB::ConstRefList<EDB::GeneralElem> 						highlights;
	mutable ODB::ConstRefList<EDB::GeneralElem>::ConstIterator	itCorrection;
	mutable ODB::ConstRefList<EDB::GeneralElem>::ConstIterator	itHighlight;
	mutable EDB::GeneralElemConstRef							currElem;

	GSFlags				filter;
	mutable GSFlags		typ;
	mutable bool		wasRemark;

	class X {};		// a type for safe comparison against nullptr

	MarkupEntryPartIterator (const MarkupEntryPartIterator& source);				// disabled
	MarkupEntryPartIterator& operator= (const MarkupEntryPartIterator& source);		// disabled

public:
	MarkupEntryPartIterator (PRMU::MarkupEntryConstRef _entry, GSFlags _filter);
	~MarkupEntryPartIterator ();

	EDB::GeneralElemConstRef	operator* () const;

	MarkupEntryPartIterator&	operator++ ();

	bool			operator== (const X*) const;
	bool			operator!= (const X*) const;

	bool			IsHighlighted (void) const			{ return (typ == Highlight); }
	bool			IsCorrection (void) const			{ return (typ == Correction); }
	bool			IsRemark (void)	const				{ return (typ == Remark); }

	Int32			GetCount (void) const;

private:

	void	SearchForNext (void) const;
};


} // namespace PRMU

#endif
