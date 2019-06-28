
// *****************************************************************************
//
//                           Classes Ref and ConstRef
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ODBREFERENCE_HPP
#define ODBREFERENCE_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "ODBBase.hpp"

#include "ObjectInfo.hpp"

#include <functional>


namespace ODB { class Object; }
namespace ODB { class Database; }
namespace ODB { ODB_DLL_EXPORT extern Database& fakeDatabase; }
namespace ODB { class IdSpace; }
namespace ODB { class DynamicClass; }
namespace ODB { template <class Type> class Ref; }
namespace ODB { template <class Type> class ConstRef; }
namespace ODB { template <class Type> class RefList; }
namespace ODB { template <class Type> class ConstRef; }
namespace ODB { template <class Type> class ConstRefList; }
namespace GS { template <class Type, USize BufferCapacity> class ArrayFB; }


// -------------------------------- Definitions --------------------------------

#if defined (DEBUVERS)
#define CHECK_DATABASE_QUERY_FOR_CURRENT_THREAD		   CheckDatabaseQueryForCurrentThread ();
#define CHECK_DATABASE_MODIFICATION_FOR_CURRENT_THREAD CheckDatabaseModificationForCurrentThread ();
#else
#define CHECK_DATABASE_QUERY_FOR_CURRENT_THREAD
#define CHECK_DATABASE_MODIFICATION_FOR_CURRENT_THREAD
#endif


// ========================== Class CommonRefUntyped ===========================

namespace ODB {

enum ReferToExistingSelector {	// refer to existing object, don't create new external reference
	ReferToExisting
};

enum IdRecalculationLevel {		// controls recalculation of identifiers of objects with dependent identity
	MultiLevelIdRecalculation,		// identifiers are recalculated across all levels
	SingleLevelIdRecalculation		// identifiers are recalculated from the parent level only
};

enum ReferToObjectSelector { ReferToObject };
enum AcquireInfoSelector { AcquireInfo };
enum PassInfoSelector { PassInfo };

typedef GS::ArrayFB<Id, 8> ContextIdList;

static const UInt64 ObjectTraceLine1 = ObjectInfo::ObjectTraceLine1;
static const UInt64 ObjectTraceLine2 = ObjectInfo::ObjectTraceLine2;
static const UInt64 ObjectTraceLine3 = ObjectInfo::ObjectTraceLine3;
static const UInt64 LinkTraceLine1	 = ObjectInfo::LinkTraceLine1;

ODB_DLL_EXPORT extern const GS::SerializationContext::Pointer	DeletedObjectIdSelector;

enum IdType { CurrentId, OriginalId };

typedef std::function<IdType (const ConstRef<Object>& object)> DeletedObjectIdSelectorFunction;


template <class Type>
constexpr bool	IsObject = GS::IsCompatible<Type, Object>;


class ODB_DLL_EXPORT CommonRefUntyped {
private:
	static GS::ClassInfo classInfo;

protected:
	ObjectInfo* info;	// stores information about the referred object

	friend class Pin;					// to allow the Pin class to access the info record
	friend class EventReceptionLock;	// to allow the EventReceptionLock class to access the info record

	static ObjectInfo*		NewObjectInfo (Object* target);

	void	Init (const Id& id, IdSpace* idSpace = nullptr);
	void	Init (ReferToExistingSelector, const Id& id, const IdSpace* idSpace = nullptr);

	inline void	AcquireObjectInfo (void);
	inline void	ReleaseObjectInfo (void);
	void		SetObjectInfo	  (ObjectInfo* newInfo);
	void		DeleteObjectInfo  (void);

	void		ProcessQueryRequestRelatedFlags		   (void) const;
	Object*		ProcessLogicalConstModificationRequest (void) const;
	void		ProcessLinkModificationRelatedFlags	   (void) const;

	void		InitializeLazyData	 (void) const;
	void		CalculateDerivedData (void) const;

	Id			CalculateContextId (const GS::Guid& classId, const Id* contextIdFromContent, const ContextIdList& contextIdList) const;

	GSErrCode	ReidentifyContextIdVersion2 (GS::IChannel& ic, Id* reidentifiedId);
	GSErrCode	ReidentifyContextIdVersion3 (GS::IChannel& ic, Id* reidentifiedId);

	ConstRef<Object>	GetScope (void) const;

	GSErrCode	ReadRefVersion1 (GS::IChannel& ic, IdSpace* inputIdSpace);
	GSErrCode	ReadRefVersion2 (GS::IChannel& ic, IdSpace* inputIdSpace);
	GSErrCode	ReadRefVersion3 (GS::IChannel& ic, IdSpace* inputIdSpace);
	GSErrCode	ReadRefVersion4 (GS::IChannel& ic, IdSpace* inputIdSpace);
	GSErrCode	ReadRefVersion5 (GS::IChannel& ic, IdSpace* inputIdSpace);
	GSErrCode	ReadRefVersion6 (GS::IChannel& ic, IdSpace* inputIdSpace);

	GSErrCode	WriteRefVersion1 (const Id& id, GS::OChannel& oc) const;
	GSErrCode	WriteRefVersion2 (const Id& id, GS::OChannel& oc) const;
	GSErrCode	WriteRefVersion3 (const Id& id, GS::OChannel& oc) const;
	GSErrCode	WriteRefVersion4 (const Id& id, GS::OChannel& oc) const;
	GSErrCode	WriteRefVersion5 (const Id& id, GS::OChannel& oc) const;
	GSErrCode	WriteRefVersion6 (GS::OChannel& oc) const;

	GSErrCode	WriteOriginalRefVersion6 (GS::OChannel& oc) const;

	bool		ClassHasOldOutputVersion	   (void) const;
	bool		OldClassVersionWasContextBased (void) const;
	bool		OldClassVersionWasContentBased (void) const;

	void		CheckDatabaseQueryForCurrentThread		  (void) const;
	void		CheckDatabaseModificationForCurrentThread (void) const;

	void		DeleteTarget (void);

public:
		// Identifier query and generation

	inline const Id&	GetId         (void) const;
	inline const Id&	GetOriginalId (void) const;
	inline bool			HasId         (void) const;
	inline bool			HasOriginalId (void) const;

	void				SetId (const Id& id, IdSpace* idSpace = nullptr) const;

	void				GenerateId		  (IdSpace* idSpace = nullptr) const;
	Id					GenerateContextId (void) const;
	Id					GenerateContentId (void) const;

	Id					CalculateContextId (const ContextIdList& contextIdList) const;
	Id					CalculateContentId (const Id& scopeId) const;
	static Id			CalculateContentId (const GS::Guid& classId, const Id& contentId, const Id& scopeId);

	void				RegenerateId		 (void) const;
	Id					RecalculateId		 (IdRecalculationLevel level = MultiLevelIdRecalculation) const;
	Id					RecalculateContextId (IdRecalculationLevel level = MultiLevelIdRecalculation) const;
	Id					RecalculateContentId (IdRecalculationLevel level = MultiLevelIdRecalculation) const;

	void				GetDirectIdGenerators (RefList<Object>* result) const;
	void				GetDirectIdGenerators (ConstRefList<Object>* result) const;

	inline bool			HasContentBasedIdentity	(void) const;
	inline void			SetContentBasedIdentity (void) const;
	inline void			ClearContentBasedIdentity (void) const;

	inline bool			HasContextBasedIdentity (void) const;
	inline void			SetContextBasedIdentity (void) const;
	inline void			ClearContextBasedIdentity (void) const;

	inline bool			HasIndependentIdentity (void) const;
	inline bool			HasDependentIdentity   (void) const;

		// Location query

	inline bool		IsNull      (void) const;
	inline bool		IsAvailable (void) const;
	inline bool		HadInternalLinks (void) const;

	inline IdSpace*	GetIdSpace (void) const;
	inline IdSpace*	GetOriginalIdSpace (void) const;

	inline Database*	GetDatabase  (void) const;
	inline bool			IsInDatabase (void) const;

		// Constness query

	inline bool		IsConst		   (void) const;
	inline bool		IsLogicalConst (void) const;

		// Modification control

	inline UInt64	GetCreationStamp			(void) const;
	inline UInt64	GetCurrentCreationStamp     (void) const;
	inline UInt64	GetModificationStamp		(void) const;
	inline UInt64	GetCurrentModificationStamp (void) const;

	inline bool		IsModifiedInSessionAfter (UInt64 startModificationStamp) const;

	inline bool		IsObjectModifiedOnTraceLine		   (UInt64 objectTraceLine) const;
	inline void		RestartObjectModificationTraceLine (UInt64 objectTraceLine) const;

	inline void		SetNotificationOnDelete (void) const;

		// Swap control

	inline void		Pin      (bool loadIfExternal = true) const;
	inline void		Unpin    (void) const;
	inline bool		IsPinned (void) const;

		// Meta data query

	ODB_FORCE_INLINE const GS::ClassInfo*	GetClassInfo (void) const;
	ODB_FORCE_INLINE bool					HasClassInfo (void) const;
	ODB_FORCE_INLINE const GS::Guid&		GetClassId	 (void) const;
	ODB_FORCE_INLINE bool					HasClassId	 (void) const;

	const DynamicClass*						GetDynamicClass (void) const;
	bool									HasDynamicClass (void) const;


		// Dynamic property query

	inline bool		HasOwnerObject (void) const;
	inline bool		HasOwnerLink   (void) const;
	inline bool		HasOwner	   (void) const;

	inline bool		IsSharedByAssociation (void) const;
	inline bool		IsSharedByReference (void) const;

	inline bool		IsDerived (void) const;

	inline UInt32	GetDataLayer (void) const;

		// I/O

	GSErrCode			ReadRef			 (GS::IChannel& ic, IdSpace* inputIdSpace = nullptr);
	GSErrCode			WriteRef		 (GS::OChannel& oc) const;
	GSErrCode			WriteOriginalRef (GS::OChannel& oc) const;
	inline GSErrCode	WriteId			 (GS::OChannel& oc) const;

	GSErrCode		ReadRefXML  (GS::XMLIChannel& ic, IdSpace* inputIdSpace = nullptr);
	GSErrCode		WriteRefXML (GS::XMLOChannel& oc) const;

		// Other

	ODB_FORCE_INLINE ULong	GenerateHashValue (void) const;

