

// *****************************************************************************
//
//                               Class ObjectInfo
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined OBJECTINFO_HPP
#define OBJECTINFO_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "ODBBase.hpp"

#include "ODBId.hpp"

#include "Atomic.hpp"
#include "MemoryBarrier.hpp"


// ------------------------------ Predeclarations ------------------------------

namespace ODB { class IdSpace; }
namespace ODB { class Database; }
namespace ODB { class Object; }
namespace ODB { class ObjectDataStore; }


// ============================= Class ObjectInfo ==============================

namespace ODB {


#if defined (_MSC_VER) && defined (GS_32BIT)
#pragma pack(push, 4)
#endif

class ODB_DLL_EXPORT ObjectInfo {
private:
	const GS::ClassInfo*	classInfo;				// class descriptor
	IdSpace*				idSpace;				// identifier space to which the object belongs
	Database*				database;				// database to which the object belongs
	Object*					memoryAddress;			// memory address of the object
	Id						id;						// identifier of the object
	UInt64					creationStamp;			// creation stamp of the object
	UInt64					modificationStamp;		// modification stamp of the object
	volatile UInt64			flags;					// various boolean informations
	ObjectDataStore*		objectDataStore;		// stores object related data (e.g. links, owner object)
	volatile UInt32			referenceCounter;		// number of references to this ObjectInfo instance
	UShort					accessLevel;			// last transaction level at which copy of the object was created (0 = no copy) or DerivedNotificationIsEnabled which enables modification of derived objects without modification scope
	UInt8					clockFlag;				// flag used by the clock algorithm
	UInt8					reservedForAllocator;	// reserved for the ObjectInfo memory allocator -> it is put here to utilize the last byte (because ObjectInfo is padded to 68 bytes and only 67 is used)

	void*	operator new (size_t, void*) throw () { return nullptr; }	// disabled
	void	operator delete (void*, void*) {}							// disabled
	void*	operator new[] (size_t) throw () { return nullptr; }		// disabled
	void	operator delete[] (void*) {}								// disabled

	// Flags should not be modified in read-only operations, because setting flags is neither locked nor atomic. Setting a flag bit can 
	// interfere with concurrent writes to other flag bits.
	// The only exception is the AssociationIndexNotification flag which can change from unset to set by association queries running in parallel. This race-condition
	// is acceptable, because AssociationIndexNotification is the ONLY flag bit that might change during read-only operations. Don't add other flags with similar 
	// behavior to the flags integer!
	
	static const UInt64 FlagCount									   = 43;
	static const UInt64 LastFlagPower								   = FlagCount - 1;

	static const UInt64 Internal									   = 1ull <<  0;			// object is in the memory
	static const UInt64 External									   = 1ull <<  1;			// object is not in the memory
	static const UInt64 WasInternalFlag								   = 1ull <<  2; 			// object was at least once in the memory during the current execution
	static const UInt64 Loadable									   = 1ull <<  3; 			// if the object is external then it is loadable by someone (database or object loading manager)
	static const UInt64 LoadingObject								   = 1ull <<  4; 			// object is loading (object is under transition from external to internal -> it is needed to prevent other threads to find the object internal too early)
	static const UInt64 LoadingLinks								   = 1ull <<  5; 			// links are loading
	static const UInt64 ExternalLinks								   = 1ull <<  6;			// object has links that are not in the memory (but may have links that are in the memory along some transient associations)
	static const UInt64 HadInternalLinksFlag						   = 1ull <<  7; 			// object had at least once all of it links in the memory during the current execution
	static const UInt64 LinksAreUnavailable							   = 1ull <<  8;			// object's links are not available (loadable)
	static const UInt64 Const										   = 1ull <<  9; 			// object is not modifiable because it is constant (read only)
	static const UInt64 LogicalConst								   = 1ull << 10; 			// object is logically not modifiable because it is logically constant
	static const UInt64 Undeletable									   = 1ull << 11; 			// object is not deletable
	static const UInt64 UnauthorizedToModify						   = 1ull << 12; 			// object is not modifiable because the current user has not enough privileges (object is owned by another user)
	static const UInt64 UnauthorizedToLogicallyModify				   = 1ull << 13; 			// object is logically not modifiable because the current user has not enough privileges (object is owned by another user)
	static const UInt64 HasOwnerObjectFlag							   = 1ull << 14; 			// object is owned by another object along an association
	static const UInt64 HasOwnerLinkFlag							   = 1ull << 15; 			// object is owned by a link along an association with association class
	static const UInt64 SharedByAssociation							   = 1ull << 16; 			// object is logically owned by one object but is physically shared among multiple objects (ownership is not necessarily along an association)
	static const UInt64 SharedByReference							   = 1ull << 17;
	static const UInt64 ContentBasedIdentity						   = 1ull << 18;			// object's identifier is determined by object's content
	static const UInt64 ContextBasedIdentity						   = 1ull << 19;			// object's identifier is determined by object's context
	static const UInt64 Derived										   = 1ull << 20; 			// object is derived from other (core or derived) objects
	static const UInt64 ObjectModifiedOnTraceLine1					   = 1ull << 21;			// object is modified on trace line 1
	static const UInt64 ObjectModifiedOnTraceLine2					   = 1ull << 22;			// object is modified on trace line 2
	static const UInt64 ObjectModifiedOnTraceLine3					   = 1ull << 23;			// object is modified on trace line 3
	static const UInt64 LinkModifiedOnTraceLine1					   = 1ull << 24;			// object has modification in its connections (links) on trace line 1
	static const UInt64 Pinned										   = 1ull << 25; 			// object is pinned in the memory
	static const UInt64 ExternalOnDelete							   = 1ull << 26; 			// object becomes external after it is deleted
	static const UInt64 EventReceptionIsDisabled					   = 1ull << 27; 			// object can't receive events
	static const UInt64 AssociationIndexNotification				   = 1ull << 28; 			// at least one of the object's indices is consistent with the state of this object and needs notification on modification request
	static const UInt64 DependencyNotification						   = 1ull << 29; 			// at least one of the object's dependent objects is consistent with the state of this object and needs notification on modification request
	static const UInt64 LazyDataNotification						   = 1ull << 30; 			// object has lazy data to be initialized on access
	static const UInt64 DerivedDataNotification						   = 1ull << 31; 			// object has derived data to be initialized on access
	static const UInt64 ObjectModificationNotificationForRing		   = 1ull << 32; 			// modification ring should be notified at the next object modification
	static const UInt64 ObjectModificationNotificationForTimeline	   = 1ull << 33; 			// timeline should be notified at the next object modification
	static const UInt64 LinkModificationNotificationForTimeline		   = 1ull << 34; 			// timeline should be notified at the next link modification
	static const UInt64 ObjectDeletionNotification					   = 1ull << 35;			// object deletion should send AboutToDelete notification
	static const UInt64 CreatedBySubThread							   = 1ull << 36;			// true when ObjectInfo is created by a sub thread (not by the main thread)
	static const UInt64 ModifiableWithoutModificationScope			   = 1ull << 37; 			// object is modifiable without modification scope
	static const UInt64 LogicalConstModifiableWithoutModificationScope = 1ull << 38; 			// object is logical const modifiable without modification scope
	static const UInt64 DataLayerBit1								   = 1ull << 39; 			// 1. bit of the data layer index
	static const UInt64 DataLayerBit2								   = 1ull << 40; 			// 2. bit of the data layer index
	static const UInt64 DataLayerBit3								   = 1ull << 41; 			// 3. bit of the data layer index
	static const UInt64 CheckFlag1									   = 1ull << LastFlagPower;	// set by SharedAssociation11 for objects stored in newRightObjects, checked by Object's destructor

