// *********************************************************************************************************************
// MarkupEntry: Record to manage a set of elements in redlining
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	VV
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (MARKUPENTRY_HPP)
#define MARKUPENTRY_HPP

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------

// GSRoot
#include "Definitions.hpp"
#include "EventSource.hpp"
#include "EventObserver.hpp"
#include "UniString.hpp"
// PN
//#include "CaptureData.hpp"
// ObjectDatabase
#include "ODBObject.hpp"
#include "ODBDependencyNode.hpp"

// VBElements
#include "EDBGeneralDefinitions.hpp"
#include "FloorTypes.hpp"

// own
#include "AssignInfo.hpp"
#include "EntryRemark.hpp"
#include "EntryComment.hpp"
#include "EntryCommentList.hpp"
#include "MarkupExport.hpp"


// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace PRMU {
	class MarkupEntryObserver;
	class MarkupEntry;
	class MarkupEntryClientData;
	class MarkupClientConversionData;

	typedef ODB::Ref<MarkupEntry> MarkupEntryRef;
	typedef ODB::ConstRef<MarkupEntry> MarkupEntryConstRef;

	typedef ODB::Ref<MarkupEntryClientData> MarkupEntryClientDataRef;
	typedef ODB::ConstRef<MarkupEntryClientData> MarkupEntryClientDataConstRef;
}

namespace VBES {
	class ElemSet;
	typedef ODB::Ref<ElemSet>		ElemSetRef;
	typedef ODB::ConstRef<ElemSet>	ElemSetConstRef;
}


namespace PRMU {
// === MarkupEntry class ===============================================================================================


class MARKUP_DLL_EXPORT MarkupEntryClientData : public ODB::Object
{
	DECLARE_DYNAMIC_CLASS_INFO (MarkupEntryClientData)

#define _MARKUPENTRY_CLIENT_DATA_MEMBERS_																						 \
private:																														 \
	bool	turnedOn;		/* switches on/off	(run time data in TW mode) */

	_MARKUPENTRY_CLIENT_DATA_MEMBERS_

protected:
	class IsolatedState : public ODB::Object::IsolatedState {
		private:
			friend class MarkupEntryClientData;
			_MARKUPENTRY_CLIENT_DATA_MEMBERS_

		public:
			virtual ~IsolatedState ();
	};

public:
	MarkupEntryClientData ();
	MarkupEntryClientData (bool _turnedOn);
	~MarkupEntryClientData ();

	bool								IsTurnedOn		(void) const;
	void								SetTurnedOn		(bool _turnedOn);