		// Module private methods

#ifdef ODB_MODULE_PRIVATE

	inline void		SetAsCore	 (void) const;
	inline void		SetAsDerived (void) const;

	inline bool		IsInternal  (void) const;
	inline bool		IsExternal  (void) const;

	inline bool		WasInternal (void) const;
	inline bool		IsDeleting  (void) const;

	inline bool		IsLoadingObject (void) const;
	inline bool		IsLoadingLinks  (void) const;

	inline void		PrintFlags (char (&result)[1024]) const;

	inline UChar	GetPersistentFlags (void) const;
	inline void		SetPersistentFlags (UChar newPersistentFlags) const;

	inline void		MarkObjectAsModifiedOnTraceLine (UInt64 objectTraceLine) const;

	inline bool		HasLinkModificationOnTraceLine	 (UInt64 linkTraceLine) const;
	inline void		RestartLinkModificationTraceLine (UInt64 linkTraceLine) const;

	inline void		SetObjectOwnership	 (void) const;
	inline void		ClearObjectOwnership (void) const;

	inline ULong	GetReferenceCounter (void) const;

	inline UShort	GetAccessLevel (void) const;
	inline void		SetAccessLevel (UShort newAccessLevel) const;

	inline ObjectDataStore*			GetDataStore (void) const;
	inline void						SetDataStore (ObjectDataStore* newDataStore) const;

	inline const ObjectDataStore*	GetLinks		   (void) const;
	inline const ObjectDataStore*	GetCurrentLinks	   (void) const;
	inline ObjectDataStore*			ModifyLinks		   (void) const;
	inline ObjectDataStore*			ModifyCurrentLinks (void) const;

	inline const ObjectDataStore*	GetIndices			 (void) const;
	inline const ObjectDataStore*	GetCurrentIndices	 (void) const;
	inline ObjectDataStore*			ModifyIndices		 (void) const;
	inline ObjectDataStore*			ModifyCurrentIndices (void) const;

	inline bool		IsObjectModificationNotificationForRingStarted (void) const;
	inline void		StartObjectModificationNotificationForRing	   (void) const;
	inline void		StopObjectModificationNotificationForRing	   (void) const;

	inline bool		IsObjectModificationNotificationForTimelineStarted (void) const;
	inline void		StartObjectModificationNotificationForTimeline	   (void) const;
	inline void		StopObjectModificationNotificationForTimeline	   (void) const;

	inline bool		IsLinkModificationNotificationForTimelineStarted (void) const;
	inline void		StartLinkModificationNotificationForTimeline	 (void) const;
	inline void		StopLinkModificationNotificationForTimeline		 (void) const;

	inline bool		IsNotificationOnDeleteSet (void) const;
	inline void		ClearNotificationOnDelete (void) const;

	inline bool		IsLogicalConstModifiableWithoutModificationScope (void) const;

	inline bool		GetCheckFlag1	(void) const;
	inline void		SetCheckFlag1	(void) const;
	inline void		ClearCheckFlag1 (void) const;

	inline bool		AreObjectDeletionCheckFlagsCleared (void) const;

	inline void		LoadLinks (void) const;

#endif

	inline const Object* GetConstMemoryAddress (void) const;
	
	inline void		EnableEventReception  (void) const;
	inline void		DisableEventReception (void) const;
	
	inline bool		IsModifiableWithoutModificationScope (void) const;
	
	inline void		MarkObjectAsModified (void) const;
	inline void		MarkWithLinkModification (void) const;
	
	ODB_FORCE_INLINE ObjectInfo*	GetObjectInfo (void) const;
};


inline GSErrCode	Read  (GS::IChannel& ic, CommonRefUntyped& ref);
inline GSErrCode	Write (GS::OChannel& oc, const CommonRefUntyped& ref);

inline GSErrCode	WriteOriginal (GS::OChannel& oc, const CommonRefUntyped& ref);

ODB_FORCE_INLINE ULong	GenerateHashValue (const CommonRefUntyped& target);

GS_FORCE_INLINE void	Append (GS::FastLogger::LogComposer& logComposer, const CommonRefUntyped& ref);

}	// namespace ODB



inline void		ODB::CommonRefUntyped::AcquireObjectInfo (void)
{
	info->Acquire ();
}


inline void		ODB::CommonRefUntyped::ReleaseObjectInfo (void)
{
    UInt32 newReferenceCounter = info->Release ();

    if (newReferenceCounter <= 1) {			// optimization: one test is used for special cases
        if (newReferenceCounter == 0)
            DeleteObjectInfo ();
        else if (info->IsAutoDeletable ())	// object is internal and has one reference (thisRef) and is shared by reference so it should be deleted
            DeleteTarget ();
    }
}



inline const ODB::Id&	ODB::CommonRefUntyped::GetId (void) const
{
	return info->GetId ();
}


inline const ODB::Id&	ODB::CommonRefUntyped::GetOriginalId (void) const
{
	return info->GetOriginalId ();
}


inline bool		ODB::CommonRefUntyped::HasId (void) const
{
	return info->HasId ();
}


inline bool		ODB::CommonRefUntyped::HasOriginalId (void) const
{
	return info->HasOriginalId ();
}


inline bool		ODB::CommonRefUntyped::HasContentBasedIdentity (void) const
{
	return info->HasContentBasedIdentity ();
}


inline void		ODB::CommonRefUntyped::SetContentBasedIdentity (void) const
{
	info->SetContentBasedIdentity ();
}


inline void		ODB::CommonRefUntyped::ClearContentBasedIdentity (void) const
{
	info->ClearContentBasedIdentity ();
}


inline bool		ODB::CommonRefUntyped::HasContextBasedIdentity (void) const
{
	return info->HasContextBasedIdentity ();
}

inline void		ODB::CommonRefUntyped::SetContextBasedIdentity (void) const
{
	info->SetContextBasedIdentity ();
}


inline void		ODB::CommonRefUntyped::ClearContextBasedIdentity (void) const
{
	info->ClearContextBasedIdentity ();
}


inline bool		ODB::CommonRefUntyped::HasIndependentIdentity (void) const
{
	return info->HasIndependentIdentity ();
}


inline bool		ODB::CommonRefUntyped::HasDependentIdentity (void) const
{
	return info->HasDependentIdentity ();
}


inline bool		ODB::CommonRefUntyped::IsNull (void) const
{
	return info->IsNull ();
}


inline bool		ODB::CommonRefUntyped::IsAvailable (void) const
{
	return info->IsAvailable ();
}


inline bool		ODB::CommonRefUntyped::HadInternalLinks (void) const
{
	return info->HadInternalLinks ();
}


inline ODB::IdSpace*	ODB::CommonRefUntyped::GetIdSpace (void) const
{
	return info->GetIdSpace ();
}


inline ODB::IdSpace*	ODB::CommonRefUntyped::GetOriginalIdSpace (void) const
{
	return info->GetOriginalIdSpace ();
}


inline ODB::Database*	ODB::CommonRefUntyped::GetDatabase (void) const
{
	return info->GetDatabase ();
}


inline bool		ODB::CommonRefUntyped::IsInDatabase (void) const
{
	return (info->GetDatabase () != &fakeDatabase);
}


inline bool		ODB::CommonRefUntyped::IsConst (void) const
{
	return info->IsConst ();
}


inline bool		ODB::CommonRefUntyped::IsLogicalConst (void) const
{
	return info->IsLogicalConst ();
}


inline UInt64	ODB::CommonRefUntyped::GetCreationStamp (void) const
{
	return info->GetCreationStamp ();
}


inline UInt64	ODB::CommonRefUntyped::GetCurrentCreationStamp (void) const
{
	return info->GetCurrentCreationStamp ();
}


inline UInt64	ODB::CommonRefUntyped::GetModificationStamp (void) const
{
	return info->GetModificationStamp ();
}


inline UInt64	ODB::CommonRefUntyped::GetCurrentModificationStamp (void) const
{
	return info->GetCurrentModificationStamp ();
}


inline bool		ODB::CommonRefUntyped::IsModifiedInSessionAfter (UInt64 startModificationStamp) const
{
	return info->IsModifiedInSessionAfter (startModificationStamp);
}


inline bool		ODB::CommonRefUntyped::IsObjectModifiedOnTraceLine (UInt64 objectTraceLine) const
{
	return info->IsObjectModifiedOnTraceLine (objectTraceLine);
}


inline void		ODB::CommonRefUntyped::RestartObjectModificationTraceLine (UInt64 objectTraceLine) const
{
	info->RestartObjectModificationTraceLine (objectTraceLine);
}


inline void		ODB::CommonRefUntyped::SetNotificationOnDelete (void) const
{
	info->SetNotificationOnDelete ();
}


inline void		ODB::CommonRefUntyped::Pin (bool loadIfExternal) const
{
	if (loadIfExternal)
		info->GetMemoryAddress ();	// loads the object into the memory if it is external

	info->Pin ();
}


inline void		ODB::CommonRefUntyped::Unpin (void) const
{
	info->Unpin ();
}


inline bool		ODB::CommonRefUntyped::IsPinned (void) const
{
	return info->IsPinned ();
}


ODB_FORCE_INLINE const GS::ClassInfo*	ODB::CommonRefUntyped::GetClassInfo (void) const
{
	return info->GetClassInfo ();
}


ODB_FORCE_INLINE bool	ODB::CommonRefUntyped::HasClassInfo (void) const
{
	return info->HasClassInfo ();
}


ODB_FORCE_INLINE const GS::Guid&	ODB::CommonRefUntyped::GetClassId (void) const
{
	return info->GetClassId ();
}


ODB_FORCE_INLINE bool	ODB::CommonRefUntyped::HasClassId (void) const
{
	return info->HasClassId ();
}


inline bool		ODB::CommonRefUntyped::HasOwnerObject (void) const
{
	return info->HasOwnerObject ();
}


inline bool		ODB::CommonRefUntyped::HasOwnerLink (void) const
{
	return info->HasOwnerLink ();
}


inline bool		ODB::CommonRefUntyped::HasOwner (void) const
{
	return info->HasOwner ();
}


inline bool		ODB::CommonRefUntyped::IsSharedByAssociation (void) const
{
	return info->IsSharedByAssociation ();
}


