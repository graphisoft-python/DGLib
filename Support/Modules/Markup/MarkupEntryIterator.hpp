// *********************************************************************************************************************
// Scan all the MarkupEntries of a container
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	VV
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (MARKUPENTRYITERATOR_HPP)
#define MARKUPENTRYITERATOR_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"

#include "MarkupEntry.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace EDB {
	class IElemDatabase;
}

namespace PRMU {

// --- Type definitions	------------------------------------------------------------------------------------------------

class MARKUP_DLL_EXPORT MarkupEntryIterator {
private:
	ODB::RefList<MarkupEntry> entries;
	ODB::RefList<MarkupEntry>::Iterator it;

	class X {};		// a type for safe comparison against nullptr

	MarkupEntryIterator (const MarkupEntryIterator& source);					// disabled
	MarkupEntryIterator&	operator= (const MarkupEntryIterator& source);		// disabled

public:
	MarkupEntryIterator (VBES::ElemSetRef elemSet);
	~MarkupEntryIterator ();

	MarkupEntryRef			operator* () const;

	MarkupEntryIterator&	operator++ ();

	bool					operator== (const X*) const;
	bool					operator!= (const X*) const;
};


} // namespace PRMU

#endif