	MarkupEntryConstRef					GetMarkupEntry		 (void) const;

protected:
	virtual GSErrCode					StoreIsolatedState   	(ODB::Object::IsolatedState* isolatedState) const override;
	virtual GSErrCode					RestoreIsolatedState 	(const ODB::Object::IsolatedState* isolatedState) override;
	virtual void						Isolate					(void) override;
	virtual	ODB::Object::IsolatedState*	CreateIsolatedState		(void) const override;
	virtual USize						GetIsolatedSize			(void) const override;
	virtual GSErrCode					WriteIsolatedState   	(GS::OChannel& oc) const override;
	virtual GSErrCode					ReadIsolatedState 		(GS::IChannel& ic) override;

private:
	GSErrCode							WriteIsolatedStateVersion1   	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode							ReadIsolatedStateVersion1 		(GS::IChannel& ic, const GS::InputFrame& frame);

};

class MARKUP_DLL_EXPORT MarkupEntry : public TW::Object,
					public GS::EventSource
{
	DECLARE_DYNAMIC_CLASS_INFO (MarkupEntry)

	friend class MarkupEntryReflection;

#define _MARKUPENTRY_DATA_MEMBERS_																								 \
private:																														 \
	ODB::ConstRef<MarkupEntry>	parentEntry;		/* reference of the Entry parent (thread,  0- no parent) */					 \
	GS::UniString				name;				/* name of the entry */														 \
	short						styleIndex;			/* style to apply on elements upon draw */									 \
	GSTime						creaTime;			/* time created */															 \
	GSTime						modiTime;			/* time modified */															 \
	EntryRemark					remark;				/* the remark of the entry */												 \
	GS::Guid					handlerGuid;		/* external handler id (nullGUID if internal) */							 \
	GS::Guid					externalId;			/* external Id could be given in a BCF import, otherwise NULLGuid*/			 \
	GS::UniString				noneFullNameString;	/* string for empty assignInfo creation */

	_MARKUPENTRY_DATA_MEMBERS_

	// ... Transaction management class ................................................................................

protected:
	class IsolatedState : public TW::Object::IsolatedState {
		private:
			friend class MarkupEntry;

			_MARKUPENTRY_DATA_MEMBERS_

		public:
			virtual ~IsolatedState ();
	};

	// ... Disabled methods ............................................................................................

private:
	MarkupEntry (const MarkupEntry&		source);

	// ... Constructors / destructor ...................................................................................

public:
	MarkupEntry ();
	MarkupEntry (EDB::FloorRef				floor,
				 ODB::ConstRef<MarkupEntry>	parent,
				 const GS::UniString&		name,
				 short						styleIndex,
				 const GS::Guid&			ownerId,
				 const GS::UniString&		ownerFullName,
				 const GS::UniString&		noneFullName,
				 bool						onOffSwitch = true);
	~MarkupEntry ();

	// ... Accessors	................................................................................................
public:

		   EDB::FloorConstRef			GetFloor			(void) const;

	inline ODB::ConstRef<MarkupEntry>	GetParentEntry		(void) const										{ return parentEntry; }

	inline const GS::UniString&			GetName				(void) const										{ return name;		  }

	inline short						GetStyleIndex		(void) const										{ return styleIndex;  }

	inline GSTime						GetCreationTime		(void) const										{ return creaTime;	  }
	inline GSTime						GetModificationTime (void) const										{ return modiTime;	  }

		   GS::Guid						GetCreatorGuid		(void) const;
		   GS::Guid						GetPrevOwnerGuid	(void) const;

	inline const EntryRemark&			GetRemark			(void) const										{ return remark;	  }
	ODB::ConstRefList<EntryComment>		GetCommentList		(void) const;

	inline const GS::Guid&				GetHandlerGuid		(void) const										{ return handlerGuid; }
	GS::Guid							GetIdForBCF			() const;

		   void							GetOwnedElements	(ODB::ConstRefList<EDB::GeneralElem>* list) const;
		   void							GetOwnedElements	(ODB::RefList<EDB::GeneralElem>* list);
	static void							GetOwnedElements	(MarkupEntryRef markupEntry, ODB::RefList<EDB::GeneralElem>* list);
		   Int32						GetOwnedElemNumber	() const;
		   void							GetPaintedElements	(ODB::ConstRefList<EDB::GeneralElem>* list) const;
		   void							GetPaintedElements	(ODB::RefList<EDB::GeneralElem>* list);
	static void							GetPaintedElements	(MarkupEntryRef markupEntry, ODB::RefList<EDB::GeneralElem>* list);
		   Int32						GetPaintedElemNumber () const;
	static void							GetElementPainterEntries	(EDB::GeneralElemConstRef elem, ODB::ConstRefList<PRMU::MarkupEntry>* list);
	static void							GetElementPainterEntries	(EDB::GeneralElemRef elem, ODB::RefList<PRMU::MarkupEntry>* list);

		   bool							IsTurnedOn			(void) const;

		   void							PostChanges			(const MarkupEntry& originalEntry);

			// Modifiers
		   void							SetFloor (EDB::FloorRef floor);
		   void							SetParentEntry		(ODB::ConstRef<MarkupEntry> parent)					{ parentEntry = parent; }

		   void							SetName				(const GS::UniString& str);
		   void							SetStyleReference	(short styleIndex);

	inline void							SetCreationTime (const GSTime& time) { creaTime = time; }
	inline void							SetModificationTime (const GSTime& time) { modiTime = time; }

		   void							SetRemark			(const GS::UniString& str);
		   void							SetRemarkPlacedWord	(VBElem::WordRef w);
		   void							HandlePlacedRemarkChange ();
		   void							SetRemarkVisible	(bool show);

		   EntryCommentConstRef			AddComment			(const GS::Guid&					userId,
															 const GS::UniString&				str,
															 PRMU::EntryComment::CommentStatus	status = PRMU::EntryComment::Unknown,
															 const GS::UniString&				verbalStatus = "",
															 const GS::Guid&					commentId = GS::NULLGuid,
															 const GS::UniString&				author = "",
															 GSTime								commentCreaTime = TIGetTime ());

		   void							SetHandlerGuid		(const GS::Guid& guid);
		   void							SetExternalId		(const GS::Guid& guid);

	static void							TWReceivePostProcess	(MarkupEntryRef markupEntry);
	static void							SetTurnedOn				(MarkupEntryRef markupEntry, bool turnedOn);

			// Component management
			bool						AttachElement 			(EDB::GeneralElemRef elem, bool asCorrection, bool touch = false);
			bool						DetachElement 			(EDB::GeneralElemRef elem, bool fromCorrection);
			bool						AttachRemarkText 		(VBElem::WordRef word);

			bool						IsOwnedElement			(EDB::GeneralElemConstRef elem) const;
			bool						IsPaintedElement		(EDB::GeneralElemConstRef elem) const;

			void						Share					(void);

			AssignInfoRef				CreateAssignInfo		(void);
			AssignInfoConstRef			GetAssignInfo			(void) const;
			AssignInfoRef				GetAssignInfo			(void);
			static AssignInfoConstRef 	GetConstAssignInfo		(MarkupEntryConstRef markupEntry);
			static AssignInfoRef		GetAssignInfo			(MarkupEntryRef markupEntry);

		// Object realization
	virtual GSErrCode	Write	(GS::OChannel& oc) const override;
	virtual GSErrCode	Read	(GS::IChannel& ic) override;

			void 		Debug	(void) const;

private:
	void	AddCommentSorted					(EntryCommentRef commentRef);
	void 	PostNameChangedEvent				(void);
	void	PostFloorChangedEvent				(void);
	void	PostStyleReferenceChangedEvent		(void);
	void	PostRemarkChangedEvent				(void);
	void	PostRemarkPlacementChangedEvent		(void);
	void	PostRemarkVisibilityChangedEvent	(void);
	void	PostCommentAddedEvent				(void);
	void	PostElemlistChangedEvent			(void);
	void	PostEntryOnOffSwitchChangedEvent	(void) const;

	GSErrCode	ReadVersion1	(GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode	ReadVersion2	(GS::IChannel& ic, const GS::InputFrame& frame);

public:
	void	PostCaptureDataChangedEvent			(void);
		void	Attach (MarkupEntryObserver& observer);
		void	Detach (MarkupEntryObserver& observer);

protected:
	virtual GSErrCode					StoreIsolatedState   	(ODB::Object::IsolatedState* isolatedState) const override;
	virtual GSErrCode					RestoreIsolatedState 	(const ODB::Object::IsolatedState* isolatedState) override;
	virtual void						Isolate					(void) override;
	virtual	ODB::Object::IsolatedState*	CreateIsolatedState		(void) const override;
	virtual USize						GetIsolatedSize			(void) const override;
	virtual GSErrCode					WriteIsolatedState   	(GS::OChannel& oc) const override;
	virtual GSErrCode					ReadIsolatedState 		(GS::IChannel& ic) override;
	virtual	GSErrCode					WriteTWIsolatedState	(GS::OChannel& oc) const override;
	virtual	GSErrCode					ReadTWIsolatedState		(GS::IChannel& ic) override;

private:
			GSErrCode					WriteIsolatedStateVersion1   	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
			GSErrCode					ReadIsolatedStateVersion1 		(GS::IChannel& ic, const GS::InputFrame& frame);

			GSErrCode					WriteCoreIsolatedStateVersion2	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
			GSErrCode					ReadCoreIsolatedStateVersion2	(GS::IChannel& ic, const GS::InputFrame& frame);

			GSErrCode					WriteIsolatedStateVersion2   	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
			GSErrCode					ReadIsolatedStateVersion2		(GS::IChannel& ic, const GS::InputFrame& frame);

			GSErrCode					WriteCoreIsolatedStateVersion3	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
			GSErrCode					ReadCoreIsolatedStateVersion3	(GS::IChannel& ic, const GS::InputFrame& frame);

			GSErrCode					WriteIsolatedStateVersion3   	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
			GSErrCode					ReadIsolatedStateVersion3		(GS::IChannel& ic, const GS::InputFrame& frame);

			GSErrCode					WriteTWIsolatedStateVersionLast	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
			GSErrCode					ReadTWIsolatedStateVersionLast	(GS::IChannel& ic, const GS::InputFrame& frame);
};

// === MarkupEntryObserver class =======================================================================================


class MARKUP_DLL_EXPORT MarkupEntryObserver : public GS::EventObserver
{
protected:
	virtual ~MarkupEntryObserver ();

public:
	virtual void	MarkupEntryNameChanged				(MarkupEntryConstRef) {}
	virtual void	MarkupEntryFloorChanged				(MarkupEntryConstRef) {}
	virtual void	MarkupEntryCaptureDataChanged		(MarkupEntryConstRef) {}
	virtual void	MarkupEntryStyleReferenceChanged	(MarkupEntryConstRef) {}
	virtual void	MarkupEntrySendToOwnerIdChanged		(MarkupEntryConstRef) {}
	virtual void	MarkupEntryRemarkChanged			(MarkupEntryConstRef) {}
	virtual void	MarkupEntryRemarkPlacementChanged	(MarkupEntryConstRef) {}
	virtual void	MarkupEntryRemarkVisibilityChanged	(MarkupEntryConstRef) {}		// no effect on moditime
	virtual void	MarkupEntryCommentAdded				(MarkupEntryConstRef) {}
	virtual void	MarkupEntryElemlistChanged			(MarkupEntryConstRef) {}
	virtual void	MarkupEntryOnOffSwitchChanged		(MarkupEntryConstRef) {}		// no effect on moditime

	virtual void	MarkupEntryModitimeChanged			(MarkupEntryConstRef) {}
};

// === Helper functions ================================================================================================

MARKUP_DLL_EXPORT void						DeleteMarkupEntry			(MarkupEntryRef				entry);
MARKUP_DLL_EXPORT bool						HasElemSetMarkupEntries		(VBES::ElemSetRef			elemSet);
MARKUP_DLL_EXPORT void						DeleteAllEntriesInElemSet	(VBES::ElemSetRef			elemSet);
MARKUP_DLL_EXPORT VBES::ElemSetRef			GetElemSetByMarkupEntry		(MarkupEntryRef				entry);
MARKUP_DLL_EXPORT VBES::ElemSetConstRef		GetElemSetByMarkupEntry		(MarkupEntryConstRef		entry);
MARKUP_DLL_EXPORT ODB::RefList<MarkupEntry>	GetMarkUpEntriesByElemSet	(VBES::ElemSetRef			elemSet);
MARKUP_DLL_EXPORT GSErrCode					ConnectInMarkupEntries		(VBES::ElemSetRef elemSet, MarkupEntryRef entry);

MARKUP_DLL_EXPORT GS::Guid					GetOwnedElementsAssocId		(void);
MARKUP_DLL_EXPORT GS::Guid					GetPaintedElementsAssocId	(void);
MARKUP_DLL_EXPORT GS::Guid					GetOwnedCommentsAssocId		(void);
MARKUP_DLL_EXPORT GS::Guid					GetAssignInfoAssocId		(void);

MARKUP_DLL_EXPORT bool						IsCorrectionElement			(EDB::GeneralElemConstRef elem);
MARKUP_DLL_EXPORT bool						IsHighlightedElement		(EDB::GeneralElemConstRef elem);
MARKUP_DLL_EXPORT MarkupEntryConstRef		GetOwnerMarkupEntryByElem	(EDB::GeneralElemConstRef elem);
MARKUP_DLL_EXPORT MarkupEntryRef			GetOwnerMarkupEntryByElem	(EDB::GeneralElemRef elem);
MARKUP_DLL_EXPORT bool						IsMarkupedElement			(const EDB::GeneralElemConstRef& pElem, bool* pDisableDraw, short* pPenIndex, bool showMarkupItems);
MARKUP_DLL_EXPORT bool						GetIFCCompareEntry			(EDB::GeneralElemRef elemRef, const GS::UniString&	nameFormat, PRMU::MarkupEntryRef& markupEntryRef);

MARKUP_DLL_EXPORT MarkupEntryRef			GetMarkUpEntryByAssignInfo	(AssignInfoRef assignInfoRef);
MARKUP_DLL_EXPORT void						ShowMarkUpEntriesByElem		(EDB::GeneralElemConstRef elem);

MARKUP_DLL_EXPORT void						ConvertMarkupFromAC11		(EDB::IElemDatabase* db, VBES::ElemSetRef elemSet, const GS::UniString& noneFullNameString);
MARKUP_DLL_EXPORT void						ConvertMarkupToAC11			(EDB::IElemDatabase* db, EDB::IElemDatabase* origDb, VBES::ElemSetRef elemSet, VBES::ElemSetRef origElemSet);

MARKUP_DLL_EXPORT MarkupClientConversionData* 	ConvertMarkupFromAC19		(MarkupEntryConstRef& markupEntry);
MARKUP_DLL_EXPORT void							ConvertMarkupToAC19			(MarkupEntryRef& markupEntry, const MarkupClientConversionData* conversionData);

extern MARKUP_DLL_EXPORT ODB::DependencyNode	clientDataToEntryPropagator;

}	// namespace PRMU


#endif