inline bool		ODB::CommonRefUntyped::IsSharedByReference (void) const
{
	return info->IsSharedByReference ();
}


inline bool		ODB::CommonRefUntyped::IsDerived (void) const
{
	return info->IsDerived ();
}


inline UInt32	ODB::CommonRefUntyped::GetDataLayer (void) const
{
	return info->GetDataLayer (); 
}


inline GSErrCode	ODB::CommonRefUntyped::WriteId (GS::OChannel& oc) const
{
	return info->GetId ().Write (oc);
}


ODB_FORCE_INLINE ULong	ODB::CommonRefUntyped::GenerateHashValue (void) const
{
#if defined (GS_64BIT)
	return static_cast<ULong> ((((UInt64) info >> 32) & 0xFFFFFFFFUL) + ((UInt64) info & 0xFFFFFFFFUL));;
#else
	return (ULong)(GS::UIntPtr) info;
#endif
}


GS_FORCE_INLINE void	ODB::Append (GS::FastLogger::LogComposer& logComposer, const CommonRefUntyped& ref)
{
	logComposer.Append (ref.GetId ().ToGuid ());
}


#ifdef ODB_MODULE_PRIVATE

inline void		ODB::CommonRefUntyped::SetAsCore (void) const
{
	info->SetAsCore ();
}


inline void		ODB::CommonRefUntyped::SetAsDerived (void) const
{
	info->SetAsDerived ();
}


inline bool		ODB::CommonRefUntyped::IsInternal (void) const
{
	return info->IsInternal ();
}


inline bool		ODB::CommonRefUntyped::IsExternal (void) const
{
	return info->IsExternal ();
}


inline bool		ODB::CommonRefUntyped::WasInternal (void) const
{
	return info->WasInternal ();
}


inline bool		ODB::CommonRefUntyped::IsDeleting (void) const
{
	return info->IsDeleting ();
}


inline bool		ODB::CommonRefUntyped::IsLoadingObject (void) const
{
	return info->IsLoadingObject ();
}


inline bool		ODB::CommonRefUntyped::IsLoadingLinks (void) const
{
	return info->IsLoadingLinks ();
}


inline void		ODB::CommonRefUntyped::PrintFlags (char (&result)[1024]) const
{
	return info->PrintFlags (result);
}


inline UChar	ODB::CommonRefUntyped::GetPersistentFlags (void) const
{
	return info->GetPersistentFlags ();
}


inline void		ODB::CommonRefUntyped::SetPersistentFlags (UChar newPersistentFlags) const
{
	info->SetPersistentFlags (newPersistentFlags);
}


inline void		ODB::CommonRefUntyped::MarkObjectAsModifiedOnTraceLine (UInt64 objectTraceLine) const
{
	info->MarkObjectAsModifiedOnTraceLine (objectTraceLine);
}


inline bool		ODB::CommonRefUntyped::HasLinkModificationOnTraceLine (UInt64 linkTraceLine) const
{
	return info->HasLinkModificationOnTraceLine (linkTraceLine);
}


inline void		ODB::CommonRefUntyped::RestartLinkModificationTraceLine (UInt64 linkTraceLine) const
{
	info->RestartLinkModificationTraceLine (linkTraceLine);
}


inline void		ODB::CommonRefUntyped::SetObjectOwnership (void) const
{
	info->SetObjectOwnership ();
}


inline void		ODB::CommonRefUntyped::ClearObjectOwnership (void) const
{
	info->ClearObjectOwnership ();
}


inline ULong	ODB::CommonRefUntyped::GetReferenceCounter (void) const
{
	return info->GetReferenceCounter ();
}


inline UShort	ODB::CommonRefUntyped::GetAccessLevel (void) const
{
	return info->GetAccessLevel ();
}


inline void		ODB::CommonRefUntyped::SetAccessLevel (UShort newAccessLevel) const
{
	info->SetAccessLevel (newAccessLevel);
}


inline ODB::ObjectDataStore*	ODB::CommonRefUntyped::GetDataStore (void) const
{
	return info->GetDataStore ();
}


inline void		ODB::CommonRefUntyped::SetDataStore (ObjectDataStore* newDataStore) const
{
	info->SetDataStore (newDataStore);
}


inline const ODB::ObjectDataStore*	ODB::CommonRefUntyped::GetLinks (void) const
{
	return info->GetLinks ();
}


inline const ODB::ObjectDataStore*	ODB::CommonRefUntyped::GetCurrentLinks (void) const
{
	return info->GetCurrentLinks ();
}


inline ODB::ObjectDataStore*	ODB::CommonRefUntyped::ModifyLinks (void) const
{
	if (info->IsLinkModificationNotificationForTimelineStarted () && !info->IsLoadingLinks ())	// !IsLoadingLinks: loaded links are currently stored with link modification
		ProcessLinkModificationRelatedFlags ();

	return info->ModifyLinks ();
}


inline ODB::ObjectDataStore*	ODB::CommonRefUntyped::ModifyCurrentLinks (void) const
{
	if (info->IsLinkModificationNotificationForTimelineStarted ())
		ProcessLinkModificationRelatedFlags ();

	return info->ModifyCurrentLinks ();
}


inline const ODB::ObjectDataStore*	ODB::CommonRefUntyped::GetIndices (void) const
{
	return info->GetIndices ();
}


inline const ODB::ObjectDataStore*	ODB::CommonRefUntyped::GetCurrentIndices (void) const
{
	return info->GetCurrentIndices ();
}


inline ODB::ObjectDataStore*	ODB::CommonRefUntyped::ModifyIndices (void) const
{
	return info->ModifyIndices ();
}


inline ODB::ObjectDataStore*	ODB::CommonRefUntyped::ModifyCurrentIndices (void) const
{
	return info->ModifyCurrentIndices ();
}


inline bool		ODB::CommonRefUntyped::IsObjectModificationNotificationForRingStarted (void) const
{
	return info->IsObjectModificationNotificationForRingStarted ();
}


inline void		ODB::CommonRefUntyped::StartObjectModificationNotificationForRing (void) const
{
	info->StartObjectModificationNotificationForRing ();
}


inline void		ODB::CommonRefUntyped::StopObjectModificationNotificationForRing (void) const
{
	info->StopObjectModificationNotificationForRing ();
}


inline bool		ODB::CommonRefUntyped::IsObjectModificationNotificationForTimelineStarted (void) const
{
	return info->IsObjectModificationNotificationForTimelineStarted ();
}


inline void		ODB::CommonRefUntyped::StartObjectModificationNotificationForTimeline (void) const
{
	info->StartObjectModificationNotificationForTimeline ();
}


inline void		ODB::CommonRefUntyped::StopObjectModificationNotificationForTimeline (void) const
{
	info->StopObjectModificationNotificationForTimeline ();
}


inline bool		ODB::CommonRefUntyped::IsLinkModificationNotificationForTimelineStarted (void) const
{
	return info->IsLinkModificationNotificationForTimelineStarted ();
}


inline void		ODB::CommonRefUntyped::StartLinkModificationNotificationForTimeline (void) const
{
	info->StartLinkModificationNotificationForTimeline ();
}


inline void		ODB::CommonRefUntyped::StopLinkModificationNotificationForTimeline (void) const
{
	info->StopLinkModificationNotificationForTimeline ();
}


inline bool		ODB::CommonRefUntyped::IsNotificationOnDeleteSet (void) const
{
	return info->IsNotificationOnDeleteSet ();
}


inline void		ODB::CommonRefUntyped::ClearNotificationOnDelete (void) const
{
	info->ClearNotificationOnDelete ();
}


inline bool   ODB::CommonRefUntyped::IsLogicalConstModifiableWithoutModificationScope (void) const
{
	return info->IsLogicalConstModifiableWithoutModificationScope ();
}


inline bool		ODB::CommonRefUntyped::GetCheckFlag1 (void) const
{
	return info->GetCheckFlag1 ();
}


inline void		ODB::CommonRefUntyped::SetCheckFlag1 (void) const
{
	info->SetCheckFlag1 ();
}


inline void		ODB::CommonRefUntyped::ClearCheckFlag1 (void) const
{
	info->ClearCheckFlag1 ();
}


inline bool		ODB::CommonRefUntyped::AreObjectDeletionCheckFlagsCleared (void) const
{
	return info->AreObjectDeletionCheckFlagsCleared ();
}


inline void		ODB::CommonRefUntyped::LoadLinks (void) const
{
	info->GetLinks ();
}

#endif


inline const ODB::Object*	ODB::CommonRefUntyped::GetConstMemoryAddress (void) const
{
	return info->GetMemoryAddress ();
}


inline void		ODB::CommonRefUntyped::EnableEventReception (void) const
{
	info->EnableEventReception ();
}


inline void		ODB::CommonRefUntyped::DisableEventReception (void) const
{
	info->DisableEventReception ();
}


inline bool   ODB::CommonRefUntyped::IsModifiableWithoutModificationScope (void) const
{
	return info->IsModifiableWithoutModificationScope ();
}


inline void		ODB::CommonRefUntyped::MarkObjectAsModified (void) const
{
	info->MarkObjectAsModified ();
}


inline void		ODB::CommonRefUntyped::MarkWithLinkModification (void) const
{
	info->MarkWithLinkModification ();
}


ODB_FORCE_INLINE ODB::ObjectInfo*	ODB::CommonRefUntyped::GetObjectInfo (void) const
{
	return info;
}


inline GSErrCode	ODB::Read (GS::IChannel& ic, CommonRefUntyped& ref)
{
	return ref.ReadRef (ic);
}


inline GSErrCode	ODB::Write (GS::OChannel& oc, const CommonRefUntyped& ref)
{
	return ref.WriteRef (oc);
}


inline GSErrCode	ODB::WriteOriginal (GS::OChannel& oc, const ODB::CommonRefUntyped& ref)
{
	return ref.WriteOriginalRef (oc);
}


ODB_FORCE_INLINE ULong	ODB::GenerateHashValue (const CommonRefUntyped& target)
{
	return target.GenerateHashValue ();
}
// __________________________ Class CommonRefUntyped ___________________________



// ============================= Class RefUntyped ==============================