	static_assert (Internal	+ External + WasInternalFlag + Loadable + LoadingObject + LoadingLinks + ExternalLinks + HadInternalLinksFlag + LinksAreUnavailable + Const +
				   LogicalConst + Undeletable + UnauthorizedToModify + UnauthorizedToLogicallyModify + HasOwnerObjectFlag + HasOwnerLinkFlag + SharedByAssociation + SharedByReference + ContentBasedIdentity + ContextBasedIdentity +
				   Derived + ObjectModifiedOnTraceLine1 + ObjectModifiedOnTraceLine2 + ObjectModifiedOnTraceLine3 + LinkModifiedOnTraceLine1 + Pinned + ExternalOnDelete + EventReceptionIsDisabled + AssociationIndexNotification + DependencyNotification +
				   LazyDataNotification + DerivedDataNotification + ObjectModificationNotificationForRing + ObjectModificationNotificationForTimeline + LinkModificationNotificationForTimeline +	ObjectDeletionNotification + CreatedBySubThread + ModifiableWithoutModificationScope + LogicalConstModifiableWithoutModificationScope +
				   DataLayerBit1 + DataLayerBit2 + DataLayerBit3 + CheckFlag1 == (1ull << FlagCount) - 1, "Flag values are not distinct successive power of 2");

	static const UInt64 DataLayerPosition = Log2<DataLayerBit1>::Value;
	static const UInt64 DataLayerBits	  = DataLayerBit1 + DataLayerBit2 + DataLayerBit3;
	static const UInt64 MaxDataLayer	  = DataLayerBits >> DataLayerPosition;

	static const UInt64 ExistenceFlags				  = Internal | External;									// flags indicating a normal existing object (not Null)
	static const UInt64 AvailabilityFlags			  = Internal | Loadable;									// flags indicating an usable object
	static const UInt64 PhysicalModificationFlags	  = Const | UnauthorizedToModify;							// flags related to the physical modification of the object
	static const UInt64 LogicalModificationFlags	  = LogicalConst | UnauthorizedToLogicallyModify;			// flags related to the logical modification of the object
	static const UInt64 ModificationFlags			  = PhysicalModificationFlags | LogicalModificationFlags;	// flags related to the modification of the object
	static const UInt64 QueryRequestRelatedFlags	  = External | LazyDataNotification;						// flags that have effect on the query request (const method call)
	static const UInt64 ObjectModificationRequestRelatedFlags = External | AssociationIndexNotification | DependencyNotification | LazyDataNotification | ModificationFlags | ObjectModificationNotificationForRing | ObjectModificationNotificationForTimeline;	// flags that have effect on the object modification request (non-const method call)
	static const UInt64 LogicalConstObjectModificationRequestRelatedFlags = External | AssociationIndexNotification | DependencyNotification | LazyDataNotification | PhysicalModificationFlags;	// flags that have effect on the non-logical object modification request
	static const UInt64 TransactionRelatedFlags		  = LazyDataNotification | ObjectModifiedOnTraceLine1 | ObjectModifiedOnTraceLine2 | ObjectModifiedOnTraceLine3;	// flags to be saved / restored under transaction
	static const UInt64 DeletionFlags				  = Undeletable | ModificationFlags | HasOwnerLinkFlag | SharedByAssociation;	// flags related to the deletion of the object
	static const UInt64 HasOwnerFlags				  = HasOwnerObjectFlag | HasOwnerLinkFlag;					// flags indicating that the object is owned by an entity
	static const UInt64 GeneratedIdentityFlags		  = ContentBasedIdentity | ContextBasedIdentity;			// flags indicating generated (non-independent) identity
	static const UInt64 ObjectDeletionCheckFlags	  = SharedByAssociation | HasOwnerFlags | CheckFlag1;					// these flags should be 0 at object deletion after the links are destroyed
	static const UInt64 AutoDeletableFlags			  = Internal | SharedByReference;

	enum {
		ClockFlagIsCleared = 0,
		ClockFlagIsSet = 1		
	};

	enum PersistentFlags {
		P_ContentBasedIdentity = 0x1,
		P_ContextBasedIdentity = 0x2,

		P_GeneratedIdentityFlags = P_ContentBasedIdentity | P_ContextBasedIdentity
	};

	ObjectInfo (const ObjectInfo& source);				// disabled
	ObjectInfo&	operator= (const ObjectInfo& source);	// disabled

	void	SetLocationFlags (void);

	void	LoadObject (void);
	void	LoadLinks (void);

public:
		// Default specifiable flags

	static const UInt64 DS_ContentBasedIdentity = ContentBasedIdentity;
	static const UInt64 DS_Pinned				= Pinned;
	static const UInt64 DS_Derived				= Derived;
	static const UInt64 DS_ModifiableWithoutModificationScope			  = ModifiableWithoutModificationScope;
	static const UInt64 DS_LogicalConstModifiableWithoutModificationScope = LogicalConstModifiableWithoutModificationScope;
	static const UInt64 DS_DataLayer1			= UInt64 (1) << DataLayerPosition;
	static const UInt64 DS_DataLayer2			= UInt64 (2) << DataLayerPosition;
	static const UInt64 DS_DataLayer3			= UInt64 (3) << DataLayerPosition;
	static const UInt64 DS_DataLayer4			= UInt64 (4) << DataLayerPosition;
	static const UInt64 DS_DataLayer5			= UInt64 (5) << DataLayerPosition;
	static const UInt64 DS_DataLayer6			= UInt64 (6) << DataLayerPosition;
	static const UInt64 DS_DataLayer7			= UInt64 (7) << DataLayerPosition;

