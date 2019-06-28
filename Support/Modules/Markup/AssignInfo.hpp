// *********************************************************************************************************************
// AssignInfo: Class to store user guid used in MarkUpEntry assign Operations
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	TVT
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (PRMUASSIGNINFO_HPP)
#define PRMUASSIGNINFO_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from TWRoot
#include "TWObject.hpp"

// own
#include "MarkupExport.hpp"

namespace PRMU {

// --- Type definitions	------------------------------------------------------------------------------------------------


// === MarkupEntry class ===============================================================================================


class MARKUP_DLL_EXPORT AssignInfo : public TW::Object
{
	DECLARE_DYNAMIC_CLASS_INFO (AssignInfo)

#define _ASSIGNINFO_MEMBERS_																										\
private:																															\
	GS::Guid			  creaOwnerId;			/* ID of the creator user													   */	\
	GS::Guid			  prevOwnerId;			/* ID of the previous user	(who passed the entry to the current owner)		   */	\
	GS::Guid			  nextOwnerId;			/* ID of the receiving user	(who will receive the MarkupEntry)				   */	\
	GS::UniString		  creaOwnerFullName;	/* cached full name of creator user											   */	\
	GS::UniString		  prevOwnerFullName;	/* cached full name of previous user										   */

	_ASSIGNINFO_MEMBERS_

protected:
	mutable Int64		revisionNumber;		// latest version received from server (runtime data)
	mutable bool		wasReceive;			// runtime data

public:
	enum UserIdType {
		CreaOwner,
		PrevOwner,
		Owner
	};

	// ... Transaction management class ................................................................................

protected:
	class IsolatedState : public TW::Object::IsolatedState {
	private:
		friend class AssignInfo;

		_ASSIGNINFO_MEMBERS_

	public:
		virtual ~IsolatedState ();
	};

	// ... Constructors / destructor ...................................................................................

public:
	AssignInfo  ();
	AssignInfo  (const GS::UniString& noneFullName);
	AssignInfo  (const GS::Guid& creaOwnerId,
					const GS::Guid& prevOwnerId,
					const GS::Guid& ownerId,
					const GS::UniString& creaOwnerFullName,
					const GS::UniString& prevOwnerFullName);
	AssignInfo	(const AssignInfo& source);
	~AssignInfo ();

public:
	AssignInfo& operator= (const AssignInfo& source);


public:
	virtual AssignInfo* Clone (void) const override;

	// ... Accessors methods ...........................................................................................

public:
	void	Reset (const GS::UniString& noneFullNameString);

	inline GS::Guid	GetCreatorGuid		(void) const					{ return creaOwnerId;	  	  }
	inline GS::Guid	GetPrevOwnerGuid	(void) const					{ return prevOwnerId;		  }
	inline GS::Guid	GetNextOwnerGuid	(void) const					{ return nextOwnerId;		  }

		   void		SetCreatorGuid		(const GS::Guid& pCreaOwnerId, const GS::UniString& pCreaOwnerFullName);
		   void		SetPrevOwnerGuid	(const GS::Guid& pPrevOwnerId, const GS::UniString& pPrevOwnerFullName);

public:
	GS::UniString	GetCreatorFullName  (void) const					{ return creaOwnerFullName;	  }
	GS::UniString	GetPrevOwnerFullName(void) const					{ return prevOwnerFullName;	  }

public:
	void			SetRevisionNumber	(Int64 revision) const			{ revisionNumber = revision;  }
	Int64			GetRevisionNumber	(void) const					{ return revisionNumber;      }
	void			SetWasReceive		(void) const					{ wasReceive = true;		 }
	void			ClearWasReceive		(void) const					{ wasReceive = false;		 }
	bool			WasReceive			(void) const					{ return wasReceive;		  }

	// ... Serialization methods .......................................................................................

public:
	GSErrCode	Write			(GS::OChannel& oc) const override;
	GSErrCode	Read			(GS::IChannel& ic) override;

private:
	GSErrCode	WriteVersion1	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode	ReadVersion1	(GS::IChannel& ic, const GS::InputFrame& frame);

	// ... Transaction management methods ..............................................................................

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

private:
			GSErrCode		WriteCoreIsolatedStateVersion1		(GS::OChannel& oc, const GS::OutputFrame& frame) const;
			GSErrCode		ReadCoreIsolatedStateVersion1		(GS::IChannel& ic, const GS::InputFrame& frame);

			GSErrCode		WriteIsolatedStateVersion1			(GS::OChannel& oc, const GS::OutputFrame& frame) const;
			GSErrCode		ReadIsolatedStateVersion1			(GS::IChannel& ic, const GS::InputFrame& frame);

			GSErrCode		WriteTWIsolatedStateVersion1		(GS::OChannel& oc, const GS::OutputFrame& frame) const;
			GSErrCode		ReadTWIsolatedStateVersion1			(GS::IChannel& ic, const GS::InputFrame& frame);

};


typedef ODB::Ref<AssignInfo>		AssignInfoRef;
typedef ODB::ConstRef<AssignInfo>	AssignInfoConstRef;


}	// namespace PRMU

#endif		// PRMUASSIGNINFO_HPP