namespace ODB {

enum LogicalConstSelector {
	LogicalConst				// indicates modification that doesn't affect the user level logical state of
};								// the object, only the implementation level

enum ModificationAuthorizationControl {		// controls the checking of the authorization to modify the object
	CheckModificationAuthorization,				// check the authorization to modify the object
	IgnoreModificationAuthorization				// ignore the authorization to modify the object
};


class ODB_DLL_EXPORT RefUntyped: public CommonRefUntyped {
protected:
	Object*		ProcessModificationRequest (void) const;
	Object*		ProcessModificationRequest (ModificationAuthorizationControl control) const;

	Object*		ProcessPointerConversionRequest (void) const;

public:
		// Reviving

	GSErrCode		Revive (IdSpace* idSpace = nullptr) const;

		// Modification control

	inline void		SetAsConst     (void) const;
	inline void		ClearConstness (void) const;

	inline void		SetAsLogicalConst     (void) const;
	inline void		ClearLogicalConstness (void) const;

	inline bool		IsDeletingEnabled (void) const;
	inline void		EnableDeleting	  (void) const;
	inline void		DisableDeleting	  (void) const;

	inline bool		IsAuthorizedToModify             (void) const;
	inline void		AcquireModificationAuthorization (void) const;
	inline void		ReleaseModificationAuthorization (void) const;

	inline bool		IsAuthorizedToLogicallyModify           (void) const;
	inline void		AcquireLogicalModificationAuthorization (void) const;
	inline void		ReleaseLogicalModificationAuthorization (void) const;

	inline bool		IsModifiable			 (void) const;
	inline bool		IsLogicalConstModifiable (void) const;
	inline bool		IsDeletable				 (void) const;

		// Lazy and derived data management

	inline bool		HasLazyDataToBeInitialized	(void) const;
	inline void		SetLazyDataInitialization	(void) const;
	inline void		ClearLazyDataInitialization	(void) const;

	inline bool		HasDerivedDataToBeInitialized  (void) const;
	inline void		SetDerivedDataInitialization   (void) const;
	inline void		ClearDerivedDataInitialization (void) const;

		// Module private methods

/* Module private method!!! */	void			SetIdSpace (IdSpace* newIdSpace) const;

/* Module private method!!! */	inline void		SetDatabase   (Database* newDatabase) const;
/* Module private method!!! */	inline void		ClearDatabase (void) const;

/* Module private method!!! */	void			ChangeId	(const Id& newId, IdSpace* newIdSpace) const;
/* Module private method!!! */	void			Reidentify	(void) const;
/* Module private method!!! */	void			Reidentify	(const Id& newId) const;

/* Module private method!!! */	inline void		SetCreationStamp     (UInt64 newCreationStamp) const;
/* Module private method!!! */	inline void		SetModificationStamp (UInt64 newModificationStamp) const;

/* Module private method!!! */	inline void		SetLinkOwnership   (void) const;
/* Module private method!!! */	inline void		ClearLinkOwnership (void) const;

/* Module private method!!! */	inline void		MarkAsSharedByAssociation (void) const;
/* Module private method!!! */	inline void		ClearSharingByAssociation (void) const;

/* Module private method!!! */	inline void		MarkAsSharedByReference (void) const;
/* Module private method!!! */	inline void		ClearSharingByReference (void) const;

/* Module private method!!! */	inline void		SetContextBasedIdentity	  (void) const;
/* Module private method!!! */	inline void		ClearContextBasedIdentity (void) const;

/* Module private method!!! */	inline bool		IsClockFlagSet (void) const;
/* Module private method!!! */	inline void		SetClockFlag   (void) const;
/* Module private method!!! */	inline void		ClearClockFlag (void) const;

/* Module private method!!! */	inline bool		BecomesExternalOnDelete   (void) const;
/* Module private method!!! */	inline void		SetExternalOnDeleteMode   (void) const;
/* Module private method!!! */	inline void		ClearExternalOnDeleteMode (void) const;

/* Module private method!!! */	inline bool		IsEventReceptionEnabled (void) const;

/* Module private method!!! */	inline UInt64	GetTransactionRelatedFlags  (void) const;
/* Module private method!!! */	inline void		SetTransactionRelatedFlags  (UInt64 newFlags) const;

/* Module private method!!! */	inline Object*	GetMemoryAddress   (void) const;
/* Module private method!!! */	inline void		SetTarget          (const GS::ClassInfo* classInfo, Object* object) const;
/* Module private method!!! */	inline void		SetClassInfo       (const GS::ClassInfo* classInfo) const;
/* Module private method!!! */	void			SetAsDeleted       (void) const;
/* Module private method!!! */	inline void		SetAsDeleting      (void) const;
/* Module private method!!! */	inline void		SetAsExternal      (void) const;
/* Module private method!!! */	inline void		ClearWasInternalFlag (void) const;
/* Module private method!!! */	inline void		SetAsLoadable	   (void) const;
/* Module private method!!! */	inline void		ClearLoadableFlag  (void) const;
/* Module private method!!! */	inline void		SetAsLoadingObject (void) const;
/* Module private method!!! */	inline void		ClearLoadingObject (void) const;
/* Module private method!!! */	inline void		SetAsLoadingLinks  (void) const;
/* Module private method!!! */	inline void		ClearLoadingLinks  (void) const;
/* Module private method!!! */	inline bool		HasExternalLinks	   (void) const;
/* Module private method!!! */	inline void		MarkWithExternalLinks  (void) const;
/* Module private method!!! */	inline void		ClearExternalLinksFlag (void) const;
/* Module private method!!! */	inline void		MarkAsHadInternalLinks (void) const;
/* Module private method!!! */	inline void		ClearHadInternalLinksFlag (void) const;
/* Module private method!!! */	inline bool		AreLinksAvailable (void) const;
/* Module private method!!! */	inline void		MarkAsLinksAreAvailable   (void) const;
/* Module private method!!! */	inline void		MarkAsLinksAreUnavailable (void) const;

/* Module private method!!! */	inline void		StartAssociationIndexNotification (void) const;
/* Module private method!!! */	inline void		StopAssociationIndexNotification  (void) const;


	class ODB_DLL_EXPORT ClassForDeleteAndBoolConversion {
	private:
		static void		Delete (void* pointer);

	public:
		ODB_FORCE_INLINE void	operator delete (void* pointer) noexcept (false) { if (pointer != nullptr) Delete (pointer); }
	};

/* Module private method!!! */	ODB_FORCE_INLINE operator ClassForDeleteAndBoolConversion* () const;

};

}	// namespace ODB



inline void		ODB::RefUntyped::SetAsConst (void) const
{
	info->SetAsConst ();
}


inline void		ODB::RefUntyped::ClearConstness (void) const
{
	info->ClearConstness ();
}


inline void		ODB::RefUntyped::SetAsLogicalConst (void) const
{
	info->SetAsLogicalConst ();
}


inline void		ODB::RefUntyped::ClearLogicalConstness (void) const
{
	info->ClearLogicalConstness ();
}


inline bool		ODB::RefUntyped::IsDeletingEnabled (void) const
{
	return info->IsDeletingEnabled ();
}


inline void		ODB::RefUntyped::EnableDeleting (void) const
{
	info->EnableDeleting ();
}


inline void		ODB::RefUntyped::DisableDeleting (void) const
{
	info->DisableDeleting ();
}


inline bool		ODB::RefUntyped::IsAuthorizedToModify (void) const
{
	return info->IsAuthorizedToModify ();
}


inline void		ODB::RefUntyped::AcquireModificationAuthorization (void) const
{
	info->AcquireModificationAuthorization ();
}


inline void		ODB::RefUntyped::ReleaseModificationAuthorization (void) const
{
	info->ReleaseModificationAuthorization ();
}


inline bool		ODB::RefUntyped::IsAuthorizedToLogicallyModify (void) const
{
	return info->IsAuthorizedToLogicallyModify ();
}


inline void		ODB::RefUntyped::AcquireLogicalModificationAuthorization (void) const
{
	info->AcquireLogicalModificationAuthorization ();
}


inline void		ODB::RefUntyped::ReleaseLogicalModificationAuthorization (void) const
{
	info->ReleaseLogicalModificationAuthorization ();
}


inline bool		ODB::RefUntyped::IsModifiable (void) const
{
	return info->IsModifiable ();
}


inline bool		ODB::RefUntyped::IsLogicalConstModifiable (void) const
{
	return info->IsLogicalConstModifiable ();
}


inline bool		ODB::RefUntyped::IsDeletable (void) const
{
	return info->IsDeletable ();
}


inline bool		ODB::RefUntyped::HasLazyDataToBeInitialized	(void) const
{
	return info->HasLazyDataToBeInitialized ();
}


inline void		ODB::RefUntyped::SetLazyDataInitialization (void) const
{
	info->SetLazyDataInitialization ();
}


inline void		ODB::RefUntyped::ClearLazyDataInitialization (void) const
{
	info->ClearLazyDataInitialization ();
}


inline void		ODB::RefUntyped::SetDatabase (Database* newDatabase) const
{
	info->SetDatabase (newDatabase);
}


inline void		ODB::RefUntyped::ClearDatabase (void) const
{
	info->ClearDatabase ();
}


inline void		ODB::RefUntyped::SetCreationStamp (UInt64 newCreationStamp) const
{
	info->SetCreationStamp (newCreationStamp);
}


inline void		ODB::RefUntyped::SetModificationStamp (UInt64 newModificationStamp) const
{
	info->SetModificationStamp (newModificationStamp);
}


inline void		ODB::RefUntyped::SetLinkOwnership (void) const
{
	info->SetLinkOwnership ();
}


inline void		ODB::RefUntyped::ClearLinkOwnership (void) const
{
	info->ClearLinkOwnership ();
}


inline void		ODB::RefUntyped::MarkAsSharedByAssociation (void) const
{
	info->MarkAsSharedByAssociation ();
}


inline void		ODB::RefUntyped::ClearSharingByAssociation (void) const
{
	info->ClearSharingByAssociation ();
}


inline void		ODB::RefUntyped::MarkAsSharedByReference (void) const
{
	info->MarkAsSharedByReference ();
}


inline void		ODB::RefUntyped::ClearSharingByReference (void) const
{
	info->ClearSharingByReference ();
}


inline void		ODB::RefUntyped::SetContextBasedIdentity (void) const
{
	info->SetContextBasedIdentity ();
}