	static const UInt64 ObjectTraceLine1 = ObjectModifiedOnTraceLine1;
	static const UInt64 ObjectTraceLine2 = ObjectModifiedOnTraceLine2;
	static const UInt64 ObjectTraceLine3 = ObjectModifiedOnTraceLine3;
	static const UInt64 LinkTraceLine1	 = LinkModifiedOnTraceLine1;

	ObjectInfo (Database* database, Object* memoryAddress);
	ObjectInfo (IdSpace* idSpace, Database* database, const Id& id, Object* memoryAddress);
   ~ObjectInfo ();

	ODB_FORCE_INLINE void	Acquire		  (void);
	ODB_FORCE_INLINE bool	AcquireIfUsed (void);
	ODB_FORCE_INLINE UInt32	Release		  (void);

	ODB_FORCE_INLINE const GS::ClassInfo*	GetClassInfo (void) const;
	ODB_FORCE_INLINE bool					HasClassInfo (void) const;
	ODB_FORCE_INLINE void 					SetClassInfo (const GS::ClassInfo* newClassInfo);
	ODB_FORCE_INLINE const GS::Guid&		GetClassId	 (void) const;
	ODB_FORCE_INLINE bool					HasClassId	 (void) const;
	const char*								GetClassLogName (void) const;

	ODB_FORCE_INLINE IdSpace*	GetIdSpace (void) const;
	ODB_FORCE_INLINE IdSpace*	GetOriginalIdSpace (void) const;
	inline void					SetIdSpace (IdSpace* newIdSpace);

	ODB_FORCE_INLINE Database*	GetDatabase   (void) const;
	inline void					SetDatabase   (Database* newDatabase);
	void						ClearDatabase (void);

	inline const Id&	GetId		  (void) const;
	inline const Id&	GetOriginalId (void) const;
	inline bool			HasId		  (const Id& id) const;
	inline bool			HasId		  (void) const;
	inline bool			HasOriginalId (void) const;
	void				SetId		  (const Id& newId);
	void				ClearId		  (void);

	ODB_FORCE_INLINE UInt64	GetCreationStamp		(void) const;
	ODB_FORCE_INLINE UInt64	GetCurrentCreationStamp (void) const;
	ODB_FORCE_INLINE void	SetCreationStamp		(UInt64 newCreationStamp);

	ODB_FORCE_INLINE UInt64	GetModificationStamp		(void) const;
	ODB_FORCE_INLINE UInt64	GetCurrentModificationStamp (void) const;
	ODB_FORCE_INLINE void	SetModificationStamp		(UInt64 newModificationStamp);

	ODB_FORCE_INLINE bool	IsModifiedInSessionAfter (UInt64 startModificationStamp) const;

	ODB_FORCE_INLINE void	SetDefaultSpecifiableFlags (UInt64 defaultSpecifiableFlags);

	ODB_FORCE_INLINE UChar	GetPersistentFlags (void) const;
	ODB_FORCE_INLINE void	SetPersistentFlags (UChar newPersistentFlags);
	ODB_FORCE_INLINE static bool	HasContentBasedIdentity (UChar persistentFlags);
	ODB_FORCE_INLINE static bool	HasContextBasedIdentity (UChar persistentFlags);
	ODB_FORCE_INLINE static bool	HasIndependentIdentity  (UChar persistentFlags);
	ODB_FORCE_INLINE static bool	HasDependentIdentity	(UChar persistentFlags);
	ODB_FORCE_INLINE static void	ClearContentBasedIdentity (UChar& persistentFlags);
	ODB_FORCE_INLINE static void	ClearContextBasedIdentity (UChar& persistentFlags);

	ODB_FORCE_INLINE bool	HasOwnerObject		 (void) const;
	ODB_FORCE_INLINE void	SetObjectOwnership	 (void);
	ODB_FORCE_INLINE void	ClearObjectOwnership (void);

	ODB_FORCE_INLINE bool	HasOwnerLink	   (void) const;
	ODB_FORCE_INLINE void	SetLinkOwnership   (void);
	ODB_FORCE_INLINE void	ClearLinkOwnership (void);

	ODB_FORCE_INLINE bool	HasOwner (void) const;

	ODB_FORCE_INLINE bool	IsSharedByAssociation	 (void) const;
	ODB_FORCE_INLINE void	MarkAsSharedByAssociation (void);
	ODB_FORCE_INLINE void	ClearSharingByAssociation (void);

	ODB_FORCE_INLINE bool	IsSharedByReference	    (void) const;
	ODB_FORCE_INLINE void	MarkAsSharedByReference (void);
	ODB_FORCE_INLINE void	ClearSharingByReference (void);

	ODB_FORCE_INLINE bool	HasContentBasedIdentity	(void) const;
	ODB_FORCE_INLINE void	SetContentBasedIdentity (void);
	ODB_FORCE_INLINE void	ClearContentBasedIdentity (void);

	ODB_FORCE_INLINE bool	HasContextBasedIdentity	  (void) const;
	ODB_FORCE_INLINE void	SetContextBasedIdentity	  (void);
	ODB_FORCE_INLINE void	ClearContextBasedIdentity (void);

	ODB_FORCE_INLINE bool	HasIndependentIdentity (void) const;
	ODB_FORCE_INLINE bool	HasDependentIdentity   (void) const;

	ODB_FORCE_INLINE bool	IsDerived	 (void) const;
	void					SetAsCore	 (void);
	void					SetAsDerived (void);

	ODB_FORCE_INLINE void	MarkObjectAsModified (void);
	ODB_FORCE_INLINE void	MarkObjectAsModifiedOnTraceLine (UInt64 objectTraceLine);

	ODB_FORCE_INLINE bool	IsObjectModifiedOnTraceLine        (UInt64 objectTraceLine) const;
	ODB_FORCE_INLINE void	RestartObjectModificationTraceLine (UInt64 objectTraceLine);

	ODB_FORCE_INLINE void	MarkWithLinkModification  (void);

	ODB_FORCE_INLINE bool	HasLinkModificationOnTraceLine	 (UInt64 linkTraceLine) const;
	ODB_FORCE_INLINE void	RestartLinkModificationTraceLine (UInt64 linkTraceLine);

