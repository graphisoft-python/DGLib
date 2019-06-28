// *********************************************************************************************************************
// List of comment assigned to MarkupEntry
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMUAC11
// Contact person:	VV
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (ENTRYCOMMENTLISTAC11_HPP)
#define ENTRYCOMMENTLISTAC11_HPP

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "vaarray.hpp"

// own
#include "MarkupExport.hpp"
#include "EntryCommentAC11.hpp"


namespace PRMUAC11 {

// --- Type definitions	------------------------------------------------------------------------------------------------


// =============================================================================
// EntryCommentList
//
// =============================================================================

class EntryCommentArray : public GS::VAArray<EntryComment> {	// VC++
public:
	virtual ~EntryCommentArray ();
};

class MARKUP_DLL_EXPORT EntryCommentList : public EntryCommentArray {
	DECLARE_ROOT_CLASS_INFO

public:
	EntryCommentList ();
	EntryCommentList (const EntryCommentList& source);
	~EntryCommentList ();

	EntryCommentList& operator= (const EntryCommentList& source);

	EntryComment*	GetComment (UIndex unId);

	GSErrCode		Read (GS::IChannel& ic);
	GSErrCode		Write (GS::OChannel& oc) const;

	void			ReSort (void);

private:
	static CmpResult	SortFunct (const void* p1, const void* p2);
};


} // namespace PRMUAC11

#endif