inline void		ODB::RefUntyped::ClearContextBasedIdentity (void) const
{
	info->ClearContextBasedIdentity ();
}


inline bool		ODB::RefUntyped::IsClockFlagSet (void) const
{
	return info->IsClockFlagSet ();;
}


inline void		ODB::RefUntyped::SetClockFlag (void) const
{
	info->SetClockFlag ();
}


inline void		ODB::RefUntyped::ClearClockFlag (void) const
{
	info->ClearClockFlag ();
}


inline bool		ODB::RefUntyped::BecomesExternalOnDelete (void) const
{
	return info->BecomesExternalOnDelete ();;
}


inline void		ODB::RefUntyped::SetExternalOnDeleteMode (void) const
{
	info->SetExternalOnDeleteMode ();
}


inline void		ODB::RefUntyped::ClearExternalOnDeleteMode (void) const
{
	info->ClearExternalOnDeleteMode ();
}


inline bool		ODB::RefUntyped::IsEventReceptionEnabled (void) const
{
	return info->IsEventReceptionEnabled ();;
}


inline UInt64	ODB::RefUntyped::GetTransactionRelatedFlags (void) const
{
	return info->GetTransactionRelatedFlags ();
}


inline void		ODB::RefUntyped::SetTransactionRelatedFlags (UInt64 newFlags) const
{
	info->SetTransactionRelatedFlags (newFlags);
}


inline ODB::Object*		ODB::RefUntyped::GetMemoryAddress (void) const
{
	return info->GetMemoryAddress ();
}


inline void		ODB::RefUntyped::SetTarget (const GS::ClassInfo* classInfo, Object* object) const
{
	SetClassInfo (classInfo);

	info->SetMemoryAddress (object);
}


inline void		ODB::RefUntyped::SetClassInfo (const GS::ClassInfo* classInfo) const
{
	if (classInfo != nullptr)
		info->SetDefaultSpecifiableFlags (classInfo->GetObjectDefaults ());

	info->SetClassInfo (classInfo);
}


inline void		ODB::RefUntyped::SetAsDeleting (void) const
{
	info->SetAsDeleting ();
}


inline void		ODB::RefUntyped::SetAsExternal (void) const
{
	info->SetAsExternal ();
}


inline void		ODB::RefUntyped::ClearWasInternalFlag (void) const
{
	info->ClearWasInternalFlag ();
}


inline void		ODB::RefUntyped::SetAsLoadable (void) const
{
	info->SetAsLoadable ();
}


inline void		ODB::RefUntyped::ClearLoadableFlag (void) const
{
	info->ClearLoadableFlag ();
}


inline void		ODB::RefUntyped::SetAsLoadingObject (void) const
{
	info->SetAsLoadingObject ();
}


inline void		ODB::RefUntyped::ClearLoadingObject (void) const
{
	info->ClearLoadingObject ();
}


inline void		ODB::RefUntyped::SetAsLoadingLinks (void) const
{
	info->SetAsLoadingLinks ();
}


inline void		ODB::RefUntyped::ClearLoadingLinks (void) const
{
	info->ClearLoadingLinks ();
}


inline bool		ODB::RefUntyped::HasExternalLinks (void) const
{
	return info->HasExternalLinks ();
}


inline void		ODB::RefUntyped::MarkWithExternalLinks (void) const
{
	info->MarkWithExternalLinks ();
}


inline void		ODB::RefUntyped::ClearExternalLinksFlag (void) const
{
	info->ClearExternalLinksFlag ();
}


inline void		ODB::RefUntyped::MarkAsHadInternalLinks (void) const
{
	info->MarkAsHadInternalLinks ();
}


inline void		ODB::RefUntyped::ClearHadInternalLinksFlag (void) const
{
	info->ClearHadInternalLinksFlag ();
}


inline bool		ODB::RefUntyped::AreLinksAvailable (void) const
{
	return info->AreLinksAvailable ();
}


inline void		ODB::RefUntyped::MarkAsLinksAreAvailable (void) const
{
	info->MarkAsLinksAreAvailable ();
}


inline void		ODB::RefUntyped::MarkAsLinksAreUnavailable (void) const
{
	info->MarkAsLinksAreUnavailable ();
}


inline void		ODB::RefUntyped::StartAssociationIndexNotification (void) const
{
	info->StartAssociationIndexNotification ();
}


inline void		ODB::RefUntyped::StopAssociationIndexNotification (void) const
{
	info->StopAssociationIndexNotification ();
}


ODB_FORCE_INLINE ODB::RefUntyped::operator ODB::RefUntyped::ClassForDeleteAndBoolConversion* () const
{
	return reinterpret_cast<ClassForDeleteAndBoolConversion*> (info->GetMemoryAddress ());
}

// _____________________________ Class RefUntyped ______________________________

namespace ODB {

template <class Class, typename... Args>
ODB::Ref<Class> NewShared (Args&&... args)
{
	ODB::Ref<Class> ref = new Class (std::forward<Args> (args)...);
	ref.MarkAsSharedByReference ();
	return ref;
}

} // namespace ODB

// ================================= Class Ref =================================

namespace ODB {

class NullRefType;

template <class Type>
class Ref: public RefUntyped {
private:
	template <class T> friend class Ref;		// to allow different Ref<T> to access each other's members
	template <class T> friend class ConstRef;	// to allow assignment and comparison between ConstRef and Ref

	class X {};	// helper type for the safe comparison against nullptr

public:
	typedef Type ObjectType;

		// Constructors, destructor, assignment

	ODB_FORCE_INLINE Ref ();
	ODB_FORCE_INLINE Ref (std::nullptr_t);
	inline           Ref (Type* object);
	ODB_FORCE_INLINE Ref (const NullRefType&);
	ODB_FORCE_INLINE explicit Ref (const Id& id, IdSpace* idSpace = nullptr);
	ODB_FORCE_INLINE Ref (ReferToExistingSelector, const Id& id, const IdSpace* idSpace = nullptr);

	ODB_FORCE_INLINE Ref (const Ref& source);
	ODB_FORCE_INLINE Ref (Ref&& source);

	template <class SourceType>
	ODB_FORCE_INLINE Ref (const Ref<SourceType>& source);
	template <class SourceType>
	ODB_FORCE_INLINE Ref (Ref<SourceType>&& source);

	inline Ref&				operator= (Type* object);
	ODB_FORCE_INLINE Ref&	operator= (const Ref& source);
	ODB_FORCE_INLINE Ref&	operator= (Ref&& source);

	template <class SourceType>
	ODB_FORCE_INLINE Ref&	operator= (const Ref<SourceType>& source);
	template <class SourceType>
	ODB_FORCE_INLINE Ref&	operator= (Ref<SourceType>&& source);

	ODB_FORCE_INLINE ~Ref ();

		// Comparison

	ODB_FORCE_INLINE bool		operator== (const Ref& rightOp) const;
	template <class RightType>
	ODB_FORCE_INLINE bool		operator== (const Ref<RightType>& rightOp) const;
	template <class RightType>
	ODB_FORCE_INLINE bool		operator== (const ConstRef<RightType>& rightOp) const;
	ODB_FORCE_INLINE bool		operator== (const X*) const;
	ODB_FORCE_INLINE bool		operator!= (const Ref& rightOp) const;
	template <class RightType>
	ODB_FORCE_INLINE bool		operator!= (const Ref<RightType>& rightOp) const;
	template <class RightType>
	ODB_FORCE_INLINE bool		operator!= (const ConstRef<RightType>& rightOp) const;
	ODB_FORCE_INLINE bool		operator!= (const X*) const;

		// Dereferencing

	ODB_FORCE_INLINE const Type*	operator-> () const;
	ODB_FORCE_INLINE const Type&	operator* () const;
	ODB_FORCE_INLINE Type*			operator() (void) const;
	ODB_FORCE_INLINE Type*			operator() (LogicalConstSelector) const;
	ODB_FORCE_INLINE Type*			operator() (ModificationAuthorizationControl control) const;

	ODB_FORCE_INLINE Type*			ToPtr      (void) const;
	ODB_FORCE_INLINE const Type*	ToConstPtr (void) const;

		// Casting

	template <class BaseType>
	ODB_FORCE_INLINE const Ref<BaseType>&	As (void) const;

	ODB_FORCE_INLINE const Ref<Object>&		AsObject (void) const;

	ODB_FORCE_INLINE const ConstRef<Type>&	AsConst (void) const;

		// Module private methods

								
/* Module private method!!! */	inline Ref (ReferToObjectSelector, const GS::ClassInfo* classInfo, Object* target);
/* Module private method!!! */	inline Ref (AcquireInfoSelector, ObjectInfo* objectInfo);
/* Module private method!!! */	inline Ref (PassInfoSelector, ObjectInfo* objectInfo);
};


class ODB_DLL_EXPORT NullRefType: public Ref<Object> {};

ODB_DLL_EXPORT extern const NullRefType	NullRef;	// Null reference

typedef Ref<Object>	ObjectRef;

}	// namespace ODB