	ODB_FORCE_INLINE bool	IsClockFlagSet (void) const;
	ODB_FORCE_INLINE void	SetClockFlag   (void);
	ODB_FORCE_INLINE void	ClearClockFlag (void);

	ODB_FORCE_INLINE void	MarkAsAccessed (void);

	ODB_FORCE_INLINE bool	IsPinned (void) const;
	ODB_FORCE_INLINE void	Pin      (void);
	ODB_FORCE_INLINE void	Unpin    (void);

	ODB_FORCE_INLINE bool	IsConst        (void) const;
	ODB_FORCE_INLINE void	SetAsConst     (void);
	ODB_FORCE_INLINE void	ClearConstness (void);

	ODB_FORCE_INLINE bool	IsLogicalConst		  (void) const;
	ODB_FORCE_INLINE void	SetAsLogicalConst     (void);
	ODB_FORCE_INLINE void	ClearLogicalConstness (void);

	ODB_FORCE_INLINE bool	IsDeletingEnabled (void) const;
	ODB_FORCE_INLINE void	EnableDeleting	  (void);
	ODB_FORCE_INLINE void	DisableDeleting	  (void);

	ODB_FORCE_INLINE bool	IsAuthorizedToModify             (void) const;
	ODB_FORCE_INLINE void	AcquireModificationAuthorization (void);
	ODB_FORCE_INLINE void	ReleaseModificationAuthorization (void);

	ODB_FORCE_INLINE bool	IsAuthorizedToLogicallyModify		    (void) const;
	ODB_FORCE_INLINE void	AcquireLogicalModificationAuthorization (void);
	ODB_FORCE_INLINE void	ReleaseLogicalModificationAuthorization (void);

	ODB_FORCE_INLINE bool	IsModifiable			 (void) const;
	ODB_FORCE_INLINE bool	IsLogicalConstModifiable (void) const;
	ODB_FORCE_INLINE bool	IsDeletable				 (void) const;

	ODB_FORCE_INLINE bool	BecomesExternalOnDelete   (void) const;
	ODB_FORCE_INLINE void	SetExternalOnDeleteMode   (void);
	ODB_FORCE_INLINE void	ClearExternalOnDeleteMode (void);

	ODB_FORCE_INLINE bool	IsEventReceptionEnabled (void) const;
	ODB_FORCE_INLINE void	EnableEventReception    (void);
	ODB_FORCE_INLINE void	DisableEventReception   (void);

	ODB_FORCE_INLINE bool	HasQueryRequestRelatedFlags		   (void) const;
	ODB_FORCE_INLINE bool	HasObjectModificationRequestRelatedFlags (void) const;
	ODB_FORCE_INLINE bool	HasLogicalConstObjectModificationRequestRelatedFlags (void) const;
	ODB_FORCE_INLINE bool   HasOnlyObjectModificationNotificationForRingFlag (void) const;

	ODB_FORCE_INLINE UInt64	GetTransactionRelatedFlags  (void) const;
	ODB_FORCE_INLINE void	SetTransactionRelatedFlags  (UInt64 newFlags);

	ODB_FORCE_INLINE bool		IsInternal		   (void) const;
	ODB_FORCE_INLINE bool		IsExternal		   (void) const;
	ODB_FORCE_INLINE bool		IsNull			   (void) const;
	ODB_FORCE_INLINE bool		WasInternal		   (void) const;
	ODB_FORCE_INLINE bool		IsDeleting		   (void) const;
	ODB_FORCE_INLINE bool		IsDeleted		   (void) const;
	ODB_FORCE_INLINE bool		IsLoadingObject	   (void) const;
	ODB_FORCE_INLINE bool		IsLoadingLinks	   (void) const;
	ODB_FORCE_INLINE Object*	GetMemoryAddress   (void) const;
	ODB_FORCE_INLINE Object*	GetCurrentMemoryAddress (void) const;
	ODB_FORCE_INLINE bool		HasMemoryAddress   (void) const;
	void						SetMemoryAddress   (Object* newMemoryAddress);
	void						SetAsDeleted	   (void);
	void						SetAsDeleting	   (void);
	void						SetAsExternal	   (void);
	void						ClearWasInternalFlag (void);
	ODB_FORCE_INLINE bool		IsAvailable		   (void) const;
	void						SetAsLoadable	   (void);
	void						ClearLoadableFlag  (void);
	ODB_FORCE_INLINE void		SetAsLoadingObject (void);
	ODB_FORCE_INLINE void		ClearLoadingObject (void);
	ODB_FORCE_INLINE void		SetAsLoadingLinks  (void);
	ODB_FORCE_INLINE void		ClearLoadingLinks  (void);

	ODB_FORCE_INLINE bool		HasExternalLinks	   (void) const;
	ODB_FORCE_INLINE void		MarkWithExternalLinks  (void);
	ODB_FORCE_INLINE void		ClearExternalLinksFlag (void);
	ODB_FORCE_INLINE bool		HadInternalLinks	   (void) const;
	ODB_FORCE_INLINE void		MarkAsHadInternalLinks (void);
	ODB_FORCE_INLINE void		ClearHadInternalLinksFlag (void);
	ODB_FORCE_INLINE bool		AreLinksAvailable	   (void) const;
	ODB_FORCE_INLINE void		MarkAsLinksAreAvailable   (void);
	ODB_FORCE_INLINE void		MarkAsLinksAreUnavailable (void);

	ODB_FORCE_INLINE UInt32	GetReferenceCounter (void) const;

	ODB_FORCE_INLINE UShort	GetAccessLevel (void) const;
	inline void				SetAccessLevel (UShort newAccessLevel);

	ODB_FORCE_INLINE bool	IsAssociationIndexNotificationStarted (void) const;
	ODB_FORCE_INLINE void	StartAssociationIndexNotification	  (void);
	ODB_FORCE_INLINE void	StopAssociationIndexNotification	  (void);

	ODB_FORCE_INLINE bool	IsDependencyNotificationStarted	(void) const;
	ODB_FORCE_INLINE void	StartDependencyNotification		(void);
	ODB_FORCE_INLINE void	StopDependencyNotification		(void);

	ODB_FORCE_INLINE bool	HasLazyDataToBeInitialized	(void) const;
	ODB_FORCE_INLINE void	SetLazyDataInitialization	(void);
	ODB_FORCE_INLINE void	ClearLazyDataInitialization	(void);

