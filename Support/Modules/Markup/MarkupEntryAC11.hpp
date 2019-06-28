// *********************************************************************************************************************
// MarkupEntry: Record to manage a set of elements in redlining
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	VV
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (MARKUPENTRYAC11_HPP)
#define MARKUPENTRYAC11_HPP

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"
#include "EventSource.hpp"
#include "EventObserver.hpp"
#include "String.hpp"

// from ElementManager
#include "EDBGeneralDefinitions.hpp"
#include "GeneralService.hpp"
#include "ElemTables.hpp"

// own
#include "MarkupExport.hpp"
#include "EntryRemarkAC11.hpp"
#include "EntryCommentAC11.hpp"
#include "EntryCommentListAC11.hpp"


// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace EDB {
	class IElemDatabase;
}

namespace PRMUAC11 {

// --- Type definitions	------------------------------------------------------------------------------------------------

// =============================================================================
// MarkupEntry
//
// =============================================================================

class MARKUP_DLL_EXPORT MarkupEntry : public EDBAC11::GeneralService,
					public GS::EventSource
{
	DECLARE_DYNAMIC_CLASS_INFO (MarkupEntry)

#define _MARKUPENTRYAC11_DATA_MEMBERS_																								\
private:																														\
	EDB::IElemDatabase*						db;					/* database the entry assigned to */										\
	short									floorId;			/* floor of database the entry assigned to */								\
	ODB::ConstRef<MarkupEntry>				parentEntry;		/* reference of the Entry parent (thread,  0- no parent) */					\
	GS::UniString							name;				/* name of the entry */														\
	short									styleIndex;			/* style to apply on elements upon draw */									\
	GSTime									creaTime;			/* time created */															\
	GSTime									modiTime;			/* time modified */															\
	short									creaOwnerId;		/* ID of the creator user */												\
	short									prevOwnerId;		/* ID of the previous user	(who passed the entry to the current owner) */	\
	short									ownerId;			/* ID of the current user	(who owns the MarkupEntry for modification) */	\
	short									sendToOwnerId;		/* ID of the next user		(to whom the current user will pass the ownership) */	\
	EntryRemark								remark;				/* the remark of the entry */												\
	EntryCommentList						commentList;		/* discussion items of the entry */											\
	GS::HashSet<EDB::GeneralElemRef>		ownedElements;		/* elements owned by the MarkupEntry */										\
	GS::HashSet<EDB::GeneralElemConstRef>	paintedElements;	/* elements not owned, just skinned with style attributes */				\
	bool									onOffSwitch;		/* switches on/off	(overwritten by the owner's attribute upon SendChanges */		\
	bool									skipInMerge;		/* flag for TW Send/Receive Changes */

	_MARKUPENTRYAC11_DATA_MEMBERS_

	// ... Transaction management class ................................................................................

protected:
	class IsolatedState : public EDBAC11::GeneralService::IsolatedState {
		private:
			friend class MarkupEntry;

			_MARKUPENTRYAC11_DATA_MEMBERS_

		public:
			virtual ~IsolatedState ();
	};

	// ... Disabled methods ............................................................................................

private:
	MarkupEntry (const MarkupEntry&		source);

	// ... Constructors / destructors ..................................................................................

public:
	MarkupEntry ();
	MarkupEntry (const MarkupEntry&			source,
				 const EDB::NewElemRefList&	newElemList);
	MarkupEntry (short						floorId,
				 ODB::ConstRef<MarkupEntry>	parent,
				 const GS::UniString&		name,
				 short						styleIndex,
				 short						ownerId,
				 EDB::IElemDatabase*		db);
	~MarkupEntry ();

	// ... Overridden virtual methods (GS::Object) .....................................................................

public:
	virtual MarkupEntry*	Clone 		(const EDB::NewElemRefList& newElemList) const override;

	// ... Accessors	................................................................................................

	inline EDB::IElemDatabase*			GetDatabase (void) const			{ return db; }

	inline short						GetFloorId (void) const				{ return floorId; }

	inline ODB::ConstRef<MarkupEntry>	GetParentEntry (void) const			{ return parentEntry; }

	inline const GS::UniString&			GetName (void) const				{ return name; }

	inline short						GetStyleIndex (void) const			{ return styleIndex; }

	inline GSTime						GetCreationTime (void) const		{ return creaTime; }
	inline GSTime						GetModificationTime (void) const	{ return modiTime; }

	inline short						GetCreatorOwnerId (void) const		{ return creaOwnerId; }
	inline short						GetPrevOwnerId (void) const			{ return prevOwnerId; }
	inline short						GetOwnerId (void) const				{ return ownerId; }
	inline short						GetSentToOwnerId (void) const		{ return sendToOwnerId; }

	inline const EntryRemark&				GetRemark (void) const			{ return remark; }
	inline const EntryCommentList&			GetCommentList (void) const		{ return commentList; }

	inline const GS::HashSet<EDB::GeneralElemRef>&		GetOwnedElements (void) const	{ return ownedElements; }
	inline const GS::HashSet<EDB::GeneralElemConstRef>&	GetPaintedElements (void) const	{ return paintedElements; }

	inline GS::HashSet<EDB::GeneralElemRef>&			GetOwnedElements (void)			{ return ownedElements; }
	inline GS::HashSet<EDB::GeneralElemConstRef>&		GetPaintedElements (void)		{ return paintedElements; }

	inline bool							IsTurnedOn (void) const				{ return onOffSwitch; }

	inline bool							MustSkipInMerge (void) const		{ return skipInMerge; }

	void	PostChanges				(const MarkupEntry& originalEntry);

		// Modifiers
	void	SetDatabase				(EDB::IElemDatabase* _db)			{ db = _db; }

	void	SetParentEntry			(ODB::ConstRef<MarkupEntry> parent)	{ parentEntry = parent; }
	void	SetRemarkPlacedWord		(VBElem::WordRef w);
	void	SetRemarkVisible		(bool show);

		// Component management
	void	AddComment				(short userId, const GS::String& str);
	bool	AttachElement 			(EDB::GeneralElemRef elem, bool asCorrection);
	bool	IsOwnedElement			(EDB::GeneralElemConstRef elem) const;
	bool	IsPaintedElement		(EDB::GeneralElemConstRef elem) const;

		// Object realization
	virtual GSErrCode	Write (GS::OChannel& oc) const override;
	virtual GSErrCode	Read (GS::IChannel& ic) override;

		// StorageRecord realization
//	virtual void		Copy (const VBUtil::StorageRecord& source);
	virtual void 		Debug (void) const;

		// GeneralService realization
	virtual bool		IsNewComponentsExist	(const EDB::NewElemRefList& newElemList) const;
	virtual bool		IsValid					(bool allowPartial = false) const override;
	virtual bool		RefreshLinks			(ODB::IdSpace* idSpace);

private:
	GSErrCode	ReadVersion1					(GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode	ReadVersion3					(GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode	WriteIsolatedStateVersion3   	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode	ReadIsolatedStateVersion3 		(GS::IChannel& ic, const GS::InputFrame& frame);

public:
	virtual GSErrCode					StoreIsolatedState   	(ODB::Object::IsolatedState* isolatedState) const override;
	virtual GSErrCode					RestoreIsolatedState 	(const ODB::Object::IsolatedState* isolatedState) override;
	virtual void						Isolate					(void) override;
	virtual	ODB::Object::IsolatedState*	CreateIsolatedState		(void) const override;
	virtual USize						GetIsolatedSize			(void) const override;
	virtual GSErrCode					WriteIsolatedState   	(GS::OChannel& oc) const override;
	virtual GSErrCode					ReadIsolatedState 		(GS::IChannel& ic) override;

};

}	// namespace PRMUAC11


#endif
