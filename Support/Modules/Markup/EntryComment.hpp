// *********************************************************************************************************************
// A comment of the MarkupEntry
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	VV
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (ENTRYCOMMENT_HPP)
#define ENTRYCOMMENT_HPP

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Object.hpp"
#include "UniString.hpp"
#include "GSTime.hpp"

// from TWRoot
#include "TWObject.hpp"

// own
#include "MarkupExport.hpp"


namespace PRMU {

// --- Type definitions	------------------------------------------------------------------------------------------------

class MARKUP_DLL_EXPORT EntryComment : public TW::Object
{
	DECLARE_DYNAMIC_CLASS_INFO (EntryComment)

public:
	enum CommentStatus {
		First		= 0,

		Error		= 0,
		Warning		= 1,
		Info		= 2,
		Unknown		= 3,

		Last		= 3
	};

	#define _ENTRYCOMMENT_DATA_MEMBERS_	\
private:								\
	friend class MarkupEntry;			\
	GS::UniString	text;				\
	GS::Guid		userId;				\
	GSTime			creaTime;			\
	CommentStatus	status;				\
	GS::UniString	verbalStatus;		\
	GS::Guid		externalId;			\
	GS::UniString	author;

	_ENTRYCOMMENT_DATA_MEMBERS_

	// ... Transaction management class ................................................................................
private:
	class IsolatedState : public TW::Object::IsolatedState {
	private:
		friend class EntryComment;
		_ENTRYCOMMENT_DATA_MEMBERS_

	public:
		virtual ~IsolatedState ();
	};

public:
	EntryComment ();
	EntryComment (const GS::UniString& comment, const GS::Guid& userId, CommentStatus status, const GS::UniString& verbalStatus, const GS::Guid& externalId, const GS::UniString& author, GSTime commentCreaTime);
	EntryComment (const EntryComment& source);
	~EntryComment ();

		// operators
	EntryComment& operator= (const EntryComment &source);

	// from GS::Object via ODB::Object
	virtual EntryComment*   Clone			(void) const override;
		// accessors
	const GS::UniString&	GetText			(void) const					{ return text;     }
	const GS::Guid&			GetUserId		(void) const					{ return userId;   }
	GSTime					GetCreationTime (void) const					{ return creaTime; }
	const CommentStatus		GetStatus		(void) const					{ return status; }
	const GS::UniString&	GetVerbalStatus	(void) const					{ return verbalStatus; }
	GS::Guid				GetExternalId	(void) const					{ return externalId; }
	const GS::UniString&	GetAuthor		(void) const					{ return author; }
	GS::Guid				GetIdForBCF		(void) const;

		// Object realization
	virtual GSErrCode		Write (GS::OChannel& oc) const override;
	virtual GSErrCode		Read (GS::IChannel& ic) override;

public:
	virtual GSErrCode					StoreIsolatedState   	(ODB::Object::IsolatedState* isolatedState) const override;
	virtual GSErrCode					RestoreIsolatedState 	(const ODB::Object::IsolatedState* isolatedState) override;
	virtual void						Isolate					(void) override;
	virtual	ODB::Object::IsolatedState*	CreateIsolatedState		(void) const override;
	virtual USize						GetIsolatedSize			(void) const override;
	virtual GSErrCode					WriteIsolatedState   	(GS::OChannel& oc) const override;
	virtual GSErrCode					ReadIsolatedState 		(GS::IChannel& ic) override;
	virtual	GSErrCode					WriteTWIsolatedState	(GS::OChannel& oc) const override;
	virtual	GSErrCode					ReadTWIsolatedState		(GS::IChannel& ic) override;

	// ... Other private methods .......................................................................................

private:

	GSErrCode					ReadAsString 					(GS::IChannel& ic, GS::UniString& uniStr);
	GSErrCode					WriteAsString				   	(GS::OChannel& oc, const GS::UniString& uniStr) const;

	GSErrCode					ReadVersion1 					(GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode					WriteVersion2				   	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode					ReadVersion2 					(GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode					WriteVersion3				   	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode					ReadVersion3 					(GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode					WriteCoreIsolatedStateVersion2	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode					ReadCoreIsolatedStateVersion2	(GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode					WriteCoreIsolatedStateVersion3	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode					ReadCoreIsolatedStateVersion3	(GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode					ReadIsolatedStateVersion1 		(GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode					WriteIsolatedStateVersion2   	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode					ReadIsolatedStateVersion2		(GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode					WriteIsolatedStateVersion3   	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode					ReadIsolatedStateVersion3		(GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode					WriteTWIsolatedStateVersion2	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode					ReadTWIsolatedStateVersion2		(GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode					WriteTWIsolatedStateVersion3	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode					ReadTWIsolatedStateVersion3		(GS::IChannel& ic, const GS::InputFrame& frame);

};

typedef ODB::Ref<EntryComment> EntryCommentRef;
typedef ODB::ConstRef<EntryComment> EntryCommentConstRef;
} // namespace PRMU

#endif