	ODB_FORCE_INLINE bool   IsObjectModificationNotificationForRingStarted (void) const;
	ODB_FORCE_INLINE void   StartObjectModificationNotificationForRing     (void);
	ODB_FORCE_INLINE void   StopObjectModificationNotificationForRing      (void);

	ODB_FORCE_INLINE bool   IsObjectModificationNotificationForTimelineStarted (void) const;
	ODB_FORCE_INLINE void   StartObjectModificationNotificationForTimeline     (void);
	ODB_FORCE_INLINE void   StopObjectModificationNotificationForTimeline      (void);

	ODB_FORCE_INLINE bool   IsLinkModificationNotificationForTimelineStarted (void) const;
	ODB_FORCE_INLINE void   StartLinkModificationNotificationForTimeline     (void);
	ODB_FORCE_INLINE void   StopLinkModificationNotificationForTimeline      (void);

	ODB_FORCE_INLINE ObjectDataStore*		GetDataStore (void) const;
	void									SetDataStore (ObjectDataStore* newDataStore);

	ODB_FORCE_INLINE const ObjectDataStore*	GetLinks		   (void) const;
	ODB_FORCE_INLINE const ObjectDataStore*	GetCurrentLinks	   (void) const;
	ODB_FORCE_INLINE ObjectDataStore*		ModifyLinks		   (void);
	ODB_FORCE_INLINE ObjectDataStore*		ModifyCurrentLinks (void);

	ODB_FORCE_INLINE const ObjectDataStore*	GetIndices			 (void) const;
	ODB_FORCE_INLINE const ObjectDataStore*	GetCurrentIndices	 (void) const;
	ODB_FORCE_INLINE ObjectDataStore*		ModifyIndices		 (void);
	ODB_FORCE_INLINE ObjectDataStore*		ModifyCurrentIndices (void);

	ODB_FORCE_INLINE bool   IsNotificationOnDeleteSet (void) const;
	ODB_FORCE_INLINE void   SetNotificationOnDelete	  (void);
	ODB_FORCE_INLINE void   ClearNotificationOnDelete (void);

	ODB_FORCE_INLINE bool   IsModifiableWithoutModificationScope			 (void) const;
	ODB_FORCE_INLINE bool   IsLogicalConstModifiableWithoutModificationScope (void) const;

	ODB_FORCE_INLINE UInt32	GetDataLayer (void) const;
	void					SetDataLayer (UInt32 newDataLayer);

	ODB_FORCE_INLINE bool   GetCheckFlag1	(void) const;
	ODB_FORCE_INLINE void   SetCheckFlag1	(void);
	ODB_FORCE_INLINE void   ClearCheckFlag1 (void);

	ODB_FORCE_INLINE bool	AreObjectDeletionCheckFlagsCleared (void) const;

	ODB_FORCE_INLINE bool	IsAutoDeletable (void) const;

		// Memory management

	void*	operator new (size_t size);
	void	operator delete (void* pointer);

		// Debug, test

	void	PrintFlags (char (&result)[1024]) const;
};


#if defined (_MSC_VER) && defined (GS_32BIT)
#pragma pack(pop)
#endif

class ODB_DLL_EXPORT NullObjectInfoType: public ObjectInfo {
public:
	NullObjectInfoType ();
};


ODB_DLL_EXPORT extern NullObjectInfoType	NullObjectInfo;		// represents the nullptr address

}	// namespace ODB