template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref ()
{
	info = &NullObjectInfo;
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref (std::nullptr_t)
{
	info = &NullObjectInfo;
}


template <class Type>
inline ODB::Ref<Type>::Ref (Type* object)
{
	if (object == nullptr) {
		info = &NullObjectInfo;
	} else {
		info = object->GetRef ().info;
		AcquireObjectInfo ();
	}
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref (const NullRefType&)
{
	info = &NullObjectInfo;
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref (const Id& id, IdSpace* idSpace)
{
	Init (id, idSpace);
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref (ReferToExistingSelector, const Id& id, const IdSpace* idSpace)
{
	Init (ReferToExisting, id, idSpace);
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref (const Ref& source)
{
	info = source.info;
	if (info != &NullObjectInfo)
		AcquireObjectInfo ();
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref (Ref&& source)
{
	info = source.info;
	source.info = &NullObjectInfo;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref (const Ref<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	info = source.info;
	if (info != &NullObjectInfo)
		AcquireObjectInfo ();
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref (Ref<SourceType>&& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	info = source.info;
	source.info = &NullObjectInfo;
}


template <class Type>
inline ODB::Ref<Type>&	ODB::Ref<Type>::operator= (Type* object)
{
	if (object == nullptr)
		SetObjectInfo (&NullObjectInfo);
	else
		SetObjectInfo (object->GetRef ().info);

	return *this;
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>&	ODB::Ref<Type>::operator= (const Ref& source)
{
	SetObjectInfo (source.info);

	return *this;
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>&	ODB::Ref<Type>::operator= (Ref&& source)
{
	GS::Swap (info, source.info);

	return *this;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::Ref<Type>&	ODB::Ref<Type>::operator= (const Ref<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	SetObjectInfo (source.info);

	return *this;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::Ref<Type>&	ODB::Ref<Type>::operator= (Ref<SourceType>&& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	GS::Swap (info, source.info);

	return *this;
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>::~Ref ()
{
	if (info != &NullObjectInfo)
		ReleaseObjectInfo ();

	info = reinterpret_cast<ObjectInfo*> (GS::BadPointer);
}


template <class Type>
ODB_FORCE_INLINE bool	ODB::Ref<Type>::operator== (const Ref& rightOp) const
{
	return (info == rightOp.info);
}


template <class Type>
template <class RightType>
ODB_FORCE_INLINE bool	ODB::Ref<Type>::operator== (const Ref<RightType>& rightOp) const
{
	static_assert (GS::AreRelated<Type, RightType>, "'Type' and 'RightType' are unrelated.");

	return (info == rightOp.info);
}


template <class Type>
ODB_FORCE_INLINE bool	ODB::Ref<Type>::operator== (const X*) const
{
	return !info->HasMemoryAddress ();
}


template <class Type>
ODB_FORCE_INLINE bool	ODB::Ref<Type>::operator!= (const Ref& rightOp) const
{
	return (info != rightOp.info);
}


template <class Type>
template <class RightType>
ODB_FORCE_INLINE bool	ODB::Ref<Type>::operator!= (const Ref<RightType>& rightOp) const
{
	static_assert (GS::AreRelated<Type, RightType>, "'Type' and 'RightType' are unrelated.");

	return (info != rightOp.info);
}


template <class Type>
ODB_FORCE_INLINE bool	ODB::Ref<Type>::operator!= (const X*) const
{
	return info->HasMemoryAddress ();
}


template <class Type>
ODB_FORCE_INLINE const Type*	ODB::Ref<Type>::operator-> () const
{
	CHECK_DATABASE_QUERY_FOR_CURRENT_THREAD

	if (info->HasQueryRequestRelatedFlags ())
		ProcessQueryRequestRelatedFlags ();

	info->MarkAsAccessed ();

	return static_cast<Type*> (info->GetCurrentMemoryAddress ());
}


template <class Type>
ODB_FORCE_INLINE const Type&	ODB::Ref<Type>::operator* () const
{
	CHECK_DATABASE_QUERY_FOR_CURRENT_THREAD

	if (info->HasQueryRequestRelatedFlags ())
		ProcessQueryRequestRelatedFlags ();

	info->MarkAsAccessed ();

	return *static_cast<Type*> (info->GetCurrentMemoryAddress ());
}


template <class Type>
ODB_FORCE_INLINE Type*	ODB::Ref<Type>::operator() (void) const
{
	return static_cast<Type*> (ProcessModificationRequest ());
}


template <class Type>
ODB_FORCE_INLINE Type*	ODB::Ref<Type>::operator() (LogicalConstSelector) const
{
	return static_cast<Type*> (ProcessLogicalConstModificationRequest ());
}


template <class Type>
ODB_FORCE_INLINE Type*	ODB::Ref<Type>::operator() (ModificationAuthorizationControl control) const
{
	return static_cast<Type*> (ProcessModificationRequest (control));
}


template <class Type>
ODB_FORCE_INLINE Type*	ODB::Ref<Type>::ToPtr (void) const
{
	return static_cast<Type*> (ProcessPointerConversionRequest ());
}


template <class Type>
ODB_FORCE_INLINE const Type*	ODB::Ref<Type>::ToConstPtr (void) const
{
	CHECK_DATABASE_QUERY_FOR_CURRENT_THREAD

	if (info->HasQueryRequestRelatedFlags ())
		ProcessQueryRequestRelatedFlags ();

	const Type* pointer = static_cast<Type*> (info->GetCurrentMemoryAddress ());

	if (pointer != nullptr)
		info->MarkAsAccessed ();

	return pointer;
}


template <class Type>
template <class BaseType>
ODB_FORCE_INLINE const ODB::Ref<BaseType>&	ODB::Ref<Type>::As (void) const
{
	static_assert (GS::IsCompatible<Type, BaseType>, "'Type' is not compatible with 'BaseType'.");

	return *reinterpret_cast<const Ref<BaseType>*> (this);
}


template <class Type>
ODB_FORCE_INLINE const ODB::Ref<ODB::Object>&	ODB::Ref<Type>::AsObject (void) const
{
	return *reinterpret_cast<const Ref<Object>*> (this);
}


template <class Type>
ODB_FORCE_INLINE const ODB::ConstRef<Type>&		ODB::Ref<Type>::AsConst (void) const
{
	return *reinterpret_cast<const ConstRef<Type>*> (this);
}


template <class Type>
inline ODB::Ref<Type>::Ref (ReferToObjectSelector, const GS::ClassInfo* classInfo, Object* target)
{
	info = NewObjectInfo (target);

	AcquireObjectInfo ();

	SetClassInfo (classInfo);
}


template <class Type>
inline ODB::Ref<Type>::Ref (AcquireInfoSelector, ObjectInfo* objectInfo)
{
	if (objectInfo == nullptr) {
		info = &NullObjectInfo;
	} else {
		info = objectInfo;
		AcquireObjectInfo ();
	}
}


template <class Type>
inline ODB::Ref<Type>::Ref (PassInfoSelector, ObjectInfo* objectInfo)
{
	info = objectInfo;
}
// _________________________________ Class Ref _________________________________



// =========================== Class ConstRefUntyped ===========================

namespace ODB {

class ODB_DLL_EXPORT ConstRefUntyped: public CommonRefUntyped {
private:
	class ClassForBoolConversion {
	private:
		void	operator delete (void* pointer);	// deleting through ConstRef is not allowed
	};

public:
	ODB_FORCE_INLINE operator const ClassForBoolConversion* () const;
};

}	// namespace ODB



ODB_FORCE_INLINE ODB::ConstRefUntyped::operator const ODB::ConstRefUntyped::ClassForBoolConversion* () const
{
	return reinterpret_cast<ClassForBoolConversion*> (info->GetMemoryAddress ());
}
// ___________________________ Class ConstRefUntyped ___________________________



// ============================== Class ConstRef ===============================

namespace ODB {

template <class Type>
class ConstRef: public ConstRefUntyped {
private:
	template <class T> friend class ConstRef;	// to allow different ConstRef<T> to access each other's mebers
	template <class T> friend class Ref;		// to allow comparison between Ref and ConstRef

	class X {};	// helper type for the safe comparison against nullptr

public:
	typedef Type ObjectType;

		// Constructors, destructor, assigment

	ODB_FORCE_INLINE ConstRef ();
	ODB_FORCE_INLINE ConstRef (std::nullptr_t);
	inline           ConstRef (const Type* object);
	ODB_FORCE_INLINE ConstRef (const NullRefType&);
	ODB_FORCE_INLINE explicit ConstRef (const Id& id, IdSpace* idSpace = nullptr);
	ODB_FORCE_INLINE ConstRef (ReferToExistingSelector, const Id& id, const IdSpace* idSpace = nullptr);

	ODB_FORCE_INLINE ConstRef (const ConstRef& source);
	ODB_FORCE_INLINE ConstRef (ConstRef&& source);

	template <class SourceType>
	ODB_FORCE_INLINE ConstRef (const ConstRef<SourceType>& source);
	template <class SourceType>
	ODB_FORCE_INLINE ConstRef (ConstRef<SourceType>&& source);

	template <class SourceType>
	ODB_FORCE_INLINE ConstRef (const Ref<SourceType>& source);
	template <class SourceType>
	ODB_FORCE_INLINE ConstRef (Ref<SourceType>&& source);


	inline ConstRef&	        operator= (const Type* object);
	ODB_FORCE_INLINE ConstRef&	operator= (const ConstRef& source);
	ODB_FORCE_INLINE ConstRef&	operator= (ConstRef&& source);

	template <class SourceType>
	ODB_FORCE_INLINE ConstRef&	operator= (const ConstRef<SourceType>& source);
	template <class SourceType>
	ODB_FORCE_INLINE ConstRef&	operator= (ConstRef<SourceType>&& source);

	template <class SourceType>
	ODB_FORCE_INLINE ConstRef&	operator= (const Ref<SourceType>& source);
	template <class SourceType>
	ODB_FORCE_INLINE ConstRef&	operator= (Ref<SourceType>&& source);

	ODB_FORCE_INLINE ~ConstRef ();

		// Comparison

	ODB_FORCE_INLINE bool		operator== (const ConstRef& rightOp) const;
	template <class RightType>
	ODB_FORCE_INLINE bool		operator== (const ConstRef<RightType>& rightOp) const;
	template <class RightType>
	ODB_FORCE_INLINE bool		operator== (const Ref<RightType>& rightOp) const;
	ODB_FORCE_INLINE bool		operator== (const X*) const;
	ODB_FORCE_INLINE bool		operator!= (const ConstRef& rightOp) const;
	template <class RightType>
	ODB_FORCE_INLINE bool		operator!= (const ConstRef<RightType>& rightOp) const;
	template <class RightType>
	ODB_FORCE_INLINE bool		operator!= (const Ref<RightType>& rightOp) const;
	ODB_FORCE_INLINE bool		operator!= (const X*) const;

		// Dereferencing

	ODB_FORCE_INLINE const Type*	operator-> () const;
	ODB_FORCE_INLINE const Type&	operator* () const;

	ODB_FORCE_INLINE const Type*	ToPtr (void) const;

		// Casting

	template <class BaseType>
	ODB_FORCE_INLINE const ConstRef<BaseType>&	As (void) const;

	ODB_FORCE_INLINE const ConstRef<Object>&	AsObject (void) const;

		// Module private methods

/* Module private method!!! */	inline ConstRef (AcquireInfoSelector, ObjectInfo* objectInfo);
};

typedef ConstRef<Object>	ObjectConstRef;

}	// namespace ODB



template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef ()
{
	info = &NullObjectInfo;
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (std::nullptr_t)
{
	info = &NullObjectInfo;
}


template <class Type>
inline ODB::ConstRef<Type>::ConstRef (const Type* object)
{
	if (object == nullptr) {
		info = &NullObjectInfo;
	} else {
		info = object->GetRef ().info;
		AcquireObjectInfo ();
	}
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (const NullRefType&)
{
	info = &NullObjectInfo;
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (const Id& id, IdSpace* idSpace)
{
	Init (id, idSpace);
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (ReferToExistingSelector, const Id& id, const IdSpace* idSpace)
{
	Init (ReferToExisting, id, idSpace);
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (const ConstRef& source)
{
	info = source.info;
	if (info != &NullObjectInfo)
		AcquireObjectInfo ();
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (ConstRef&& source)
{
	info = source.info;
	source.info = &NullObjectInfo;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (const ConstRef<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	info = source.info;
	if (info != &NullObjectInfo)
		AcquireObjectInfo ();
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (ConstRef<SourceType>&& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	info = source.info;
	source.info = &NullObjectInfo;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (const Ref<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	info = source.info;
	if (info != &NullObjectInfo)
		AcquireObjectInfo ();
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (Ref<SourceType>&& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	info = source.info;
	source.info = &NullObjectInfo;
}


template <class Type>
inline ODB::ConstRef<Type>&		ODB::ConstRef<Type>::operator= (const Type* object)
{
	if (object == nullptr)
		SetObjectInfo (&NullObjectInfo);
	else
		SetObjectInfo (object->GetRef ().info);

	return *this;
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>&	ODB::ConstRef<Type>::operator= (const ConstRef& source)
{
	SetObjectInfo (source.info);

	return *this;
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>&	ODB::ConstRef<Type>::operator= (ConstRef&& source)
{
	GS::Swap (info, source.info);

	return *this;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::ConstRef<Type>&	ODB::ConstRef<Type>::operator= (const ConstRef<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	SetObjectInfo (source.info);

	return *this;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::ConstRef<Type>&	ODB::ConstRef<Type>::operator= (ConstRef<SourceType>&& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	GS::Swap (info, source.info);

	return *this;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::ConstRef<Type>&	ODB::ConstRef<Type>::operator= (const Ref<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	SetObjectInfo (source.info);

	return *this;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::ConstRef<Type>&	ODB::ConstRef<Type>::operator= (Ref<SourceType>&& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	GS::Swap (info, source.info);

	return *this;
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::~ConstRef ()
{
	if (info != &NullObjectInfo)
		ReleaseObjectInfo ();

	info = reinterpret_cast<ObjectInfo*> (GS::BadPointer);
}


template <class Type>
ODB_FORCE_INLINE bool	ODB::ConstRef<Type>::operator== (const ConstRef& rightOp) const
{
	return (info == rightOp.info);
}


template <class Type>
template <class RightType>
ODB_FORCE_INLINE bool	ODB::ConstRef<Type>::operator== (const ConstRef<RightType>& rightOp) const
{
	static_assert (GS::AreRelated<Type, RightType>, "'Type' and 'RightType' are unrelated.");

	return (info == rightOp.info);
}


template <class Type>
template <class RightType>
ODB_FORCE_INLINE bool	ODB::ConstRef<Type>::operator== (const Ref<RightType>& rightOp) const
{
	static_assert (GS::AreRelated<Type, RightType>, "'Type' and 'RightType' are unrelated.");

	return (info == rightOp.info);
}


template <class Type>
ODB_FORCE_INLINE bool	ODB::ConstRef<Type>::operator== (const X*) const
{
	return !info->HasMemoryAddress ();
}


template <class Type>
ODB_FORCE_INLINE bool	ODB::ConstRef<Type>::operator!= (const ConstRef& rightOp) const
{
	return (info != rightOp.info);
}


template <class Type>
template <class RightType>
ODB_FORCE_INLINE bool	ODB::ConstRef<Type>::operator!= (const ConstRef<RightType>& rightOp) const
{
	static_assert (GS::AreRelated<Type, RightType>, "'Type' and 'RightType' are unrelated.");

	return (info != rightOp.info);
}


template <class Type>
template <class RightType>
ODB_FORCE_INLINE bool	ODB::ConstRef<Type>::operator!= (const Ref<RightType>& rightOp) const
{
	static_assert (GS::AreRelated<Type, RightType>, "'Type' and 'RightType' are unrelated.");

	return (info != rightOp.info);
}


template <class Type>
ODB_FORCE_INLINE bool	ODB::ConstRef<Type>::operator!= (const X*) const
{
	return info->HasMemoryAddress ();
}


template <class Type>
ODB_FORCE_INLINE const Type*	ODB::ConstRef<Type>::operator-> () const
{
	CHECK_DATABASE_QUERY_FOR_CURRENT_THREAD

	if (info->HasQueryRequestRelatedFlags ())
		ProcessQueryRequestRelatedFlags ();

	info->MarkAsAccessed ();

	return static_cast<Type*> (info->GetCurrentMemoryAddress ());
}


template <class Type>
ODB_FORCE_INLINE const Type&	ODB::ConstRef<Type>::operator* () const
{
	CHECK_DATABASE_QUERY_FOR_CURRENT_THREAD

	if (info->HasQueryRequestRelatedFlags ())
		ProcessQueryRequestRelatedFlags ();

	info->MarkAsAccessed ();

	return *static_cast<Type*> (info->GetCurrentMemoryAddress ());
}


template <class Type>
ODB_FORCE_INLINE const Type*	ODB::ConstRef<Type>::ToPtr (void) const
{
	CHECK_DATABASE_QUERY_FOR_CURRENT_THREAD

	if (info->HasQueryRequestRelatedFlags ())
		ProcessQueryRequestRelatedFlags ();

	const Type* pointer = static_cast<Type*> (info->GetCurrentMemoryAddress ());

	if (pointer != nullptr)
		info->MarkAsAccessed ();

	return pointer;
}


template <class Type>
template <class BaseType>
ODB_FORCE_INLINE const ODB::ConstRef<BaseType>&		ODB::ConstRef<Type>::As (void) const
{
	static_assert (GS::IsCompatible<Type, BaseType>, "'Type' is not compatible with 'BaseType'.");

	return *reinterpret_cast<const ConstRef<BaseType>*> (this);
}


template <class Type>
ODB_FORCE_INLINE const ODB::ConstRef<ODB::Object>&	ODB::ConstRef<Type>::AsObject (void) const
{
	return *reinterpret_cast<const ConstRef<Object>*> (this);
}


template <class Type>
inline ODB::ConstRef<Type>::ConstRef (AcquireInfoSelector, ObjectInfo* objectInfo)
{
	if (objectInfo == nullptr) {
		info = &NullObjectInfo;
	} else {
		info = objectInfo;
		AcquireObjectInfo ();
	}
}
// ______________________________ Class ConstRef _______________________________


// === Global functions ================================================================================================

namespace ODB {


namespace Imp {


template <class ToType, class FromType, class Choice = void>
class CastDispatcher {
	static_assert (GS::IsClass<ToType>, "'ToType' should be a class.");
	static_assert (GS::AlwaysFalse<ToType>, "To be able to cast to interface types, you must #include \"ODBIRef.hpp\".");
};


template <class ToType, class FromType>
class CastDispatcher<ToType, FromType, EnableIf<IsObject<ToType> && IsObject<FromType>>> {
public:
	static const Ref<ToType>&	StaticCast (const Ref<FromType>& from)
	{
		static_assert (GS::AreRelated<FromType, ToType>, "'FromType' and 'ToType' are unrelated.");
	
		DBASSERT ((!from.HasClassInfo () && !from.IsAvailable ()) || DynamicCast (from) != NullRef);	// !IsAvailable is used instead of (GetConstMemoryAddress () == nullptr) condition because if the object is not available then DynamicCast causes assert due to unsuccessful loading
	
		return reinterpret_cast<const Ref<ToType>&> (from);
	}


	static Ref<ToType>&&	StaticCast (Ref<FromType>&& from)
	{
		static_assert (GS::AreRelated<FromType, ToType>, "'FromType' and 'ToType' are unrelated.");

		DBASSERT ((!from.HasClassInfo () && !from.IsAvailable ()) || DynamicCast (from) != NullRef);	// !IsAvailable is used instead of (GetConstMemoryAddress () == nullptr) condition because if the object is not available then DynamicCast causes assert due to unsuccessful loading

		return reinterpret_cast<Ref<ToType>&&> (from);
	}


	static const ConstRef<ToType>&		StaticCast (const ConstRef<FromType>& from)
	{
		static_assert (GS::AreRelated<FromType, ToType>, "'FromType' and 'ToType' are unrelated.");

		DBASSERT ((!from.HasClassInfo () && !from.IsAvailable ()) || DynamicCast (from) != NullRef);	// !IsAvailable is used instead of (GetConstMemoryAddress () == nullptr) condition because if the object is not available then DynamicCast causes assert due to unsuccessful loading

		return reinterpret_cast<const ConstRef<ToType>&> (from);
	}


	static ConstRef<ToType>&&		StaticCast (ConstRef<FromType>&& from)
	{
		static_assert (GS::AreRelated<FromType, ToType>, "'FromType' and 'ToType' are unrelated.");

		DBASSERT ((!from.HasClassInfo () && !from.IsAvailable ()) || DynamicCast (from) != NullRef);	// !IsAvailable is used instead of (GetConstMemoryAddress () == nullptr) condition because if the object is not available then DynamicCast causes assert due to unsuccessful loading

		return reinterpret_cast<ConstRef<ToType>&&> (from);
	}


	static const Ref<ToType>&		DynamicCast (const Ref<FromType>& from)
	{
		if (from.HasClassInfo ()) {
			if (from.GetClassInfo ()->IsCompatibleWith (ToType::GetClassInfoStatic ()))
				return reinterpret_cast<const Ref<ToType>&> (from);
			else
				return reinterpret_cast<const Ref<ToType>&> (NullRef);
		}
	
		if (dynamic_cast<const ToType*> (from.GetConstMemoryAddress ()) != nullptr)
			return reinterpret_cast<const Ref<ToType>&> (from);
		else
			return reinterpret_cast<const Ref<ToType>&> (NullRef);
	}


	static Ref<ToType>		DynamicCast (Ref<FromType>&& from)
	{
		if (from.HasClassInfo ()) {
			if (from.GetClassInfo ()->IsCompatibleWith (ToType::GetClassInfoStatic ()))
				return reinterpret_cast<Ref<ToType>&&> (from);
			else
				return NullRef;
		}

		if (dynamic_cast<const ToType*> (from.GetConstMemoryAddress ()) != nullptr)
			return reinterpret_cast<Ref<ToType>&&> (from);
		else
			return NullRef;
	}


	static const ConstRef<ToType>&		DynamicCast (const ConstRef<FromType>& from)
	{
		if (from.HasClassInfo ()) {
			if (from.GetClassInfo ()->IsCompatibleWith (ToType::GetClassInfoStatic ()))
				return reinterpret_cast<const ConstRef<ToType>&> (from);
			else
				return reinterpret_cast<const ConstRef<ToType>&> (NullRef);
		}

		if (dynamic_cast<const ToType*> (from.GetConstMemoryAddress ()) != nullptr)
			return reinterpret_cast<const ConstRef<ToType>&> (from);
		else
			return reinterpret_cast<const ConstRef<ToType>&> (NullRef);
	}


	static ConstRef<ToType>		DynamicCast (ConstRef<FromType>&& from)
	{
		if (from.HasClassInfo ()) {
			if (from.GetClassInfo ()->IsCompatibleWith (ToType::GetClassInfoStatic ()))
				return reinterpret_cast<ConstRef<ToType>&&> (from);
			else
				return NullRef;
		}

		if (dynamic_cast<const ToType*> (from.GetConstMemoryAddress ()) != nullptr)
			return reinterpret_cast<ConstRef<ToType>&&> (from);
		else
			return NullRef;
	}


	static bool		IsType (const Ref<FromType>& from)
	{
		if (from.HasClassInfo ())
			return from.GetClassInfo ()->IsCompatibleWith (ToType::GetClassInfoStatic ());
	
		return dynamic_cast<const ToType*> (from.GetConstMemoryAddress ()) != nullptr;
	}


	static bool		IsType (const ConstRef<FromType>& from)
	{
		if (from.HasClassInfo ())
			return from.GetClassInfo ()->IsCompatibleWith (ToType::GetClassInfoStatic ());

		return dynamic_cast<const ToType*> (from.GetConstMemoryAddress ()) != nullptr;
	}
};


}	// namespace Imp


template <class ToType, class FromType>
decltype (auto)		StaticCast (const Ref<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::StaticCast (from);
}


template <class ToType, class FromType>
auto				StaticCast (Ref<FromType>&& from)
{
	return Imp::CastDispatcher<ToType, FromType>::StaticCast (std::move (from));
}


template <class ToType, class FromType>
decltype (auto)		StaticCast (const ConstRef<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::StaticCast (from);
}


template <class ToType, class FromType>
auto				StaticCast (ConstRef<FromType>&& from)
{
	return Imp::CastDispatcher<ToType, FromType>::StaticCast (std::move (from));
}


template <class ToType, class FromType>
decltype (auto)		DynamicCast (const Ref<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::DynamicCast (from);
}


template <class ToType, class FromType>
decltype (auto)		DynamicCast (Ref<FromType>&& from)
{
	return Imp::CastDispatcher<ToType, FromType>::DynamicCast (std::move (from));
}


template <class ToType, class FromType>
decltype (auto)		DynamicCast (const ConstRef<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::DynamicCast (from);
}


template <class ToType, class FromType>
decltype (auto)		DynamicCast (ConstRef<FromType>&& from)
{
	return Imp::CastDispatcher<ToType, FromType>::DynamicCast (std::move (from));
}


template <class ToType, class FromType>
bool	IsType (const Ref<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::IsType (from);
}


template <class ToType, class FromType>
bool	IsType (const ConstRef<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::IsType (from);
}


template <class ToType, class FromType>
bool	IsExactType (const Ref<FromType>& from)
{
	return from.GetClassInfo () == ToType::GetClassInfoStatic ();
}


template <class ToType, class FromType>
bool	IsExactType (const ConstRef<FromType>& from)
{
	return from.GetClassInfo () == ToType::GetClassInfoStatic ();
}


template <class Type>
Ref<Type>			ConstCast (Ref<Type> /*from*/)
{
	static_assert (GS::AlwaysFalse<Type>, "No need to const cast an ODB::Ref, because it is already not const.");
	return {};
}


template <class Type>
const Ref<Type>&	ConstCast (const ConstRef<Type>& from)
{
	return reinterpret_cast<const Ref<Type>&> (from);
}


template <class Type>
Ref<Type>&			ConstCast (ConstRef<Type>& from)
{
	return reinterpret_cast<Ref<Type>&> (from);
}


template <class Type>
Ref<Type>			ConstCast (ConstRef<Type>&& from)
{
	return reinterpret_cast<Ref<Type>&&> (from);
}


template <class Type>
Type*	LogicalConstCast (const ConstRef<Type>& from)
{
	return reinterpret_cast<const Ref<Type>*> (&from)->operator() (LogicalConst);
}


}	// namespace ODB



// ================================= Class Ref =================================

template <class Type>
template <class RightType>
ODB_FORCE_INLINE bool	ODB::Ref<Type>::operator== (const ConstRef<RightType>& rightOp) const
{
	static_assert (GS::AreRelated<Type, RightType>, "'Type' and 'RightType' are unrelated.");

	return (info == rightOp.info);
}


template <class Type>
template <class RightType>
ODB_FORCE_INLINE bool	ODB::Ref<Type>::operator!= (const ConstRef<RightType>& rightOp) const
{
	static_assert (GS::AreRelated<Type, RightType>, "'Type' and 'RightType' are unrelated.");

	return (info != rightOp.info);
}
// _________________________________ Class Ref _________________________________



// ================================= Class Pin =================================

namespace ODB {

class ODB_DLL_EXPORT Pin {
private:
	CommonRefUntyped* object;		// reference to the object to be pinned
	bool			  wasPinned;	// stores the initial pinning state

	Pin (const Pin& source);				// disabled
	Pin&	operator= (const Pin& source);	// disabled

	void*	operator new (size_t) throw () { return nullptr; }			// disabled
	void	operator delete (void*) {}								// disabled
	void*	operator new (size_t, void*) throw () { return nullptr; }	// disabled
	void	operator delete (void*, void*) {}						// disabled
	void*	operator new[] (size_t) throw () { return nullptr; }		// disabled
	void	operator delete[] (void*) {}							// disabled

public:
		// Constructors, destructor

	inline explicit Pin (const CommonRefUntyped& object, bool loadIfExternal = true);

	inline ~Pin ();
};

}	// namespace ODB



inline ODB::Pin::Pin (const CommonRefUntyped& object, bool loadIfExternal):
	object	  (const_cast<CommonRefUntyped*> (&object)),
	wasPinned (object.IsPinned ())
{
	this->object->AcquireObjectInfo ();
	this->object->Pin (loadIfExternal);
}


inline ODB::Pin::~Pin ()
{
	if (!wasPinned)
		object->Unpin ();
	object->ReleaseObjectInfo ();
}
// _________________________________ Class Pin _________________________________



// ========================= Class EventReceptionLock ==========================

namespace ODB {

class ODB_DLL_EXPORT EventReceptionLock {
private:
	CommonRefUntyped* object;		// reference to the object to be locked
	bool			  wasEnabled;	// stores the initial event reception state

	EventReceptionLock (const EventReceptionLock& source);				// disabled
	EventReceptionLock&	operator= (const EventReceptionLock& source);	// disabled

	void*	operator new (size_t) throw () { return nullptr; }			// disabled
	void	operator delete (void*) {}								// disabled
	void*	operator new (size_t, void*) throw () { return nullptr; }	// disabled
	void	operator delete (void*, void*) {}						// disabled
	void*	operator new[] (size_t) throw () { return nullptr; }		// disabled
	void	operator delete[] (void*) {}							// disabled

public:
		// Constructors, destructor

	inline explicit EventReceptionLock (const CommonRefUntyped& object);

	inline ~EventReceptionLock ();
};

}	// namespace ODB



inline ODB::EventReceptionLock::EventReceptionLock (const CommonRefUntyped& object):
	object	   (const_cast<CommonRefUntyped*> (&object)),
	wasEnabled (object.info->IsEventReceptionEnabled ())
{
	this->object->AcquireObjectInfo ();
	this->object->DisableEventReception ();
}


inline ODB::EventReceptionLock::~EventReceptionLock ()
{
	if (wasEnabled)
		object->EnableEventReception ();
	object->ReleaseObjectInfo ();
}
// _________________________ Class EventReceptionLock __________________________



// ======================= Object based assert subjects ========================

namespace ODB {

struct ObjectAssertSubject {
	Ref<Object> object;
	GSErrCode	errorCode;

	ObjectAssertSubject (const Ref<Object>& object, GSErrCode errorCode = NoError): object (object), errorCode (errorCode) {}
};


struct ConstObjectAssertSubject {
	ConstRef<Object> object;
	GSErrCode		 errorCode;

	ConstObjectAssertSubject (const ConstRef<Object>& object, GSErrCode errorCode = NoError): object (object), errorCode (errorCode) {}
};

inline auto		Subject (const Ref<Object>& object)	     { return GS::Subject (object); }
inline auto		Subject (const ConstRef<Object>& object) { return GS::Subject (object); }

inline auto		Subject (const Ref<Object>& object, GSErrCode errorCode)	  { return GS::Subject (ObjectAssertSubject (object, errorCode)); }
inline auto		Subject (const ConstRef<Object>& object, GSErrCode errorCode) { return GS::Subject (ConstObjectAssertSubject (object, errorCode)); }


ODB_DLL_EXPORT GS::String	LogAssertSubject (GS::FastLogger::LogComposer& logComposer, const ObjectAssertSubject& subject);
ODB_DLL_EXPORT GS::String	LogAssertSubject (GS::FastLogger::LogComposer& logComposer, const ConstObjectAssertSubject& subject);

}	// namespace ODB
// _______________________ Object based assert subjects ________________________


#endif