ODB_FORCE_INLINE void	ODB::ObjectInfo::Acquire (void)
{
	GS::AtomicIncrement (reinterpret_cast<volatile Int32*> (&referenceCounter));
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::AcquireIfUsed (void)
{
	UInt32 oldReferenceCounter = referenceCounter;
	GS::MemoryBarrierForVolatile ();	 // to ensure that referenceCounter is read from memory before it is modified

	while (oldReferenceCounter != 0) {
		if (GS::AtomicCompareAndSwap (reinterpret_cast<volatile Int32*> (&referenceCounter), static_cast<Int32> (oldReferenceCounter + 1), static_cast<Int32> (oldReferenceCounter)))
			return true;

		oldReferenceCounter = referenceCounter;
		GS::MemoryBarrierForVolatile ();	// to ensure that referenceCounter is read from memory before it is modified
	}

	return false;
}


ODB_FORCE_INLINE UInt32	ODB::ObjectInfo::Release (void)
{
	DBASSERT (referenceCounter != 0);

	return static_cast<UInt32> (GS::AtomicDecrement (reinterpret_cast<volatile Int32*> (&referenceCounter)));
}


ODB_FORCE_INLINE const GS::ClassInfo*	ODB::ObjectInfo::GetClassInfo (void) const
{
	return classInfo;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasClassInfo (void) const
{
	return (classInfo != nullptr);
}


ODB_FORCE_INLINE void 	ODB::ObjectInfo::SetClassInfo (const GS::ClassInfo* newClassInfo)
{
	classInfo = newClassInfo;
}


ODB_FORCE_INLINE const GS::Guid&	ODB::ObjectInfo::GetClassId (void) const
{
	if (classInfo == nullptr)
		return GS::NULLGuid;
	else
		return classInfo->GetId ();
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasClassId (void) const
{
	return (classInfo != nullptr && classInfo->HasId ());
}


ODB_FORCE_INLINE ODB::IdSpace*	ODB::ObjectInfo::GetIdSpace (void) const
{
	if ((flags & ExistenceFlags) != 0)
		return idSpace;
	else
		return nullptr;
}


ODB_FORCE_INLINE ODB::IdSpace*	ODB::ObjectInfo::GetOriginalIdSpace (void) const
{
	return idSpace;
}


inline void		ODB::ObjectInfo::SetIdSpace (IdSpace* newIdSpace)
{
	DBASSERT (this != &NullObjectInfo);

	idSpace = newIdSpace;
}


ODB_FORCE_INLINE ODB::Database*		ODB::ObjectInfo::GetDatabase (void) const
{
	return database;
}


inline void		ODB::ObjectInfo::SetDatabase (Database* newDatabase)
{
	DBASSERT (this != &NullObjectInfo);
	DBASSERT (newDatabase != nullptr);

	database = newDatabase;
}


inline const ODB::Id&	ODB::ObjectInfo::GetId (void) const
{
	if ((flags & ExistenceFlags) != 0)
		return id;
	else
		return NullId;
}


inline const ODB::Id&	ODB::ObjectInfo::GetOriginalId (void) const
{
	return id;
}


inline bool		ODB::ObjectInfo::HasId (const Id& id) const
{
	return (((flags & ExistenceFlags) != 0 && this->id == id) || ((flags & ExistenceFlags) == 0 && id.IsNull ()));
}


inline bool		ODB::ObjectInfo::HasId (void) const
{
	return ((flags & ExistenceFlags) != 0 && !id.IsNull ());
}


inline bool		ODB::ObjectInfo::HasOriginalId (void) const
{
	return !id.IsNull ();
}


ODB_FORCE_INLINE UInt64		ODB::ObjectInfo::GetCreationStamp (void) const
{
	if ((flags & WasInternalFlag) == 0 && (flags & ExistenceFlags) != 0)
		const_cast<ObjectInfo*> (this)->LoadObject ();

	return creationStamp;
}


ODB_FORCE_INLINE UInt64		ODB::ObjectInfo::GetCurrentCreationStamp (void) const
{
	return creationStamp;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetCreationStamp (UInt64 newCreationStamp)
{
	creationStamp = newCreationStamp;
}


ODB_FORCE_INLINE UInt64		ODB::ObjectInfo::GetModificationStamp (void) const
{
	if ((flags & WasInternalFlag) == 0 && (flags & ExistenceFlags) != 0)
		const_cast<ObjectInfo*> (this)->LoadObject ();

	return modificationStamp;
}


ODB_FORCE_INLINE UInt64		ODB::ObjectInfo::GetCurrentModificationStamp (void) const
{

	return modificationStamp;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetModificationStamp (UInt64 newModificationStamp)
{
	modificationStamp = newModificationStamp;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsModifiedInSessionAfter (UInt64 startModificationStamp) const
{
	return (modificationStamp > startModificationStamp);	// modification stamp is 0 before the first loading of FileDatabase objects so an object with stamp 0 is surely not be modified in this session => this method doesn't load so it should be used instead of GetModificationStamp in "GetModificationStamp > stamp" like expressions
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetDefaultSpecifiableFlags (UInt64 defaultSpecifiableFlags)
{
	flags |= defaultSpecifiableFlags;
}


ODB_FORCE_INLINE UChar	ODB::ObjectInfo::GetPersistentFlags (void) const
{
	UChar persistentFlags = 0;

	if (HasContentBasedIdentity ())
		persistentFlags |= P_ContentBasedIdentity;

	if (HasContextBasedIdentity ())
		persistentFlags |= P_ContextBasedIdentity;

	return persistentFlags;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetPersistentFlags (UChar newPersistentFlags)
{
	if ((newPersistentFlags & P_ContentBasedIdentity) != 0)
		SetContentBasedIdentity ();
	else
		ClearContentBasedIdentity ();

	if ((newPersistentFlags & P_ContextBasedIdentity) != 0)
		SetContextBasedIdentity ();
	else
		ClearContextBasedIdentity ();
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasContentBasedIdentity (UChar persistentFlags)
{
	return ((persistentFlags & P_ContentBasedIdentity) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasContextBasedIdentity (UChar persistentFlags)
{
	return ((persistentFlags & P_ContextBasedIdentity) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasIndependentIdentity (UChar persistentFlags)
{
	return ((persistentFlags & P_GeneratedIdentityFlags) == 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasDependentIdentity (UChar persistentFlags)
{
	return ((persistentFlags & P_GeneratedIdentityFlags) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearContentBasedIdentity (UChar& persistentFlags)
{
	persistentFlags &= ~P_ContentBasedIdentity;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearContextBasedIdentity (UChar& persistentFlags)
{
	persistentFlags &= ~P_ContextBasedIdentity;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasOwnerObject (void) const
{
	if ((flags & HadInternalLinksFlag) == 0 && (flags & ExistenceFlags) != 0)
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return ((flags & HasOwnerObjectFlag) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetObjectOwnership (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags |= HasOwnerObjectFlag;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearObjectOwnership (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~HasOwnerObjectFlag;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasOwnerLink (void) const
{
	if ((flags & HadInternalLinksFlag) == 0 && (flags & ExistenceFlags) != 0)
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return ((flags & HasOwnerLinkFlag) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetLinkOwnership (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags |= HasOwnerLinkFlag;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearLinkOwnership (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~HasOwnerLinkFlag;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasOwner (void) const
{
	return ((flags & HasOwnerFlags) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsSharedByAssociation (void) const
{
	if ((flags & HadInternalLinksFlag) == 0 && (flags & ExistenceFlags) != 0)
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return ((flags & SharedByAssociation) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkAsSharedByAssociation (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags |= SharedByAssociation;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearSharingByAssociation (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~SharedByAssociation;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsSharedByReference (void) const
{
	if ((flags & HadInternalLinksFlag) == 0 && (flags & ExistenceFlags) != 0)
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return ((flags & SharedByReference) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkAsSharedByReference (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags |= SharedByReference;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearSharingByReference (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~SharedByReference;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasContentBasedIdentity (void) const
{
	return ((flags & ContentBasedIdentity) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetContentBasedIdentity (void)
{
	DBASSERT (this != &NullObjectInfo);
	DBASSERT ((flags & ContextBasedIdentity) == 0);

	flags &= ~ContextBasedIdentity;
	flags |= ContentBasedIdentity;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearContentBasedIdentity (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~ContentBasedIdentity;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasContextBasedIdentity (void) const
{
	if ((flags & HadInternalLinksFlag) == 0 && (flags & ExistenceFlags) != 0)
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return ((flags & ContextBasedIdentity) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetContextBasedIdentity (void)
{
	DBASSERT (this != &NullObjectInfo);
	DBASSERT ((flags & ContentBasedIdentity) == 0);

	flags &= ~ContentBasedIdentity;
	flags |= ContextBasedIdentity;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearContextBasedIdentity (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~ContextBasedIdentity;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasIndependentIdentity (void) const
{
	if ((flags & HadInternalLinksFlag) == 0 && (flags & ExistenceFlags) != 0)
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return ((flags & GeneratedIdentityFlags) == 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasDependentIdentity (void) const
{
	if ((flags & HadInternalLinksFlag) == 0 && (flags & ExistenceFlags) != 0)
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return ((flags & GeneratedIdentityFlags) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsDerived (void) const
{
	if ((flags & HadInternalLinksFlag) == 0 && (flags & ExistenceFlags) != 0)
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return ((flags & Derived) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkObjectAsModified (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags |= (ObjectModifiedOnTraceLine1 | ObjectModifiedOnTraceLine2 | ObjectModifiedOnTraceLine3);
	clockFlag = ClockFlagIsSet;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkObjectAsModifiedOnTraceLine (UInt64 objectTraceLine)
{
	DBASSERT (this != &NullObjectInfo);

	flags |= objectTraceLine;
	clockFlag = ClockFlagIsSet;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsObjectModifiedOnTraceLine (UInt64 objectTraceLine) const
{
	return ((flags & objectTraceLine) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::RestartObjectModificationTraceLine (UInt64 objectTraceLine)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~objectTraceLine;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkWithLinkModification (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags |= LinkModifiedOnTraceLine1;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasLinkModificationOnTraceLine (UInt64 linkTraceLine) const
{
	return ((flags & linkTraceLine) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::RestartLinkModificationTraceLine (UInt64 linkTraceLine)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~linkTraceLine;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsClockFlagSet (void) const
{
	return clockFlag == ClockFlagIsSet;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetClockFlag (void)
{
	DBASSERT (this != &NullObjectInfo);

	clockFlag = ClockFlagIsSet;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearClockFlag (void)
{
	DBASSERT (this != &NullObjectInfo);

	clockFlag = ClockFlagIsCleared;	
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkAsAccessed (void)
{
	DBASSERT (this != &NullObjectInfo);

	clockFlag = ClockFlagIsSet;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsPinned (void) const
{
	return ((flags & Pinned) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::Pin (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags |= Pinned;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::Unpin (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~Pinned;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsConst (void) const
{
	return ((flags & Const) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetAsConst (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags |= Const;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearConstness (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~Const;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsLogicalConst (void) const
{
	return ((flags & LogicalConst) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetAsLogicalConst (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags |= LogicalConst;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearLogicalConstness (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~LogicalConst;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsDeletingEnabled (void) const
{
	return ((flags & Undeletable) == 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::EnableDeleting (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~Undeletable;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::DisableDeleting (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags |= Undeletable;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsAuthorizedToModify (void) const
{
	return ((flags & UnauthorizedToModify) == 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::AcquireModificationAuthorization (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~UnauthorizedToModify;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ReleaseModificationAuthorization (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags |= UnauthorizedToModify;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsAuthorizedToLogicallyModify (void) const
{
	return ((flags & UnauthorizedToLogicallyModify) == 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::AcquireLogicalModificationAuthorization (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~UnauthorizedToLogicallyModify;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ReleaseLogicalModificationAuthorization (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags |= UnauthorizedToLogicallyModify;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsModifiable (void) const
{
	return ((flags & ModificationFlags) == 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsLogicalConstModifiable (void) const
{
	return ((flags & PhysicalModificationFlags) == 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsDeletable (void) const
{
	return ((flags & DeletionFlags) == 0);
}


bool	ODB::ObjectInfo::BecomesExternalOnDelete (void) const
{
	return ((flags & ExternalOnDelete) != 0);
}


void	ODB::ObjectInfo::SetExternalOnDeleteMode (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags |= ExternalOnDelete;
}


void	ODB::ObjectInfo::ClearExternalOnDeleteMode (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~ExternalOnDelete;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsEventReceptionEnabled (void) const
{
	return ((flags & EventReceptionIsDisabled) == 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::EnableEventReception (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~EventReceptionIsDisabled;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::DisableEventReception (void)
{
	DBASSERT (this != &NullObjectInfo);

	flags |= EventReceptionIsDisabled;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasQueryRequestRelatedFlags (void) const
{
	return ((flags & QueryRequestRelatedFlags) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasObjectModificationRequestRelatedFlags (void) const
{
	return ((flags & ObjectModificationRequestRelatedFlags) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasLogicalConstObjectModificationRequestRelatedFlags (void) const
{
	return ((flags & LogicalConstObjectModificationRequestRelatedFlags) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasOnlyObjectModificationNotificationForRingFlag (void) const
{
	return ((flags & LogicalConstObjectModificationRequestRelatedFlags) == ObjectModificationNotificationForRing);
}


ODB_FORCE_INLINE UInt64	ODB::ObjectInfo::GetTransactionRelatedFlags (void) const
{
	return (flags & TransactionRelatedFlags);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetTransactionRelatedFlags (UInt64 newFlags)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~TransactionRelatedFlags;
	flags |= (newFlags & TransactionRelatedFlags);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsInternal (void) const
{
	return ((flags & Internal) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsExternal (void) const
{
	return ((flags & External) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsNull (void) const
{
	return ((flags & ExistenceFlags) == 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::WasInternal (void) const
{
	return ((flags & WasInternalFlag) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsDeleting (void) const
{
	return (IsInternal () && memoryAddress == nullptr);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsDeleted (void) const
{
	return (IsNull () && this != &NullObjectInfo);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsLoadingObject (void) const
{
	return ((flags & LoadingObject) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsLoadingLinks (void) const
{
	return ((flags & LoadingLinks) != 0);
}


ODB_FORCE_INLINE ODB::Object*	ODB::ObjectInfo::GetMemoryAddress (void) const
{
	if ((flags & External) != 0)
		const_cast<ObjectInfo*> (this)->LoadObject ();

	return memoryAddress;
}


ODB_FORCE_INLINE ODB::Object*	ODB::ObjectInfo::GetCurrentMemoryAddress (void) const
{
	return memoryAddress;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasMemoryAddress (void) const
{
	if ((flags & External) != 0)
		const_cast<ObjectInfo*> (this)->LoadObject ();

	return (memoryAddress != nullptr);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsAvailable (void) const
{
	return ((flags & AvailabilityFlags) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetAsLoadingObject (void)
{
	DBASSERT ((flags & External) != 0);

	flags |= LoadingObject;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearLoadingObject (void)
{
	DBASSERT ((flags & LoadingObject) != 0);

	flags &= ~LoadingObject;

	SetLocationFlags ();
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetAsLoadingLinks (void)
{
	flags |= LoadingLinks;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearLoadingLinks (void)
{
	DBASSERT ((flags & LoadingLinks) != 0);

	flags &= ~LoadingLinks;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasExternalLinks (void) const
{
	return ((flags & ExternalLinks) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkWithExternalLinks (void)
{
	flags |= ExternalLinks;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearExternalLinksFlag (void)
{
	flags &= ~ExternalLinks;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HadInternalLinks (void) const
{
	return ((flags & HadInternalLinksFlag) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkAsHadInternalLinks (void)
{
	flags |= HadInternalLinksFlag;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearHadInternalLinksFlag (void)
{
	flags &= ~HadInternalLinksFlag;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::AreLinksAvailable (void) const
{
	return ((flags & ExistenceFlags) != 0 && (flags & LinksAreUnavailable) == 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkAsLinksAreAvailable (void)
{
	flags &= ~LinksAreUnavailable;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkAsLinksAreUnavailable (void)
{
	flags |= LinksAreUnavailable;
}


ODB_FORCE_INLINE UInt32	ODB::ObjectInfo::GetReferenceCounter (void) const
{
	return referenceCounter;
}


ODB_FORCE_INLINE UShort		ODB::ObjectInfo::GetAccessLevel (void) const
{
	return accessLevel;
}


inline void		ODB::ObjectInfo::SetAccessLevel (UShort newAccessLevel)
{
	DBASSERT (this != &NullObjectInfo);

	accessLevel = newAccessLevel;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsAssociationIndexNotificationStarted (void) const
{
	return ((flags & AssociationIndexNotification) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::StartAssociationIndexNotification (void)
{
	flags |= AssociationIndexNotification;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::StopAssociationIndexNotification (void)
{
	flags &= ~AssociationIndexNotification;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsDependencyNotificationStarted (void) const
{
	return ((flags & DependencyNotification) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::StartDependencyNotification (void)
{
	flags |= DependencyNotification;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::StopDependencyNotification (void)
{
	flags &= ~DependencyNotification;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasLazyDataToBeInitialized (void) const
{
	return ((flags & LazyDataNotification) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetLazyDataInitialization (void)
{
	flags |= LazyDataNotification;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearLazyDataInitialization (void)
{
	flags &= ~LazyDataNotification;
}


ODB_FORCE_INLINE bool   ODB::ObjectInfo::IsObjectModificationNotificationForRingStarted (void) const
{
	return ((flags & ObjectModificationNotificationForRing) != 0);
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::StartObjectModificationNotificationForRing (void)
{
	flags |= ObjectModificationNotificationForRing;
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::StopObjectModificationNotificationForRing (void)
{
	flags &= ~ObjectModificationNotificationForRing;
}


ODB_FORCE_INLINE bool   ODB::ObjectInfo::IsObjectModificationNotificationForTimelineStarted (void) const
{
	return ((flags & ObjectModificationNotificationForTimeline) != 0);
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::StartObjectModificationNotificationForTimeline (void)
{
	flags |= ObjectModificationNotificationForTimeline;
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::StopObjectModificationNotificationForTimeline (void)
{
	flags &= ~ObjectModificationNotificationForTimeline;
}


ODB_FORCE_INLINE bool   ODB::ObjectInfo::IsLinkModificationNotificationForTimelineStarted (void) const
{
	return ((flags & LinkModificationNotificationForTimeline) != 0);
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::StartLinkModificationNotificationForTimeline (void)
{
	flags |= LinkModificationNotificationForTimeline;
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::StopLinkModificationNotificationForTimeline (void)
{
	flags &= ~LinkModificationNotificationForTimeline;
}


ODB_FORCE_INLINE bool   ODB::ObjectInfo::IsNotificationOnDeleteSet (void) const
{
	return ((flags & ObjectDeletionNotification) != 0);
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::SetNotificationOnDelete (void)
{
	flags |= ObjectDeletionNotification;
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::ClearNotificationOnDelete (void)
{
	flags &= ~ObjectDeletionNotification;
}


ODB_FORCE_INLINE bool   ODB::ObjectInfo::IsModifiableWithoutModificationScope (void) const
{
	return ((flags & ModifiableWithoutModificationScope) != 0);
}


ODB_FORCE_INLINE bool   ODB::ObjectInfo::IsLogicalConstModifiableWithoutModificationScope (void) const
{
	return ((flags & (ModifiableWithoutModificationScope | LogicalConstModifiableWithoutModificationScope)) != 0);		// if the object is modifiable then it is also logical const modifiable
}


ODB_FORCE_INLINE UInt32		ODB::ObjectInfo::GetDataLayer (void) const
{
	return ((flags & DataLayerBits) >> DataLayerPosition);
}


ODB_FORCE_INLINE bool   ODB::ObjectInfo::GetCheckFlag1 (void) const
{
	return ((flags & CheckFlag1) != 0);
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::SetCheckFlag1 (void)
{
	flags |= CheckFlag1;
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::ClearCheckFlag1 (void)
{
	flags &= ~CheckFlag1;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::AreObjectDeletionCheckFlagsCleared (void) const
{
	return ((flags & ObjectDeletionCheckFlags) == 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsAutoDeletable (void) const
{
	return ((flags & AutoDeletableFlags) == AutoDeletableFlags);
}


ODB_FORCE_INLINE ODB::ObjectDataStore*	ODB::ObjectInfo::GetDataStore (void) const
{
	return objectDataStore;
}


ODB_FORCE_INLINE const ODB::ObjectDataStore*	ODB::ObjectInfo::GetLinks (void) const
{
	if ((flags & ExternalLinks) != 0)
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return objectDataStore;
}


ODB_FORCE_INLINE const ODB::ObjectDataStore*	ODB::ObjectInfo::GetCurrentLinks (void) const
{
	return objectDataStore;
}


ODB_FORCE_INLINE ODB::ObjectDataStore*	ODB::ObjectInfo::ModifyLinks (void)
{
	if ((flags & ExternalLinks) != 0)
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return objectDataStore;
}


ODB_FORCE_INLINE ODB::ObjectDataStore*	ODB::ObjectInfo::ModifyCurrentLinks (void)
{
	return objectDataStore;
}


ODB_FORCE_INLINE const ODB::ObjectDataStore*	ODB::ObjectInfo::GetIndices (void) const
{
	if ((flags & ExternalLinks) != 0)
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return objectDataStore;
}


ODB_FORCE_INLINE const ODB::ObjectDataStore*	ODB::ObjectInfo::GetCurrentIndices (void) const
{
	return objectDataStore;
}


ODB_FORCE_INLINE ODB::ObjectDataStore*	ODB::ObjectInfo::ModifyIndices (void)
{
	if ((flags & ExternalLinks) != 0)
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return objectDataStore;
}


ODB_FORCE_INLINE ODB::ObjectDataStore*	ODB::ObjectInfo::ModifyCurrentIndices (void)
{
	return objectDataStore;
}
// _____________________________ Class ObjectInfo ______________________________


#endif
